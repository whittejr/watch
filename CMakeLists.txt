cmake_minimum_required(VERSION 3.22)
project(${TARGET_MCU} C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXECUTABLE "firmware")

set(THIRD_PARTY_QP "${CMAKE_CURRENT_SOURCE_DIR}/lib/third_party")
set(AO_APP_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/tools/watch/src")
set(THIRD_PARTY_LVGL "${CMAKE_CURRENT_SOURCE_DIR}/lib/third_party/lvgl")

if(NOT DEFINED MCU_FAMILY)
    message(FATAL_ERROR "MCU_FAMILY não definida!")
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/mcu/${MCU_FAMILY}.cmake")

if("${LINKER_SCRIPT}" STREQUAL "")
    message(FATAL_ERROR "ERRO: A variável LINKER_SCRIPT está vazia! Verifique o seu arquivo ${MCU_FAMILY}.cmake.")
endif()

if("${HAL_SOURCES}" STREQUAL "")
    message(FATAL_ERROR "ERRO: A variável HAL_SOURCES está vazia! A HAL não será compilada.")
endif()

file(GLOB_RECURSE LVGL_SOURCES
    "${THIRD_PARTY_LVGL}/src/*.c"
)
list(FILTER LVGL_SOURCES EXCLUDE REGEX "src/drivers")
list(FILTER LVGL_SOURCES EXCLUDE REGEX "src/debugging/test")
list(FILTER LVGL_SOURCES EXCLUDE REGEX "src/libs")
list(FILTER LVGL_SOURCES EXCLUDE REGEX "src/draw/(espressif|eve|nanovg|nema_gfx|nxp|opengles|renesas|sdl|sifli|vg_lite)")
list(FILTER LVGL_SOURCES EXCLUDE REGEX "src/osal/lv_(windows|pthread|rtthread|mqx|sdl2)")
list(FILTER LVGL_SOURCES EXCLUDE REGEX "src/stdlib/(micropython|rtthread|uefi)")
list(FILTER LVGL_SOURCES EXCLUDE REGEX "src/fs/lv_fs_(win32|uefi|posix|stdio)")
list(FILTER LVGL_SOURCES EXCLUDE REGEX "src/font/lv_font_(dejavu|source_han|unscii|montserrat_(8|10|12|14_aligned|16|18|20|22|24|26|28|30|32|34|36|38|40|42|44|46|48))")

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "core/src/*.c"
    "app/*.c"
    "lib/BSP/src/*.c"
    "lib/components/*.c"

    "${THIRD_PARTY_QP}/qpc/src/qf/*.c"
    "${THIRD_PARTY_QP}/qpc/src/qv/*.c"
    "${THIRD_PARTY_QP}/qpc/ports/arm-cm/qv/gnu/*.c"
    "${AO_APP_SOURCE}/*.c"
)

set(APP_INCLUDES
    "core/inc"
    "app"
    "app/ui"
    "lib/BSP/inc"
    "lib/components"
    "lib/components/adxl362"
    "lib/components/ls013b7dh03"
    "lib/components/max30102"
    "lib/components/ssd1306"
    "${THIRD_PARTY_QP}/qpc/include"
    "${THIRD_PARTY_QP}/qpc/ports/arm-cm/qv/gnu"
    "${AO_APP_SOURCE}"
    "${THIRD_PARTY_LVGL}"
    "${THIRD_PARTY_LVGL}/src"
)

add_library(lvgl STATIC ${LVGL_SOURCES})
target_include_directories(lvgl PUBLIC 
    ${THIRD_PARTY_LVGL}
    ${THIRD_PARTY_LVGL}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/core/inc
)
target_compile_definitions(lvgl PUBLIC LV_CONF_INCLUDE_SIMPLE)
target_compile_options(lvgl PRIVATE 
    -Wno-unused-parameter
)

add_executable(${EXECUTABLE} ${APP_SOURCES} ${HAL_SOURCES})

target_include_directories(${EXECUTABLE} PRIVATE 
    ${APP_INCLUDES}
    ${HAL_INCLUDES}
)

target_compile_options(${EXECUTABLE} PRIVATE 
    -Wall 
    -Wpedantic 
    -Wno-unused-parameter
)

target_link_options(${EXECUTABLE} PRIVATE
    -T${LINKER_SCRIPT}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    --specs=nano.specs
    -Wl,--print-memory-usage
    -Wl,--gc-sections
)

target_link_libraries(${EXECUTABLE} PRIVATE lvgl -lc -lm)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
)
set_target_properties(${EXECUTABLE} PROPERTIES SUFFIX ".elf")
#include "ui.h"
#include "include/lvgl/api_map/lv_api_map_v9_2.h"
#include "screens.h"

#include <string.h>

static int16_t currentScreen = -1;

static lv_obj_t *getLvglObjectFromIndex(int32_t index) {
    if (index == -1) {
        return 0;
    }
    return ((lv_obj_t **)&objects)[index];
}

void loadScreen(enum ScreensEnum screenId) {
    currentScreen = screenId - 1;
    lv_obj_t *screen = getLvglObjectFromIndex(currentScreen);
    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_FADE_IN, 0, 0, false);
}

void ui_init() {
    create_screens();
    lv_display_t *disp = lv_display_get_default();                                                                                                      
    lv_theme_t *theme = lv_theme_mono_init(disp, true, LV_FONT_DEFAULT);                                                                                
    lv_display_set_theme(disp, theme);
    loadScreen(SCREEN_ID_WATCHFACE);

}

void ui_tick() {
    tick_screen(currentScreen);
}
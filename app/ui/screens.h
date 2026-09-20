#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_WATCHFACE = 1,
    SCREEN_ID_ALARM = 2,
    SCREEN_ID_COUNTDOWN = 3,
    _SCREEN_ID_LAST = 3
};

typedef struct _objects_t {
    lv_obj_t *watchface;
    lv_obj_t *alarm;
    lv_obj_t *countdown;
    lv_obj_t *timekeeping_label;
    lv_obj_t *alarm_label;
    lv_obj_t *countdown_label;
} objects_t;

extern objects_t objects;

void create_screen_watchface();
void tick_screen_watchface();

void create_screen_alarm();
void tick_screen_alarm();

void create_screen_countdown();
void tick_screen_countdown();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
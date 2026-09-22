/**
 * @file ui.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-09-22
 */

#ifndef UI_H
#define UI_H

#include "lvgl.h"

void ui_init(void);
lv_obj_t *create_box(lv_obj_t *parent, int32_t width, int32_t height);
lv_obj_t *create_label(lv_obj_t *parent, const lv_font_t* font);

#endif // UI_H

/**
* @file    ui.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-22
*/

#include "ui.h"

void ui_init(void) {
    lv_display_t *disp = lv_display_get_default();
    if(disp) {
        lv_theme_t *theme = lv_theme_mono_init(disp,true, LV_FONT_DEFAULT);
        lv_display_set_theme(disp, theme);
    }
}


lv_obj_t *create_box(lv_obj_t *parent, int32_t width, int32_t height) {
	lv_obj_t *obj = lv_obj_create(parent);
	lv_obj_set_size(obj, width, height);

    lv_obj_set_style_border_width(obj, 0, 0);
    lv_obj_set_style_radius(obj, 0, 0);
    lv_obj_set_style_pad_all(obj, 0, 0);
    lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, 0);

	return obj;
}

lv_obj_t *create_label(lv_obj_t *parent, const lv_font_t* font) {
	lv_obj_t *label = lv_label_create(parent);
	lv_obj_set_style_text_font(label, font, 0);

	return label;
}


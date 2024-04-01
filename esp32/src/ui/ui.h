// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_events.h"
// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_lblTitle;
extern lv_obj_t * ui_arcBattery;
extern lv_obj_t * ui_lblBattery;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_imgForward;
extern lv_obj_t * ui_lblGo;
extern lv_obj_t * ui_imgReverse;
extern lv_obj_t * ui_imgFaster;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Label4;
// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
extern lv_obj_t * ui_Screen2;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_lblError;
extern lv_obj_t * ui____initial_actions0;

LV_IMG_DECLARE(ui_img_forward_png);    // assets\forward.png
LV_IMG_DECLARE(ui_img_reverse_png);    // assets\reverse.png
LV_IMG_DECLARE(ui_img_faster_png);    // assets\faster.png

LV_FONT_DECLARE(ui_font_large);
LV_FONT_DECLARE(ui_font_px76);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

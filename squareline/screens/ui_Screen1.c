// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    // ui_Spinner1 = lv_spinner_create(ui_Screen1, 1000, 90);
    // lv_obj_set_width(ui_Spinner1, 20);
    // lv_obj_set_height(ui_Spinner1, 20);
    // lv_obj_set_x(ui_Spinner1, -69);
    // lv_obj_set_y(ui_Spinner1, -82);
    // lv_obj_set_align(ui_Spinner1, LV_ALIGN_CENTER);
    // lv_obj_clear_flag(ui_Spinner1, LV_OBJ_FLAG_CLICKABLE);      /// Flags

    // ui_Spinner2 = lv_spinner_create(ui_Screen1, 1000, 90);
    // lv_obj_set_width(ui_Spinner2, 80);
    // lv_obj_set_height(ui_Spinner2, 80);
    // lv_obj_set_x(ui_Spinner2, 59);
    // lv_obj_set_y(ui_Spinner2, -73);
    // lv_obj_set_align(ui_Spinner2, LV_ALIGN_CENTER);
    // lv_obj_clear_flag(ui_Spinner2, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    // lv_obj_set_style_bg_img_recolor(ui_Spinner2, lv_color_hex(0x40FF68), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_img_recolor_opa(ui_Spinner2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_arc_color(ui_Spinner2, lv_color_hex(0x42FF40), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_arc_opa(ui_Spinner2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Chart2 = lv_chart_create(ui_Screen1);
    // lv_obj_set_width(ui_Chart2, 160);
    // lv_obj_set_height(ui_Chart2, 100);
    // lv_obj_set_x(ui_Chart2, 3);
    // lv_obj_set_y(ui_Chart2, 28);
    // lv_obj_set_align(ui_Chart2, LV_ALIGN_CENTER);
    // lv_chart_set_type(ui_Chart2, LV_CHART_TYPE_LINE);
    // lv_chart_set_axis_tick(ui_Chart2, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 2, true, 50);
    // lv_chart_set_axis_tick(ui_Chart2, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
    // lv_chart_set_axis_tick(ui_Chart2, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);
    // lv_chart_series_t * ui_Chart2_series_1 = lv_chart_add_series(ui_Chart2, lv_color_hex(0x808080),
    //                                                              LV_CHART_AXIS_PRIMARY_Y);
    // static lv_coord_t ui_Chart2_series_1_array[] = { 0, 10, 20, 40, 80, 80, 40, 20, 10, 0 };
    // lv_chart_set_ext_y_array(ui_Chart2, ui_Chart2_series_1, ui_Chart2_series_1_array);



    // ui_TextArea1 = lv_textarea_create(ui_Screen1);
    // lv_obj_set_width(ui_TextArea1, 50);
    // lv_obj_set_height(ui_TextArea1, 30);
    // lv_obj_set_x(ui_TextArea1, -19);
    // lv_obj_set_y(ui_TextArea1, -56);
    // lv_obj_set_align(ui_TextArea1, LV_ALIGN_CENTER);
    // lv_textarea_set_text(ui_TextArea1, "ww");
    // lv_textarea_set_placeholder_text(ui_TextArea1, "Placeholder...");



}


// #include <stdio.h>
// static lv_obj_t *label_time;
// static lv_obj_t *label_fps;


// static void update_time_task(lv_task_t *task) {
//     // Your update time task code here
// }

// // 更新FPS任务回调函数
// static void update_fps_task(lv_task_t *task) {
//     // Your update FPS task code here
// }

// void ui_Screen1_screen_init(void) {
//     // 创建屏幕
//     ui_Screen1 = lv_obj_create(NULL);
//     lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);

//     // 创建实时时间标签
//     label_time = lv_label_create(ui_Screen1);
//     lv_label_set_text(label_time, "00:00:00");
//     lv_obj_align(label_time, LV_ALIGN_TOP_LEFT, 10, 10);

//     // 创建FPS标签
//     label_fps = lv_label_create(ui_Screen1);
//     lv_label_set_text(label_fps, "FPS: 0");
//     lv_obj_align(label_fps, LV_ALIGN_BOTTOM_LEFT, 10, -10);

//     // 注册一个回调函数，每秒更新一次时间
//     lv_task_create(update_time_task, 1000, LV_TASK_PRIO_LOW, NULL);
// }

// // 更新时间任务回调函数
// static void update_time_task(lv_task_t *task) {
//     // 获取系统时间
//     time_t rawtime;
//     struct tm *timeinfo;
//     time(&rawtime);
//     timeinfo = localtime(&rawtime);

//     // 格式化时间字符串
//     char buffer[9];
//     strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);

//     // 更新时间标签的文本
//     lv_label_set_text(label_time, buffer);
// }

// 更新FPS任务回调函数
// static void update_fps_task(lv_task_t *task) {
//     // 获取当前屏幕的帧率
//     uint32_t fps = lv_disp_get_fps(lv_disp_get_default());

//     // 将帧率转换为字符串
//     char fps_buffer[10];
//     snprintf(fps_buffer, sizeof(fps_buffer), "FPS: %d", fps);

//     // 更新FPS标签的文本
//     lv_label_set_text(label_fps, fps_buffer);
// }

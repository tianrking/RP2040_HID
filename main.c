#include "main.h"
#include "lvgl.h"
#include "math.h"
// LVGL的显示和刷新回调函数
static void lvgl_display_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);

#define OLED_HEIGHT_240 240
#define OLED_WIDTH_240 240

static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;
static lv_indev_t indev;
static lv_obj_t *scr;
int main()
{
    stdio_init_all();
    init_spi();
    //ssd1306_init();
    GC9A01_init();

    // while (1==1)
    // {
    //     /* code */
    // }
    
    lv_init();

    // 创建显示缓冲区
    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf[OLED_WIDTH_240 * 10]; // 缓冲区大小可以根据需要调整
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, OLED_WIDTH_240 * 10);

    // 创建显示驱动
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = OLED_WIDTH_240;
    disp_drv.ver_res = OLED_HEIGHT_240;
    disp_drv.flush_cb = lvgl_display_flush_cb;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // 创建一个简单的标签
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "w0x7ce");
    lv_obj_center(label);

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
    const uint32_t update_period_ms = 500; // 更新周期，单位为毫秒
    uint32_t counter = 0; // 计数器

    sleep_ms(4000); // 假设等待2秒
    //lv_obj_del(label);
     // 创建圆形
    lv_obj_t * circle = lv_obj_create(lv_scr_act());
    lv_obj_set_size(circle, 20, 20);
    lv_obj_set_style_bg_color(circle, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_radius(circle, LV_RADIUS_CIRCLE, 0);

    const int radius = 20; // 移动半径
    const int center_x = OLED_WIDTH_240 / 2 - 15;
    const int center_y = OLED_HEIGHT_240 / 2 - 7;
    double angle = 0.0;

    ui_init();
    ui_Screen1_screen_init();
    while (true) {
        // // 更新LVGL
        // lv_tick_inc(20); // 更新时间，5ms为例
        // lv_timer_handler();
        // //ssd1306_refresh_gram(); // 刷新OLED显示

        // // 每500ms切换文本
        // if (++counter >= update_period_ms / 5) {
        //     counter = 0; // 重置计数器

        //     // 更改标签的文本
        //     if (strcmp(lv_label_get_text(label), "TEXT1") == 0) {
        //         lv_label_set_text(label, "TEXT2");
        //     } else {
        //         lv_label_set_text(label, "TEXT1");
        //     }
        // }

        // sleep_ms(5);
                // 更新LVGL
          // 更新LVGL
        lv_tick_inc(5);
        lv_timer_handler();

        // 计算圆形新位置
        int x = center_x + radius * cos(angle);
        int y = center_y + radius * sin(angle);
        lv_obj_set_pos(circle, x, y);

        angle += 0.05; // 改变角度以移动圆形
        if (angle >= 2 * M_PI) {
            angle -= 2 * M_PI; // 保持角度在0到2π之间
        }

        ssd1306_refresh_gram(); // 刷新OLED显示
        sleep_ms(5);
    }

    return 0;

}

// 实现LVGL的显示刷新回调
// static void lvgl_display_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
// {
//     for (int y = area->y1; y <= area->y2; y++)
//     {
//         for (int x = area->x1; x <= area->x2; x++)
//         {
//             // 将LVGL的颜色数据写入到OLED缓冲区
//             ssd1306_draw_point(x, y, color_p->full);
//             color_p++;
//         }
//     }
//     lv_disp_flush_ready(disp_drv); // 告诉LVGL数据已经刷新完毕
// }

// static void lvgl_display_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
//     for (int y = area->y1; y <= area->y2; y++) {
//         for (int x = area->x1; x <= area->x2; x++) {
//             ssd1306_draw_point(x, y, color_p->full);
//             color_p++;
//         }
//     }

//     ssd1306_refresh_gram(); // 刷新OLED显示
//     lv_disp_flush_ready(disp_drv); // 告诉LVGL数据已经刷新完毕
// }


static void lvgl_display_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    // 计算区域大小
    int32_t size = lv_area_get_width(area) * lv_area_get_height(area);

    // 首先，设置地址窗口
    GC9A01_set_address_window(area->x1, area->y1, area->x2, area->y2);

    // 发送像素数据
    GC9A01_write_continue((uint8_t *)color_p, size * 2); // 假设LVGL颜色深度为16位

    lv_disp_flush_ready(disp_drv); // 告诉LVGL数据已经刷新完毕
}

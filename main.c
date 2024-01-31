#include "main.h"
#include "lvgl.h"
#include "math.h"
#include "time.h"
#include "stdlib.h"
// LVGL的显示和刷新回调函数
static void lvgl_display_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
static void timer_switch_screen(lv_timer_t *timer) ;
// static void chart_update_cb(lv_timer_t *timer) ;

// extern lv_obj_t * ui_Chart1;
// extern lv_chart_series_t * ui_Chart2_series_1 ;
#define OLED_HEIGHT_240 240
#define OLED_WIDTH_240 240

static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;
static lv_indev_t indev;
static lv_obj_t *scr;

void lv_example_label_1(void) {
    lv_obj_t * label1 = lv_label_create(lv_scr_act());
    lv_label_set_text(label1, "Hello, world!");
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);
}
int main()
{
    stdio_init_all();
    //init_spi();
    //ssd1306_init();
    //GC9A01_init();

     // 初始化屏幕
    ST7735_init_spi();  // 初始化SPI
    ST7735_Init(0); // 初始化屏幕
    ST7735_Clear(0x001F); // 清屏为blue色
    ST7735_Clear(0x07E0); // 清屏为green

    lv_init();

    // 创建显示缓冲区
    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf[OLED_WIDTH_240 * 100]; // 缓冲区大小可以根据需要调整
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, OLED_WIDTH_240 * 10);

    // 创建显示驱动
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = OLED_WIDTH_240;
    disp_drv.ver_res = OLED_HEIGHT_240;
    disp_drv.flush_cb = lvgl_display_flush_cb;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    ui_init();
    ui_Screen1_screen_init();
    ui_Screen5_screen_init();

    // 创建定时器
    lv_timer_create(timer_switch_screen, 5000, NULL); // 每5秒切换一次视窗

    while (true) {
    
        lv_tick_inc(5);
        lv_timer_handler();

        sleep_ms(5);
    }

    return 0;

}



static void lvgl_display_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    // 设置ST7735屏幕的显示窗口
    ST7735_SetWindows(area->x1, area->y1, area->x2, area->y2);

    // 遍历指定区域并写入颜色数据
    for (int y = area->y1; y <= area->y2; y++) {
        for (int x = area->x1; x <= area->x2; x++) {
            // 发送颜色数据到ST7735屏幕
            uint16_t color = color_p->full; // 假设颜色数据是16位
            ST7735_write_data(color >> 8);   // 高8位
            ST7735_write_data(color & 0xFF); // 低8位
            color_p++;
        }
    }

    // 通知LVGL刷新操作已完成
    lv_disp_flush_ready(disp_drv);
}

static void timer_switch_screen(lv_timer_t *timer) {
    static bool toggle = true;
    if (toggle) {
        lv_scr_load(ui_Screen1);
    } else {
        lv_scr_load(ui_Screen5);
    }
    toggle = !toggle;
}


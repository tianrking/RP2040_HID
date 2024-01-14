#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// #include "bsp/board.h"
#include "hardware/gpio.h"
#include "main.h"

uint16_t ColorTab[5]={RED,GREEN,BLUE,YELLOW,RED};
uint16_t POINT_COLOR=WHITE;

void lcd_hw_init(void) {
    // Initialize GPIO, SPI, etc. for LCD
    // ...

    // Reset LCD to a known state
    lcd_reset();
}

// // void my_disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p) { lv_fs_drv_t
// // Corrected function declaration
// // Corrected function declaration

// void my_disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p) {

//     // Set the area to be updated
//     uint16_t x1 = area->x1;
//     uint16_t y1 = area->y1;
//     uint16_t x2 = area->x2;
//     uint16_t y2 = area->y2;

//     // Write pixel data
//     for (int y = y1; y <= y2; y++) {
//         for (int x = x1; x <= x2; x++) {

//             // Access the full 16-bit color value
//             uint16_t color = color_p->full;

//             // **Bitwise Operations (Recommended)**
//             // Extract color components directly from `color_p->full`
//             uint8_t red = (color >> 11) & 0x1F;
//             uint8_t green = (color >> 5) & 0x3F;
//             uint8_t blue = color & 0x1F;

//             // Write the pixel (using the appropriate format for your LCD driver)
//             lcd_write_data_16bit(red << 11 | green << 5 | blue);  // Assuming your LCD driver expects 16-bit colors

//             color_p++;
//         }
//     }
// }



// static lv_disp_drv_t disp_drv; 

// void lvgl_init() {
//     // Initialize LVGL
//     lv_init();

//     // Initialize the display buffer for LVGL
//     static lv_disp_draw_buf_t draw_buf;  // Use the correct type for display buffer
//     static lv_color_t buf_1[LV_HOR_RES_MAX * 10];  // Example buffer size, adjust as needed
//     lv_disp_draw_buf_init(&draw_buf, buf_1, NULL, sizeof(buf_1) / sizeof(buf_1[0]));   // Initialize the buffer

//     // Initialize your LCD (SPI, GPIO, etc.)
//     my_spi_init();
//     lcd_gpio_init();
//     lcd_reset();
//     lcd_init();
//     lcd_clear(0xFFFF); // Clear with white color (or any other color)

//     // Setup the display driver
//     // static lv_disp_drv_t disp_drv;  // Use the correct type for display driver
//     lv_disp_drv_init(&disp_drv);    // Initialize the driver
//     disp_drv.flush_cb = my_disp_flush;  // Set your driver function
//     disp_drv.draw_buf = &draw_buf;   // Assign the buffer to the driver
//     disp_drv.hor_res = 320;         // Set horizontal resolution
//     disp_drv.ver_res = 240;         // Set vertical resolution

//     // Register the driver in LVGL
//     lv_disp_drv_register(&disp_drv);

//     // //test
//     // lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);

//     // /*Create a white label, set its text and align it to the center*/
//     // lv_obj_t * label = lv_label_create(lv_screen_active());
//     // lv_label_set_text(label, "Hello world");
//     // lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
//     // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
//     // //test
// }


// void create_simple_gui(void) {
//     // Create a simple label
//     lv_obj_t * label = lv_label_create(lv_scr_act());
//     lv_label_set_text(label, "Hello LVGL!");
//     lv_obj_center(label);
// }

///test main
// LVGL requires a buffer to work with
static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10]; /* Declare a buffer for 10 lines */

// LVGL display flushing
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
    
    lcd_set_windows(area->x1, area->y1, area->x2, area->y2);
    for (int y = area->y1; y <= area->y2; y++) {
        for (int x = area->x1; x <= area->x2; x++) {
            lcd_write_data_16bit(color_p->full);  // Write a pixel
            color_p++;
        }
    }

    lv_disp_flush_ready(disp_drv); /* Indicate you are ready with the flushing*/
}

void lv_example_anim_1(void) {
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    lv_style_set_bg_color(&style, lv_color_make(0xFF, 0, 0)); // Red Color

    /* Create an object with the new style */
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_add_style(obj, &style, 0);
    lv_obj_set_size(obj, 50, 50); // 50x50 pixels
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0); // Align to center

    /* Create an animation for the X position */
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, 0, lv_disp_get_hor_res(NULL) - 50); // From left to right
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_time(&a, 100); // 3 seconds to move across
    lv_anim_set_playback_time(&a, 100); // 3 seconds to move back
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); // Repeat the animation

    /* Start the animation */
    lv_anim_start(&a);
}

/* Function to add an angle to a point */
void rotate_point(float cx, float cy, float angle, lv_point_t *p) {
    float s = sin(angle);
    float c = cos(angle);

    // translate point back to origin:
    p->x -= cx;
    p->y -= cy;

    // rotate point
    float xnew = p->x * c - p->y * s;
    float ynew = p->x * s + p->y * c;

    // translate point back:
    p->x = xnew + cx;
    p->y = ynew + cy;
}

/* Draw a star with LVGL */
void draw_star(lv_obj_t * parent) {
    /* Create an array for the points of the star */
    lv_point_t points[10];

    /* Center of the star */
    float cx = 100;
    float cy = 100;

    /* Outer and inner radius of the star */
    float outer_r = 50;
    float inner_r = 20;

    /* Calculate the points */
    for(int i = 0; i < 5; i++) {
        // Outer points of star
        points[2*i].x = cx + outer_r * cos(i * 2 * M_PI / 5);
        points[2*i].y = cy + outer_r * sin(i * 2 * M_PI / 5);

        // Inner points of star
        if(i < 4) {
            points[2*i + 1].x = cx + inner_r * cos((i + 0.5) * 2 * M_PI / 5);
            points[2*i + 1].y = cy + inner_r * sin((i + 0.5) * 2 * M_PI / 5);
        }
    }

    // Connect the last inner point to the first outer point
    points[9].x = cx + inner_r * cos(4.5 * 2 * M_PI / 5);
    points[9].y = cy + inner_r * sin(4.5 * 2 * M_PI / 5);

    /* Create line and assign points */

    static lv_style_t line_style;
    lv_style_init(&line_style);
    lv_style_set_line_width(&line_style, 2); // Set the line width
    lv_style_set_line_color(&line_style, lv_palette_main(LV_PALETTE_BLUE)); // Set the line color

    lv_obj_t * line1 = lv_line_create(parent);
    lv_line_set_points(line1, points, 10);     // Set the points
    lv_obj_add_style(line1, &line_style, 0);   // Optional: Set a style if you want
}

/* 定义一个六边形的六个顶点 */
static lv_point_t hexagon_points[] = {
    {150, 50}, {250, 50},  // 第一条边的两个顶点
    {300, 150}, {250, 250}, // 第二条边的两个顶点
    {150, 250}, {100, 150}, // 第三条边的两个顶点
    {150, 50}               // 回到起点
};

void create_hexagon(lv_obj_t * parent) {
    /* 定义一个六边形的六个顶点 */
    static lv_point_t points[] = {
        {60, 0},   // 顶点1
        {120, 0},  // 顶点2
        {180, 60},  // 顶点3
        {120, 120}, // 顶点4
        {60, 120},  // 顶点5
        {0, 60},   // 顶点6
        {60, 0}    // 闭合的最后一个点
    };

    /* 创建一个 line 对象 */
    lv_obj_t * line = lv_line_create(parent);
    lv_line_set_points(line, points, 7); /* 设置点数组和点数量 */

    /* 设置线的样式 */
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_BLUE));
    lv_obj_add_style(line, &style_line, 0);

    lv_obj_align(line, LV_ALIGN_CENTER, 0, 0); /* 居中对齐 */
}


int main(void) {
    // Initialize LVGL
    lv_init();
    stdio_init_all();
    my_spi_init();
    // Initialize your display hardware
    lcd_gpio_init(); // Initialize GPIOs for LCD
    lcd_reset();     // Reset LCD
    lcd_init();      // Initialize LCD
    lcd_clear(BLUE);
    // Set up buffers for LVGL
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

    // Initialize and register a display driver
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 240;
    disp_drv.ver_res = 320;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    // Create a simple label
    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "w0x7cePPP");
    lv_obj_center(label);


    // //lv_example_anim_1();

    // lv_obj_t * parent = lv_scr_act();

//     // // Now draw the star on this parent
//     // draw_star(parent);
//  /* Create a canvas */
//     static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(200, 200)];
//     lv_obj_t* canvas = lv_canvas_create(lv_scr_act());
//     lv_canvas_set_buffer(canvas, cbuf, 200, 200, LV_IMG_CF_TRUE_COLOR);
//     lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, 0, 0);
    
//     /* Clear the canvas */
//     lv_canvas_fill_bg(canvas, lv_color_white(), LV_OPA_COVER);

//     /* Draw a hexagon */
//     draw_hexagon(canvas, lv_color_hex(0xFF0000)); // Red color hexagon
//  lv_example_polygon_1();
    /* 创建一个父对象，例如一个活动屏幕 */
    lv_obj_t * parent = lv_scr_act();

    /* 绘制六边形 */
    create_hexagon(parent);

    // Handle LVGL tasks
    while(1) {
        lv_timer_handler(); // let the GUI do its work
        sleep_ms(5);
    }

    return 0;
}


#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

// LCD pin definitions
#define LCD_MOSI_PIN 19
#define LCD_SCK_PIN 18
#define LCD_CS_PIN 17
#define LCD_RESET_PIN 20
#define LCD_DC_PIN 21
#define LCD_BACKLIGHT_PIN 22

// LCD width and height
#define LCD_WIDTH 240   // Adjust for your display
#define LCD_HEIGHT 320  // Adjust for your display

// Color definitions
#define WHITE 0xFFFF
#define BLACK 0x0000

// Initialize SPI
void my_spi_init() {
    // Initialize SPI0 at 10 MHz
    spi_init(spi0, 10 * 1000000);
    gpio_set_function(LCD_MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(LCD_SCK_PIN, GPIO_FUNC_SPI);
}

// Write byte to SPI
void spi_write_byte(uint8_t byte) {
    spi_write_blocking(spi0, &byte, 1);
}

// Write command to LCD
void lcd_write_command(uint8_t cmd) {
    gpio_put(LCD_DC_PIN, 0);
    gpio_put(LCD_CS_PIN, 0);
    spi_write_byte(cmd);
    gpio_put(LCD_CS_PIN, 1);
}

// Write data to LCD
void lcd_write_data(uint8_t data) {
    gpio_put(LCD_DC_PIN, 1);
    gpio_put(LCD_CS_PIN, 0);
    spi_write_byte(data);
    gpio_put(LCD_CS_PIN, 1);
}

// Set up GPIO for LCD
void lcd_gpio_init() {
    gpio_init(LCD_CS_PIN);
    gpio_set_dir(LCD_CS_PIN, GPIO_OUT);
    gpio_put(LCD_CS_PIN, 1);

    gpio_init(LCD_RESET_PIN);
    gpio_set_dir(LCD_RESET_PIN, GPIO_OUT);
    gpio_put(LCD_RESET_PIN, 1);

    gpio_init(LCD_DC_PIN);
    gpio_set_dir(LCD_DC_PIN, GPIO_OUT);

    gpio_init(LCD_BACKLIGHT_PIN);
    gpio_set_dir(LCD_BACKLIGHT_PIN, GPIO_OUT);
    gpio_put(LCD_BACKLIGHT_PIN, 0); // Turn off backlight initially
}

// Reset LCD
void lcd_reset() {
    gpio_put(LCD_RESET_PIN, 0);
    sleep_ms(100);
    gpio_put(LCD_RESET_PIN, 1);
    sleep_ms(100);
}

// Initialize LCD
void lcd_init() {
    lcd_reset();

  //   // Initialization commands for ILI9341
  //   	SPI2_Init(); //Ó²ŒþSPI2³õÊŒ»¯
	// LCD_GPIOInit();//LCD GPIO³õÊŒ»¯										 
 	// LCD_RESET(); //LCD žŽÎ»
//*************2.4inch ILI9341³õÊŒ»¯**********//	
	lcd_write_command(0xCF);  
	lcd_write_data(0x00); 
	lcd_write_data(0xD9); //0xC1 
	lcd_write_data(0X30); 
	lcd_write_command(0xED);  
	lcd_write_data(0x64); 
	lcd_write_data(0x03); 
	lcd_write_data(0X12); 
	lcd_write_data(0X81); 
	lcd_write_command(0xE8);  
	lcd_write_data(0x85); 
	lcd_write_data(0x10); 
	lcd_write_data(0x7A); 
	lcd_write_command(0xCB);  
	lcd_write_data(0x39); 
	lcd_write_data(0x2C); 
	lcd_write_data(0x00); 
	lcd_write_data(0x34); 
	lcd_write_data(0x02); 
	lcd_write_command(0xF7);  
	lcd_write_data(0x20); 
	lcd_write_command(0xEA);  
	lcd_write_data(0x00); 
	lcd_write_data(0x00); 
	lcd_write_command(0xC0);    //Power control 
	lcd_write_data(0x1B);   //VRH[5:0] 
	lcd_write_command(0xC1);    //Power control 
	lcd_write_data(0x12);   //SAP[2:0];BT[3:0] 0x01
	lcd_write_command(0xC5);    //VCM control 
	lcd_write_data(0x08); 	 //30
	lcd_write_data(0x26); 	 //30
	lcd_write_command(0xC7);    //VCM control2 
	lcd_write_data(0XB7); 
	lcd_write_command(0x36);    // Memory Access Control 
	lcd_write_data(0x08); 
	lcd_write_command(0x3A);   
	lcd_write_data(0x55); 
	lcd_write_command(0xB1);   
	lcd_write_data(0x00);   
	lcd_write_data(0x1A); 
	lcd_write_command(0xB6);    // Display Function Control 
	lcd_write_data(0x0A); 
	lcd_write_data(0xA2); 
	lcd_write_command(0xF2);    // 3Gamma Function Disable 
	lcd_write_data(0x00); 
	lcd_write_command(0x26);    //Gamma curve selected 
	lcd_write_data(0x01); 
	lcd_write_command(0xE0);    //Set Gamma 
	lcd_write_data(0x0F); 
	lcd_write_data(0x1D); 
	lcd_write_data(0x1A); 
	lcd_write_data(0x0A); 
	lcd_write_data(0x0D); 
	lcd_write_data(0x07); 
	lcd_write_data(0x49); 
	lcd_write_data(0X66); 
	lcd_write_data(0x3B); 
	lcd_write_data(0x07); 
	lcd_write_data(0x11); 
	lcd_write_data(0x01); 
	lcd_write_data(0x09); 
	lcd_write_data(0x05); 
	lcd_write_data(0x04); 		 
	lcd_write_command(0XE1);    //Set Gamma 
	lcd_write_data(0x00); 
	lcd_write_data(0x18); 
	lcd_write_data(0x1D); 
	lcd_write_data(0x02); 
	lcd_write_data(0x0F); 
	lcd_write_data(0x04); 
	lcd_write_data(0x36); 
	lcd_write_data(0x13); 
	lcd_write_data(0x4C); 
	lcd_write_data(0x07); 
	lcd_write_data(0x13); 
	lcd_write_data(0x0F); 
	lcd_write_data(0x2E); 
	lcd_write_data(0x2F); 
	lcd_write_data(0x05); 
	lcd_write_command(0x2B); 
	lcd_write_data(0x00);
	lcd_write_data(0x00);
	lcd_write_data(0x01);
	lcd_write_data(0x3f);
	lcd_write_command(0x2A); 
	lcd_write_data(0x00);
	lcd_write_data(0x00);
	lcd_write_data(0x00);
	lcd_write_data(0xef);	 
	lcd_write_command(0x11); //Exit Sleep
	sleep_ms(100);
	lcd_write_command(0x29); //display on

  // LCD_direction(USE_HORIZONTAL);//ÉèÖÃLCDÏÔÊŸ·œÏò
	// LCD_LED=1;//µãÁÁ±³¹â	 
	// LCD_Clear(WHITE);//ÇåÈ«ÆÁ°×É«

    gpio_put(LCD_BACKLIGHT_PIN, 1); // Turn on backlight
}

void lcd_set_windows(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd) {
    // Set the column address (x)
    lcd_write_command(0x2A); // Column addr set
    lcd_write_data(xStart >> 8);
    lcd_write_data(xStart & 0xFF); // XSTART 
    lcd_write_data(xEnd >> 8);
    lcd_write_data(xEnd & 0xFF); // XEND

    // Set the row address (y)
    lcd_write_command(0x2B); // Row addr set
    lcd_write_data(yStart >> 8);
    lcd_write_data(yStart & 0xFF); // YSTART
    lcd_write_data(yEnd >> 8);
    lcd_write_data(yEnd & 0xFF); // YEND

    // Write to RAM
    lcd_write_command(0x2C);
}

void lcd_clear(uint16_t color) {
    // Set window size to full screen
    lcd_set_windows(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

    // Select LCD for SPI communication
    gpio_put(LCD_CS_PIN, 0);

    // Switch to data mode for color transmission
    gpio_put(LCD_DC_PIN, 1);

    uint32_t total_pixels = LCD_WIDTH * LCD_HEIGHT;
    for (uint32_t i = 0; i < total_pixels; i++) {
        // Send high byte of color
        spi_write_byte(color >> 8);
        // Send low byte of color
        spi_write_byte(color & 0xFF);
    }

    // Deselect LCD once done
    gpio_put(LCD_CS_PIN, 1);
}

void lcd_set_cursor(uint16_t Xpos, uint16_t Ypos) {
    lcd_set_windows(Xpos, Ypos, Xpos, Ypos);
}

void lcd_set_direction(uint8_t direction) {
    switch(direction) {
        case 0: // 0 degrees
            lcd_write_command(0x36);
            lcd_write_data(0x48);
            break;
        case 1: // 90 degrees
            lcd_write_command(0x36);
            lcd_write_data(0x28);
            break;
        case 2: // 180 degrees
            lcd_write_command(0x36);
            lcd_write_data(0x88);
            break;
        case 3: // 270 degrees
            lcd_write_command(0x36);
            lcd_write_data(0xE8);
            break;
    }
}
void lcd_write_reg(uint8_t LCD_Reg, uint16_t LCD_RegValue) {
    lcd_write_command(LCD_Reg);  // Write the register address
    lcd_write_data(LCD_RegValue);  // Write the register value
}
void lcd_write_ram_prepare(void) {
    lcd_write_command(0x2C); // Assuming 0x2C is the command to write to RAM for your LCD
}
void lcd_write_data_16bit(uint16_t Data) {
    lcd_write_data(Data >> 8);   // Write the high byte
    lcd_write_data(Data & 0xFF); // Write the low byte
}

//uint16_t POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
void lcd_draw_point(uint16_t x, uint16_t y) {
    lcd_set_cursor(x, y);  // Set the cursor to the point where you want to draw
    lcd_write_data_16bit(POINT_COLOR); // Write the point color
}


void gui_draw_point(uint16_t x, uint16_t y, uint16_t color) {
    lcd_set_cursor(x, y);  // Set the cursor to the point where you want to draw
    lcd_write_data_16bit(color); // Write the color to that point
}

void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color) {
    lcd_set_windows(sx, sy, ex, ey);  // Set the window to the rectangle being filled

    for (uint16_t i = sy; i <= ey; i++) {
        for (uint16_t j = sx; j <= ex; j++) {
            lcd_write_data_16bit(color);  // Fill every pixel in the rectangle with the color
        }
    }

    // Optionally reset window to full screen, depending on your needs
    lcd_set_windows(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);
}

void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    int x, y, xe, ye;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int dx1 = abs(dx);
    int dy1 = abs(dy);
    int px = 2 * dy1 - dx1;
    int py = 2 * dx1 - dy1;

    if (dy1 <= dx1) {
        if (dx >= 0) {
            x = x1; y = y1; xe = x2;
        } else {
            x = x2; y = y2; xe = x1;
        }
        gui_draw_point(x, y, POINT_COLOR);

        for (int i = 0; x < xe; i++) {
            x = x + 1;
            if (px < 0) {
                px = px + 2 * dy1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    y = y + 1;
                } else {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }
            gui_draw_point(x, y, POINT_COLOR);
        }
    } else {
        if (dy >= 0) {
            x = x1; y = y1; ye = y2;
        } else {
            x = x2; y = y2; ye = y1;
        }
        gui_draw_point(x, y, POINT_COLOR);

        for (int i = 0; y < ye; i++) {
            y = y + 1;
            if (py <= 0) {
                py = py + 2 * dx1;
            } else {
                if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) {
                    x = x + 1;
                } else {
                    x = x - 1;
                }
                py = py + 2 * (dx1 - dy1);
            }
            gui_draw_point(x, y, POINT_COLOR);
        }
    }
}

void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    lcd_draw_line(x1, y1, x2, y1); // Top side
    lcd_draw_line(x1, y2, x2, y2); // Bottom side
    lcd_draw_line(x1, y1, x1, y2); // Left side
    lcd_draw_line(x2, y1, x2, y2); // Right side
}
void lcd_draw_fill_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    lcd_fill(x1, y1, x2, y2, POINT_COLOR); // Use lcd_fill with the rectangle boundaries
}
void _draw_circle_8(int xc, int yc, int x, int y, uint16_t color) {
    gui_draw_point(xc + x, yc + y, color);
    gui_draw_point(xc - x, yc + y, color);
    gui_draw_point(xc + x, yc - y, color);
    gui_draw_point(xc - x, yc - y, color);
    gui_draw_point(xc + y, yc + x, color);
    gui_draw_point(xc - y, yc + x, color);
    gui_draw_point(xc + y, yc - x, color);
    gui_draw_point(xc - y, yc - x, color);
}

void gui_circle(int xc, int yc, uint16_t color, int r, int fill) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        if (fill) {
            for (int yi = x; yi <= y; yi++) {
                _draw_circle_8(xc, yc, x, yi, color);
            }
        } else {
            _draw_circle_8(xc, yc, x, y, color);
        }

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void draw_triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    lcd_draw_line(x0, y0, x1, y1);
    lcd_draw_line(x1, y1, x2, y2);
    lcd_draw_line(x2, y2, x0, y0);
}

// void lcd_show_char(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, char num, uint8_t size, uint8_t mode) {
//     uint8_t temp, pos, t;

//     num = num - ' '; // Adjust for ASCII offset for space
//     lcd_set_windows(x, y, x + size / 2 - 1, y + size - 1);

//     for (pos = 0; pos < size; pos++) {
//         temp = (size == 12) ? asc2_1206[num][pos] : asc2_1608[num][pos];

//         for (t = 0; t < size / 2; t++) {
//             uint16_t color = (temp & 0x01) ? fc : bc;
//             if (mode) {
//                 gui_draw_point(x + t, y + pos, color);
//             } else {
//                 lcd_write_data_16bit(color);
//             }
//             temp >>= 1;
//         }
//     }

//     lcd_set_windows(0, 0, lcddev.width - 1, lcddev.height - 1); // Reset window to full screen
// }

// void lcd_show_string(uint16_t x, uint16_t y, uint8_t size, char *p, uint8_t mode) {
//     while ((*p <= '~') && (*p >= ' ')) { // Check if the character is printable
//         if (x > (lcddev.width - 1) || y > (lcddev.height - 1)) {
//             return;
//         }
//         lcd_show_char(x, y, POINT_COLOR, BACK_COLOR, *p, size, mode);
//         x += size / 2;
//         p++;
//     }
// }

// void lcd_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size) {
//     for (int pos = 0; pos < len; pos++) {
//         int digit = (num / mypow(10, len - pos - 1)) % 10;
//         lcd_show_char(x + (size / 2) * pos, y, POINT_COLOR, BACK_COLOR, '0' + digit, size, 0);
//     }
// }

void test_fill_rec(void) {
    uint8_t i = 0;
    uint16_t point_color;
    // Assuming DrawTestPage is a function that sets up the test page
    //draw_test_page("Test 2: GUI Rectangle Fill Test");

    // Clear a section of the screen where rectangles will be drawn
    lcd_fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);

    // Draw empty rectangles in different colors
    for (i = 0; i < 5; i++) {
        point_color = ColorTab[i]; // Set the current drawing color
        lcd_draw_rectangle(
            lcddev.width / 2 - 80 + (i * 15), 
            lcddev.height / 2 - 80 + (i * 15),
            lcddev.width / 2 - 80 + (i * 15) + 60,
            lcddev.height / 2 - 80 + (i * 15) + 60
        );
    }
    sleep_ms(1500);

    // Clear the area again for filled rectangles
    lcd_fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);

    // Draw filled rectangles in different colors
    for (i = 0; i < 5; i++) {
        point_color = ColorTab[i]; // Set the current drawing color
        lcd_draw_fill_rectangle(
            lcddev.width / 2 - 80 + (i * 15), 
            lcddev.height / 2 - 80 + (i * 15),
            lcddev.width / 2 - 80 + (i * 15) + 60,
            lcddev.height / 2 - 80 + (i * 15) + 60
        );
    }
    sleep_ms(1500);
}

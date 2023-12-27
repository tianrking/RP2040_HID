// lcd_ili9341.h
#ifndef LCD_ILI9341_H
#define LCD_ILI9341_H

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

// LCD width and height for 2.4" Display
#define LCD_WIDTH 240
#define LCD_HEIGHT 320

// Color definitions
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0

// Function Prototypes
void my_spi_init(void);
void spi_write_byte(uint8_t byte);
void lcd_write_command(uint8_t cmd);
void lcd_write_data(uint8_t data);
void lcd_gpio_init(void);
void lcd_reset(void);
void lcd_init(void);
void lcd_clear(uint16_t color);

void lcd_set_windows(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd) ;
void lcd_set_cursor(uint16_t Xpos, uint16_t Ypos) ;
void lcd_set_direction(uint8_t direction);

void lcd_write_reg(uint8_t LCD_Reg, uint16_t LCD_RegValue) ;
void lcd_write_ram_prepare(void) ;
void lcd_write_data_16bit(uint16_t Data) ;
void lcd_draw_point(uint16_t x, uint16_t y) ;



void gui_draw_point(uint16_t x, uint16_t y, uint16_t color) ;
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color) ;
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) ;
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) ;
void lcd_draw_fill_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) ;
void _draw_circle_8(int xc, int yc, int x, int y, uint16_t color) ;
void gui_circle(int xc, int yc, uint16_t color, int r, int fill) ;
void draw_triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) ;
void test_fill_rec(void) ;
// void lcd_show_char(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, char num, uint8_t size, uint8_t mode);
// void lcd_show_string(uint16_t x, uint16_t y, uint8_t size, char *p, uint8_t mode);
// void lcd_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size);

typedef struct {
    uint16_t width;
    uint16_t height;
    // other parameters if needed
} _lcd_dev;

// Global instance of lcddev
_lcd_dev lcddev = {
    .width = 320,  // default width
    .height = 240  // default height
};

#endif // LCD_ILI9341_H

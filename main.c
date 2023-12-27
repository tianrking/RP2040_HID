#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// #include "bsp/board.h"
#include "hardware/gpio.h"
#include "main.h"

uint16_t ColorTab[5]={RED,GREEN,BLUE,YELLOW,RED};
uint16_t POINT_COLOR=WHITE;

/*------------- MAIN -------------*/
int main(void)
{

  stdio_init_all();
  my_spi_init();
  lcd_gpio_init();
  lcd_init();

  // Fill the screen with a color
  lcd_clear(WHITE); 
  sleep_ms(3000);
  lcd_clear(BLUE); 
  while (1)
  {
    test_fill_rec();
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

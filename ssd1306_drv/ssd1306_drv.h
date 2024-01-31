#ifndef __SSD1306_H
#define __SSD1306_H

// 定义使用的GPIO引脚
#define PIN_MISO 4
#define PIN_CS   5
#define PIN_SCK  6
#define PIN_MOSI 7
#define PIN_DC   8
#define PIN_RST  9

#define __SSD1306_CS_SET()   gpio_put(PIN_CS, 1)
#define __SSD1306_CS_CLR()   gpio_put(PIN_CS, 0)
#define __SSD1306_DC_SET()   gpio_put(PIN_DC, 1)
#define __SSD1306_DC_CLR()   gpio_put(PIN_DC, 0)
#define __SSD1306_RES_SET()  gpio_put(PIN_RST, 1)
#define __SSD1306_RES_CLR()  gpio_put(PIN_RST, 0)

#define __SET_COL_START_ADDR() \
    do { \
        ssd1306_write_byte(0x00, SSD1306_CMD); \
        ssd1306_write_byte(0x10, SSD1306_CMD); \
    } while(0)

#define SSD1306_CMD    0
#define SSD1306_DAT    1

#define SSD1306_WIDTH    128
#define SSD1306_HEIGHT   64

// 定义SSD1306的SPI引脚
#define PIN_MISO 4
#define PIN_CS   5
#define PIN_SCK  6
#define PIN_MOSI 7
#define PIN_DC   8
#define PIN_RST  9

// OLED显示缓冲区的大小
#define OLED_WIDTH   128
#define OLED_HEIGHT  64

// SSD1306的命令
#define SSD1306_CMD   0
#define SSD1306_DAT   1

// 全局显示缓存
extern uint8_t s_chDispalyBuffer[OLED_WIDTH][OLED_HEIGHT / 8];

// 函数声明
void init_spi();
void ssd1306_write_byte(uint8_t chData, uint8_t chCmd);
void ssd1306_init(void);
void ssd1306_clear_screen(uint8_t chFill);
void ssd1306_refresh_gram(void);
void ssd1306_draw_point(uint8_t chXpos, uint8_t chYpos, uint8_t chPoint) ;
void ssd1306_display_char(uint8_t chXpos, uint8_t chYpos, uint8_t chChr, uint8_t chSize, uint8_t chMode) ;
void ssd1306_display_string(uint8_t chXpos, uint8_t chYpos, const uint8_t *pchString, uint8_t chSize, uint8_t chMode) ;

#endif 
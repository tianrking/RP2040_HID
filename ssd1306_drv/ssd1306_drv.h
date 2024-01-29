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

#endif 
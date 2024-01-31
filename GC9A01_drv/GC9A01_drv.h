#ifndef __GC9A01_H
#define __GC9A01_H

#include "pico/stdlib.h"
#include "hardware/spi.h"

// 定义GPIO引脚
#define PIN_RESET  9  // 替换为RESET引脚号
#define PIN_DC     8  // 替换为DC（Data/Command）引脚号
#define PIN_CS     5  // 替换为CS（Chip Select）引脚号

// #define PIN_MISO 4
// #define PIN_CS   5
// #define PIN_SCK  6
// #define PIN_MOSI 7
// #define PIN_DC   8
// #define PIN_RST  9

// 操作宏
#define RESET_ON   gpio_put(PIN_RESET, 1)
#define RESET_OFF  gpio_put(PIN_RESET, 0)
#define DC_ON      gpio_put(PIN_DC, 1)
#define DC_OFF     gpio_put(PIN_DC, 0)
#define CS_ON      gpio_put(PIN_CS, 1)
#define CS_OFF     gpio_put(PIN_CS, 0)


// Command codes:
#define COL_ADDR_SET        0x2A
#define ROW_ADDR_SET        0x2B
#define MEM_WR              0x2C
#define COLOR_MODE          0x3A
#define COLOR_MODE__12_BIT  0x03
#define COLOR_MODE__16_BIT  0x05
#define COLOR_MODE__18_BIT  0x06
#define MEM_WR_CONT         0x3C
#define ON                  1
#define OFF                 0

void GC9A01_set_reset(uint8_t val);
void GC9A01_set_data_command(uint8_t val);
void GC9A01_set_chip_select(uint8_t val);  
void GC9A01_spi_tx(uint8_t *data, size_t len);
void GC9A01_write_command(uint8_t cmd);
void GC9A01_write_data(uint8_t *data, size_t len);
// void GC9A01_write_byte(uint8_t val);
void GC9A01_write(uint8_t *data, size_t len);
void GC9A01_write_continue(uint8_t *data, size_t len);
void GC9A01_init(void);

void GC9A01_set_address_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) ;
#endif // GC9A01.h
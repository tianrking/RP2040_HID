#ifndef __ST7735_H
#define __ST7735_H

#include "main.h"

void ST7735_init_spi(void) ;

// 定义GPIO引脚
#define ST7735_PIN_CS   4  // Chip Select
#define ST7735_PIN_MOSI 3  // Master Out Slave In
#define ST7735_PIN_SCK  2  // Serial Clock
#define ST7735_PIN_DC   1  // Data/Command
#define ST7735_PIN_RST  0  // Reset

// 操作宏
#define ST7735_CS_ON   gpio_put(ST7735_PIN_CS, 1)
#define ST7735_CS_OFF  gpio_put(ST7735_PIN_CS, 0)
#define ST7735_DC_ON   gpio_put(ST7735_PIN_DC, 1)
#define ST7735_DC_OFF  gpio_put(ST7735_PIN_DC, 0)
#define ST7735_RESET_ON   gpio_put(ST7735_PIN_RST, 1)
#define ST7735_RESET_OFF  gpio_put(ST7735_PIN_RST, 0)

void ST7735_write_data(uint8_t data) ;
void ST7735_write_command(uint8_t cmd) ;
void ST7735_write_data(uint8_t data) ;
void ST7735_write_data_sequence(uint8_t *data, size_t len);

void ST7735_init_display(void) ;
void ST7735_SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend) ;
void ST7735_DisplayPoint(uint16_t X, uint16_t Y, uint16_t Color) ;

void ST7735_SetAttributes(uint8_t Scan_dir);
void ST7735_InitReg(void);
void ST7735_Init(uint8_t Scan_dir);
void ST7735_Clear(uint16_t Color) ;

void ST7735_dma_write_byte(bool command, uint8_t byte);
void ST7735_dma_init_spi(void);
void ST7735_dma_send(const uint8_t *data, size_t len);

#define HORIZONTAL 0
#define VERTICAL   1
#define ST7735_WIDTH 240
#define ST7735_HEIGHT 240

#endif
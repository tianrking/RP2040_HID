#include "main.h"
#include "hardware/dma.h"

void ST7735_init_spi(void) {
    // 初始化SPI引脚
    gpio_set_function(ST7735_PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(ST7735_PIN_SCK, GPIO_FUNC_SPI);

    // 初始化CS、DC和RST引脚
    gpio_init(ST7735_PIN_CS);
    gpio_set_dir(ST7735_PIN_CS, GPIO_OUT);
    gpio_init(ST7735_PIN_DC);
    gpio_set_dir(ST7735_PIN_DC, GPIO_OUT);
    gpio_init(ST7735_PIN_RST);
    gpio_set_dir(ST7735_PIN_RST, GPIO_OUT);

    // SPI配置
    spi_init(spi0, 100 *1000 * 1000); // 使用1MHz速度初始化SPI
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    // 默认状态
    ST7735_CS_ON;    // 释放CS
    ST7735_RESET_ON; // 默认不重置
}

void ST7735_write_command(uint8_t cmd) {
    ST7735_CS_ON;
    ST7735_DC_OFF;
    ST7735_CS_OFF;
    spi_write_blocking(spi0, &cmd, 1);
    ST7735_CS_ON;
}
void ST7735_write_data(uint8_t data) {
    ST7735_CS_ON;
    ST7735_DC_ON;
    ST7735_CS_OFF;
    spi_write_blocking(spi0, &data, 1);
    ST7735_CS_ON;
}

void ST7735_write_data_sequence(uint8_t *data, size_t len) {
    ST7735_DC_ON;
    ST7735_CS_OFF;
    spi_write_blocking(spi0, data, len);
    ST7735_CS_ON;
}

void ST7735_init_display() {
    // 重置屏幕
    ST7735_RESET_ON;
    sleep_ms(100); // 短暂延时
    ST7735_RESET_OFF;
    sleep_ms(100); // 短暂延时
    ST7735_RESET_ON;
    sleep_ms(100); // 短暂延时

    // 发送初始化命令序列
    ST7735_write_command(0x36);
    ST7735_write_data(0x70);

    ST7735_write_command(0x3A);
    ST7735_write_data(0x05);

    ST7735_write_command(0xB2);
    ST7735_write_data(0x0C);
    ST7735_write_data(0x0C);
    ST7735_write_data(0x00);
    ST7735_write_data(0x33);
    ST7735_write_data(0x33);

    ST7735_write_command(0xB7);
    ST7735_write_data(0x35);

    ST7735_write_command(0xC0);
    ST7735_write_data(0x2C);

    ST7735_write_command(0xC2);
    ST7735_write_data(0x01);

    ST7735_write_command(0xC3);
    ST7735_write_data(0x13);

    ST7735_write_command(0xC4);
    ST7735_write_data(0x20);

    ST7735_write_command(0xC6);
    ST7735_write_data(0x0F);

    ST7735_write_command(0xD0);
    ST7735_write_data(0xA4);
    ST7735_write_data(0xA1);

    ST7735_write_command(0xE0);
    uint8_t color_data1[] = {0xF0, 0x00, 0x04, 0x04, 0x05, 0x29, 0x33, 0x3E, 0x38, 0x12, 0x12, 0x28, 0x30};
    ST7735_write_data_sequence(color_data1, sizeof(color_data1));

    ST7735_write_command(0xE1);
    uint8_t color_data2[] = {0xF0, 0x07, 0x0A, 0x0D, 0x0B, 0x07, 0x28, 0x33, 0x3E, 0x36, 0x14, 0x14, 0x29, 0x23};
    ST7735_write_data_sequence(color_data2, sizeof(color_data2));

    ST7735_write_command(0x21);
    ST7735_write_command(0x11);
    ST7735_write_command(0x29);
}

// #define HORIZONTAL 1

void ST7735_SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend) {
    // if (HORIZONTAL) {
        // 设置X坐标
        ST7735_write_command(0x2A);
        ST7735_write_data((Xstart >> 8) & 0xFF);
        ST7735_write_data(Xstart & 0xFF);
        ST7735_write_data((Xend >> 8) & 0xFF);
        ST7735_write_data(Xend & 0xFF);

        // 设置Y坐标
        ST7735_write_command(0x2B);
        ST7735_write_data((Ystart >> 8) & 0xFF);
        ST7735_write_data(Ystart & 0xFF);
        ST7735_write_data((Yend >> 8) & 0xFF);
        ST7735_write_data(Yend & 0xFF);
    // } else {
    //     // 设置X坐标
    //     ST7735_write_command(0x2A);
    //     ST7735_write_data((Ystart >> 8) & 0xFF);
    //     ST7735_write_data(Ystart & 0xFF);
    //     ST7735_write_data((Yend >> 8) & 0xFF);
    //     ST7735_write_data(Yend & 0xFF);

    //     // 设置Y坐标
    //     ST7735_write_command(0x2B);
    //     ST7735_write_data((Xstart >> 8) & 0xFF);
    //     ST7735_write_data(Xstart & 0xFF);
    //     ST7735_write_data((Xend >> 8) & 0xFF);
    //     ST7735_write_data(Xend & 0xFF);
    // }

    ST7735_write_command(0x2C); // 开始写入像素
}

void ST7735_DisplayPoint(uint16_t X, uint16_t Y, uint16_t Color) {
    ST7735_SetWindows(X, Y, X, Y);

    // 发送颜色数据（16位）
    ST7735_write_data((Color >> 8) & 0xFF); // 高8位
    ST7735_write_data(Color & 0xFF);        // 低8位
}


void ST7735_SetAttributes(uint8_t Scan_dir) {
    uint8_t MemoryAccessReg = 0x00;

    // if (Scan_dir == HORIZONTAL) {
    //     ST7735_HEIGHT = 240; // 假定ST7735_REAL_WIDTH是屏幕的物理宽度
    //     ST7735_WIDTH = ST7735_REAL_HEIGHT; // 假定ST7735_REAL_HEIGHT是屏幕的物理高度
    //     MemoryAccessReg = 0x78;
    // } else {
    //     ST7735_HEIGHT = ST7735_REAL_HEIGHT;
    //     ST7735_WIDTH = ST7735_REAL_WIDTH;
    //     MemoryAccessReg = 0x00;
    // }
    // ST7735_HEIGHT = 240
    // ST7735_WIDTH = 240
    
    MemoryAccessReg = 0x00;
    ST7735_write_command(0x36);
    ST7735_write_data(MemoryAccessReg);
}

void ST7735_InitReg(void) {
    ST7735_write_command(0x11); // Sleep out
    sleep_ms(120); // 等待退出睡眠模式

    ST7735_write_command(0x36); // Memory data access control
    // if (HORIZONTAL)
    //     ST7735_write_data(0x00);
    // else
        ST7735_write_data(0x70);

    ST7735_write_command(0x3A); // Interface pixel format
    ST7735_write_data(0x05);

    ST7735_write_command(0xB2); // Porch setting
    ST7735_write_data(0x0C);
    ST7735_write_data(0x0C);
    ST7735_write_data(0x00);
    ST7735_write_data(0x33);
    ST7735_write_data(0x33);

    ST7735_write_command(0xB7); // Gate control
    ST7735_write_data(0x35);

    ST7735_write_command(0xBB); // VCOM setting
    ST7735_write_data(0x35);

    ST7735_write_command(0xC0); // LCM control
    ST7735_write_data(0x2C);

    ST7735_write_command(0xC2); // VDV and VRH command enable
    ST7735_write_data(0x01);

    ST7735_write_command(0xC3); // VRH set
    ST7735_write_data(0x13);

    ST7735_write_command(0xC4); // VDV set
    ST7735_write_data(0x20);

    ST7735_write_command(0xC6); // Frame rate control in normal mode
    ST7735_write_data(0x0F);

    ST7735_write_command(0xD0); // Power control 1
    ST7735_write_data(0xA4);
    ST7735_write_data(0xA1);

    ST7735_write_command(0xD6); // Power control 2
    ST7735_write_data(0xA1);

    ST7735_write_command(0xE0); // Positive voltage gamma control
    uint8_t positive_gamma[] = {0xF0, 0x00, 0x04, 0x04, 0x04, 0x05, 0x29, 0x33, 0x3E, 0x38, 0x12, 0x12, 0x28, 0x30};
    ST7735_write_data_sequence(positive_gamma, sizeof(positive_gamma));

    ST7735_write_command(0xE1); // Negative voltage gamma control
    uint8_t negative_gamma[] = {0xF0, 0x07, 0x0A, 0x0D, 0x0B, 0x07, 0x28, 0x33, 0x3E, 0x36, 0x14, 0x14, 0x29, 0x32};
    ST7735_write_data_sequence(negative_gamma, sizeof(negative_gamma));

    ST7735_write_command(0x21); // Inversion ON

    ST7735_write_command(0x11); // Sleep out
    sleep_ms(120); // 等待退出睡眠模式

    ST7735_write_command(0x29); // Display ON
}


void ST7735_Init(uint8_t Scan_dir) {
    // 设置PWM，具体实现取决于您的硬件设置
    // DEV_SET_PWM(90); 

    // 硬件重置
    ST7735_RESET_OFF;
    sleep_ms(100);
    ST7735_RESET_ON;
    sleep_ms(100);

    // 设置屏幕的分辨率和扫描方式
    ST7735_SetAttributes(Scan_dir);

    // 设置初始化寄存器
    ST7735_InitReg();
}

void ST7735_Clear(uint16_t Color) {
    uint16_t Image[ST7735_WIDTH * ST7735_HEIGHT];
    Color = ((Color << 8) & 0xff00) | (Color >> 8);

    for (int j = 0; j < ST7735_HEIGHT * ST7735_WIDTH; j++) {
        Image[j] = Color;
    }

    ST7735_SetWindows(0, 0, ST7735_WIDTH - 1, ST7735_HEIGHT - 1);

    ST7735_DC_ON;
    ST7735_CS_OFF;

    for (int j = 0; j < ST7735_HEIGHT; j++) {
        spi_write_blocking(spi0, (uint8_t *)&Image[j * ST7735_WIDTH], ST7735_WIDTH * 2);
    }

    ST7735_CS_ON;
}

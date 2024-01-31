cmake_minimum_required(VERSION 3.13)

# 引入 Pico-SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# 项目名称和语言设置
project(rp2040_oled C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# 初始化 Pico-SDK
pico_sdk_init()

# 设置LVGL的路径
set(LVGL_PATH $ENV{LVGL_PATH})

# 检查LVGL路径是否已设置
if(NOT LVGL_PATH)
    message(FATAL_ERROR "LVGL_PATH environment variable is not set")
endif()

# 添加LVGL源文件
file(GLOB_RECURSE LVGL_SOURCES ${LVGL_PATH}/src/*.c)

SET(SOURCES screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    )

# 创建可执行文件
add_executable(rp2040_oled
    main.c
    ${LVGL_SOURCES} # 添加LVGL源文件
    ${CMAKE_CURRENT_LIST_DIR}/ssd1306_drv/ssd1306_drv.c
    ${CMAKE_CURRENT_LIST_DIR}/GC9A01_drv/GC9A01_drv.c
    ${SOURCES}
)

# Make sure TinyUSB can find tusb_config.h
# 包含LVGL和其它所需的目录
target_include_directories(rp2040_oled PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${LVGL_PATH} # 添加LVGL的根目录
    ${LVGL_PATH}/src # 添加LVGL的src目录
    ${CMAKE_CURRENT_LIST_DIR}/ssd1306_drv
    ${CMAKE_CURRENT_LIST_DIR}/GC9A01_drv/
)

# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_device
# for TinyUSB device support and tinyusb_board for the additional board support library used by the example
target_link_libraries(rp2040_oled PUBLIC 
	pico_stdlib 
	pico_unique_id 
    hardware_spi
	)

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
#target_compile_definitions(dev_hid_composite PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)
# 设置 C 和 C++ 编译器标志
SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

# Pico 配置
pico_enable_stdio_usb(rp2040_oled 1)
pico_enable_stdio_uart(rp2040_oled 0)
add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# 生成额外的输出文件
pico_add_extra_outputs(rp2040_oled)

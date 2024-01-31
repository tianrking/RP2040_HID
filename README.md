 Here is an updated README for the RP2040 HID mouse project focusing more on the LVGL configuration:

# RP2040 HID Mouse with LVGL

This project turns the Raspberry Pi Pico RP2040 into a USB HID mouse device using the LVGL graphics library for rendering mouse cursor animations on an attached display.

## Dependencies

- Raspberry Pi Pico SDK
- TinyUSB library
- LVGL graphics library

## LVGL Setup

LVGL needs to be configured before it can be used with Pico:

1. Download LVGL and set the `LVGL_PATH` environment variable to the LVGL root directory 
2. Add LVGL source files using `file(GLOB_RECURSE LVGL_SOURCES ${LVGL_PATH}/src/*.c)`
3. Include LVGL headers and source directories in the compile flags:

```
target_include_directories(rp2040_hid_mouse PUBLIC 
  ${LVGL_PATH}
  ${LVGL_PATH}/src
)
```

4. Define the display and input drivers by configuring `lv_conf.h`



## Squareline Export

1. export
2. CMakelist  to  CMKBAK.txt
3. modify the file

```c
ui.c:25:6
///////////////////// TEST LVGL SETTINGS ////////////////////
// #if LV_COLOR_DEPTH != 8
//     #error "LV_COLOR_DEPTH should be 8bit to match SquareLine Studio's settings"
// #endif
// #if LV_COLOR_16_SWAP !=0
//     #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
// #endif
```
SPI drive
SCL-GP6
SDA-GP7
RES-GP9
DC-GP8
CS-GP5

## Features

- Simulate mouse motion and clicks over USB
- Render mouse cursor animations on a display using LVGL 
- Use on-board buttons for mouse click input

## Customization

- Modify `main.c` to change mouse behaviors
- Update `usb_descriptors.c` to set custom USB descriptors
- Configure LVGL theme and display output

Contributions welcome!

# RP2040 HID Device Project

## Introduction
This project uses the Raspberry Pi Pico (RP2040) to create a Human Interface Device (HID) that interacts with computers via USB, simulating keyboard and mouse operations. Additionally, it features a Cloudflare Worker-based web interface for visualizing mouse movements.

## Features
- **Keyboard Simulation**: Simulates keyboard shortcuts such as Alt+Tab, Alt+F4, F5 refresh, etc.
- **Mouse Simulation**: Emulates mouse movements with specific patterns like circular and elliptical trajectories.
- **GPIO Control**: Uses GPIO pins to trigger different keyboard and mouse actions.
- **LED Blinking Indication**: Indicates device states (not mounted, mounted, suspended) by blinking the onboard LED.
- **Web Visualization**: A Cloudflare Worker webpage to visualize the mouse trajectory in real-time.

## Hardware Requirements
- Raspberry Pi Pico or any RP2040 microcontroller board.
- USB cable for connecting to the host device.

## Setup Guide
1. **Environment Setup**: Ensure you have the required software development tools for RP2040 installed in your development environment.
2. **Code Download**: Download the project code to your development environment.
3. **Compile and Flash**: Compile the code and flash it onto your RP2040 device.

## Web Visualization
- The project includes a Cloudflare Worker webpage that allows users to visualize the mouse trajectory.
- The webpage provides two modes:
  - **/draw**: A simple drawing canvas to track mouse movements.
  - **/raw**: An advanced mode with dynamic coloring and real-time visual feedback.

## Usage Instructions
- Connect your RP2040 device to a computer.
- Trigger different functionalities via GPIO pins:
  - **GP2 to GP5**: Control mouse movement.
  - **GP6 to GP9**: Emulate various keyboard shortcuts.
- Access the Cloudflare Worker webpage to visualize the mouse movements.

## Development Information
- **Programming Language**: C
- **External Libraries**: TinyUSB, RP2040 SDK
- **Web Technologies**: JavaScript, HTML, Cloudflare Workers

## Cloudflare Worker Setup
- Deploy the provided worker script to your Cloudflare account.
- Access the web interface via the specified routes (`/draw` and `/raw`) to visualize the mouse movements.

/****************************************************************************************************
//=========================================电源接线================================================//
//     LCD模块                RP2040单片机 (Raspberry Pi Pico)
//      VCC          接        3.3V          //电源
//      GND          接        GND          //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为SPI总线
//     LCD模块                RP2040单片机 (Raspberry Pi Pico)
//    SDI(MOSI)      接        GPIO 19      //液晶屏SPI总线数据写信号 (SPI0 TX)
//    SDO(MISO)      接        GPIO 16      //液晶屏SPI总线数据读信号，如果不需要读，可以不接线 (SPI0 RX)
//=======================================液晶屏控制线接线==========================================//
//     LCD模块                        RP2040单片机 (Raspberry Pi Pico)
//       LED         接        GPIO 22          //液晶屏背光控制信号，如果不需要控制，接3.3V或不接
//       SCK         接        GPIO 18          //液晶屏SPI总线时钟信号 (SPI0 SCK)
//      DC/RS        接        GPIO 21          //液晶屏数据/命令控制信号
//       RST         接        GPIO 20          //液晶屏复位控制信号
//       CS          接        GPIO 17          //液晶屏片选控制信号
//=========================================触摸屏触接线=========================================//
//如果模块不带触摸功能或者带有触摸功能，但是不需要触摸功能，则不需要进行触摸屏接线
//	   LCD模块                RP2040单片机 (Raspberry Pi Pico)
//      T_IRQ        接        特定GPIO      //触摸屏触摸中断信号
//      T_DO         接        特定GPIO      //触摸屏SPI总线读信号
//      T_DIN        接        特定GPIO      //触摸屏SPI总线写信号
//      T_CS         接        特定GPIO      //触摸屏片选控制信号
//      T_CLK        接        特定GPIO      //触摸屏SPI总线时钟信号
**************************************************************************************************/



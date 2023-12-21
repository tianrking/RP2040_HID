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


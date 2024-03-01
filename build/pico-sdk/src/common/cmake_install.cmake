# Install script for directory: /home/w0x7ce/pico-sdk/src/common

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/w0x7ce/Downloads/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/w0x7ce/Desktop/LVGL/240_240_ST7789/build/pico-sdk/src/common/boot_picoboot/cmake_install.cmake")
  include("/home/w0x7ce/Desktop/LVGL/240_240_ST7789/build/pico-sdk/src/common/boot_uf2/cmake_install.cmake")
  include("/home/w0x7ce/Desktop/LVGL/240_240_ST7789/build/pico-sdk/src/common/pico_base/cmake_install.cmake")
  include("/home/w0x7ce/Desktop/LVGL/240_240_ST7789/build/pico-sdk/src/common/pico_usb_reset_interface/cmake_install.cmake")
  include("/home/w0x7ce/Desktop/LVGL/240_240_ST7789/build/pico-sdk/src/common/pico_bit_ops/cmake_install.cmake")
  include("/home/w0x7ce/Desktop/LVGL/240_240_ST7789/build/pico-sdk/src/common/pico_binary_info/cmake_install.cmake")
  include("/home/w0x7ce/Desktop/LVGL/240_240_ST7789/build/pico-sdk/src/common/pico_divider/cmake_install.cmake")
  include("/home/w0x7ce/Desktop/LVGL/240_240_ST7789/build/pico-sdk/src/common/pico_sync/cmake_install.cmake")
  include("/home/w0x7ce/Desktop/LVGL/240_240_ST7789/build/pico-sdk/src/common/pico_time/cmake_install.cmake")
  include("/home/w0x7ce/Desktop/LVGL/240_240_ST7789/build/pico-sdk/src/common/pico_util/cmake_install.cmake")
  include("/home/w0x7ce/Desktop/LVGL/240_240_ST7789/build/pico-sdk/src/common/pico_stdlib/cmake_install.cmake")

endif()


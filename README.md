# STM32-Bootloader
STM32 Custom Bootloader – NUCLEO-G071RB

This repository showcases a fully functional custom bootloader and application architecture built for the STM32G071RB microcontroller using STM32CubeIDE. It highlights embedded development skills such as memory mapping, linker script customization, firmware modularization, and runtime control handoff. This project is designed to reflect industry-relevant practices for building scalable and upgradable embedded systems.

🚀 Project Overview

The STM32 bootloader is responsible for initializing the system and conditionally jumping to a user application located at a predefined memory address. The project uses a custom linker script to define memory regions for the bootloader and application, and establishes a robust interface using linker section attributes for potential API sharing.

🔩 Features

Custom Linker Script: Divides flash into bootloader and application regions

Bootloader-to-Application Handoff: Controlled jump logic to transfer execution

Section-Based API Sharing: Use of __attribute__((section())) for potential shared data/functions

Extendable Firmware Architecture: Can be adapted for OTA or CAN-based upgrades

Safe and Isolated Code Zones: Enables reliable firmware update mechanisms in production

🧰 Tools Used

Board: STM32 NUCLEO-G071RB

IDE: STM32CubeIDE

Language: C

Debugging: UART (optional), STM32 HAL Drivers

🧪 How It Works

Bootloader starts at 0x08000000

Initializes system and checks for jump conditions

If valid, sets the stack pointer and jumps to application at 0x08004000

Application executes independently

Optional: Shared functions or variables can be placed in a designated section (.shared_api) and accessed from both regions.

📝 Future Improvements

Add firmware update interface via CAN/UART

Implement CRC-based application validity check

Support rollback and dual-application layout

Add Makefile-based CLI builds for CI/CD integration

🤝 License

MIT License. Feel free to use, modify, and build upon this project.



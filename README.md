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

📁 Project Structure

├── BootLoader/              # Bootloader project files
│   └── Core/Src
│   └── Core/Inc
│   └── BootLoader.ioc
│   └── main.c, system_stm32...
│
├── Application/            # User application project files
│   └── Core/Src
│   └── Core/Inc
│   └── Application.ioc
│
├── STM32G071RBTX_FLASH.ld  # Custom linker script

🧠 Memory Map (STM32G071RBTx – 128KB Flash)

Region

Start Address

End Address

Size

Purpose

Bootloader

0x08000000

0x08003FFF

16 KB

Boot and Jump Logic

Application

0x08004000

0x0801FFFF

112 KB

Main Application

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

📌 Highlights for Recruiters

Demonstrates mastery over embedded firmware fundamentals: bootloader logic, memory control, and linker scripting

Clean modular structure to isolate startup logic from application logic

Project-ready for enhancements such as secure firmware upgrades over CAN or UART

Reflects industry practices in embedded systems, automotive ECUs, and IoT firmware platforms

📝 Future Improvements

Add firmware update interface via CAN/UART

Implement CRC-based application validity check

Support rollback and dual-application layout

Add Makefile-based CLI builds for CI/CD integration

📷 Suggested Diagrams

Boot Sequence Flowchart

Flash Memory Layout

Application Jump Mechanism

(Feel free to place these under a /docs/ folder or embed in the README once created.)

🤝 License

MIT License. Feel free to use, modify, and build upon this project.

If you're a recruiter or engineer interested in this project, feel free to reach out via GitHub or LinkedIn!



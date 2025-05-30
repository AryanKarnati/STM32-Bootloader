/*
 ******************************************************************************
 **
 ** @file        : LinkerScript.ld
 ** @brief       : Linker script for Application (STM32G071RBTx on NUCLEO-G071RB)
 **
 ** @note        : FLASH offset = 0x8008000, RAM origin = 0x20000000
 **
 ** Copyright (c) 2025 STMicroelectronics. All rights reserved.
 ** Licensed under terms in the LICENSE file.
 **
 ******************************************************************************
*/

ENTRY(Reset_Handler)

_estack = ORIGIN(RAM) + LENGTH(RAM);
_Min_Heap_Size = 0x200;
_Min_Stack_Size = 0x400;

MEMORY
{
  RAM         (xrw) : ORIGIN = 0x20000000, LENGTH = 36K
  FLASH       (rx)  : ORIGIN = 0x8008000, LENGTH = 64K
  MY_MEMORY   (rx)  : ORIGIN = 0x8018000, LENGTH = 32K
}

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } > FLASH

  .myBufSectionRAM (NOLOAD) :
  {
    . = ALIGN(4);
    KEEP(*(.myBufSectionRAM))
    . = ALIGN(4);
  } > RAM

  .myBufSectionFLASH 0x8001000 :
  {
    KEEP(*(.myBufSectionFLASH))
  } > FLASH

  .mysection :
  {
    . = ALIGN(4);
    __mysection_start__ = .;
    *(.mysection*)
    __mysection_end__ = .;
  } > MY_MEMORY

  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)
    KEEP(*(.init))
    KEEP(*(.fini))
    . = ALIGN(4);
    _etext = .;
  } > FLASH

  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } > FLASH

  .ARM.extab (READONLY) :
  {
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } > FLASH

  .ARM (READONLY) :
  {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } > FLASH

  .preinit_array (READONLY) :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN(__preinit_array_start = .);
    KEEP(*(.preinit_array*))
    PROVIDE_HIDDEN(__preinit_array_end = .);
    . = ALIGN(4);
  } > FLASH

  .init_array (READONLY) :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN(__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array*))
    PROVIDE_HIDDEN(__init_array_end = .);
    . = ALIGN(4);
  } > FLASH

  .fini_array (READONLY) :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN(__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array*))
    PROVIDE_HIDDEN(__fini_array_end = .);
    . = ALIGN(4);
  } > FLASH

  _sidata = LOADADDR(.data);

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    *(.RamFunc)
    *(.RamFunc*)
    . = ALIGN(4);
    _edata = .;
  } > RAM AT > FLASH

  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
  } > RAM

  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE(end = .);
    PROVIDE(_end = .);
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } > RAM

  /DISCARD/ :
  {
    libc.a(*);
    libm.a(*);
    libgcc.a(*);
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
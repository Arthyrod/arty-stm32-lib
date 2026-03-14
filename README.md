# PureSTM-lib
A lightweight, bare-metal Hardware Abstraction Layer (HAL) for STM32F4 series microcontrollers, written in C without external dependencies.

--- 
## 🚀 Overview
PureSTM is a personal study project developed to explore the fundamentals of Bare-Metal embedded systems. Instead of relying on pre-built libraries like STM32 CubeHAL, this project focuses on direct communication with the ARM Cortex-M4 hardware through register manipulation.

The goal of this library is to document my learning journey in Computer Engineering, providing a hands-on understanding of memory mapping, peripheral initialization, and hardware-software interfacing.

## 🛠️ Key Learning Features
* Register-Level Access: Implementation of peripheral control by directly writing to memory addresses, based on the STM32F4 Reference Manual.

* Hardware Fundamentals: Deep dive into the RCC (Reset and Clock Control) to understand how to "wake up" and synchronize internal peripherals.

* GPIO Management: Learning the difference between registers like MODER, ODR, and BSRR for efficient digital I/O control.

* Timing & Cycles: Implementing precise software delays by configuring Hardware Timers, moving away from inaccurate "dummy loops".

* Low-Level Architecture: Hands-on experience with C structures for memory mapping and the use of volatile pointers to handle hardware-changed values.

## 📈 Roadmap
* Add UART support for serial debugging.

* Implement PWM functions for TIM9-11.

* Add ADC (Analog to Digital Converter) support.

* Implement HSE (External Crystal) clock configuration logic.

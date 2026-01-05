# JSON w-M-Bus Serializer (Embedded-Friendly C Library)

## Project Overview

This project implements a lightweight, embedded-friendly C library that serializes structured meter data into a **strictly defined JSON format**.  
It represents a realistic firmware component in a smart-meter / w-M-Bus data pipeline:

**Measurement data → Internal data structures → JSON serialization → Gateway / backend interface**

The library focuses on:
- Clean software architecture
- Embedded-oriented API design
- Controlled memory usage
- Robust and safe JSON serialization

⚠️ w-M-Bus radio communication, OMS parsing, encryption, and real meter interaction are **explicitly out of scope**.

---

## Chosen Platform & Programming Language

### Programming Language
- **C (ISO C)**
- Chosen for its:
  - Deterministic behavior
  - Low memory overhead
  - Suitability for bare-metal and RTOS-based firmware
  - Wide support across embedded toolchains

### Development Platform
- Developed and tested using **MinGW64 (GCC) on Windows**
- **Justification**:
  - The code uses no OS-specific APIs
  - No dynamic memory allocation (`malloc`)
  - No external dependencies or JSON libraries
  - Fully portable to embedded platforms such as:
    - STM32CubeIDE (STM32)
    - ESP-IDF (ESP32)
    - Arduino framework

The desktop build environment is used purely for development and demonstration convenience.

---

## Project Structure


# JSON w-M-Bus Serializer (Embedded-Friendly C Library)

## Project Overview

This project implements a lightweight, embedded-friendly **C library** that serializes structured meter data into a **strictly defined JSON format**.

It represents a realistic firmware component in a smart-meter / w-M-Bus data pipeline:

**Measurement data → Internal data structures → JSON serialization → Gateway / backend interface**

The library focuses on:
- Clean software architecture
- Embedded-oriented API design
- Controlled memory usage
- Robust and safe JSON serialization

⚠️ w-M-Bus radio communication, OMS parsing, encryption, and real meter interaction are **explicitly out of scope**.

---

## Key Features

- Fixed-size data structures (no heap / dynamic allocation)
- Safe, buffer-bounded JSON serialization
- Support for multiple devices and multiple data points
- Clear public API with error handling
- No external JSON libraries or dependencies
- Portable, compiler-agnostic ISO C code

---

## Chosen Platform & Programming Language

### Programming Language
- **C (ISO C)**

Chosen for:
- Deterministic behavior
- Low memory footprint
- Suitability for bare-metal and RTOS-based firmware
- Wide support across embedded toolchains

### Development Platform
- Developed and tested using **MinGW64 (GCC) on Windows**

**Justification**:
- The code uses no OS-specific APIs
- No dynamic memory allocation (`malloc`)
- No external libraries
- Fully portable to embedded platforms such as:
  - STM32CubeIDE (STM32)
  - ESP-IDF (ESP32)
  - Arduino framework

The desktop build environment is used **only for development and demonstration**.

---

## Intended Use Case

This library is intended to run inside an **embedded gateway or meter firmware**, where structured measurement data must be serialized into JSON before being transmitted to a backend system via any transport layer (UART, MQTT, HTTP, etc.).

The serialization logic is **transport-agnostic** and can be integrated into existing firmware pipelines.

---

## Project Structure

json-wmbus-serializer/
├── include/
│ └── json_serializer.h
├── src/
│ └── json_serializer.c
├── examples/
│ └── main.c
└── README.md

---

## Public API

```c
JsonResult serialize_to_json(
    const GatewayData *input,
    char *output,
    size_t output_size,
    size_t *bytes_written
);


---

## Build & Run (Desktop Demo)

```bash
gcc -Wall -Wextra -Iinclude src/json_serializer.c examples/main.c -o demo
./demo


##json output
[
  {
    "gatewayId": "gateway_1234",
    "date": "1970-01-01",
    "deviceType": "stromleser",
    "interval_minutes": 15,
    "total_readings": 1,
    "values": {
      "device_count": 1,
      "readings": [
        {
          "media": "water",
          "meter": "waterstarm",
          "deviceId": "stromleser_50898527",
          "unit": "m3",
          "data": [
            {
              "timestamp": "1970-01-01 00:00",
              "meter_datetime": "1970-01-01 00:00",
              "total_m3": 107.752,
              "status": "OK"
            }
          ]
        }
      ]
    }
  }
]

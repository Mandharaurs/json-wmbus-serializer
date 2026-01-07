# JSON w-M-Bus Serializer (Embedded-Friendly C Library)

## Project Overview

This project implements a lightweight, embedded-friendly C library that serializes structured meter data into a strictly predefined JSON format.

It represents a realistic firmware component in a smart-meter / w-M-Bus data pipeline:

Measurement data → Internal data structures → JSON serialization → Gateway / backend interface

The library focuses on:
- Clean software architecture
- Embedded-oriented API design
- Controlled and deterministic memory usage
- Robust, safe JSON serialization

w-M-Bus radio communication, OMS parsing, encryption, and real meter interaction are explicitly out of scope.

---

## Key Features

- Fixed-size data structures (no heap / dynamic allocation)
- Safe, buffer-bounded JSON serialization
- Support for multiple devices and multiple data points
- Transport-agnostic core logic
- Clear public API with explicit error handling
- No external JSON libraries or dependencies
- Portable, compiler-agnostic ISO C code

---

## Chosen Platform & Programming Language

### Programming Language
C (ISO C99)

Chosen for:
- Deterministic behavior
- Low memory footprint
- Suitability for bare-metal and RTOS-based firmware
- Wide support across embedded toolchains

### Development Platform
Developed and tested using MinGW64 (GCC) on Windows.

Justification:
- The code uses no OS-specific APIs
- No dynamic memory allocation (malloc / free)
- No external dependencies
- Fully portable to embedded platforms such as:
  - STM32CubeIDE (STM32)
  - ESP-IDF (ESP32)
  - Arduino framework

The desktop environment is used only for development and demonstration convenience.

---

## Intended Use Case

This library is intended to run inside an embedded gateway or meter firmware, where structured measurement data must be serialized into JSON before being transmitted to a backend system via any transport layer (UART, MQTT, HTTP, etc.).

The serialization logic is transport-agnostic and can be integrated into existing firmware pipelines.

---

## Project Structure

json-wmbus-serializer/
├── include/
│   └── json_serializer.h
├── src/
│   └── json_serializer.c
├── examples/
│   └── main.c
└── README.md

---

## Public API

JsonResult serialize_to_json(
    const GatewayData *input,
    char              *output,
    size_t             output_size,
    size_t            *bytes_written
);

API behavior:
- Serializes input data into the exact JSON structure defined in the assignment
- Writes into a caller-provided buffer
- Prevents buffer overflows
- Returns explicit error codes:
  - JSON_OK
  - JSON_ERR_BUFFER_TOO_SMALL
  - JSON_ERR_INVALID_ARGUMENT

---

## Mandatory JSON Output Format

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

Important guarantees:
- Field names are not changed
- JSON structure is not changed
- Numbers are serialized as numbers, not strings
- No additional fields are added
- The outer JSON element is always an array

---

## Build & Run (Desktop Demo)

Build:
gcc -Wall -Wextra -Iinclude src/json_serializer.c examples/main.c -o demo

Run:
./demo

The demo application:
1. Creates sample gateway and device data
2. Calls the serialization library
3. Prints the generated JSON to the console

---

## Maximum JSON Size

The maximum JSON size is bounded and deterministic.

It depends on:
- MAX_DEVICES
- MAX_DATA_POINTS
- Maximum string lengths provided by the application

Worst-case estimation:
- MAX_DEVICES = 4
- MAX_DATA_POINTS = 8

In the worst case, the generated JSON size is approximately 1-1.5 KB.

For safety, the example application uses a 2 KB output buffer, which is sufficient for all supported configurations.

If the output buffer is too small, the serializer returns JSON_ERR_BUFFER_TOO_SMALL and writes no partial data.

---

## Design Decisions & Assumptions

- Fixed-size arrays are used to guarantee deterministic memory usage
- The library does not allocate memory internally
- All strings are assumed to be null-terminated and provided by the caller
- Input strings are assumed to be valid and not JSON-escaped
- Floating-point formatting relies on snprintf support in the target C library
- JSON field names and structure strictly follow the assignment specification

---

## Limitations

- String values are not JSON-escaped
- Floating-point precision depends on the C library implementation
- Timestamp and date formats are not validated

---

## Possible Extensions

- Support for additional media types and units
- Compile-time configuration of maximum limits
- Optional JSON string escaping
- Streaming or chunk-based serialization
- Integration with UART, MQTT, or HTTP layers (outside the core library)

---
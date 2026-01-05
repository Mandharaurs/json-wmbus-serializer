#include <stdio.h>
#include "json_serializer.h"

int main(void)
{
    char json_buffer[1024];
    size_t bytes_written = 0;

    GatewayData gateway = {
        .gateway_id = "gateway_1234",
        .date = "1970-01-01",
        .device_type = "stromleser",
        .interval_minutes = 15,
        .total_readings = 1,
        .device_count = 1
    };

    gateway.devices[0] = (DeviceReading){
        .media = "water",
        .meter = "waterstarm",
        .device_id = "stromleser_50898527",
        .unit = "m3",
        .data_count = 1
    };

    gateway.devices[0].data[0] = (MeterDataPoint){
        .timestamp = "1970-01-01 00:00",
        .meter_datetime = "1970-01-01 00:00",
        .total_m3 = 107.752f,
        .status = "OK"
    };

    JsonResult res = serialize_to_json(
        &gateway,
        json_buffer,
        sizeof(json_buffer),
        &bytes_written
    );

    if (res == JSON_OK) {
        printf("JSON (%zu bytes):\n%s\n", bytes_written, json_buffer);
    } else {
        printf("Serialization failed (error %d)\n", res);
    }

    return 0;
}

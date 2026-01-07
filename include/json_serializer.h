#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <stddef.h>

/* Configuration limits */
#define MAX_DEVICES      4
#define MAX_DATA_POINTS  8

/* Single meter data point */
typedef struct 
{
    const char *timestamp;
    const char *meter_datetime;
    float       total_m3;
    const char *status;
} MeterDataPoint;

/* One device reading */
typedef struct
{
    const char       *media;
    const char       *meter;
    const char       *device_id;
    const char       *unit;
    size_t            data_count;
    MeterDataPoint    data[MAX_DATA_POINTS];
} DeviceReading;

/* Gateway-level data */
typedef struct 
{
    const char     *gateway_id;
    const char     *date;
    const char     *device_type;
    int             interval_minutes;
    int             total_readings;
    size_t          device_count;
    DeviceReading   devices[MAX_DEVICES];
} GatewayData;

/* Error codes */
typedef enum 
{
    JSON_OK = 0,
    JSON_ERR_BUFFER_TOO_SMALL,
    JSON_ERR_INVALID_ARGUMENT
} JsonResult;

/*
 * Serializes GatewayData into JSON.
 *
 * Caller must ensure all strings are valid, null-terminated,
 * and remain valid for the duration of serialization.
 *
 * - output buffer must be provided by caller
 * - no dynamic allocation
 */
JsonResult serialize_to_json(
    const GatewayData *input,
    char              *output,
    size_t             output_size,
    size_t            *bytes_written
);

#endif

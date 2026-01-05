#include "json_serializer.h"
#include <stdio.h>

/* Separate macros to avoid empty __VA_ARGS__ issues
 * and keep compatibility with embedded compilers
 */

#define WRITE_STR(str)                                  \
    do {                                                \
        int n = snprintf(out, remaining, "%s", str);   \
        if (n < 0 || (size_t)n >= remaining)            \
            return JSON_ERR_BUFFER_TOO_SMALL;           \
        out += n;                                       \
        remaining -= n;                                 \
        written += n;                                   \
    } while (0)

#define WRITE_FMT(fmt, ...)                             \
    do {                                                \
        int n = snprintf(out, remaining, fmt, __VA_ARGS__); \
        if (n < 0 || (size_t)n >= remaining)            \
            return JSON_ERR_BUFFER_TOO_SMALL;           \
        out += n;                                       \
        remaining -= n;                                 \
        written += n;                                   \
    } while (0)

JsonResult serialize_to_json(
    const GatewayData *input,
    char *output,
    size_t output_size,
    size_t *bytes_written)
{
    if (!input || !output || output_size == 0)
        return JSON_ERR_INVALID_ARGUMENT;

    char *out = output;
    size_t remaining = output_size;
    size_t written = 0;

    WRITE_STR("[{\n");
    WRITE_FMT("\"gatewayId\":\"%s\",\n", input->gateway_id);
    WRITE_FMT("\"date\":\"%s\",\n", input->date);
    WRITE_FMT("\"deviceType\":\"%s\",\n", input->device_type);
    WRITE_FMT("\"interval_minutes\":%d,\n", input->interval_minutes);
    WRITE_FMT("\"total_readings\":%d,\n", input->total_readings);

    WRITE_STR("\"values\":{\n");
    WRITE_FMT("\"device_count\":%zu,\n", input->device_count);
    WRITE_STR("\"readings\":[\n");

    for (size_t i = 0; i < input->device_count; i++) {
        const DeviceReading *d = &input->devices[i];

        WRITE_STR("{\n");
        WRITE_FMT("\"media\":\"%s\",\n", d->media);
        WRITE_FMT("\"meter\":\"%s\",\n", d->meter);
        WRITE_FMT("\"deviceId\":\"%s\",\n", d->device_id);
        WRITE_FMT("\"unit\":\"%s\",\n", d->unit);
        WRITE_STR("\"data\":[\n");

        for (size_t j = 0; j < d->data_count; j++) {
            const MeterDataPoint *p = &d->data[j];

            WRITE_FMT(
                "{\"timestamp\":\"%s\",\"meter_datetime\":\"%s\","
                "\"total_m3\":%.3f,\"status\":\"%s\"}",
                p->timestamp,
                p->meter_datetime,
                p->total_m3,
                p->status
            );

            if (j + 1 < d->data_count)
                WRITE_STR(",");

            WRITE_STR("\n");
        }

        WRITE_STR("]\n}");
        if (i + 1 < input->device_count)
            WRITE_STR(",");
        WRITE_STR("\n");
    }

    WRITE_STR("]\n}\n}]");

    if (bytes_written)
        *bytes_written = written;

    return JSON_OK;
}

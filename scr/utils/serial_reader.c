#include "serial_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>  // Para comunicación serial en Windows

static HANDLE serial_handle = INVALID_HANDLE_VALUE;

void serial_init(const char* port) {
    serial_handle = CreateFileA(
        port, GENERIC_READ | GENERIC_WRITE, 0, NULL,
        OPEN_EXISTING, 0, NULL
    );

    if (serial_handle == INVALID_HANDLE_VALUE) {
        printf("Error abriendo puerto serial %s\n", port);
        exit(1);
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    GetCommState(serial_handle, &dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;
    SetCommState(serial_handle, &dcbSerialParams);

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant   = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(serial_handle, &timeouts);
}

int serial_read_line(char* buffer, int max_len) {
    if (serial_handle == INVALID_HANDLE_VALUE) return 0;

    DWORD bytesRead;
    int i = 0;
    char c;

    while (i < max_len - 1) {
        ReadFile(serial_handle, &c, 1, &bytesRead, NULL);
        if (bytesRead > 0) {
            if (c == '\n') break;
            buffer[i++] = c;
        } else {
            Sleep(10);
        }
    }

    buffer[i] = '\0';
    return i > 0;
}

void process_scan_data(const char* line, PointCloud* cloud) {
    int layer, step;
    float angle, distance;

    if (sscanf(line, "%d,%d,%f,%f", &layer, &step, &angle, &distance) == 4) {
        pointcloud_add(cloud, layer, step, angle, distance);
    }
}

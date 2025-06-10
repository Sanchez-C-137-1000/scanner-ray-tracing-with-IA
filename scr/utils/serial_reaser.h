#ifndef SERIAL_READER_H
#define SERIAL_READER_H

#include "point_cloud.h"

void serial_init(const char* port);
int serial_read_line(char* buffer, int max_len);
void process_scan_data(const char* line, PointCloud* cloud);

#endif
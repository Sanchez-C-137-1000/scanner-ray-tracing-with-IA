#include "serial_reader.h"
#include <string.h>
#include <termios.h> // Para Linux
#include <unistd.h>
#include <fcntl.h>

static int serial_fd = -1;

void serial_init(const char* port) {
    // Implementación para Linux (ajustar para Windows)
    serial_fd = open(port, O_RDWR | O_NOCTTY);
    if(serial_fd < 0) {
        perror("Error abriendo puerto serial");
        exit(1);
    }
    
    struct termios tty;
    tcgetattr(serial_fd, &tty);
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_oflag &= ~OPOST;
    
    tcsetattr(serial_fd, TCSANOW, &tty);
}

int serial_read_line(char* buffer, int max_len) {
    if(serial_fd < 0) return 0;
    
    int n = 0;
    while(n < max_len - 1) {
        char c;
        if(read(serial_fd, &c, 1) > 0) {
            if(c == '\n') {
                buffer[n] = '\0';
                return 1;
            }
            buffer[n++] = c;
        } else {
            usleep(10000); // 10ms
        }
    }
    return 0;
}

void process_scan_data(const char* line, PointCloud* cloud) {
    int layer, step;
    float angle, distance;
    
    if(sscanf(line, "%d,%d,%f,%f", &layer, &step, &angle, &distance) == 4) {
        pointcloud_add(cloud, layer, step, angle, distance);
    }
}
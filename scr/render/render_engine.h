#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define STEPS_PER_REV 200
#define MAX_POINTS 4000 // STEPS_PER_REV * Z_STEPS_TOTAL

typedef struct {
    float x, y, z;
    float distance;
} Point3D;

typedef struct {
    Point3D points[MAX_POINTS];
    int count;
} PointCloud;

PointCloud cloud = {0};

void add_point(float distance, int theta_step, int z_step) {
    if(cloud.count >= MAX_POINTS) return;

    float theta = (theta_step * 2 * M_PI) / STEPS_PER_REV;
    float z = z_step * 0.5f; // Ajusta si tus pasos son diferentes

    cloud.points[cloud.count].x = distance * cosf(theta);
    cloud.points[cloud.count].y = distance * sinf(theta);
    cloud.points[cloud.count].z = z;
    cloud.points[cloud.count].distance = distance;

    cloud.count++;
}

void render_point_cloud() {
    printf("Renderizando %d puntos...\n", cloud.count);
    for(int i = 0; i < cloud.count; i++) {
        printf("Punto %d: (%.2f, %.2f, %.2f) Distancia: %.2f\n", i,
            cloud.points[i].x,
            cloud.points[i].y,
            cloud.points[i].z,
            cloud.points[i].distance);
    }
}

void process_serial_data(const char* data) {
    float distance;
    int theta, z;

    if(sscanf(data, "D:%f,T:%d,Z:%d", &distance, &theta, &z) == 3) {
        add_point(distance, theta, z);

        // Renderizar cada 100 puntos
        if(cloud.count % 100 == 0) {
            render_point_cloud();
        }
    }
}

#endif

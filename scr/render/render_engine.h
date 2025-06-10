#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
    float z = z_step * 0.5f; // 0.5mm por paso (ajustar)
    
    // Convertir coordenadas polares a cartesianas
    cloud.points[cloud.count].x = distance * cos(theta);
    cloud.points[cloud.count].y = distance * sin(theta);
    cloud.points[cloud.count].z = z;
    cloud.points[cloud.count].distance = distance;
    
    cloud.count++;
}

void render_point_cloud() {
    // Implementación simplificada de renderizado
    printf("Renderizando %d puntos...\n", cloud.count);
    
    // Aquí iría el código de tu motor de renderizado
    // que procesa la nube de puntos y genera la imagen
}

void process_serial_data(const char* data) {
    float distance;
    int theta, z;
    
    if(sscanf(data, "D:%f,T:%d,Z:%d", &distance, &theta, &z) == 3) {
        add_point(distance, theta, z);
        
        // Renderizar cada 100 puntos para visualización en tiempo real
        if(cloud.count % 100 == 0) {
            render_point_cloud();
        }
    }
}

#endif
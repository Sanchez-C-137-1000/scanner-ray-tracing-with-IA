#ifndef POINT_CLOUD_H
#define POINT_CLOUD_H

#include "vec3.h"

#define MAX_POINTS 4000 // 200 pasos * 20 niveles

typedef struct {
    Vec3 position;  // Coordenadas 3D
    float distance; // Distancia en cm
    int layer;      // Capa (1-20)
    int step;       // Paso (1-200)
    float angle;    // Ángulo en grados
} ScanPoint;

typedef struct {
    ScanPoint points[MAX_POINTS];
    int count;
} PointCloud;

void pointcloud_init(PointCloud* pc);
void pointcloud_add(PointCloud* pc, int layer, int step, float angle, float distance);
void pointcloud_clear(PointCloud* pc);

#endif

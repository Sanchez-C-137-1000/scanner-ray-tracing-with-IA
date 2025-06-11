#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// Estructura de un rayo
typedef struct {
    Vec3 origin;    // Origen del rayo
    Vec3 direction; // Dirección normalizada
} Ray;

// Devuelve el punto a lo largo del rayo a distancia 't'
static inline Vec3 ray_at(Ray ray, float t) {
    return vec3_add(ray.origin, vec3_mul(ray.direction, t));
}

#endif // RAY_H

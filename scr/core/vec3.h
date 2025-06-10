#ifndef VEC3_H
#define VEC3_H

#include <math.h>

// Estructura para un vector 3D
typedef struct {
    float x, y, z;
} Vec3;

// Suma de vectores
static inline Vec3 vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

// Resta de vectores
static inline Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

// Multiplicación por escalar
static inline Vec3 vec3_mul(Vec3 v, float s) {
    return (Vec3){v.x * s, v.y * s, v.z * s};
}

// Producto punto
static inline float vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Producto cruz
static inline Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return (Vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

// Longitud del vector
static inline float vec3_length(Vec3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Normalización
static inline Vec3 vec3_normalize(Vec3 v) {
    float l = vec3_length(v);
    if (l == 0.0f) return (Vec3){0.0f, 0.0f, 0.0f};
    return (Vec3){v.x / l, v.y / l, v.z / l};
}

#endif // VEC3_H
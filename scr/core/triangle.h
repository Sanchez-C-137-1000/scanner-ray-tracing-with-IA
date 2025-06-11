#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec3.h"

// Definición de un triángulo con tres vértices y su normal
typedef struct {
    Vec3 v0, v1, v2;
    Vec3 normal;
} Triangle;

// Calcula el centroide del triángulo
static inline Vec3 triangle_centroid(const Triangle* tri) {
    return vec3_mul(
        vec3_add(vec3_add(tri->v0, tri->v1), tri->v2),
        1.0f / 3.0f
    );
}

// Devuelve el i-ésimo borde del triángulo (como un vector)
static inline Vec3 triangle_edge(const Triangle* tri, int i) {
    switch(i) {
        case 0: return vec3_sub(tri->v1, tri->v0);
        case 1: return vec3_sub(tri->v2, tri->v1);
        case 2: return vec3_sub(tri->v0, tri->v2);
        default: return (Vec3){0.0f, 0.0f, 0.0f}; // Error: índice inválido
    }
}

#endif // TRIANGLE_H

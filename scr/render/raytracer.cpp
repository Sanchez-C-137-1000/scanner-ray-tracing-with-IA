// Codigo realizado por: javier triana sanchez
// Fecha de creacion: mayo 29 2025
// Descripcion:
//intersect(): Detecta colisiones rayo-triángulo.
// computeColor(): Aplica iluminación difusa y ambiental.
//render(): Lanza rayos por cada píxel y guarda los colores resultantes.

#include "raytracer.h"
#include <limits>

bool RayTracer::intersect(const Ray& ray, const Triangle& tri, float& t) {
    // Implementar Möller-Trumbore aquí
    // ...
}

Vec3 RayTracer::computeColor(const Vec3& point, const Vec3& normal) {
    Vec3 lightDir = Vec3{1, -1, -1}.normalize(); // Luz direccional
    float diffuse = std::max(normal.dot(lightDir), 0.0f);
    return Vec3{0.7f, 0.3f, 0.2f} * (0.1f + diffuse); // Ambient + Diffuse
}

void RayTracer::render(const std::vector<Triangle>& triangles, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Ray ray = { /* Calcular dirección del rayo */ };
            Vec3 color = traceRay(ray, triangles);
            // Guardar color en el píxel (x,y)
        }
    }
}
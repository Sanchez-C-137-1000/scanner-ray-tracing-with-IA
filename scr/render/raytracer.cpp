// Codigo realizado por: javier triana sanchez y Gabrielle Shekhina Velasquez Robles
// Fecha de creacion: mayo 29 2025
// Fechas de edición: junio 01 2025
// Descripcion:
//intersect(): Detecta colisiones rayo-triángulo.
// computeColor(): Aplica iluminación difusa y ambiental.
//render(): Lanza rayos por cada píxel y guarda los colores resultantes.

#include "raytracer.h"
#include <limits>


bool RayTracer::intersect(const Ray& ray, const Triangle& tri, float& t) {
    //Implementación del algoritmo Möller - Trumbore
    const float EPSILON = 1e-6;
    Vec3 e1 = tri.v1 - tri-v0;
    Vec3 e2 = tri.v2 - tri.v0;
    Vec3 h = ray.direction.cross(e2);
    float a = e1.dot(h);

    if(fabs(a) < EPSILON)
        return false; //El rayo es paralelo al triángulo
    float f = 1.0f/a;
    Vec3 s = ray.origin - tri.v0;
    float u = f * s.dot(h);

    if(u < 0.0f || u > 1.0f)
        return false;
    float tempT = f * e2.dot(q);

    if(tempT > EPSILON){
        t = tempT;
        return true; //Hay intersección
    }

    return false; //Hay una intersección "detrás" del rayo
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

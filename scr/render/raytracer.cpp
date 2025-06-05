// Codigo realizado por: javier triana sanchez
// Fecha de creacion: mayo 29 2025
// Descripcion:
//intersect(): Detecta colisiones rayo-triángulo.
// computeColor(): Aplica iluminación difusa y ambiental.
//render(): Lanza rayos por cada píxel y guarda los colores resultantes.

#include "raytracer.h"
#include <limits>

bool RayTracer::intersect(const Ray& ray, const Triangle& tri, float& t) {
     const float EPSILON = 0.0000001f;
    Vec3 edge1 = tri.v1 - tri.v0;
    Vec3 edge2 = tri.v2 - tri.v0;
    Vec3 h = ray.direction.cross(edge2);
    float a = edge1.dot(h);
    
    if (a > -EPSILON && a < EPSILON)
        return false; // Rayo paralelo al triángulo
        
    float f = 1.0f / a;
    Vec3 s = ray.origin - tri.v0;
    float u = f * s.dot(h);
    
    if (u < 0.0f || u > 1.0f)
        return false;
        
    Vec3 q = s.cross(edge1);
    float v = f * ray.direction.dot(q);
    
    if (v < 0.0f || u + v > 1.0f)
        return false;
        
    t = f * edge2.dot(q);
    return t > EPSILON;
    
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

Vec3 RayTracer::traceRay(const Ray& ray, const std::vector<Triangle>& triangles) {
    float closest_t = std::numeric_limits<float>::max();
    Vec3 closest_normal;
    bool hit = false;
    
    for (const auto& tri : triangles) {
        float t;
        if (intersect(ray, tri, t) && t < closest_t) {
            closest_t = t;
            closest_normal = tri.normal;
            hit = true;
        }
    }
    
    if (hit) {
        Vec3 hit_point = ray.at(closest_t);
        return computeColor(hit_point, closest_normal);
    }
    
    return Vec3{0.0f, 0.0f, 0.0f}; // Color de fondo (negro)
}
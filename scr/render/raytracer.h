// Codigo realizado por: javier triana sanchez
// Fecha de creacion: mayo 29 2025
// Descripcion:
//Implementar el algoritmo de trazado de rayos con iluminación básica.
#pragma once
#include "vec3.h"
#include "ray.h"
#include <vector>
#include "../loader/stl_loader.h"

class RayTracer {
public:
    void render(const std::vector<Triangle> & triangles, int width, int height);
private:
    Vec3 traceRay(const Ray& ray, const std::vector<Triangle >& triangles);
    bool intersect(const Ray& ray, const Triangle & tri, float& t);
    Vec3 computeColor(const Vec3& point, const Vec3& normal);
};
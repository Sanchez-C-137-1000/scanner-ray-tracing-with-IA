// Codigo realizado por: javier triana sanchez
// Fecha de creacion: mayo 29 2025
// Descripcion:
// Este codigo soporta todas las operaciones  necesarias para 
// la tecnica de ray tracing, incluyendo operaciones vectoriales
// como suma, resta, producto punto y cruz, normalización.
// Se usa para calcular la interacciones, iluminacion y direccion de rayos.
#pragma once
#include <cmath>

struct Vec3 {
    float x, y, z;

    // Operaciones básicas
    Vec3 operator+(const Vec3& v) const { return {x+v.x, y+v.y, z+v.z}; }
    Vec3 operator-(const Vec3& v) const { return {x-v.x, y-v.y, z-v.z}; }
    Vec3 operator*(float s) const { return {x*s, y*s, z*s}; }

    // Producto punto y cruz
    float dot(const Vec3& v) const { return x*v.x + y*v.y + z*v.z; }
    Vec3 cross(const Vec3& v) const {
        return {
            y*v.z - z*v.y,
            z*v.x - x*v.z,
            x*v.y - y*v.x
        };
    }

    // Normalización
    float length() const { return std::sqrt(x*x + y*y + z*z); }
    Vec3 normalize() const { float l = length(); return {x/l, y/l, z/l}; }
};
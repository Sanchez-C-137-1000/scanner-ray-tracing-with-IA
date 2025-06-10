// Codigo realizado por: javier triana sanchez
// Fecha de creacion: 10 de junio 2025

#pragma once
#include "vec3.h"

struct Triangle {
    Vec3 v0, v1, v2;
    Vec3 normal;
    
    
    Vec3 centroid() const { return (v0 + v1 + v2) * (1.0f/3.0f); }
    Vec3 edge(int i) const {
        switch(i) {
            case 0: return v1 - v0;
            case 1: return v2 - v1;
            case 2: return v0 - v2;
            default: return Vec3{0,0,0};
        }
    }
};
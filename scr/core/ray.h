// Codigo realizado por: javier triana sanchez
// Fecha de creacion: mayo 29 2025
// Edición: Junio 9 2025
// Por: Shekhina Velasquez
// Descripcion:
// En este codigo describe la estructura de un rayo y su interaccion con la escena
//Este se define por su origen y direccion
// at(t) devuelve el punto a lo largo del rayo, esto es util para las iteracciones 

#pragma once
#include "vec3.h"

struct Ray {
    Vec3 origin;    // Origen del rayo (ej: posición de la cámara)
    Vec3 direction; // Dirección (normalizada)

    // Calcular punto en el rayo a distancia 't'
    Vec3 at(float t) const {
        return origin + direction * t;
    }
};

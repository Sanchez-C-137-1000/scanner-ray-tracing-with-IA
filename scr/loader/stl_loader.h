// Codigo realizado por: javier triana sanchez
// Fecha de creacion: mayo 29 2025
// Edición: Junio 9 2025
// Por: Shekhina Velasquez
// Descripcion:
//Leer archivos STL binarios y convertirlos en triángulos.

#pragma once
#include <vector>
#include "vec3.h"
#include <string>

struct Triangle {
    Vec3 v0, v1, v2;
    Vec3 normal;
};

namespace STLLoader {
    std::vector<Triangle> load(const std::string & filepath);
}

// Codigo realizado por: javier triana sanchez
// Fecha de creacion: mayo 29 2025
// Descripcion:
//Leer archivos STL binarios y convertirlos en triángulos.
// Lee el formato binario de STL (80 bytes de cabecera + lista de triángulos).
// Cada triángulo contiene 3 vértices y una normal.
// Devuelve un std::vector<Triangle> para usar en el renderizado.

#include "stl_loader.h"
#include <fstream>
#include <cstdint>

std::vector<Triangle> STLLoader::load(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    std::vector<Triangle> triangles;

    char header[80];
    file.read(header, 80); // Ignorar cabecera

    uint32_t numTriangles;
    file.read(reinterpret_cast<char*>(&numTriangles), 4);

    for (uint32_t i = 0; i < numTriangles; ++i) {
        Triangle tri;
        file.read(reinterpret_cast<char*>(&tri.normal), 12);
        file.read(reinterpret_cast<char*>(&tri.v0), 12);
        file.read(reinterpret_cast<char*>(&tri.v1), 12);
        file.read(reinterpret_cast<char*>(&tri.v2), 12);
        file.ignore(2); // Atributos no usados
        triangles.push_back(tri);
    }

    return triangles;
}
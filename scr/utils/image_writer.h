//Edición: 9/06/2025
//Por: Shekhina Velasquez
#pragma once
#include "vec3.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm> // para std::min y std::max

// Función clamp compatible con C++11
inline float clamp(float value, float minVal, float maxVal) {
    return std::max(minVal, std::min(value, maxVal));
}

class ImageWriter {
public:
    static void writePPM(const std::string& filename, 
                         const std::vector<Vec3>& image, 
                         int width, int height) {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Error al abrir archivo: " << filename << std::endl;
            return;
        }

        file << "P3\n" << width << " " << height << "\n255\n";
        
        for (const auto& pixel : image) {
            int r = static_cast<int>(255.99f * clamp(pixel.x, 0.0f, 1.0f));
            int g = static_cast<int>(255.99f * clamp(pixel.y, 0.0f, 1.0f));
            int b = static_cast<int>(255.99f * clamp(pixel.z, 0.0f, 1.0f));
            file << r << " " << g << " " << b << "\n";
        }
    }
};

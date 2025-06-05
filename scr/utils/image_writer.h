#pragma once
#include "vec3.h"
#include <vector>
#include <fstream>

class ImageWriter {
public:
    static void writePPM(const std::string& filename, 
                        const std::vector<Vec3>& image, 
                        int width, int height) {
        std::ofstream file(filename);
        file << "P3\n" << width << " " << height << "\n255\n";
        
        for (const auto& pixel : image) {
            int r = static_cast<int>(255.99f * pixel.x);
            int g = static_cast<int>(255.99f * pixel.y);
            int b = static_cast<int>(255.99f * pixel.z);
            file << r << " " << g << " " << b << "\n";
        }
    }
};
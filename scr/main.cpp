#include <iostream>
#include "render/raytracer.h"
#include "loader/stl_loader.h"
#include "utils/timer.h"
#include "utils/image_writer.h"

int main() {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    
    // Cargar modelo
    Timer timer;
    std::vector<Triangle> triangles = STLLoader::load("model.stl");
    std::cout << "Model loaded in " << timer.elapsed() << " ms" << std::endl;
    
    // Renderizar
    RayTracer tracer;
    timer.reset();
    tracer.render(triangles, WIDTH, HEIGHT);
    std::cout << "Rendering completed in " << timer.elapsed() << " ms" << std::endl;
    
    return 0;
}
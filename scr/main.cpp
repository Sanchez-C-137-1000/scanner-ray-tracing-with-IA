#include <iostream>
#include "render/raytracer.h"
#include "loader/stl_loader.h"
#include "utils/timer.h"            
#include "utils/image_writer.h"     // Para guardar la imagen renderizada

int main() {
    const int WIDTH = 800;
    const int HEIGHT = 600;

    // Temporizador para carga de modelo
    Timer timer;
    timer.start();
    
    // Cargar modelo STL
    std::vector<Triangle> triangles = STLLoader::load("model.stl");
    std::cout << "Model loaded in " << timer.elapsed() << " ms" << std::endl;

    // Crear raytracer y buffer de imagen
    RayTracer tracer;
    std::vector<Vec3> image(WIDTH * HEIGHT);

    // Temporizador para renderizado
    timer.start();
    tracer.render(triangles, WIDTH, HEIGHT, image);
    std::cout << "Rendering completed in " << timer.elapsed() << " ms" << std::endl;

    // Guardar imagen
    ImageWriter::writePPM("output.ppm", image, WIDTH, HEIGHT);
    std::cout << "Image saved to output.ppm" << std::endl;

    return 0;
}

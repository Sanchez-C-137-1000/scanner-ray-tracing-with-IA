#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "stl_loader.h"
#include "raytracer.h"
#include "timer.h"
#include "image_writer.h"

int main() {
    const int WIDTH = 800;
    const int HEIGHT = 600;

    Timer timer;
    timer_start(&timer);
    
    TriangleArray model = stl_load("model.stl");
    printf("Model loaded in %.2f ms\n", timer_elapsed(&timer));

    Vec3* image = (Vec3*)malloc(WIDTH * HEIGHT * sizeof(Vec3));
    if (!image) {
        fprintf(stderr, "Error allocating image buffer\n");
        stl_free(&model);
        return 1;
    }

    timer_start(&timer);
    raytracer_render(model.triangles, model.count, WIDTH, HEIGHT, image);
    printf("Rendering completed in %.2f ms\n", timer_elapsed(&timer));

    image_write_ppm("output.ppm", image, WIDTH, HEIGHT);
    printf("Image saved to output.ppm\n");

    free(image);
    stl_free(&model);
    return 0;
}

#endif
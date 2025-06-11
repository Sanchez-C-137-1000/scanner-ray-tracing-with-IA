#ifndef STL_LOADER_H
#define STL_LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "vec3.h"

typedef struct {
    Vec3 v0, v1, v2;
    Vec3 normal;
} Triangle;

typedef struct {
    Triangle* triangles;
    size_t count;
} TriangleArray;

TriangleArray stl_load(const char* filepath) {
    FILE* file = fopen(filepath, "rb");
    TriangleArray result = {NULL, 0};
    
    if (!file) {
        fprintf(stderr, "Error opening STL file: %s\n", filepath);
        return result;
    }

    char header[80];
    fread(header, 1, 80, file);

    uint32_t numTriangles;
    fread(&numTriangles, sizeof(uint32_t), 1, file);

    result.triangles = (Triangle*)malloc(numTriangles * sizeof(Triangle));
    if (!result.triangles) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return (TriangleArray){NULL, 0};
    }
    result.count = numTriangles;

    for (uint32_t i = 0; i < numTriangles; ++i) {
        fread(&result.triangles[i].normal, sizeof(Vec3), 1, file);
        fread(&result.triangles[i].v0, sizeof(Vec3), 1, file);
        fread(&result.triangles[i].v1, sizeof(Vec3), 1, file);
        fread(&result.triangles[i].v2, sizeof(Vec3), 1, file);
        fseek(file, 2, SEEK_CUR); // Skip attributes
    }

    fclose(file);
    return result;
}

void stl_free(TriangleArray* array) {
    free(array->triangles);
    array->triangles = NULL;
    array->count = 0;
}
#endif

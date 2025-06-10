#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <float.h>
#include <math.h>
#include "camera.h"
#include "triangle.h"

static int intersect(Ray ray, Triangle tri, float* t) {
    const float EPSILON = 1e-7f;
    Vec3 edge1 = vec3_sub(tri.v1, tri.v0);
    Vec3 edge2 = vec3_sub(tri.v2, tri.v0);
    Vec3 h = vec3_cross(ray.direction, edge2);
    float a = vec3_dot(edge1, h);
    
    if (a > -EPSILON && a < EPSILON)
        return 0;
        
    float f = 1.0f / a;
    Vec3 s = vec3_sub(ray.origin, tri.v0);
    float u = f * vec3_dot(s, h);
    
    if (u < 0.0f || u > 1.0f)
        return 0;
        
    Vec3 q = vec3_cross(s, edge1);
    float v = f * vec3_dot(ray.direction, q);
    
    if (v < 0.0f || u + v > 1.0f)
        return 0;
        
    *t = f * vec3_dot(edge2, q);
    return *t > EPSILON;
}

static Vec3 compute_color(Vec3 point, Vec3 normal) {
    Vec3 lightDir = vec3_normalize((Vec3){1, -1, -1});
    float diffuse = fmaxf(vec3_dot(normal, lightDir), 0.0f);
    return vec3_mul((Vec3){0.7f, 0.3f, 0.2f}, (0.1f + diffuse));
}

static Vec3 trace_ray(Ray ray, const Triangle* triangles, size_t numTriangles) {
    float closest_t = FLT_MAX;
    Vec3 closest_normal;
    int hit = 0;
    
    for (size_t i = 0; i < numTriangles; ++i) {
        float t;
        if (intersect(ray, triangles[i], &t) && t < closest_t) {
            closest_t = t;
            closest_normal = triangles[i].normal;
            hit = 1;
        }
    }
    
    if (hit) {
        Vec3 hit_point = ray_at(ray, closest_t);
        return compute_color(hit_point, closest_normal);
    }
    
    return (Vec3){0.0f, 0.0f, 0.0f};
}

void raytracer_render(const Triangle* triangles, size_t numTriangles, 
                     int width, int height, Vec3* image) {
    Camera cam;
    camera_init(&cam, (Vec3){0, 0, 5}, (Vec3){0, 0, 0}, (Vec3){0, 1, 0}, 
               45.0f, (float)width / height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float u = (float)x / (width - 1);
            float v = (float)y / (height - 1);
            Ray ray = camera_get_ray(&cam, u, v);
            image[y * width + x] = trace_ray(ray, triangles, numTriangles);
        }
    }
}

#endif
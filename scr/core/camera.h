#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include "vec3.h"
#include "ray.h"

typedef struct {
    Vec3 position;
    Vec3 lowerLeft;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 right;
    Vec3 up;
    Vec3 forward;
} Camera;

// Inicializa una cámara
static inline void camera_init(Camera* cam, Vec3 position, Vec3 lookAt, Vec3 upVec, float fov, float aspectRatio) {
    cam->position = position;

    cam->forward = vec3_normalize(vec3_sub(lookAt, position));
    cam->right = vec3_normalize(vec3_cross(cam->forward, upVec));
    cam->up = vec3_normalize(vec3_cross(cam->right, cam->forward));

    float halfHeight = tanf(fov * 0.5f * (3.14159265f / 180.0f));
    float halfWidth = aspectRatio * halfHeight;

    cam->lowerLeft = vec3_sub(
                        vec3_sub(
                            vec3_add(cam->position, cam->forward),
                            vec3_mul(cam->right, halfWidth)),
                        vec3_mul(cam->up, halfHeight)
                    );

    cam->horizontal = vec3_mul(cam->right, 2.0f * halfWidth);
    cam->vertical = vec3_mul(cam->up, 2.0f * halfHeight);
}

// Genera un rayo a partir de la cámara
static inline Ray camera_get_ray(Camera* cam, float u, float v) {
    Vec3 direction = vec3_normalize(
        vec3_sub(
            vec3_add(
                vec3_add(cam->lowerLeft, vec3_mul(cam->horizontal, u)),
                vec3_mul(cam->vertical, v)),
            cam->position
        )
    );
    return (Ray){cam->position, direction};
}

#endif // CAMERA_H

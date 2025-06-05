#pragma once
#include "ray.h"

class Camera {
public:
    Camera(Vec3 position, Vec3 lookAt, Vec3 up, float fov, float aspectRatio)
        : position(position) {
        forward = (lookAt - position).normalize();
        right = forward.cross(up).normalize();
        up = right.cross(forward).normalize();
        
        float halfHeight = tan(fov * 0.5f * (3.14159265f / 180.0f));
        float halfWidth = aspectRatio * halfHeight;
        
        lowerLeft = position + forward - right * halfWidth - up * halfHeight;
        horizontal = right * (2.0f * halfWidth);
        vertical = up * (2.0f * halfHeight);
    }
    
    Ray getRay(float u, float v) const {
        return Ray{position, (lowerLeft + horizontal*u + vertical*v - position).normalize()};
    }
    
private:
    Vec3 position;
    Vec3 lowerLeft;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 right, up, forward;
};
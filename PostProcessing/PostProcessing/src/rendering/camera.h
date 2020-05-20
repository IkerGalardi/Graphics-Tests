#ifndef CAMERA_H
#define CAMERA_H

#include "cglm.h"

typedef struct orthographic_camera {
    float zoom;
    vec2 resolution;

    mat4 view;
} orthographic_camera_t;

orthographic_camera_t create_orthographic_camera(vec2 resolution, float zoom);
void zoom_orthographic_camera(orthographic_camera_t* cam, float zoom);

#endif // CAMERA_H
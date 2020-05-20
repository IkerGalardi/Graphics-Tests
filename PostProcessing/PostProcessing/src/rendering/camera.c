#include "camera.h"

orthographic_camera_t create_orthographic_camera(vec2 resolution, float zoom) {
    orthographic_camera_t cam;
    
    cam.zoom = zoom;
    float aspect_ratio = resolution[0] / resolution[1];
    glm_ortho(-zoom * aspect_ratio, 
               zoom * aspect_ratio,
              -zoom * aspect_ratio, 
               zoom * aspect_ratio, 
              -1, 
               1, 
               cam.view);

    glm_vec2(resolution, cam.resolution);
    return cam;
}

void zoom_orthographic_camera(orthographic_camera_t* cam, float zoom) {
    cam->zoom = zoom;
    float aspect_ratio = cam->resolution[0] / cam->resolution[1];
    glm_ortho(-zoom * aspect_ratio, 
               zoom * aspect_ratio,
              -zoom * aspect_ratio, 
               zoom * aspect_ratio, 
              -1, 
               1, 
               cam->view);
}
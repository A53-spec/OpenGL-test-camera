/*
#include "camera.h"
#include "include/glew.h"
#include "include/glfw3.h"

#define COEFF_DEGTORAD 0.01745329251

void movcam(double x, double y, camera* cam){
    float xoff = x-cam->x;
    float yoff = cam->y-y;
     
    cam->x = x;
    cam->y = y;

    float sensitivity = 0.5f;
    xoff *=sensitivity;
    yoff *=sensitivity;

    cam->yaw +=xoff;
    cam->pitch += yoff;

    if(cam->pitch >90)cam->pitch = 90;
    if(cam->pitch <-90)cam->pitch = -90;

    cam->position.x = cos(cam->yaw *COEFF_DEGTORAD) * cos(cam->pitch * COEFF_DEGTORAD);
    cam->position.y =  sin(cam->pitch *COEFF_DEGTORAD);
    cam->position.z = sin(cam->yaw * COEFF_DEGTORAD) * cos(cam->pitch * COEFF_DEGTORAD);      
}*/
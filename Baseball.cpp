//
// Created by Yorick Rommers on 5/23/16.
//

#include <cmath>
#include "Baseball.h"

#define SPEED 0.1

float Baseball::toRadian(float degree) {
    return (float) ((degree / 180) * M_PI);
}

void Baseball::update(float deltatime) {
//    ObjModel::update();
    ypos += (sin(toRadian(xrot))) * SPEED * deltatime;
    zpos += cos(toRadian(yrot))* SPEED * deltatime;
    xpos += (sin(toRadian(yrot))) * SPEED * deltatime;
    if (time_alive_counter > 5000) {
        //remove object.
        Singleton::Instance()->DeleteModel(this);
        return;
    }
    time_alive_counter = time_alive_counter + deltatime * 5;
//    printf("Counter is %f\n", time_alive_counter);
}

Baseball::Baseball(Singleton * s) : ObjModel("models/baseball/Mooiebal.obj", s) {

}






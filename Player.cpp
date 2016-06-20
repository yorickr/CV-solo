//
// Created by Yorick Rommers on 2016/06/18.
//

#include "Player.h"

Player::Player() : ObjModel("", Singleton::Instance()) {
    //no model
    boundingSpheres.clear();
    Player::InitBoundingSpheres();
}

void Player::InitBoundingSpheres() {
    boundingSpheres.push_back(new Sphere(xpos, ypos, zpos, RADIUS));
}

void Player::CalcBoundingSpheres() {
    for (auto &sphere : boundingSpheres) {
        sphere->xpos = sphere->x + this->xpos;
        sphere->ypos = sphere->y + this->ypos;
        sphere->zpos = sphere->z + this->zpos;
    }
}

void Player::draw() {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos);
    glColor3ub(0, 255, 255);
    glutWireSphere(RADIUS, 20, 20); //Radius, polycount, polycount
    glPopMatrix();

//    glPushMatrix();
//    for (auto &sphere : boundingSpheres) {
//        glTranslatef(sphere->xpos, sphere->ypos, sphere->zpos);
//        glColor3ub(0, 255, 255);
//        glutWireSphere(sphere->radius, 50, 50);
//    }
//    glPopMatrix();
}








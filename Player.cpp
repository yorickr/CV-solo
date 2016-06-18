//
// Created by Yorick Rommers on 2016/06/18.
//

#include "Player.h"

Player::Player() : ObjModel("", Singleton::Instance()) {
    //no model

}

void Player::InitBoundingSpheres() {
    boundingSpheres.push_back(new Sphere(xpos, ypos, zpos, RADIUS));
}

void Player::CalcBoundingSpheres() {
    ObjModel::CalcBoundingSpheres();
}

void Player::draw() {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos);
    glColor3ub(0, 255, 255);
    glutWireSphere(RADIUS, 20, 20); //Radius, polycount, polycount
    glPopMatrix();
}








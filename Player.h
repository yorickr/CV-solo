//
// Created by Yorick Rommers on 2016/06/18.
//

#ifndef CV_SOLO_PLAYER_H
#define CV_SOLO_PLAYER_H


#include "ObjModel.h"

#define RADIUS 5

class Player : public ObjModel{

public:
    Player();

    virtual void draw() override;

    virtual void CalcBoundingSpheres() override;

    virtual void InitBoundingSpheres() override ;

};


#endif //CV_SOLO_PLAYER_H

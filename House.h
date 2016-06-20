//
// Created by Yorick Rommers on 2016/06/20.
//

#ifndef CV_SOLO_HOUSE_H
#define CV_SOLO_HOUSE_H


#include "ObjModel.h"

class House : public ObjModel{

public:
    House();
    virtual void CalcBoundingSpheres() override;

    virtual void InitBoundingSpheres() override ;
};


#endif //CV_SOLO_HOUSE_H

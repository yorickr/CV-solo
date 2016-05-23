//
// Created by Yorick Rommers on 5/23/16.
//

#ifndef CV_SOLO_BASEBALL_H
#define CV_SOLO_BASEBALL_H


#include "ObjModel.h"

class Baseball : public ObjModel {
public:
    Baseball();

    virtual void update() override;

};


#endif //CV_SOLO_BASEBALL_H

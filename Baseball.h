//
// Created by Yorick Rommers on 5/23/16.
//

#ifndef CV_SOLO_BASEBALL_H
#define CV_SOLO_BASEBALL_H

#include "ObjModel.h"

class Baseball : public ObjModel {
public:
    Baseball(Singleton *s);
    float toRadian(float degree);
    virtual void update(float deltatime) override;
    float time_alive_counter = 0;
};


#endif //CV_SOLO_BASEBALL_H

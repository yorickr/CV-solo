//
// Created by Yorick Rommers on 2016/06/08.
//


#ifndef SHIRO_BOUGYO_HEADTRACKING_H
#define SHIRO_BOUGYO_HEADTRACKING_H

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <unistd.h>

class HeadTracking {
public:
    HeadTracking();

    bool running = false;
    ~HeadTracking();
    void cameraThreadFunc();
    void initThread();
};


#endif //SHIRO_BOUGYO_HEADTRACKING_H

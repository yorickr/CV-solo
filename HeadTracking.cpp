//
// Created by Yorick Rommers on 2016/06/08.
//

#include <zconf.h>
#include <thread>
#include "HeadTracking.h"
#include "Player.h"

using namespace cv;

/* Function Headers */
std::vector<Point> detectFace(Mat frame);

CascadeClassifier face_cascade;
unsigned int times_updated = 0;


HeadTracking::~HeadTracking() {

}

HeadTracking::HeadTracking() {
}


// Detect face
std::vector<Point> detectFace(Mat frame) {

    std::vector<Point> retFaces;
    std::vector<Rect> faces;
    Mat frame_gray;
    int minNeighbors = 2;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);   // Convert to gray
    equalizeHist(frame_gray, frame_gray);          // Equalize histogram

    // Detect face with open source cascade
    face_cascade.detectMultiScale(frame_gray, faces,
                                  1.1, minNeighbors,
                                  0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    for (size_t i = 0; i < faces.size(); i++) {
        Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        retFaces.push_back(center);
    }
    return retFaces;
}

int calcHeadPos(int pos, int camwidth) {
    return (int) ((float)((float)pos / (float)camwidth) * 60.0f - 30.0f);
}

void HeadTracking::cameraThreadFunc() {

    VideoCapture cap(0); // capture from default camera
    Mat frame;
    int camWidth = 640, camHeight = 480;
    cap.set(CV_CAP_PROP_FRAME_WIDTH, camWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, camHeight);

    face_cascade.load("xml/haarcascade_frontalface_alt.xml"); // load face classifiers
//    eyes_cascade.load("Project/opencv_xml/haarcascade_eye_tree_eyeglasses.xml"); // load eye classifiers

    std::vector<Point> points;
    while (cap.read(frame)) {
        if (!frame.empty()) {
            points = detectFace(frame);
            for (auto &m:points) {
                if(running){
                    Player *p = Singleton::Instance()->p;
//                    printf("Settings xpos to %d\n", calcHeadPos(m.x,camWidth));
                    p->xpos = calcHeadPos(m.x,camWidth);
                }
            }
            usleep(1000 * (1000 / 100));
        }
    }
}

void HeadTracking::initThread() {
    std::thread cameraThread(&HeadTracking::cameraThreadFunc, this); //Camerathread
    cameraThread.detach();
}








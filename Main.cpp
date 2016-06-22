#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <ApplicationServices/ApplicationServices.h>
#include <cstdlib>
#include <iostream>

#include "Camera.h"
#include "ObjModel.h"
#include "Baseball.h"
#include "Player.h"
#include "HeadTracking.h"
#include "House.h"


bool keys[255];
Camera camera;

int oldTimeSinceStart = 0;
#define DELTATIME_MODIFIER 10

HeadTracking *h;

int timeSinceLastBall = 0;

void onDisplay() {
    glClearColor(0.6f, 0.6f, 1, 1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, (float) camera.width / camera.height, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);


    glLoadIdentity();

    //load bow
//	gameManager.preDraw();


    glRotatef(camera.rotX, 1, 0, 0);
    glRotatef(camera.rotY, 0, 1, 0);
    glTranslatef(camera.posX, camera.posY, camera.posZ);
//	glRotatef(camera.rotZ, 0, 0, 1);

    glColor3f(1.0f, 1.0f, 1.0f);
//	gameManager.Draw();
    //Draw objects here
    for (auto &model : Singleton::Instance()->models) {
        model->draw();
    }


    glFlush();
    glutSwapBuffers();
}

void shootBall(float xpos, float ypos, float zpos, float xrot, float yrot){
    ObjModel *obj = new Baseball(Singleton::Instance());
//        obj->scale = 50;
    obj->xpos = -xpos;
    obj->ypos = -ypos;
    obj->zpos = -zpos;
    obj->yrot = -yrot - 180;
    if (obj->yrot > 90 || obj->yrot < -90)
        obj->xrot = -xrot;
    else
        obj->xrot = xrot;

    printf("Ball pos and such\n %f %f %f %f %f", obj->xpos, obj->ypos, obj->zpos, obj->xrot, obj->yrot);
    Singleton::Instance()->models.push_back(obj);
}

void onIdle() {
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    if (keys['a']) camera.posX++;
    if (keys['d']) camera.posX--;
    if (keys['w']) camera.posZ++;
    if (keys['s']) camera.posZ--;
    if(keys['c']) h->running = false;
    if(keys['v']) h->running = true;
    Player* p = Singleton::Instance()->p;
    if(keys['g']) {
        printf("xpos %f\n", p->xpos);
        if (p->xpos > -30 && p->xpos <= 30) {
            //move backward
            p->xpos--;
        }
    }
    if(keys['h']) {
        printf("xpos %f\n", p->xpos);
        if (p->xpos >= -30 && p->xpos < 30) {
            //move backward
            p->xpos++;
        }
    }

    float deltatime = (timeSinceStart - oldTimeSinceStart) / DELTATIME_MODIFIER;

//    printf("-----SOF----\n");
    bool collides = false;
    for (auto &m : Singleton::Instance()->models) {
        for (auto &n : Singleton::Instance()->models) {
            if (m != n && m->CollidesWith(n)) {
//                printf("M colliding with n? %d \n", m != n && m->CollidesWith(n));
                collides = true;
            }
        }
        if (!collides) {
            m->update(deltatime);
        }
        collides = false;
//        printf("-----------\n");
    }
//    printf("-----EOF----\n");


    bool playercollides = false;
    for (auto &m : Singleton::Instance()->models) {
        if (m != Singleton::Instance()->p && m->CollidesWith(Singleton::Instance()->p)) {
            playercollides = true;
        }
//        printf("Collides wit player? %d\n", playercollides);
        if (playercollides) {
            //End of game
            printf("You lose ;)\n");
            exit(0);
        }
        playercollides = false;
    }

    //Spawn balls

    if(timeSinceStart - timeSinceLastBall >5000) {
        std::srand((unsigned int) glutGet(GLUT_ELAPSED_TIME));
        int rand = -1 * ((std::rand() % 60) - 30);
        shootBall(rand, 0, 0, 0, 0);

        timeSinceLastBall = glutGet(GLUT_ELAPSED_TIME);
    }

    oldTimeSinceStart = timeSinceStart;
    glutPostRedisplay();
}

void onKeyboard(unsigned char key, int, int) {
    switch (key) {
        case 27:             // ESCAPE key
            exit(0);
        case '[':
            break;
        case ']':
            break;
        default:
            //just to please CLion.
            break;
    }
    keys[key] = true;
}

void onKeyboardUp(unsigned char key, int, int) {
    keys[key] = false;
}

void mousePassiveMotion(int x, int y) {

    int dx = x - camera.width / 2;
    int dy = y - camera.height / 2;
    if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400) {
        camera.rotX += dy / 10.0f;
        if (camera.rotX > 30) {
            camera.rotX = 30;
        } else if (camera.rotX < -30) {
            camera.rotX = -30;
        }

        camera.rotY += dx / 10.0f;
        glutWarpPointer(camera.width / 2, camera.height / 2);
    }
}

void mouseFunc(int button, int state, int x, int y) {
    printf("Received %d %d \n", button, state);
    if (button == 0 && state == 1) {
        //Throw ball
        shootBall(camera.posX, camera.posY, camera.posZ, camera.rotX, camera.rotY);
    }
}

void init() {

    ObjModel *obj1 = new House();
    obj1->zpos = -100;
    obj1->ypos = -20;
    obj1->yrot = 180;

    ObjModel *player = new Player();
    player->xpos = 0;
    player->ypos = 0;
    player->zpos = -30;

    Singleton::Instance()->models.push_back(obj1);
    Singleton::Instance()->models.push_back(player);
    Singleton::Instance()->p = dynamic_cast<Player *>(player);

    h = new HeadTracking();
    h->initThread();

//    obj1 = new Baseball();
//    obj1->scale = 50;
//    Singleton::Instance()->models.push_back(obj1);
}


int main(int argc, char *argv[]) {

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInit(&argc, argv);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Shiro Bougyo");

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    GLfloat LightAmbient[] = {1.5f, 1.5f, 1.5f, 2.0f};
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    //Fog
    glEnable(GL_FOG);
    float FogCol[3] = {0.8f, 0.8f, 0.8f};
    glFogfv(GL_FOG_COLOR, FogCol);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 1.f);
    glFogf(GL_FOG_END, 150.f);
    glFogf(GL_FOG_DENSITY, 2.f);
    glHint(GL_FOG_HINT, GL_NICEST);

//	glutFullScreen();
    glutSetCursor(GLUT_CURSOR_NONE);
    CGSetLocalEventsSuppressionInterval(0.0);
    glutIdleFunc(onIdle);
    glutDisplayFunc(onDisplay);
    glutReshapeFunc([](int w, int h) {
        camera.width = w;
        camera.height = h;
        glViewport(0, 0, w, h);
    });
    glutKeyboardFunc(onKeyboard);
    glutKeyboardUpFunc(onKeyboardUp);
    glutPassiveMotionFunc(mousePassiveMotion);
    glutMouseFunc(mouseFunc);

    glutWarpPointer(camera.width / 2, camera.height / 2);

    memset(keys, 0, sizeof(keys));

    init();

    glutMainLoop();
}

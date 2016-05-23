#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <ApplicationServices/ApplicationServices.h>
#include <cstdlib>
#include <iostream>
#include <cmath>

#include "Camera.h"
#include "ObjModel.h"


bool keys[255];
Camera camera;

vector<ObjModel*> models;

void onDisplay() {
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (float)camera.width / camera.height, 0.1, 100);

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

	for(auto & model : models) {
		model->draw();
	}


	glFlush();
	glutSwapBuffers();
}

void onIdle() {

	glutPostRedisplay();
}

void onTimer(int id) {
//	gameManager.Update();

	if (keys['a']) camera.posX++;
	if (keys['d']) camera.posX--;
	if (keys['w']) camera.posZ++;
	if (keys['s']) camera.posZ--;

	glutTimerFunc(1000 / 60, onTimer, 1);
}

void onKeyboard(unsigned char key, int, int) {
	switch (key)
	{
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
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		camera.rotX += dy / 10.0f;
		if(camera.rotX > 30){
			camera.rotX = 30;
		}else if(camera.rotX < -30){
			camera.rotX = -30;
		}

		camera.rotY += dx / 10.0f;
		glutWarpPointer(camera.width / 2, camera.height / 2);
	}
}

void mouseFunc(int button, int state, int x, int y) {
    printf("Received %d %d \n", button, state);
    if (button == 0 && state == 1) {
        //Tell gamestatemanager to shoot arrow

    }
}

void init(){
	ObjModel *obj1 = new ObjModel("models/cottage/scco.obj");
	obj1->zpos = -100;
	obj1->ypos = -20;
	obj1->yrot = 180;
	models.push_back(obj1);
}

void turnOnFog(){
	float FogCol[3]={0.8f,0.8f,0.8f};
	glFogfv(GL_FOG_COLOR,FogCol);
	glFogi(GL_FOG_MODE, GL_LINEAR);

}

int main(int argc, char* argv[]) {

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Shiro Bougyo");

	glEnable(GL_DEPTH_TEST);
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);
	CGSetLocalEventsSuppressionInterval(0.0);
	glutIdleFunc(onIdle);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc([](int w, int h) { camera.width = w; camera.height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(onKeyboard);
	glutTimerFunc(1000 / 60, onTimer, 1);
	glutKeyboardUpFunc(onKeyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);
    glutMouseFunc(mouseFunc);

	glutWarpPointer(camera.width / 2, camera.height / 2);

	memset(keys, 0, sizeof(keys));

	init();
	turnOnFog();

	glutMainLoop();
}

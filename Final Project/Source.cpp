#define Chess_CPP_
#include "util.h"
#include "CImg.h"
#include <iostream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
#include <cstdlib>
#include <ctime>
#include <fstream>

int is_fullscreen = 0;
int pos_x = 100;
int pos_y = 100;

void display(void) {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    {
        glColor3f(1, 0, 0);
        glVertex2f(0, 0);

        glColor3f(0, 1, 0);
        glVertex2f(.5, 0);

        glColor3f(0, 0, 1);
        glVertex2f(.5, .5);
    }
    glEnd();

    glutSwapBuffers();
}

void idle(void) {
    if (!is_fullscreen) {
        pos_x = glutGet(GLUT_WINDOW_X);
        pos_y = glutGet(GLUT_WINDOW_Y);
    }
}

void toggle_fullscreen() {
    if (is_fullscreen) {
        glutReshapeWindow(1000, 625);
        glutPositionWindow(pos_x, pos_y);
    }
    else {
        glutFullScreen();
    }
    is_fullscreen = !is_fullscreen;
}

void reshape(int x, int y) {
    printf("Resizing to... %d, %d\n", x, y);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'f':
        toggle_fullscreen();
        break;
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("My Game");
    glutReshapeWindow(900, 600);
    glutPositionWindow(pos_x, pos_y);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
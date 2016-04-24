#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <GL/glut.h>
#include "math.h"

class Graphics{
private:
    int argc;
    char** argv;

    float width, height;
    
    static void drawWorld();
    static void initLight();
    static void timerHandler(int v);
    static void changeWindowSize(GLsizei w, GLsizei h);

    static void defineMaterial();

    static void drawBall();
    static void drawRobot();
    
public:
    Graphics();

    void init(int argc, char** argv);
};

#endif  // _GRAPHICS_H_



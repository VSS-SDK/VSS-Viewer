#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <GL/glut.h>
#include "math.h"
#include "iostream"
#include "vector"
#include "thread"

#include "interface/interface.h"
#include "commons/commons.h"

using namespace common;
using namespace std;

class Graphics{
private:
    int argc;
    char** argv;

    float width, height;
    thread *thread_draw;
    thread *thread_receive;
    
    void draw_thread();
    void receive_thread();
    void handlePosition();

    static void drawWorld();
    static void initLight();
    // trocar handler para event
    static void timerHandler(int v);
    static void changeWindowSize(GLsizei w, GLsizei h);

    static void material(int color = BLACK);

    static void drawFloor();
    static void drawRobot(int);
    static void drawBall();  
public:
    Graphics();

    void init(int argc, char** argv);
};

#endif  // _GRAPHICS_H_



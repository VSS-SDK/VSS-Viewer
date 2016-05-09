/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */


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
    static void material(Pixel);

    static void drawFloor();
    static void drawRobot(int);
    static void drawBall();  
public:
    Graphics();

    void init(int argc, char** argv);
};

#endif  // _GRAPHICS_H_



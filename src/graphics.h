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

#include "VSS-Interface/interface.h"
#include "commons.h"

using namespace common;
using namespace std;

//! This class is responsible for draw the 3D World and receive data from VSS-Simulator and VSS-Vision.
class Graphics{
private:
    int argc;
    char** argv;
    bool debug;
    
    float width, height;

    thread *thread_draw;
    thread *thread_state;
    thread *thread_debug;

    Interface interface_state, interface_debug;
    vss_state::Global_State global_state;
    vss_debug::Global_Debug global_debug;
public:
    //! Allocates a vector of robots, in the software stream we only update the values.
    Graphics();

    //! Method responsible for initialize the software: control variables and threads.
    void init(int argc, char** argv, bool debug);

    //! Method responsible for handle a thread to draw the 3D world with Freeglut, it's unreachable (has a "infite" loop).
    void draw_thread();

    //! Method responsible for handle a thread to receive the state of game from VSS-Simulator or VSS-Vision.
    void state_thread();

    //! Method responsible for handle a thread to receive the debug data from VSS-Simulator or VSS-Vision.
    void debug_thread();

    //! Method responsible for transform the coordenates from OpenCV (VSS-Vision) and Bullet-Physics (VSS-Simulator) to Freeglut.
    void handlePosition();

    //! Method responsible for handle all 3D draws, like: Field, Robots and Ball.
    static void drawWorld();

    //! Method responsible for set the light Ambience, Diffuse, Speculate and the position.
    static void initLight();

    //! Method (Callback) responsible for redraw the 3D World keeping at least 30 Fps.
    static void timerHandler(int v);

    //! Method (Callback) responsible for update the control variables if the user resize manually the window.
    static void changeWindowSize(GLsizei w, GLsizei h);

    //! Method responsible for set the color of material: ORANGE, BLUE, YELLOW, RED, GREEN, PURPLE, PINK, BROWN, WHITE, GRAY, BLACK, BLACK2, BLACK3.
    static void material(int color = BLACK);

    //! Method responsible for set the color of material, receiving a RGB Color.
    static void material(Pixel);

    //! Method responsible for draw the field: floor and sidewalls.
    static void drawField();

    //! Method responsible for draw one robot: Body and wheels.
    static void drawRobot(int);

    //! Method responsible for draw the ball.
    static void drawBall();  
};

#endif  // _GRAPHICS_H_



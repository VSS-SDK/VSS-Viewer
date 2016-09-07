/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */


#include "graphics.h"

float staticWidth, staticHeight;

int x_ini = 0, y_ini = 0, z_ini = 0, but = -1;  //Glut - Initial x,y,z
float aspect;                   //Glut - Reason between width and height
float initAngle = 60.0f;        //Glut - Initial angle
float dx, dy, dz;               //Glut - Delta distance
float ex = 1, ey = 1, ez = 1;   //Glut - Scale
GLfloat rotX = 150.0,rotY = 90.0, rotZ = 0.0;    //Glut - Delta Rotation
GLfloat rotX_ini, rotY_ini, rotZ_ini;       //Glut - Init rotation
GLfloat obsX_ini, obsY_ini, obsZ_ini;       //Glut - Initial perspective observation position
GLfloat obsX = 100.0, obsY = 75.0, obsZ = 0.0;
float lookAt = 0;
vector<Robot> robots;
Pose ball;
bool staticDebug = false;
GLUquadric* qobj;

//! Addendum
//! --------
//! 
//! > Initializes the vector of robots with default values.
//! > The software have the concept of teams  
Graphics::Graphics(){
    //! > Initializes the team 1
    for(int i = 0 ; i < 3 ; i++){
        Robot robot;
        robot.id = i;
        robot.team = BLUE;
        robot.color = 3+i;
        robot.rgb_color = Pixel(0, 0, 0);
        robot.team_label = SQUARE;
        robot.color_label = SQUARE;
        robot.radius = 1.0;
        robot.pose = Pose(-20, -i*20, 0);
        robot.final_pose = robot.pose;
        robot.path.poses.push_back(Pose(0, 0, 0));

        robots.push_back(robot);
    }
    

    //! > Initializes the team 2
    for(int i = 0 ; i < 3 ; i++){
        Robot robot;
        robot.id = i;
        robot.team = YELLOW;
        robot.color = 5+i;
        robot.rgb_color = Pixel(0, 0, 0);
        robot.team_label = SQUARE;
        robot.color_label = SQUARE;
        robot.radius = 1.0;
        robot.pose = Pose(20, i*20, 0);
        robot.final_pose = robot.pose;
        robot.path.poses.push_back(Pose(0, 0, 0));

        robots.push_back(robot);
    }

    debug = false;
}

//! Addendum
//! --------
//! 
//! > Initializes control variables, the Draw thread and Interface of receiving thread.
void Graphics::init(int argc, char** argv, bool debug){
    //! > Receives argc and argv of main function because of glutInit. See: [freeglut](http://freeglut.sourceforge.net/).
    this->argc = argc;
    this->argv = argv;
    this->debug = debug;
    staticDebug = this->debug;

    width = 920;
    height = 576;

    staticWidth = width;
    staticHeight = height;

    thread_draw = new thread(bind(&Graphics::draw_thread, this));
    thread_state = new thread(bind(&Graphics::state_thread, this));
    if(debug){
        thread_debug_team1 = new thread(bind(&Graphics::debug_thread_team1, this));
        //thread_debug_team2 = new thread(bind(&Graphics::debug_thread_team2, this));
    }

    thread_draw->join();
    thread_state->join();
    if(debug){
        thread_debug_team1->join();
        //thread_debug_team2->join();
    }
}

//! Addendum
//! --------
//! 
//! > Set all callbacks and control variables
void Graphics::draw_thread(){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowPosition(5,5); 
    glutInitWindowSize(width, height); 
    glutCreateWindow("VSS-Viewer");
    glutDisplayFunc(drawWorld);
    glutReshapeFunc(changeWindowSize);
    glutTimerFunc(5, timerHandler, 0);
    
    initLight();

    //! qobj it's used on the draw of wheels
    qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);

    glutMainLoop();
}

void Graphics::debug_thread_team1(){
    interface_debug_team1.createReceiveDebugTeam1(&global_debug_team1);

    while(true){
        interface_debug_team1.receiveDebugTeam1();

        for(int i = 0 ; i < global_debug_team1.step_poses_size() ; i++){
            robots.at(i).step_pose.x = global_debug_team1.step_poses(i).y() - (150/2.0) + 9;
            robots.at(i).step_pose.y = global_debug_team1.step_poses(i).x() - (130/2.0) - 11;   
            robots.at(i).step_pose.yaw = global_debug_team1.step_poses(i).yaw()*180.0/M_PI;    
        }

        for(int i = 0 ; i < global_debug_team1.final_poses_size() ; i++){
            robots.at(i).final_pose.x = global_debug_team1.final_poses(i).y() - (150/2.0) + 9;
            robots.at(i).final_pose.y = global_debug_team1.final_poses(i).x() - (130/2.0) - 11;   
            robots.at(i).final_pose.yaw = global_debug_team1.final_poses(i).yaw()*180.0/M_PI;
        }

        for(int i = 0 ; i < global_debug_team1.paths_size() ; i++){
            Path path;
            for(int j = 0 ; j < global_debug_team1.paths(i).poses_size() ; j++){
                Pose pose;
                pose.x = global_debug_team1.paths(i).poses(j).y() - (150/2.0) + 9;
                pose.y = global_debug_team1.paths(i).poses(j).x() - (130/2.0) - 11;
                pose.yaw = global_debug_team1.paths(i).poses(j).yaw()*180.0/M_PI;

                path.poses.push_back(pose);
            }
            robots.at(i).path = path;
        }
    }
}

void Graphics::debug_thread_team2(){
    interface_debug_team2.createReceiveDebugTeam2(&global_debug_team2);

    while(true){
        interface_debug_team2.receiveDebugTeam2();

        for(int i = 0 ; i < global_debug_team2.step_poses_size() ; i++){
            robots.at(i+3).step_pose.x = global_debug_team2.step_poses(i).y() - (150/2.0) + 9;
            robots.at(i+3).step_pose.y = global_debug_team2.step_poses(i).x() - (130/2.0) - 11;   
            robots.at(i+3).step_pose.yaw = global_debug_team2.step_poses(i).yaw()*180.0/M_PI;    
        }

        for(int i = 0 ; i < global_debug_team2.final_poses_size() ; i++){
            robots.at(i+3).final_pose.x = global_debug_team2.final_poses(i).y() - (150/2.0) + 9;
            robots.at(i+3).final_pose.y = global_debug_team2.final_poses(i).x() - (130/2.0) - 11;   
            robots.at(i+3).final_pose.yaw = global_debug_team2.final_poses(i).yaw()*180.0/M_PI;    
        }

        for(int i = 0 ; i < global_debug_team2.paths_size() ; i++){
            Path path;
            for(int j = 0 ; j < global_debug_team2.paths(i).poses_size() ; j++){
                Pose pose;
                pose.x = global_debug_team2.paths(i).poses(j).y() - (150/2.0) + 9;
                pose.y = global_debug_team2.paths(i).poses(j).x() - (130/2.0) - 11;
                pose.yaw = global_debug_team2.paths(i).poses(j).yaw()*180.0/M_PI;

                path.poses.push_back(pose);
            }
            robots.at(i+3).path = path;
        }
    }
}

//! Addendum
//! --------
//! 
//! > The data vss_state::Global_State states carry all states "Poses" of robots and ball.
//! 
//! > It's a data of Interface that allows the communication between VSS-SampleStrategy, VSS-Vision, VSS-Simulator and VSS-Viewer.
//! 
//! Was created by a compilation of proto file.  See: [Protobuf](https://developers.google.com/protocol-buffers/).
void Graphics::state_thread(){
    interface_state.createSocketReceiveState(&global_state);

    while(true){
        interface_state.receiveState();
        global_state.id();

        ball.x = global_state.balls(0).pose().y() - (150/2.0) + 9;
        ball.y = global_state.balls(0).pose().x() - (130/2.0) - 11;
        
        for(int i = 0 ; i < 3 ; i++){
            robots.at(i).team = YELLOW;
            robots.at(i).pose.x = global_state.robots_yellow(i).pose().y() - (150/2.0) + 9;
            robots.at(i).pose.y = global_state.robots_yellow(i).pose().x() - (130/2.0) - 11;
            robots.at(i).pose.yaw = global_state.robots_yellow(i).pose().yaw()*180.0/M_PI;
            robots.at(i).rgb_color.rgb[0] = 0;
            robots.at(i).rgb_color.rgb[1] = 0;
            robots.at(i).rgb_color.rgb[2] = 0;

            robots.at(i+3).team = BLUE;
            robots.at(i+3).pose.x = global_state.robots_blue(i).pose().y() - (150/2.0) + 9;
            robots.at(i+3).pose.y = global_state.robots_blue(i).pose().x() - (130/2.0) - 11;
            robots.at(i+3).pose.yaw = global_state.robots_blue(i).pose().yaw()*180.0/M_PI;
            robots.at(i+3).rgb_color.rgb[0] = 0;
            robots.at(i+3).rgb_color.rgb[1] = 0;
            robots.at(i+3).rgb_color.rgb[2] = 0;
        }
    }
}

//! Addendum
//! --------
//! 
//! > Create and positioning the light 
void Graphics::initLight(void){   
    GLfloat luzAmbiente[4] = { 0.35, 0.35, 0.35, 1.0 };
    GLfloat luzDifusa[4] = { 0.05, 0.05, 0.05, 1.0 };
    GLfloat luzEspecular[4] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat posLuz[4] = { 0, 100, 0, 1.0 };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posLuz);

    glEnable(GL_LINE_SMOOTH);
    glShadeModel(GL_SMOOTH);

    glClearColor(0.2f, 0.2f, 0.6f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
}

//! Addendum
//! --------
//! 
//! > Callback responsible for resize the window
void Graphics::changeWindowSize(GLsizei w, GLsizei h){
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    float aspect = (float)w / h;
    float depthObs = 3000;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60, aspect, 0.1f, depthObs);

    glMatrixMode(GL_MODELVIEW);
}

//! Addendum
//! --------
//! 
//! > Callback responsble for positioning the "camera" and draw the 3D World.
void Graphics::drawWorld(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
  
    glTranslatef(0.0f, 0.0f, -lookAt);
    glRotatef(rotX, 1, 0, 0);

    glRotatef(rotY, 0, 1, 0);
    glTranslatef(-obsX, -obsY, -obsZ);

    drawField();
    drawBall();
    for(unsigned int i = 0 ; i < robots.size() ; i++){
        drawRobot(i);
        if(staticDebug){
            drawDebugFinalRobot(i);
            drawDebugPath(i);
        }
    }

    glutSwapBuffers();
}

//! Addendum
//! --------
//! 
//! > Callback responsible for update the screen
void Graphics::timerHandler(int v){
    glutPostRedisplay();
    //! > Must define the frequency of update
    glutTimerFunc(5, timerHandler, 0);
}


void Graphics::drawBall(){
    glPushMatrix();
        glTranslatef(THICK_THINGS*1.4, ball.x, ball.y);
        material(ORANGE);
        glutSolidSphere(2.0, 8.0, 8.0);
    glPopMatrix();
}

//! Addendum
//! --------
//! 
//! > Draw the robot i
void Graphics::drawRobot(int i){
    glPushMatrix();
        //! > Draw the body of the robot
        glTranslatef(THICK_THINGS*1.4, robots.at(i).pose.x, robots.at(i).pose.y);
        glRotatef(-robots.at(i).pose.yaw, 1, 0, 0);
        glScalef(SIZE_ROBOT, SIZE_ROBOT, SIZE_ROBOT);
        material(BLACK3);
        glutSolidCube(1);

        //! > Draw the team label "blue or yellow"
        glPushMatrix();
            glTranslatef(0.5, -0.2, -0.2);
            glScalef(0.1f, SIZE_SQUARE/SIZE_ROBOT, SIZE_SQUARE/SIZE_ROBOT);
            material(robots.at(i).team);
            glutSolidCube(1);
        glPopMatrix();

        //! > Draw the second "robot" label
        glPushMatrix();
            glTranslatef(0.5, 0.2, 0.2);
            glScalef(0.1f, SIZE_SQUARE/SIZE_ROBOT, SIZE_SQUARE/SIZE_ROBOT);
            if(robots.at(i).rgb_color.rgb[0] == 0 && robots.at(i).rgb_color.rgb[1] == 0 && robots.at(i).rgb_color.rgb[2] == 0){
                //! > When the VSS-Viewer run side by side with the VSS-Simulator, ins't important the label colors, so twe use default colors.
                material(robots.at(i).color);
            }else{
                //! > When the VSS-Viewer run side by side with the VSS-Vision, it's important the labels have the same color and the real world, so we used the RGB color calibrated on VSS-Vision
                material(robots.at(i).rgb_color);
            }
            glutSolidCube(1);
        glPopMatrix();

        //! > Draw the wheels of the robot
        glPushMatrix();
            glRotatef(90.0, 1, 0, 0);
            glTranslatef(-0.10, 0.0, -0.61);
            material(WHITE);
            gluCylinder(qobj, 0.2f, 0.2f, 1.2f, 16.0, 16.0); // Radius 1, Radius 2, Lenght, Precision1, Precision2
        glPopMatrix();

    glPopMatrix();
}

//! Addendum
//! --------
//! 
//! > Draw the debug final position
void Graphics::drawDebugFinalRobot(int i){
    glPushMatrix();
        //! > Draw the body of the robot
        glTranslatef(1.5, robots.at(i).final_pose.x, robots.at(i).final_pose.y);
        glRotatef(-robots.at(i).final_pose.yaw, 1, 0, 0);
        glScalef(0.1f, SIZE_ROBOT, SIZE_ROBOT);
        material(GRAY);
        glLineWidth(4.0f);
        glutWireCube(1);

        //! > Draw the team label "blue or yellow"
        glPushMatrix();
            glTranslatef(0.1, -0.2, -0.2);
            glScalef(0.1f, SIZE_SQUARE/SIZE_ROBOT, SIZE_SQUARE/SIZE_ROBOT);
            material(robots.at(i).team);
            glutSolidCube(1);
        glPopMatrix();

        //! > Draw the second "robot" label
        glPushMatrix();
            glTranslatef(0.1, 0.2, 0.2);
            glScalef(0.1f, SIZE_SQUARE/SIZE_ROBOT, SIZE_SQUARE/SIZE_ROBOT);
            if(robots.at(i).rgb_color.rgb[0] == 0 && robots.at(i).rgb_color.rgb[1] == 0 && robots.at(i).rgb_color.rgb[2] == 0){
                //! > When the VSS-Viewer run side by side with the VSS-Simulator, ins't important the label colors, so twe use default colors.
                material(robots.at(i).color);
            }else{
                //! > When the VSS-Viewer run side by side with the VSS-Vision, it's important the labels have the same color and the real world, so we used the RGB color calibrated on VSS-Vision
                material(robots.at(i).rgb_color);
            }
            glutSolidCube(1);
        glPopMatrix();

    glPopMatrix();
}

//! Addendum
//! --------
//! 
//! > Draw the debug step position
void Graphics::drawDebugStepRobot(int i){
    glPushMatrix();
        //! > Draw the body of the robot
        glTranslatef(1.5, robots.at(i).final_pose.x, robots.at(i).final_pose.y);
        glRotatef(-robots.at(i).final_pose.yaw, 1, 0, 0);
        glScalef(0.1f, SIZE_ROBOT, SIZE_ROBOT);
        material(GRAY2);
        glLineWidth(4.0f);
        glutWireCube(1);

        //! > Draw the team label "blue or yellow"
        glPushMatrix();
            glTranslatef(0.1, -0.2, -0.2);
            glScalef(0.1f, SIZE_SQUARE/SIZE_ROBOT, SIZE_SQUARE/SIZE_ROBOT);
            material(robots.at(i).team);
            glutSolidCube(1);
        glPopMatrix();

        //! > Draw the second "robot" label
        glPushMatrix();
            glTranslatef(0.1, 0.2, 0.2);
            glScalef(0.1f, SIZE_SQUARE/SIZE_ROBOT, SIZE_SQUARE/SIZE_ROBOT);
            if(robots.at(i).rgb_color.rgb[0] == 0 && robots.at(i).rgb_color.rgb[1] == 0 && robots.at(i).rgb_color.rgb[2] == 0){
                //! > When the VSS-Viewer run side by side with the VSS-Simulator, ins't important the label colors, so twe use default colors.
                material(robots.at(i).color);
            }else{
                //! > When the VSS-Viewer run side by side with the VSS-Vision, it's important the labels have the same color and the real world, so we used the RGB color calibrated on VSS-Vision
                material(robots.at(i).rgb_color);
            }
            glutSolidCube(1);
        glPopMatrix();

    glPopMatrix();
}

void Graphics::drawDebugPath(int i){
    glPushMatrix();
        if(robots.at(i).rgb_color.rgb[0] == 0 && robots.at(i).rgb_color.rgb[1] == 0 && robots.at(i).rgb_color.rgb[2] == 0){
            material3f(robots.at(i).color);     
        }else{
            material3f(robots.at(i).rgb_color);
        }
        if(robots.at(i).path.poses.size() >= 2){
            for(unsigned int j = 0 ; j < robots.at(i).path.poses.size()-1 ; j++){
                glBegin(GL_LINES);
                    glVertex3f(1, robots.at(i).path.poses.at(j).x, robots.at(i).path.poses.at(j).y);
                    glVertex3f(1, robots.at(i).path.poses.at(j+1).x, robots.at(i).path.poses.at(j+1).y);
                glEnd();
            }
        }
    glPopMatrix();
}

//! Addendum
//! --------
//! 
//! 
void Graphics::drawField(){
    //! > **Draw the blocks of wood**
    //! > Draw the floor
    glPushMatrix();
        glScalef(1, FIELD_DEPTH, FIELD_WIDTH);
        material(BLACK);
        glutSolidCube(1);
    glPopMatrix();
    //! > Draw the left goal
    glPushMatrix();
        glTranslatef(0, 0, -FIELD_WIDTH/1.88);
        glScalef(1, GOAL_WIDTH+0.6, GOAL_DEPTH+0.6);
        material(BLACK);
        glutSolidCube(1);
    glPopMatrix();
    //! > Draw the right goal
    glPushMatrix();
        glTranslatef(0, 0, FIELD_WIDTH/1.88);
        glScalef(1, GOAL_WIDTH+0.6, GOAL_DEPTH+0.6);
        material(BLACK);
        glutSolidCube(1);
    glPopMatrix();
    //! > Draw the top wall in perspective
    glPushMatrix();
        glTranslatef(THICK_THINGS, -FIELD_DEPTH/2.0, 0);
        glScalef(WALL_HEIGHT, THICK_THINGS, FIELD_WIDTH);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    //! > Draw the bottom wall in perspective
    glPushMatrix();
        glTranslatef(THICK_THINGS, FIELD_DEPTH/2.0, 0);
        glScalef(WALL_HEIGHT, THICK_THINGS, FIELD_WIDTH);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    //! > Draw the left-bottom wall in perspective
    glPushMatrix();
        glTranslatef(THICK_THINGS, 43.0, -FIELD_WIDTH/1.97);
        glScalef(WALL_HEIGHT, WALL_TOPS_B, THICK_THINGS);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    //! > Draw the left-top wall in perspective
    glPushMatrix();
        glTranslatef(THICK_THINGS, -43.0, -FIELD_WIDTH/1.97);
        glScalef(WALL_HEIGHT, WALL_TOPS_B, THICK_THINGS);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    //! > Draw the wall of left goal
    glPushMatrix();
        glTranslatef(THICK_THINGS, 0, (-FIELD_WIDTH/1.98) - GOAL_DEPTH );
        glScalef(WALL_HEIGHT, GOAL_WIDTH+1.25, THICK_THINGS);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    // WALL GOAL TOP
    glPushMatrix();
        glTranslatef(THICK_THINGS, -22, -FIELD_WIDTH/1.85);
        glScalef(WALL_HEIGHT, THICK_THINGS, GOAL_DEPTH+1.35);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    // WALL GOAL BOTTOM
    glPushMatrix();
        glTranslatef(THICK_THINGS, 22, -FIELD_WIDTH/1.85);
        glScalef(WALL_HEIGHT, THICK_THINGS, GOAL_DEPTH+1.35);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();

    // WALL LEFT/BOTTOM
    glPushMatrix();
        glTranslatef(THICK_THINGS, 43.0, FIELD_WIDTH/1.97);
        glScalef(WALL_HEIGHT, WALL_TOPS_B, THICK_THINGS);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    // WALL LEFT/TOP
    glPushMatrix();
        glTranslatef(THICK_THINGS, -43.0, FIELD_WIDTH/1.97);
        glScalef(WALL_HEIGHT, WALL_TOPS_B, THICK_THINGS);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    // WALL GOAL RIGHT
    glPushMatrix();
        glTranslatef(THICK_THINGS, 0, FIELD_WIDTH/1.98 + GOAL_DEPTH );
        glScalef(WALL_HEIGHT, GOAL_WIDTH+1.25, THICK_THINGS);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    // WALL GOAL TOP
    glPushMatrix();
        glTranslatef(THICK_THINGS, -22, FIELD_WIDTH/1.85);
        glScalef(WALL_HEIGHT, THICK_THINGS, GOAL_DEPTH+1.35);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    // WALL GOAL BOTTOM
    glPushMatrix();
        glTranslatef(THICK_THINGS, 22, FIELD_WIDTH/1.85);
        glScalef(WALL_HEIGHT, THICK_THINGS, GOAL_DEPTH+1.35);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    // TRIANGLE RIGHT BOTTOM
    glPushMatrix();
        glTranslatef(THICK_THINGS, (FIELD_DEPTH/2.0)-4.5, (FIELD_WIDTH/2.0)-4.5);
        glRotatef(45.0, 1, 0, 0);
        glScalef(WALL_HEIGHT, THICK_THINGS, 14.0);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    // TRIANGLE LEFT TOP
    glPushMatrix();
        glTranslatef(THICK_THINGS, -(FIELD_DEPTH/2.0)+4.5, -(FIELD_WIDTH/2.0)+4.5);
        glRotatef(45.0, 1, 0, 0);
        glScalef(WALL_HEIGHT, THICK_THINGS, 14.0);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    // TRIANGLE RIGHT BOTTOM
    glPushMatrix();
        glTranslatef(THICK_THINGS, -(FIELD_DEPTH/2.0)+4.5, (FIELD_WIDTH/2.0)-4.5);
        glRotatef(-45.0, 1, 0, 0);
        glScalef(WALL_HEIGHT, THICK_THINGS, 14.0);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();
    // TRIANGLE LEFT TOP
    glPushMatrix();
        glTranslatef(THICK_THINGS, (FIELD_DEPTH/2.0)-4.5, -(FIELD_WIDTH/2.0)+4.5);
        glRotatef(-45.0, 1, 0, 0);
        glScalef(WALL_HEIGHT, THICK_THINGS, 14.0);
        material(BLACK2);
        glutSolidCube(1);
    glPopMatrix();

    // PAINTS
    // LINE CENTER
    glPushMatrix();
        glTranslatef(0.05, 0, 0);
        glScalef(1.0, FIELD_DEPTH, 1.0);
        material(WHITE);
        glutSolidCube(1);
    glPopMatrix();

    // LINE GOAL GOAL LEFT
    glPushMatrix();
        glTranslatef(0.05, 0, (FIELD_WIDTH/2.0)+0.4);
        glScalef(1.0, 40.0, 1.0);
        material(WHITE);
        glutSolidCube(1);
    glPopMatrix();
    // LINE GOAL LEFT
    glPushMatrix();
        glTranslatef(0.05, 0, (FIELD_WIDTH/2.0)-15.0);
        glScalef(1.0, 70.0, 1.0);
        material(WHITE);
        glutSolidCube(1);
    glPopMatrix();
    // LINE GOAL LEFT/BOTTOM
    glPushMatrix();
        glTranslatef(0.05, 34.5, (FIELD_WIDTH/2.0)-7.5);
        glScalef(1.0, 1.0, 15.0);
        material(WHITE);
        glutSolidCube(1);
    glPopMatrix();
    // LINE GOAL LEFT/TOP
    glPushMatrix();
        glTranslatef(0.05, -34.5, (FIELD_WIDTH/2.0)-7.5);
        glScalef(1.0, 1.0, 15.0);
        material(WHITE);
        glutSolidCube(1);
    glPopMatrix();

    // LINE GOAL GOAL RIGHT
    glPushMatrix();
        glTranslatef(0.05, 0, -(FIELD_WIDTH/2.0)-0.4);
        glScalef(1.0, 40.0, 1.0);
        material(WHITE);
        glutSolidCube(1);
    glPopMatrix();
    // LINE GOAL RIGHT
    glPushMatrix();
        glTranslatef(0.05, 0, -(FIELD_WIDTH/2.0)+15.0);
        glScalef(1.0, 70.0, 1.0);
        material(WHITE);
        glutSolidCube(1);
    glPopMatrix();
    // LINE GOAL RIGHT/BOTTOM
    glPushMatrix();
        glTranslatef(0.05, 34.5, -(FIELD_WIDTH/2.0)+7.5);
        glScalef(1.0, 1.0, 15.0);
        material(WHITE);
        glutSolidCube(1);
    glPopMatrix();
    // LINE GOAL RIGHT/TOP
    glPushMatrix();
        glTranslatef(0.05, -34.5, -(FIELD_WIDTH/2.0)+7.5);
        glScalef(1.0, 1.0, 15.0);
        material(WHITE);
        glutSolidCube(1);
    glPopMatrix();

    /* CROSS MIDDLE-LEFT
    glPushMatrix();
        glTranslatef(0.05, 0, 37.5);
        material(WHITE);
        glPushMatrix();
            glScalef(1.0, 1.0, 5.0);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glScalef(1.0, 5.0, 1.0);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    // CROSS BOTTOM-LEFT
    glPushMatrix();
        glTranslatef(0.05, 37.5, 37.5);
        material(WHITE);
        glPushMatrix();
            glScalef(1.0, 1.0, 5.0);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glScalef(1.0, 5.0, 1.0);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    // CROSS TOP-LEFT
    glPushMatrix();
        glTranslatef(0.05, -37.5, 37.5);
        material(WHITE);
        glPushMatrix();
            glScalef(1.0, 1.0, 5.0);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glScalef(1.0, 5.0, 1.0);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();

    // CROSS MIDDLE-RIGHT
    glPushMatrix();
        glTranslatef(0.05, 0, -37.5);
        material(WHITE);
        glPushMatrix();
            glScalef(1.0, 1.0, 5.0);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glScalef(1.0, 5.0, 1.0);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    // CROSS BOTTOM-RIGHT
    glPushMatrix();
        glTranslatef(0.05, 37.5, -37.5);
        material(WHITE);
        glPushMatrix();
            glScalef(1.0, 1.0, 5.0);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glScalef(1.0, 5.0, 1.0);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    // CROSS TOP-RIGHT
    glPushMatrix();
        glTranslatef(0.05, -37.5, -37.5);
        material(WHITE);
        glPushMatrix();
            glScalef(1.0, 1.0, 5.0);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glScalef(1.0, 5.0, 1.0);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();*/
}

//! Addendum
//! --------
//! 
//! Sets the material with base in the RGB of VSS-Vision
void Graphics::material(Pixel p){
    GLfloat diffuse[4];
    GLfloat ambient[4];
    GLfloat specular[4];
    GLfloat shininess;

    //! Converts RGB (0-255) to RGB (0-1) 
    diffuse[0] = p.rgb[0]/255.0;   diffuse[1] = p.rgb[1]/255.0;   diffuse[2] = p.rgb[2]/255.0;   diffuse[3] = 1.0;
    ambient[0] = p.rgb[0]/255.0;   ambient[1] = p.rgb[1]/255.0;   ambient[2] = p.rgb[2]/255.0;   ambient[3] = 1.0;
    specular[0] = p.rgb[0]/255.0;  specular[1] = p.rgb[1]/255.0;  specular[2] = p.rgb[2]/255.0;  specular[3] = 1.0;
    shininess = 10.0;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void Graphics::material(int color){
    GLfloat diffuse[4];
    GLfloat ambient[4];
    GLfloat specular[4];
    GLfloat shininess;

    switch(color){
        case ORANGE:{
            diffuse[0] = 1.0;   diffuse[1] = 0.4;   diffuse[2] = 0.2;   diffuse[3] = 1.0;
            ambient[0] = 1.0;   ambient[1] = 0.4;   ambient[2] = 0.2;   ambient[3] = 1.0;
            specular[0] = 1.0;  specular[1] = 0.4;  specular[2] = 0.2;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case BLUE:{
            diffuse[0] = 0.2;   diffuse[1] = 0.2;   diffuse[2] = 0.7;   diffuse[3] = 1.0;
            ambient[0] = 0.2;   ambient[1] = 0.2;   ambient[2] = 0.7;   ambient[3] = 1.0;
            specular[0] = 0.2;  specular[1] = 0.2;  specular[2] = 0.7;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case YELLOW:{
            diffuse[0] = 0.85;   diffuse[1] = 0.75;   diffuse[2] = 0.25;   diffuse[3] = 1.0;
            ambient[0] = 0.85;   ambient[1] = 0.75;   ambient[2] = 0.25;   ambient[3] = 1.0;
            specular[0] = 0.85;  specular[1] = 0.75;  specular[2] = 0.25;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case RED:{
            diffuse[0] = 0.7;   diffuse[1] = 0.2;   diffuse[2] = 0.2;   diffuse[3] = 1.0;
            ambient[0] = 0.7;   ambient[1] = 0.2;   ambient[2] = 0.2;   ambient[3] = 1.0;
            specular[0] = 0.7;  specular[1] = 0.2;  specular[2] = 0.2;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case GREEN:{
            diffuse[0] = 0.2;   diffuse[1] = 0.7;   diffuse[2] = 0.2;   diffuse[3] = 1.0;
            ambient[0] = 0.2;   ambient[1] = 0.7;   ambient[2] = 0.2;   ambient[3] = 1.0;
            specular[0] = 0.2;  specular[1] = 0.7;  specular[2] = 0.2;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case PURPLE:{
            diffuse[0] = 0.45;   diffuse[1] = 0.1;   diffuse[2] = 0.7;   diffuse[3] = 1.0;
            ambient[0] = 0.45;   ambient[1] = 0.1;   ambient[2] = 0.7;   ambient[3] = 1.0;
            specular[0] = 0.45;  specular[1] = 0.1;  specular[2] = 0.7;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case PINK:{
            diffuse[0] = 0.8;   diffuse[1] = 0.5;   diffuse[2] = 0.5;   diffuse[3] = 1.0;
            ambient[0] = 0.8;   ambient[1] = 0.5;   ambient[2] = 0.5;   ambient[3] = 1.0;
            specular[0] = 0.8;  specular[1] = 0.5;  specular[2] = 0.5;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case BROWN:{
            diffuse[0] = 0.4;   diffuse[1] = 0.2;   diffuse[2] = 0.1;   diffuse[3] = 1.0;
            ambient[0] = 0.4;   ambient[1] = 0.2;   ambient[2] = 0.1;   ambient[3] = 1.0;
            specular[0] = 0.4;  specular[1] = 0.2;  specular[2] = 0.1;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        //! > There are more than one BLACK to differentiate: robot, wall and floor
        case BLACK:{
            diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
            ambient[0] = 0.1;   ambient[1] = 0.1;   ambient[2] = 0.1;   ambient[3] = 1.0;
            specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case BLACK2:{
            diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
            ambient[0] = 0.1;   ambient[1] = 0.1;   ambient[2] = 0.1;   ambient[3] = 1.0;
            specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case BLACK3:{
            diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
            ambient[0] = 0.0;   ambient[1] = 0.0;   ambient[2] = 0.0;   ambient[3] = 1.0;
            specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case WHITE:{
            diffuse[0] = 0.9;   diffuse[1] = 0.9;   diffuse[2] = 0.9;   diffuse[3] = 1.0;
            ambient[0] = 0.9;   ambient[1] = 0.9;   ambient[2] = 0.9;   ambient[3] = 1.0;
            specular[0] = 0.9;  specular[1] = 0.9;  specular[2] = 0.9;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case GRAY:{
            diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
            ambient[0] = 0.2;   ambient[1] = 0.2;   ambient[2] = 0.2;   ambient[3] = 1.0;
            specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case GRAY2:{
            diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
            ambient[0] = 0.4;   ambient[1] = 0.4;   ambient[2] = 0.4;   ambient[3] = 1.0;
            specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

//! Addendum
//! --------
//! 
//! Sets the material 2d in 3d with base in the RGB of VSS-Vision
void Graphics::material3f(Pixel p){
    glColor3f(p.rgb[0], p.rgb[1], p.rgb[2]);
}

void Graphics::material3f(int color){
    switch(color){
        case ORANGE:{
            glColor3f(1.0, 0.4, 0.2);
        }break;
        case BLUE:{
            glColor3f(0.2, 0.2, 0.7);
        }break;
        case YELLOW:{
            glColor3f(0.85, 0.75, 0.25);
        }break;
        case RED:{
            glColor3f(0.7, 0.2, 0.2);
        }break;
        case GREEN:{
            glColor3f(0.2, 0.7, 0.2);
        }break;
        case PURPLE:{
            glColor3f(0.45, 0.1, 0.7);
        }break;
        case PINK:{
            glColor3f(0.8, 0.5, 0.5);
        }break;
        case BROWN:{
            glColor3f(0.4, 0.2, 0.1);
        }break;
        //! > There are more than one BLACK to differentiate: robot, wall and floor
        case BLACK:{
            glColor3f(0.1, 0.1, 0.1);
        }break;
        case BLACK2:{
            glColor3f(0.1, 0.1, 0.1);
        }break;
        case BLACK3:{
            glColor3f(0.1, 0.1, 0.1);
        }break;
        case WHITE:{
            glColor3f(0.9, 0.9, 0.9);
        }break;
        case GRAY:{
            glColor3f(0.2, 0.2, 0.2);
        }break;
        case GRAY2:{
            glColor3f(0.4, 0.4, 0.4);
        }break;
    }
}
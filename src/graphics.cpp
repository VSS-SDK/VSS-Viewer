#include "graphics.h"

float staticWidth, staticHeight;
int x_ini = 0, y_ini = 0, z_ini = 0, but = -1;  //Glut - Initial x,y,z
float aspect;                   //Glut - Reason between width and height
float initAngle = 60.0f;        //Glut - Initial angle
float dx, dy, dz;               //Glut - Delta distance
float ex = 1, ey = 1, ez = 1;   //Glut - Scale
GLfloat rotX = 90.0,rotY = 90.0, rotZ = 0.0;    //Glut - Delta Rotation
GLfloat rotX_ini, rotY_ini, rotZ_ini;       //Glut - Init rotation
GLfloat obsX_ini, obsY_ini, obsZ_ini;       //Glut - Initial perspective observation position
GLfloat obsX = SIZE_WIDTH/2, obsY = 170.0, obsZ = SIZE_DEPTH/2;
float lookAt = 0;

Graphics::Graphics(){

}

void Graphics::init(int argc, char** argv){
    this->argc = argc;
    this->argv = argv;

    width = 1280;
    height = 720;

    staticWidth = width;
    staticHeight = height;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowPosition(5,5); 
    glutInitWindowSize(width, height); 
    glutCreateWindow("VSS-Viewer");
    glutDisplayFunc(drawWorld);
    glutReshapeFunc(changeWindowSize);
    glutTimerFunc(5, timerHandler, 0);
    glutMouseFunc(mouseHandler);
    glutMotionFunc(motionHandler);
    initLight();

    glutMainLoop();
}

void Graphics::initLight(void){   
    GLfloat luzAmbiente[4] = { 0.35, 0.35, 0.35, 1.0 };
    GLfloat luzDifusa[4] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat luzEspecular[4] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat posLuz[4] = { 200, 200, 200, 1.0 };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posLuz);

    glEnable(GL_LINE_SMOOTH);
    glShadeModel(GL_SMOOTH);

    glClearColor(0.05f, 0.35f, 0.05f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
}

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

void Graphics::mouseHandler(int button, int state, int x, int y){
    if (state == GLUT_DOWN){
        but = button;
        x_ini = x;
        y_ini = y;
        rotX_ini = rotX;
        rotY_ini = rotY;
    }
    else{
        but = -1;
    }
}

void Graphics::motionHandler(int x, int y){

    if(but == GLUT_LEFT_BUTTON){
        int diffx=x_ini - x; //check the difference between the current x and the last x position
        int diffy=y_ini - y; //check the difference between the current y and the last y position

        rotX = ((float)rotX_ini - (float)diffy); //set the xrot to xrot with the additionof the difference in the y position
        rotY = ((float)rotY_ini - (float)diffx);    //set the xrot to yrot with the additionof the difference in the x position
    }

    glutPostRedisplay();
}

void Graphics::drawWorld(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
  
    glTranslatef(0.0f, 0.0f, -lookAt);
    glRotatef(rotX, 1, 0, 0);

    glRotatef(rotY, 0, 1, 0);
    glTranslatef(-obsX, -obsY, -obsZ);

    drawFloor();

    glutSwapBuffers();
}

void Graphics::timerHandler(int v){
    glutPostRedisplay();
    glutTimerFunc(5, timerHandler, 0);
}

void Graphics::drawBall(){

}

void Graphics::drawFloor(){
    glPushMatrix();
        glTranslatef(0,0,0);
        glScalef(1, 150, 130);
        material(BLACK);
        glutSolidCube(1);
    glPopMatrix();
}


void Graphics::material(int color){
    GLfloat diffuse[4];
    GLfloat ambient[4];
    GLfloat specular[4];
    GLfloat shininess;

    switch(color){
        case ORANGE:{

        }break;
        case BLUE:{

        }break;
        case YELLOW:{

        }break;
        case RED:{

        }break;
        case GREEN:{

        }break;
        case PURPLE:{

        }break;
        case PINK:{

        }break;
        case BROWN:{

        }break;
        case BLACK:{
            diffuse[0] = 0.1;   diffuse[1] = 0.1;   diffuse[2] = 0.1;   diffuse[3] = 1.0;
            ambient[0] = 0.1;   ambient[1] = 0.1;   ambient[2] = 0.1;   ambient[3] = 1.0;
            specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
            shininess = 10.0;
        }break;
        case WHITE:{
  
        }break;
        case GRAY:{

        }break;
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
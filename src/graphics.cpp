#include "graphics.h"

float staticWidth, staticHeight;

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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowPosition(5,5); 
    glutInitWindowSize(width, height); 
    glutCreateWindow("VSS-Viewer");
    glutDisplayFunc(drawWorld);
    glutReshapeFunc(changeWindowSize);
    glutTimerFunc(5, timerHandler, 0);
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

void Graphics::drawWorld(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLfloat rotX = 90.0,rotY = 90.0, rotZ = 0.0;  

    GLfloat obsX = 150/2, obsY = 170.0, obsZ = 130/2;
    float lookAt = 0;
  
    glTranslatef(0.0f, 0.0f, -lookAt);
    glRotatef(rotX, 1, 0, 0);

    glRotatef(rotY, 0, 1, 0);
    glTranslatef(-obsX, -obsY, -obsZ);

    drawRobot();

    glutSwapBuffers();
}

void Graphics::timerHandler(int v){
    glutPostRedisplay();
    glutTimerFunc(5, timerHandler, 0);
}

void Graphics::drawBall(){

}

void Graphics::drawRobot(){
    glPushMatrix();
        glTranslatef(0,0,0);
        glScalef(1, 1, 1);
        defineMaterial();
        glutSolidCube(1);
        
    glPopMatrix();
}

void Graphics::defineMaterial(){
    GLfloat diffuseColor[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat ambientColor[] = {0.1, 0.1, 0.1, 1.0 };
    GLfloat specularColor[] = { 0.1, 0.1, 0.1, 1.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularColor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);
}
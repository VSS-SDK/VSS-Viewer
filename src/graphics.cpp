/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "graphics.h"
#include "functional"

float staticWidth, staticHeight;

int x_ini = 0, y_ini = 0, z_ini = 0, but = -1;  //Glut - Initial x,y,z
float aspect;                   //Glut - Reason between width and height
float initAngle = 60.0f;        //Glut - Initial angle
float dx, dy, dz;               //Glut - Delta distance
float ex = 1, ey = 1, ez = 1;   //Glut - Scale
GLfloat rotX = 150.0, rotY = 90.0, rotZ = 0.0;    //Glut - Delta Rotation
GLfloat rotX_ini, rotY_ini, rotZ_ini;       //Glut - Init rotation
GLfloat obsX_ini, obsY_ini, obsZ_ini;       //Glut - Initial perspective observation position
GLfloat obsX = 100.0, obsY = 75.0, obsZ = 0.0;
float lookAt = 0;

string cameraStatic = "top";
vector<Robot> robots;
Pose ball, v_ball;
bool staticDebug = false;
string static_name_team_1, static_name_team_2;
int static_score_team_1, static_score_team_2;

GLUquadric* qobj;

//! Inicializa o vector de robôs com valores default.
//! O software tem o conceito de times
Graphics::Graphics(){
	//! Inicializa o time 1
	for(int i = 0; i < 3; i++) {
		Robot robot;
		robot.id = i;
		robot.team = BLUE;
		robot.color = 3 + i;
		robot.rgb_color = Pixel( 0, 0, 0 );
		robot.team_label = SQUARE;
		robot.color_label = SQUARE;
		robot.radius = 1.0;
		robot.pose = Pose( -20, -i * 20, 0 );
		robot.final_pose = robot.pose;
		robot.path.poses.push_back( Pose( 0, 0, 0 ));

		robots.push_back( robot );
	}

	//! Inicializa o time 2
	for(int i = 0; i < 3; i++) {
		Robot robot;
		robot.id = i;
		robot.team = YELLOW;
		robot.color = 5 + i;
		robot.rgb_color = Pixel( 0, 0, 0 );
		robot.team_label = SQUARE;
		robot.color_label = SQUARE;
		robot.radius = 1.0;
		robot.pose = Pose( 20, i * 20, 0 );
		robot.final_pose = robot.pose;
		robot.path.poses.push_back( Pose( 0, 0, 0 ));

		robots.push_back( robot );
	}

	debug = false;

	static_name_team_1 = name_team_1 = "Yellow";
	static_name_team_2 = name_team_2 = "Blue";

	static_score_team_1 = 0;
	static_score_team_1 = 0;
	score_team_1 = 0;
	score_team_2 = 0;
	situation = 0;
}

//! Inicializa as variaveis de controle, a thread de desenho e as threads de recebimento de informações
void Graphics::init( int argc, char** argv, bool debug, string camera, string ip ){
	//! argc e argv da função main devido a glutInit. Veja: [freeglut](http://freeglut.sourceforge.net/).
	this->argc = argc;
	this->argv = argv;
	this->debug = debug;
	this->camera = camera;
	this->ip = "tcp://" + ip + ":5555";

	cameraStatic = camera;
	staticDebug = this->debug;

	width = 920;
	height = 576;

	staticWidth = width;
	staticHeight = height;

	thread_draw = new thread( std::bind( &Graphics::draw_thread, this ));
	thread_state = new thread( std::bind( &Graphics::state_thread, this ));
	if(debug) {
		thread_debug_team1 = new thread( std::bind( &Graphics::debug_thread_team1, this ));
		thread_debug_team2 = new thread( std::bind( &Graphics::debug_thread_team2, this ));
	}

	thread_draw->join();
	thread_state->join();
	if(debug) {
		thread_debug_team1->join();
		thread_debug_team2->join();
	}
}

//! Define todas as callbacks e variáveis de controle
void Graphics::draw_thread(){
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE );
	glutInitWindowPosition( 5, 5 );
	glutInitWindowSize( width, height );
	glutCreateWindow( "VSS-Viewer" );
	glutDisplayFunc( drawWorld );
	glutReshapeFunc( changeWindowSize );
	glutKeyboardFunc( getKeyDown );
	glutTimerFunc( 5, timerHandler, 0 );

	initLight();

	//! qobj é utilizado para desenhar as rodas
	qobj = gluNewQuadric();
	gluQuadricNormals( qobj, GLU_SMOOTH );

	glutMainLoop();
}

void Graphics::debug_thread_team1(){
	//! Inicializa o recebimento de debug do time amarelo
	interface_debug_team1.createReceiveDebugTeam1( &global_debug_team1 );

	while(true) {
		//! Recebe um pacote novo
		interface_debug_team1.receiveDebugTeam1();

		//! Recebe os vetores de movimento
		for(int i = 0; i < global_debug_team1.step_poses_size(); i++) {
			if(global_debug_team1.step_poses( i ).y() != 0 && global_debug_team1.step_poses( i ).y() != 0) {
				robots.at( i ).has_step = true;
				robots.at( i ).step_pose.x = global_debug_team1.step_poses( i ).y() - (130 / 2.0);
				robots.at( i ).step_pose.y = global_debug_team1.step_poses( i ).x() - (170 / 2.0);
				robots.at( i ).step_pose.yaw = global_debug_team1.step_poses( i ).yaw() * 180.0 / M_PI;
			}else{
				robots.at( i ).has_step = false;
			}
		}

		//! Recebe as poses finais
		for(int i = 0; i < global_debug_team1.final_poses_size(); i++) {
			if(global_debug_team1.final_poses( i ).y() != 0 && global_debug_team1.final_poses( i ).y() != 0) {
				robots.at( i ).has_final = true;
				robots.at( i ).final_pose.x = global_debug_team1.final_poses( i ).y() - (130 / 2.0);
				robots.at( i ).final_pose.y = global_debug_team1.final_poses( i ).x() - (170 / 2.0);
				robots.at( i ).final_pose.yaw = global_debug_team1.final_poses( i ).yaw() * 180.0 / M_PI;
			}else{
				robots.at( i ).has_final = false;
			}
		}

		//! Recebe os caminhos
		for(int i = 0; i < global_debug_team1.paths_size(); i++) {
			Path path;
			for(int j = 0; j < global_debug_team1.paths( i ).poses_size(); j++) {
				Pose pose;
				pose.x = global_debug_team1.paths( i ).poses( j ).y() - (130 / 2.0);
				pose.y = global_debug_team1.paths( i ).poses( j ).x() - (170 / 2.0);
				pose.yaw = global_debug_team1.paths( i ).poses( j ).yaw() * 180.0 / M_PI;

				path.poses.push_back( pose );
			}
			robots.at( i ).path = path;
		}
	}
}

void Graphics::debug_thread_team2(){
	//! Inicializa o recebimento de debug do time azul
	interface_debug_team2.createReceiveDebugTeam2( &global_debug_team2 );

	while(true) {
		//! Recebe um pacote novo
		interface_debug_team2.receiveDebugTeam2();

		//! Recebe os vetores de movimento
		for(int i = 0; i < global_debug_team2.step_poses_size(); i++) {
			if(global_debug_team2.step_poses( i ).y() != 0 && global_debug_team2.step_poses( i ).y() != 0) {
				robots.at( i + 3 ).has_step = true;
				robots.at( i + 3 ).step_pose.x = global_debug_team2.step_poses( i ).y() - (130 / 2.0);
				robots.at( i + 3 ).step_pose.y = global_debug_team2.step_poses( i ).x() - (170 / 2.0);
				robots.at( i + 3 ).step_pose.yaw = global_debug_team2.step_poses( i ).yaw() * 180.0 / M_PI;
			}else{
				robots.at( i + 3 ).has_step = false;
			}
		}

		//! Recebe as poses finais
		for(int i = 0; i < global_debug_team2.final_poses_size(); i++) {
			if(global_debug_team2.final_poses( i ).y() != 0 && global_debug_team2.final_poses( i ).y() != 0) {
				robots.at( i + 3 ).has_final = true;
				robots.at( i + 3 ).final_pose.x = global_debug_team2.final_poses( i ).y() - (130 / 2.0);
				robots.at( i + 3 ).final_pose.y = global_debug_team2.final_poses( i ).x() - (170 / 2.0);
				robots.at( i + 3 ).final_pose.yaw = global_debug_team2.final_poses( i ).yaw() * 180.0 / M_PI;
			}else{
				robots.at( i + 3 ).has_final = false;
			}
		}

		//! Recebe os caminhos
		for(int i = 0; i < global_debug_team2.paths_size(); i++) {
			Path path;
			for(int j = 0; j < global_debug_team2.paths( i ).poses_size(); j++) {
				Pose pose;
				pose.x = global_debug_team2.paths( i ).poses( j ).y() - (130 / 2.0);
				pose.y = global_debug_team2.paths( i ).poses( j ).x() - (170 / 2.0);
				pose.yaw = global_debug_team2.paths( i ).poses( j ).yaw() * 180.0 / M_PI;

				path.poses.push_back( pose );
			}
			robots.at( i + 3 ).path = path;
		}
	}
}

void Graphics::state_thread(){
	//! Inicializa o recebimento de estados do VSS-Vision e VSS-Simulator
	interface_state.createSocketReceiveState( &global_state, ip );

	while(true) {
		//! Recebe um novo pacote
		interface_state.receiveState();
		global_state.id();

		//! Atualiza a posição da bola
		ball.x = global_state.balls( 0 ).pose().y() - (130 / 2.0);
		ball.y = global_state.balls( 0 ).pose().x() - (170 / 2.0);

		v_ball.x = global_state.balls( 0 ).v_pose().y();
		v_ball.y = global_state.balls( 0 ).v_pose().x();

		//! Atualiza as posições dos robôs
		for(int i = 0; i < 3; i++) {
			robots.at( i ).team = YELLOW;
			robots.at( i ).pose.x = global_state.robots_yellow( i ).pose().y() - (130 / 2.0);
			robots.at( i ).pose.y = global_state.robots_yellow( i ).pose().x() - (170 / 2.0);
			robots.at( i ).pose.yaw = global_state.robots_yellow( i ).pose().yaw() * 180.0 / M_PI;
			robots.at( i ).rgb_color.rgb[0] = global_state.robots_yellow( i ).color().r();
			robots.at( i ).rgb_color.rgb[1] = global_state.robots_yellow( i ).color().g();
			robots.at( i ).rgb_color.rgb[2] = global_state.robots_yellow( i ).color().b();

			robots.at( i + 3 ).team = BLUE;
			robots.at( i + 3 ).pose.x = global_state.robots_blue( i ).pose().y() - (130 / 2.0);
			robots.at( i + 3 ).pose.y = global_state.robots_blue( i ).pose().x() - (170 / 2.0);
			robots.at( i + 3 ).pose.yaw = global_state.robots_blue( i ).pose().yaw() * 180.0 / M_PI;
			robots.at( i + 3 ).rgb_color.rgb[0] = global_state.robots_blue( i ).color().r();
			robots.at( i + 3 ).rgb_color.rgb[1] = global_state.robots_blue( i ).color().g();
			robots.at( i + 3 ).rgb_color.rgb[2] = global_state.robots_blue( i ).color().b();
		}

		//! Se saiu um gol do time amarelo do VSS-Simulator, atualiza o placar do amarelo
		if(global_state.has_goals_yellow()) {
			static_score_team_1 = global_state.goals_yellow();
		}

		//! Se saiu um gol do time azul do VSS-Simulator, atualiza o placar do azul
		if(global_state.has_goals_blue()) {
			static_score_team_2 = global_state.goals_blue();
		}

		//! Se a estratégia possui um nome, atualiza o nome do amarelo
		if(global_state.has_name_yellow()) {
			static_name_team_1 = global_state.name_yellow();
		}

		//! Se a estratégia possui um nome, atualiza o nome do azul
		if(global_state.has_name_blue()) {
			static_name_team_2 = global_state.name_blue();
		}
	}
}

void Graphics::initLight( void ){
	GLfloat luzAmbiente[4] = { 0.35, 0.35, 0.35, 1.0 };
	GLfloat luzDifusa[4] = { 0.05, 0.05, 0.05, 1.0 };
	GLfloat luzEspecular[4] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat posLuz[4] = { 0, 100, 0, 1.0 };

	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, luzAmbiente );

	glLightfv( GL_LIGHT0, GL_AMBIENT, luzAmbiente );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv( GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv( GL_LIGHT0, GL_POSITION, posLuz );

	glEnable( GL_LINE_SMOOTH );
	glShadeModel( GL_SMOOTH );

	glClearColor( 0.05f, 0.05f, 0.3f, 1.0f );

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_NORMALIZE );

	glColorMaterial( GL_FRONT_AND_BACK, GL_DIFFUSE );

	glEnable( GL_LIGHTING );
	glEnable( GL_COLOR_MATERIAL );
	glEnable( GL_LIGHT0 );
}

void Graphics::changeWindowSize( GLsizei w, GLsizei h ){
	if (h == 0)
		h = 1;

	staticWidth = w;
	staticHeight = h;

	glViewport( 0, 0, w, h );
	float aspect = (float)w / h;
	float depthObs = 3000;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluPerspective( 60, aspect, 0.1f, depthObs );

	glMatrixMode( GL_MODELVIEW );
}

void Graphics::getKeyDown( unsigned char key, int x, int y ){
	switch (key) {
	case 27:
		exit( 0 );
		break;
	}

	glutPostRedisplay();
}

void Graphics::drawWorld( void ){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	//! Define a posição da camera como TV
	if(cameraStatic == "tv") {
		glTranslatef( 0.0f, 0.0f, -lookAt );
		glRotatef( rotX, 1, 0, 0 );

		glRotatef( rotY, 0, 1, 0 );
		glTranslatef( -obsX, -obsY, -obsZ );
	}else{
		//! Define a posição da camera como TOPO
		glTranslatef( 0.0f, 0.0f, 0 );
		glRotatef( 180.0, 1, 0, 0 );

		glRotatef( 90.0, 0, 1, 0 );
		glTranslatef( -130.0, 0.0, -0.0 );
	}

	//! Desenha o referencial global (No sistema de coordenadas da glut)
	drawGlobalReferential();
	//! Desenha campo
	drawField();
	//! Desenha a bola
	drawBall();
	//! Desenha placar
	drawScoreboard();

	//! Desenha as informações de debug
	for(unsigned int i = 0; i < robots.size(); i++) {
		drawRobot( i );
		if(staticDebug) {
			drawDebugPath( i );
			drawDebugFinalRobot( i );
			drawDebugStepRobot( i );
		}
	}

	if(staticDebug) {
		//! Desenha a posição futura da bola
		drawDebugFutureBall();
	}

	glutSwapBuffers();
}

void Graphics::timerHandler( int v ){
	glutPostRedisplay();
	//! Define a frequência de atualização
	glutTimerFunc( 5, timerHandler, 0 );
}

void Graphics::drawBall(){
	glPushMatrix();
	glTranslatef( THICK_THINGS * 1.4, ball.x, ball.y );
	material( ORANGE );
	glutSolidSphere( 2.0, 8.0, 8.0 );
	glPopMatrix();
}

void Graphics::drawDebugFutureBall(){
	Pose half_second, one_second;

	half_second.x = ball.x + (v_ball.x * 0.5);
	half_second.y = ball.y + (v_ball.y * 0.5);

	float radius = 2.3;
	glPushMatrix();
	glLineWidth( 2.0f );
	material( ORANGE );
	//! Desenha a bola em uma origem
	for(float arco = 0; arco < 2 * M_PI; arco += 0.05) {
		glBegin( GL_LINES );
		glVertex3f( 1, radius * cos( arco ) + half_second.x, radius * sin( arco ) + half_second.y );
		glVertex3f( 1, radius * cos((arco + 0.1)) + half_second.x, radius * sin((arco + 0.1)) + half_second.y );
		glEnd();
	}
	glPopMatrix();
}

//! Desenha o robô i
void Graphics::drawRobot( int i ){
	glPushMatrix();
	//! Desenha o corpo do robô
	glTranslatef( THICK_THINGS * 1.4, robots.at( i ).pose.x, robots.at( i ).pose.y );
	glRotatef( -robots.at( i ).pose.yaw, 1, 0, 0 );
	glScalef( SIZE_ROBOT, SIZE_ROBOT, SIZE_ROBOT );
	material( BLACK3 );
	glutSolidCube( 1 );

	//! Desenha a etiqueta do time. Azul ou Amarelo
	glPushMatrix();
	glTranslatef( 0.5, -0.2, -0.2 );
	glScalef( 0.1f, SIZE_SQUARE / SIZE_ROBOT, SIZE_SQUARE / SIZE_ROBOT );
	material( robots.at( i ).team );
	glutSolidCube( 1 );
	glPopMatrix();

	//! Desenha a segunda etiqueta do robô
	glPushMatrix();
	glTranslatef( 0.5, 0.2, 0.2 );
	glScalef( 0.1f, SIZE_SQUARE / SIZE_ROBOT, SIZE_SQUARE / SIZE_ROBOT );
	if(robots.at( i ).rgb_color.rgb[0] == 0 && robots.at( i ).rgb_color.rgb[1] == 0 && robots.at( i ).rgb_color.rgb[2] == 0) {
		//! Utiliza cores pré-definidas. Utilizado se obtém dados do VSS-Simulator
		material( robots.at( i ).color );
	}else{
		//! Utiliza cores RGB. Utilizado se obtém os dados do VSS-Vision
		material( robots.at( i ).rgb_color );
	}
	glutSolidCube( 1 );
	glPopMatrix();

	//! Desenha as rodas de um robô
	glPushMatrix();
	glRotatef( 90.0, 1, 0, 0 );
	glTranslatef( -0.10, 0.0, -0.61 );
	material( WHITE );
	gluCylinder( qobj, 0.2f, 0.2f, 1.2f, 16.0, 16.0 ); // Radius 1, Radius 2, Lenght, Precision1, Precision2
	glPopMatrix();

	glPopMatrix();
}

//! Desenha a pose final de um robô
void Graphics::drawDebugFinalRobot( int i ){
	if(robots.at( i ).has_final) {
		glPushMatrix();
		//! Desenha o corpo do robô transladado
		glTranslatef( 1.5, robots.at( i ).final_pose.x, robots.at( i ).final_pose.y );
		glRotatef( -robots.at( i ).final_pose.yaw, 1, 0, 0 );
		glScalef( 0.1f, SIZE_ROBOT, SIZE_ROBOT );
		material( GRAY );
		glLineWidth( 4.0f );
		glutWireCube( 1 );

		//! Desenha a etiqueta do time
		glPushMatrix();
		glTranslatef( 0.1, -0.2, -0.2 );
		glScalef( 0.1f, SIZE_SQUARE / SIZE_ROBOT, SIZE_SQUARE / SIZE_ROBOT );
		material( robots.at( i ).team );
		glutSolidCube( 1 );
		glPopMatrix();

		//! Desenha a etiqueta secundária do robô
		glPushMatrix();
		glTranslatef( 0.1, 0.2, 0.2 );
		glScalef( 0.1f, SIZE_SQUARE / SIZE_ROBOT, SIZE_SQUARE / SIZE_ROBOT );
		if(robots.at( i ).rgb_color.rgb[0] == 0 && robots.at( i ).rgb_color.rgb[1] == 0 && robots.at( i ).rgb_color.rgb[2] == 0) {
			//! Utiliza cores pré-definidas. Utilizado se obtém dados do VSS-Simulator
			material( robots.at( i ).color );
		}else{
			//! Utiliza cores RGB. Utilizado se obtém os dados do VSS-Vision
			material( robots.at( i ).rgb_color );
		}
		glutSolidCube( 1 );
		glPopMatrix();

		glPopMatrix();
	}
}

//! Desenha um vetor de movimento
void Graphics::drawDebugStepRobot( int i ){
	if(robots.at( i ).has_step) {
		glPushMatrix();
		if(robots.at( i ).rgb_color.rgb[0] == 0 && robots.at( i ).rgb_color.rgb[1] == 0 && robots.at( i ).rgb_color.rgb[2] == 0) {
			material( robots.at( i ).color );
		}else{
			material( robots.at( i ).rgb_color );
		}

		glBegin( GL_LINES );
		glVertex3f( 2, robots.at( i ).pose.x, robots.at( i ).pose.y );
		glVertex3f( 2, robots.at( i ).step_pose.x, robots.at( i ).step_pose.y );
		glEnd();
		glPopMatrix();
	}
}

//! Desenha um caminho
void Graphics::drawDebugPath( int i ){
	glPushMatrix();
	if(robots.at( i ).path.poses.size() >= 2) {
		if(robots.at( i ).rgb_color.rgb[0] == 0 && robots.at( i ).rgb_color.rgb[1] == 0 && robots.at( i ).rgb_color.rgb[2] == 0) {
			material( robots.at( i ).color );
		}else{
			material( robots.at( i ).rgb_color );
		}
		for(unsigned int j = 0; j < robots.at( i ).path.poses.size() - 1; j++) {
			glBegin( GL_LINES );
			glVertex3f( 1, robots.at( i ).path.poses.at( j ).x, robots.at( i ).path.poses.at( j ).y );
			glVertex3f( 1, robots.at( i ).path.poses.at( j + 1 ).x, robots.at( i ).path.poses.at( j + 1 ).y );
			glEnd();
		}
	}
	glPopMatrix();
}

void Graphics::drawGlobalReferential(){
	Pose pose = Pose( -65, -85, 0 );
	glPushMatrix();
	//! Desenha o referencial global X (RED) no 0 da coordenada
	glPushMatrix();
	glTranslatef( THICK_THINGS * 1.4, pose.x, 2.1 + pose.y );
	//glRotatef(0, 1, 0, 0);
	material( RED );
	glPushMatrix();
	glScalef( 0.6, 0.6, SIZE_ROBOT * 0.6 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( 0, 0, 2 );
	glutSolidCone( 1, 3, 10, 10 );
	glPopMatrix();
	glPopMatrix();

	//! Desenha o referencial global Y (GREEN) no 0 da coordenada
	glPushMatrix();
	glTranslatef( THICK_THINGS * 1.4, 2.1 + pose.x, pose.y );
	glRotatef( -90, 1, 0, 0 );
	material( GREEN );
	glPushMatrix();
	glScalef( 0.6, 0.6, SIZE_ROBOT * 0.6 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( 0, 0, 2 );
	glutSolidCone( 1, 3, 10, 10 );
	glPopMatrix();
	glPopMatrix();

	//! Desenha o referencial global Z (Blue) no 0 da coordenada
	glPushMatrix();
	glTranslatef( 2.1 + (THICK_THINGS * 1.4), pose.x, pose.y );
	glRotatef( 90, 0, 1, 0 );
	material( BLUE );
	glPushMatrix();
	glScalef( 0.6, 0.6, SIZE_ROBOT * 0.6 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( 0, 0, 2 );
	glutSolidCone( 1, 3, 10, 10 );
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}

void Graphics::drawField(){
	glPushMatrix();
	glScalef( 1, FIELD_DEPTH, FIELD_WIDTH );
	material( BLACK );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( 0, 0, -FIELD_WIDTH / 1.88 );
	glScalef( 1, GOAL_WIDTH + 2.0, GOAL_DEPTH + 2.0 );
	material( BLACK );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 0.0, (-FIELD_WIDTH / 1.88) - (THICK_THINGS) * 1.9 );
	glScalef( WALL_HEIGHT, GOAL_WIDTH + 2.0, 0.1 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 38, (-FIELD_WIDTH / 2.0) + 0.1 );
	glScalef( WALL_HEIGHT, 34, 0.1 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -37.7, (-FIELD_WIDTH / 2.0) + 0.1 );
	glScalef( WALL_HEIGHT, 34.2, 0.1 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( 0, 0, FIELD_WIDTH / 1.88 );
	glScalef( 1, GOAL_WIDTH + 2.0, GOAL_DEPTH + 2.0 );
	material( BLACK );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 0.0, (FIELD_WIDTH / 1.88) + (THICK_THINGS) * 1.9 );
	glScalef( WALL_HEIGHT, GOAL_WIDTH + 2.0, 0.1 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 38, (FIELD_WIDTH / 2.0) - 0.1 );
	glScalef( WALL_HEIGHT, 34, 0.1 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -38, (FIELD_WIDTH / 2.0) - 0.1 );
	glScalef( WALL_HEIGHT, 34, 0.1 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -FIELD_DEPTH / 2.0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, FIELD_WIDTH );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -FIELD_DEPTH / 2.0 + (THICK_THINGS / 2.0), 0 );
	glScalef( WALL_HEIGHT, 0.1, FIELD_WIDTH - (9.0 * 2.0));
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, FIELD_DEPTH / 2.0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, FIELD_WIDTH );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, FIELD_DEPTH / 2.0 - (THICK_THINGS / 2.0), 0 );
	glScalef( WALL_HEIGHT, 0.1, FIELD_WIDTH - (9.0 * 2.0));
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 43.2, -FIELD_WIDTH / 1.97 );
	glScalef( WALL_HEIGHT, WALL_TOPS_B, THICK_THINGS );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -43.2, -FIELD_WIDTH / 1.97 );
	glScalef( WALL_HEIGHT, WALL_TOPS_B, THICK_THINGS );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 0, (-FIELD_WIDTH / 1.98) - GOAL_DEPTH );
	glScalef( WALL_HEIGHT, GOAL_WIDTH + 1.25, THICK_THINGS );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -22, -FIELD_WIDTH / 1.85 );
	glScalef( WALL_HEIGHT, THICK_THINGS, GOAL_DEPTH + 1.35 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -20.6, -FIELD_WIDTH / 1.85 );
	glScalef( WALL_HEIGHT, 0.1, GOAL_DEPTH + 1.35 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 22, -FIELD_WIDTH / 1.85 );
	glScalef( WALL_HEIGHT, THICK_THINGS, GOAL_DEPTH + 1.35 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 20.6, -FIELD_WIDTH / 1.875 );
	glScalef( WALL_HEIGHT, 0.1, GOAL_DEPTH + 0.5 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 20.6, FIELD_WIDTH / 1.875 );
	glScalef( WALL_HEIGHT, 0.1, GOAL_DEPTH + 0.5 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -20.6, FIELD_WIDTH / 1.875 );
	glScalef( WALL_HEIGHT, 0.1, GOAL_DEPTH + 0.5 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 44.0, FIELD_WIDTH / 1.97 );
	glScalef( WALL_HEIGHT, WALL_TOPS_B, THICK_THINGS );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -44.0, FIELD_WIDTH / 1.97 );
	glScalef( WALL_HEIGHT, WALL_TOPS_B, THICK_THINGS );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 0, FIELD_WIDTH / 1.98 + GOAL_DEPTH );
	glScalef( WALL_HEIGHT, GOAL_WIDTH + 1.25, THICK_THINGS );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -22, FIELD_WIDTH / 1.85 );
	glScalef( WALL_HEIGHT, THICK_THINGS, GOAL_DEPTH + 1.35 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 22, FIELD_WIDTH / 1.85 );
	glScalef( WALL_HEIGHT, THICK_THINGS, GOAL_DEPTH + 1.35 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 4.5, (FIELD_WIDTH / 2.0) - 4.5 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 14.1 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 5.5, (FIELD_WIDTH / 2.0) - 5.5 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, 0.1, 14.5 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 3.0, (FIELD_WIDTH / 2.0) - 3.0 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 9.5 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 1.5, (FIELD_WIDTH / 2.0) - 1.5 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 5.5 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 5.5, -(FIELD_WIDTH / 2.0) + 5.5 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, 0.1, 14.5 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 4.5, -(FIELD_WIDTH / 2.0) + 4.5 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 14.1 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 3.0, -(FIELD_WIDTH / 2.0) + 3.0 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 9.5 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 1.5, -(FIELD_WIDTH / 2.0) + 1.5 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 5.5 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 5.5, (FIELD_WIDTH / 2.0) - 5.5 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, 0.1, 14.5 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 4.5, (FIELD_WIDTH / 2.0) - 4.5 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 14.1 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 3.0, (FIELD_WIDTH / 2.0) - 3.0 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 9.5 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 1.5, (FIELD_WIDTH / 2.0) - 1.5 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 5.5 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 5.5, -(FIELD_WIDTH / 2.0) + 5.5 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, 0.1, 14.5 );
	material( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 4.5, -(FIELD_WIDTH / 2.0) + 4.5 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 14.1 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 3.0, -(FIELD_WIDTH / 2.0) + 3.0 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 9.5 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 1.5, -(FIELD_WIDTH / 2.0) + 1.5 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 5.5 );
	material( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glLineWidth( 5.0f );
	material( WHITE );
	glBegin( GL_LINES );
	glVertex3f( 0.7, -FIELD_DEPTH / 2.0, 0 );
	glVertex3f( 0.7, FIELD_DEPTH / 2.0, 0 );
	glEnd();

	// CIRCLE CENTER
	float radius = 20.0;
	for(float arco = 0; arco < 2 * M_PI; arco += 0.05) {
		glBegin( GL_LINES );
		glVertex3f( 1, radius * cos( arco ), radius * sin( arco ));
		glVertex3f( 1, radius * cos((arco + 0.1)), radius * sin((arco + 0.1)) );
		glEnd();
	}

	// CIRCLE GOAL
	radius = 10.0;
	for(float arco = M_PI * 1.15; arco < 1.85 * M_PI; arco += 0.05) {
		glBegin( GL_LINES );
		glVertex3f( 1, radius * cos( arco ), 64.5 + radius * sin( arco ));
		glVertex3f( 1, radius * cos((arco + 0.1)), 64.5 + radius * sin((arco + 0.1)) );
		glEnd();
	}

	// CIRCLE GOAL
	radius = 10.0;
	for(float arco = 0.4; arco < M_PI * 0.85; arco += 0.05) {
		glBegin( GL_LINES );
		glVertex3f( 1, radius * cos( arco ), -64.5 + radius * sin( arco ));
		glVertex3f( 1, radius * cos((arco + 0.1)), -64.5 + radius * sin((arco + 0.1)) );
		glEnd();
	}

	// GOAL LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, -20, 75.5 );
	glVertex3f( 0.7, 20, 75.5 );
	glEnd();

	// AREA LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, -35, 60.5 );
	glVertex3f( 0.7, 35, 60.5 );
	glEnd();

	// AREA BOTTOM LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, 35, 60.5 );
	glVertex3f( 0.7, 35, 75 );
	glEnd();

	// AREA TOP LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, -35, 60.5 );
	glVertex3f( 0.7, -35, 75 );
	glEnd();

	// GOAL LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, -20, -75.5 );
	glVertex3f( 0.7, 20, -75.5 );
	glEnd();

	// AREA BOTTOM LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, 35, -60.5 );
	glVertex3f( 0.7, 35, -75 );
	glEnd();

	// AREA TOP LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, -35, -60.5 );
	glVertex3f( 0.7, -35, -75 );
	glEnd();

	// AREA LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, -35, -60.5 );
	glVertex3f( 0.7, 35, -60.5 );
	glEnd();

	// CROSS MIDDLE RIGHT
	glBegin( GL_LINES );
	glVertex3f( 0.7, 0, 37.5 - 2.5 );
	glVertex3f( 0.7, 0, 37.5 + 2.5 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.7, -2.5, 37.5 );
	glVertex3f( 0.7, 2.5, 37.5 );
	glEnd();

	// CROSS DOWN RIGHT
	glBegin( GL_LINES );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25, 37.5 - 2.5 );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25, 37.5 + 2.5 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25 - 2.5, 37.5 );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25 + 2.5, 37.5 );
	glEnd();

	// CROSS UP RIGHT
	glBegin( GL_LINES );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25, 37.5 - 2.5 );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25, 37.5 + 2.5 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25 - 2.5, 37.5 );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25 + 2.5, 37.5 );
	glEnd();

	// CROSS MIDDLE LEFT
	glBegin( GL_LINES );
	glVertex3f( 0.7, 0, -37.5 - 2.5 );
	glVertex3f( 0.7, 0, -37.5 + 2.5 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.7, -2.5, -37.5 );
	glVertex3f( 0.7, 2.5, -37.5 );
	glEnd();

	// CROSS DOWN LEFT
	glBegin( GL_LINES );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25, -37.5 - 2.5 );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25, -37.5 + 2.5 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25 - 2.5, -37.5 );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25 + 2.5, -37.5 );
	glEnd();

	// CROSS UP LEFT
	glBegin( GL_LINES );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25, -37.5 - 2.5 );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25, -37.5 + 2.5 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25 - 2.5, -37.5 );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25 + 2.5, -37.5 );
	glEnd();
	glPopMatrix();
}

void Graphics::drawScoreboard(){
	glPushMatrix();
	stringstream ss;
	ss << static_name_team_1 << " " << static_score_team_1 << " - " << static_score_team_2 << " " << static_name_team_2;
	material( WHITE );
	glRasterPos3f( 10, (staticHeight - staticHeight / 2.0) / 250.0 + 70, -70 );
	glutBitmapString( GLUT_BITMAP_HELVETICA_18, (const unsigned char *)ss.str().c_str());
	glPopMatrix();
}

void Graphics::material( Pixel p ){
	GLfloat diffuse[4];
	GLfloat ambient[4];
	GLfloat specular[4];
	GLfloat shininess;

	//! Converte RGB (0-255) para RGB (0-1)
	diffuse[0] = p.rgb[0] / 255.0;   diffuse[1] = p.rgb[1] / 255.0;   diffuse[2] = p.rgb[2] / 255.0;   diffuse[3] = 1.0;
	ambient[0] = p.rgb[0] / 255.0;   ambient[1] = p.rgb[1] / 255.0;   ambient[2] = p.rgb[2] / 255.0;   ambient[3] = 1.0;
	specular[0] = p.rgb[0] / 255.0;  specular[1] = p.rgb[1] / 255.0;  specular[2] = p.rgb[2] / 255.0;  specular[3] = 1.0;
	shininess = 10.0;

	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambient );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular );
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );
}

void Graphics::material( int color ){
	GLfloat diffuse[4];
	GLfloat ambient[4];
	GLfloat specular[4];
	GLfloat shininess;

	switch(color) {
	case ORANGE: {
		diffuse[0] = 1.0;   diffuse[1] = 0.4;   diffuse[2] = 0.2;   diffuse[3] = 1.0;
		ambient[0] = 1.0;   ambient[1] = 0.4;   ambient[2] = 0.2;   ambient[3] = 1.0;
		specular[0] = 1.0;  specular[1] = 0.4;  specular[2] = 0.2;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case BLUE: {
		diffuse[0] = 0.2;   diffuse[1] = 0.2;   diffuse[2] = 0.7;   diffuse[3] = 1.0;
		ambient[0] = 0.2;   ambient[1] = 0.2;   ambient[2] = 0.7;   ambient[3] = 1.0;
		specular[0] = 0.2;  specular[1] = 0.2;  specular[2] = 0.7;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case YELLOW: {
		diffuse[0] = 0.85;   diffuse[1] = 0.75;   diffuse[2] = 0.25;   diffuse[3] = 1.0;
		ambient[0] = 0.85;   ambient[1] = 0.75;   ambient[2] = 0.25;   ambient[3] = 1.0;
		specular[0] = 0.85;  specular[1] = 0.75;  specular[2] = 0.25;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case RED: {
		diffuse[0] = 0.7;   diffuse[1] = 0.2;   diffuse[2] = 0.2;   diffuse[3] = 1.0;
		ambient[0] = 0.7;   ambient[1] = 0.2;   ambient[2] = 0.2;   ambient[3] = 1.0;
		specular[0] = 0.7;  specular[1] = 0.2;  specular[2] = 0.2;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case GREEN: {
		diffuse[0] = 0.2;   diffuse[1] = 0.7;   diffuse[2] = 0.2;   diffuse[3] = 1.0;
		ambient[0] = 0.2;   ambient[1] = 0.7;   ambient[2] = 0.2;   ambient[3] = 1.0;
		specular[0] = 0.2;  specular[1] = 0.7;  specular[2] = 0.2;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case PURPLE: {
		diffuse[0] = 0.45;   diffuse[1] = 0.1;   diffuse[2] = 0.7;   diffuse[3] = 1.0;
		ambient[0] = 0.45;   ambient[1] = 0.1;   ambient[2] = 0.7;   ambient[3] = 1.0;
		specular[0] = 0.45;  specular[1] = 0.1;  specular[2] = 0.7;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case PINK: {
		diffuse[0] = 0.8;   diffuse[1] = 0.5;   diffuse[2] = 0.5;   diffuse[3] = 1.0;
		ambient[0] = 0.8;   ambient[1] = 0.5;   ambient[2] = 0.5;   ambient[3] = 1.0;
		specular[0] = 0.8;  specular[1] = 0.5;  specular[2] = 0.5;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case BROWN: {
		diffuse[0] = 0.4;   diffuse[1] = 0.2;   diffuse[2] = 0.1;   diffuse[3] = 1.0;
		ambient[0] = 0.4;   ambient[1] = 0.2;   ambient[2] = 0.1;   ambient[3] = 1.0;
		specular[0] = 0.4;  specular[1] = 0.2;  specular[2] = 0.1;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case BLACK: {
		diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
		ambient[0] = 0.1;   ambient[1] = 0.1;   ambient[2] = 0.1;   ambient[3] = 1.0;
		specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case BLACK2: {
		diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
		ambient[0] = 0.1;   ambient[1] = 0.1;   ambient[2] = 0.1;   ambient[3] = 1.0;
		specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case BLACK3: {
		diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
		ambient[0] = 0.0;   ambient[1] = 0.0;   ambient[2] = 0.0;   ambient[3] = 1.0;
		specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case WHITE: {
		diffuse[0] = 1.0;   diffuse[1] = 1.0;   diffuse[2] = 1.0;   diffuse[3] = 1.0;
		ambient[0] = 1.0;   ambient[1] = 1.0;   ambient[2] = 1.0;   ambient[3] = 1.0;
		specular[0] = 1.0;  specular[1] = 1.0;  specular[2] = 1.0;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case GRAY: {
		diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
		ambient[0] = 0.2;   ambient[1] = 0.2;   ambient[2] = 0.2;   ambient[3] = 1.0;
		specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case GRAY2: {
		diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
		ambient[0] = 0.4;   ambient[1] = 0.4;   ambient[2] = 0.4;   ambient[3] = 1.0;
		specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	}

	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambient );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular );
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );
}

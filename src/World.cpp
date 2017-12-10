/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <typeinfo>
#include "World.h"
#include "TopCamera.h"
#include "TvCamera.h"

World::World( IFieldDrawer *fieldDrawer, IRobotDrawer *robotDrawer, IBallDrawer *ballDrawer, ICamera *camera, Pose *ball, std::vector<Robot> *robots, std::vector<Path> *paths, std::vector<Pose> *stepPoses, std::vector<Pose> *finalPoses, bool *paused ){
	this->fieldDrawer = fieldDrawer;
	this->robotDrawer = robotDrawer;
	this->ballDrawer = ballDrawer;
	this->camera = camera;
	this->ball = ball;
	this->robots = robots;
	this->paths = paths;
	this->stepPoses = stepPoses;
	this->finalPoses = finalPoses;
	this->paused = paused;

	material = new Material();

	controlSender = new ControlSender( ball, robots );
}

void World::display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	camera->applyPosition();
	fieldDrawer->draw();
	ballDrawer->draw( ball );

	for(unsigned int i = 0; i < robots->size(); i++)
		robotDrawer->draw( &robots->at( i ));
}

void World::reshape( int width, int height ) {
	this->windowWidth = width;
	this->windowHeight = height;

	if(windowHeight < 500)
		windowHeight = 500;

	// Força proporção 16:9, 1.777777778 = 16/9
	windowWidth = windowHeight * 1.777777778;
	glutReshapeWindow( windowWidth, windowHeight );
	glViewport( 0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight );

	// 500 = altura minima da janela
	// Obtém a razão entre a altura do campo e a altura da janela
	// 0.072 = (altura da janela - altura do campo) / 500
	// 0.000013155 = função que define a diferença entre altura da janela e altura do campo de acordo com a resolução
	// Quando 500 a diferença é 0.072, quando 1080 a diferença é 0.079
	auto reasonY = 0.072 - ((500 - windowHeight) * 0.000013155);

	// Como o campo é menor do que a janela sempre, é 100% menos a reasonY
	// Assim é obtido a altura do campo
	fieldHeight = windowHeight * (1.0 - reasonY);

	// Aplica a porporção 17:13 do campo, assim obtendo o tamanho do campo
	fieldWidth = fieldHeight * 1.307692308;
}

void World::mouseButtonPress( int button, int state, int x, int y ){
	mouseAction = (MouseAction)button;
	mouseState = (MouseState)state;

	switch(mouseAction) {
	  case MouseAction::ScrollTop: {
		  // rotateRobot left
	  } break;
	  case MouseAction::ScrollDown: {
		  // rotateRobot right
	  } break;
	  case MouseAction::LeftClick: {
		  toggleSelectedRobotStrategy( new Pose((float)x, (float)y, 0.0 ));
	  } break;
	  default: {
		  std::cout << "[Warning]: Action not assigned." << std::endl;
	  } break;
	}
}

void World::mouseMove( int x, int y ){
	if(mouseAction == MouseAction::LeftClick and mouseState == MouseState::On)
		moveRobotStrategy( new Pose((float)x, (float)y, 0.0 ));
}

void World::specialKeyboardDown( int key, int x, int y ){
	SpecialKey keyPushed = (SpecialKey)key;

	switch(keyPushed) {
	  case SpecialKey::Left: {
		  rotateRobotStrategy( true );
	  } break;
	  case SpecialKey::Right: {
		  rotateRobotStrategy( false );
	  } break;
	  default: {

	  } break;
	}
}

void World::keyboardDown( unsigned char key, int x, int y ) {
	Key keyPushed = (Key)key;

	switch(keyPushed) {
	  case Key::c: {
		  changeCameraStrategy();
	  } break;
	  case Key::C: {
		  changeCameraStrategy();
	  } break;
	  case Key::Space: {
		  controlSender->send( !*paused );

		  if(*paused)
			  startStrategy();
		  else
			  pauseStrategy();
	  } break;
	  case Key::Esc: {
		  closeStrategy();
	  } break;
	  default: {
		  std::cout << keyPushed << std::endl;
	  } break;
	}
}

void World::toggleSelectedRobotStrategy( Pose *pose ){
	if(*paused) {
		auto t = Core::bulletToGlut( Core::windowToBullet( pose, windowWidth, windowHeight, fieldWidth, fieldHeight ));
		int bot = Core::robotMostCloseToClick( &t, robots );

		if(mouseState == MouseState::On)
			robots->at( bot ).setSelected( true );
		else
			for(unsigned int i = 0; i < robots->size(); i++)
				robots->at( i ).setSelected( false );
	}
}

void World::moveRobotStrategy( Pose *pose ){
	auto t = Core::bulletToGlut( Core::windowToBullet( pose, windowWidth, windowHeight, fieldWidth, fieldHeight ));
	for(unsigned int i = 0; i < robots->size(); i++)
		if(robots->at( i ).getSelected() == true) {
			robots->at( i ).pose.x = t.x;
			robots->at( i ).pose.y = t.y;
		}
}

void World::rotateRobotStrategy( bool direction ){
	for(unsigned int i = 0; i < robots->size(); i++)
		if(robots->at( i ).getSelected() == true) {
			if(direction)
				robots->at( i ).pose.yaw += 3.0;
			else
				robots->at( i ).pose.yaw -= 3.0;
		}
}

void World::closeStrategy(){
	std::cout << "[Info]: Exiting VSS-Viewer..." << std::endl;
	exit( 0 );
}

void World::changeCameraStrategy(){
	if(!*paused) {
		auto object = (string)typeid(*camera).name();

		if (object.find( "TvCamera" ) not_eq std::string::npos) {
			camera = new TopCamera();
			std::cout << "[Info]: Changed camera to Top." << std::endl;
		}else{
			camera = new TvCamera();
			std::cout << "[Info]: Changed camera to Tv." << std::endl;
		}
	}else{
		std::cout << "[Warning]: Can't change camera while simulation is paused. Press <space> to start simulation and enable camera exchange." << std::endl;
	}
}

void World::pauseStrategy(){
	*paused = true;
	camera = new TopCamera();
	std::cout << "[Info]: Simulation paused, changed camera to Top and camera exchange disabled." << std::endl;
}

void World::startStrategy(){
	*paused = false;
	std::cout << "[Info]: Simulation started, camera exchange enabled." << std::endl;
}

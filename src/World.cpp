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

World::World( IFieldDrawer *fieldDrawer, IRobotDrawer *robotDrawer, IBallDrawer *ballDrawer, ICamera *camera, Pose *ball, std::vector<Robot> *robots, bool *paused ){
	this->fieldDrawer = fieldDrawer;
	this->robotDrawer = robotDrawer;
	this->ballDrawer = ballDrawer;
	this->camera = camera;
	this->ball = ball;
	this->robots = robots;
	this->paused = paused;

	material = new Material();
	ballDrawer->setBall( ball );
}

void World::display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	camera->applyPosition();
	fieldDrawer->draw();
	ballDrawer->draw();

	for(unsigned int i = 0; i < robots->size(); i++) {
		robotDrawer->setRobot( &robots->at( i ) );
		robotDrawer->draw();
	}
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

	switch(mouseAction) {
	  case MouseAction::ScrollTop: {
		  // rotateRobot left
	  } break;
	  case MouseAction::ScrollDown: {
		  // rotateRobot right
	  } break;
	  default: {
		  auto t = Core::windowToBullet( new Pose( x, y, 0.0 ), windowWidth, windowHeight, fieldWidth, fieldHeight );
		  t = Core::bulletToGlut( t );
		  int bot = Core::robotMostCloseToClick( &t, robots );
		  robots->at( bot ).setSelected( true );
	  } break;
	}
}

void World::keyboardDown( unsigned char key, int x, int y ) {
	Key keyPushed = (Key)key;
	cout << keyPushed << endl;
	switch(keyPushed) {
	  case Key::c: {
		  changeCameraStrategy();
	  } break;
	  case Key::C: {
		  changeCameraStrategy();
	  } break;
	  case Key::Space: {
		  if(*paused)
			  startStrategy();
		  else
			  pauseStrategy();
	  } break;
	  case Key::Esc: {
		  closeStrategy();
	  } break;
	  default: {
		  // None
	  } break;
	}
}

void World::toggleSelectedRobot( Key key ){
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

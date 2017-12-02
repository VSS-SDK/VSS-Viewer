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

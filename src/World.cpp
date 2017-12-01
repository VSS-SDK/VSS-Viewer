/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <typeinfo>
#include "World.h"
#include "Cameras/TopCamera.h"
#include "Cameras/TvCamera.h"

World::World( IFieldDrawer *fieldDrawer, IRobotDrawer *robotDrawer, ICamera *camera ){
	this->fieldDrawer = fieldDrawer;
	this->robotDrawer = robotDrawer;
	this->camera = camera;
}

void World::display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	camera->applyPosition();
	fieldDrawer->draw();
	robotDrawer->draw();
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
	  case Key::ESC: {
		  closeStrategy();
	  } break;
	  default: {
		  // None
	  } break;
	}
}

void World::closeStrategy(){
	exit( 0 );
}

void World::changeCameraStrategy(){
	auto object = (string)typeid(*camera).name();

	if (object.find( "TvCamera" ) != std::string::npos) {
		camera = new TopCamera();
	}else{
		camera = new TvCamera();
	}
}

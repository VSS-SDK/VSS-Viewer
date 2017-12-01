/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "World.h"

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

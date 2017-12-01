/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "World.h"

World::World( IFieldDrawer *fieldDrawer, IRobotDrawer *robotDrawer ){
	this->fieldDrawer = fieldDrawer;
	this->robotDrawer = robotDrawer;
}

void World::display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glTranslatef( 0.0f, 0.0f, 0 );
	glRotatef( 180.0, 1, 0, 0 );
	glRotatef( 90.0, 0, 1, 0 );
	glTranslatef( -130.0, 0.0, -0.0 );

	fieldDrawer->draw();
	robotDrawer->draw();
}

/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Pose.h"

Pose::Pose(){
	x = y = yaw = 0.0;
}

Pose::Pose( float x, float y, float yaw ){
	this->x = x;
	this->y = y;
	this->yaw = yaw;
}

Pose::Pose( Pose *pose ){
	x = pose->x;
	y = pose->y;
	yaw = pose->yaw;
}

void Pose::setPose( Pose pose ){
	x = pose.x;
	y = pose.y;
	yaw = pose.yaw;
}

void Pose::setPose( float x, float y, float yaw ){
	this->x = x;
	this->y = y;
	this->yaw = yaw;
}

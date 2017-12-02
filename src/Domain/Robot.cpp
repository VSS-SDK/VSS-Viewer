/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Robot.h"

Robot::Robot(){
	pose = new Pose( 0, 0, 0 );
	teamColor = ColorName::Yellow;
	robotColor = ColorName::Green;
}

Robot::Robot( Pose *pose, ColorName teamColor, ColorName robotColor ){
	this->pose = pose;
	this->teamColor = teamColor;
	this->robotColor = robotColor;
}

Robot::Robot( Robot *robot ){
	pose = robot->pose;
	teamColor = robot->teamColor;
	robotColor = robot->robotColor;
}

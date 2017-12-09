/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Robot.h"

Robot::Robot(){
	pose = new Pose();
	teamColor = ColorName::Yellow;
	robotColor = ColorName::Green;
	selected = false;
}

Robot::Robot( Pose *pose, ColorName teamColor, ColorName robotColor ){
	this->pose = *pose;
	this->teamColor = teamColor;
	this->robotColor = robotColor;
	selected = false;
}

Robot::Robot( Robot *robot ){
	pose = robot->pose;
	teamColor = robot->teamColor;
	robotColor = robot->robotColor;
	selected = false;
}

void Robot::setSelected( bool selected ){
	this->selected = selected;
}

bool Robot::getSelected(){
	return selected;
}

void Robot::setPose( Pose pose ){
	this->pose = pose;
}

Pose Robot::getPose(){
	return pose;
}

void Robot::show(){
	pose.show();
	std::cout << "selected: " << selected << std::endl;
	std::cout << "teamColor:" << teamColor << std::endl;
	std::cout << "robotColor: " << robotColor << std::endl;
}

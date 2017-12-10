/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef CORE_MATH_H
#define CORE_MATH_H

#include <limits>
#include "Pose.h"
#include "Robot.h"
#include "math.h"

namespace Core {

float inline distance( const Pose &t1, const Pose &t2 ){
	return sqrt(((t1.x - t2.x) * (t1.x - t2.x)) + ((t1.y - t2.y) * (t1.y - t2.y)));
}

float inline distance( const Robot &t1, const Robot &t2 ){
	return sqrt(((t1.pose.x - t2.pose.x) * (t1.pose.x - t2.pose.x)) + ((t1.pose.y - t2.pose.y) * (t1.pose.y - t2.pose.y)));
}

float inline distance( const Robot &t1, const Pose &t2 ){
	return sqrt(((t1.pose.x - t2.x) * (t1.pose.x - t2.x)) + ((t1.pose.y - t2.y) * (t1.pose.y - t2.y)));
}

float inline distance( const Pose &t1, const Robot &t2 ){
	return sqrt(((t1.x - t2.pose.x) * (t1.x - t2.pose.x)) + ((t1.y - t2.pose.y) * (t1.y - t2.pose.y)));
}

Pose inline bulletToGlut( const Pose &bullet ){
	return new Pose( bullet.y - (130 / 2.0), bullet.x - (170 / 2.0), bullet.yaw * 180.0 / M_PI );
}

Pose inline glutToBullet( const Pose &glut ){
	return new Pose( glut.y + (170 / 2.0), glut.x + (130 / 2.0), glut.yaw * M_PI / 180.0 );
}

bool inline isOriginInGlut( const Pose &glut ){
	return (glut.x == -65 && glut.y == -85) ? true : false;
}

Pose inline windowToBullet( const Pose &window, float windowWidth, float windowHeight, float fieldWidth, float fieldHeight ){
	auto different_x = (windowWidth - fieldWidth) / 2.0;
	auto fc_x = window.x - different_x;
	auto new_x = fc_x * 170.0 / fieldWidth;

	auto different_y = (windowHeight - fieldHeight) / 2.0;
	auto fc_y = window.y - different_y;
	auto new_y = fc_y * 130 / fieldHeight;

	return new Pose( new_x, new_y, 0.0 );
}

int inline robotMostCloseToClick( Pose *click, std::vector<Robot> *robots ){
	auto minDistance = distance( click, robots->at( 0 ));
	auto idMinDistance = 0;

	for(unsigned int i = 1; i < robots->size(); i++) {
		auto actDistance = distance( click, robots->at( i ));
		if(actDistance < minDistance) {
			minDistance = actDistance;
			idMinDistance = i;
		}
	}

	return idMinDistance;
}

}

#endif // CORE_MATH_H

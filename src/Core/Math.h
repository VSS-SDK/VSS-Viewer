/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef CORE_MATH_H
#define CORE_MATH_H

#include "Pose.h"
#include "Robot.h"

float inline distance( const Pose &t1, const Pose &t2 ){
	return sqrt(((t1.x - t2.x) * (t1.x - t2.x)) + ((t1.y - t2.y) * (t1.y - t2.y)));
}

float inline distance( const Robot &t1, const Robot &t2 ){
	return sqrt(((t1.x - t2.x) * (t1.x - t2.x)) + ((t1.y - t2.y) * (t1.y - t2.y)));
}

float inline distance( const Robot &t1, const Pose &t2 ){
	return sqrt(((t1.x - t2.x) * (t1.x - t2.x)) + ((t1.y - t2.y) * (t1.y - t2.y)));
}

float inline distance( const Pose &t1, const Robot &t2 ){
	return sqrt(((t1.x - t2.x) * (t1.x - t2.x)) + ((t1.y - t2.y) * (t1.y - t2.y)));
}

#endif // CORE_MATH_H

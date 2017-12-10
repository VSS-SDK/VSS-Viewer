/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef IDEBUG_H
#define IDEBUG_H

#ifdef _WIN32
#include <windows.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#elif __linux
#include <GL/glut.h>
#endif

#include "Pose.h"
#include "Path.h"
#include "Robot.h"
#include "ColorEnum.h"

class IDebugDrawer {
public:

	void virtual drawPath( const Robot &robot, const Path &path ) = 0;
	void virtual drawStep( const Robot &robot, const Pose &stepPose ) = 0;
	void virtual drawFinal( const Robot &robot, const Pose &finalPose ) = 0;
};

#endif // IDEBUG_H

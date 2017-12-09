/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef DEBUG_DRAWER_BASE_H
#define DEBUG_DRAWER_BASE_H

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
#include "ColorEnum.h"

class DebugDrawerBase {
public:

	DebugDrawerBase();
	void virtual draw();
	void virtual setData( Pose *actPose, Pose *stepPose, Pose *finalPose, Path *path, ColorName teamColor, ColorName robotColor );
};

#endif // DEBUG_DRAWER_BASE_H

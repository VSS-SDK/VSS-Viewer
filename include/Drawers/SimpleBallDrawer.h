/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef SIMPLE_BALL_DRAWER_H
#define SIMPLE_BALL_DRAWER_H

#ifdef _WIN32
#include <windows.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#elif __linux
#include <GL/glut.h>
#endif

#include "IBallDrawer.h"
#include "Pose.h"
#include "ColorEnum.h"
#include "Material.h"

class SimpleBallDrawer : public IBallDrawer {
public:

	const float thickOfThings = 2.5;

	SimpleBallDrawer();

	void draw( Pose *pose ) override;
};
#endif // SIMPLE_BALL_DRAWER_H

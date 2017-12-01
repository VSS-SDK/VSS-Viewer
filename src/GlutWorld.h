/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef GLUT_WORLD_H
#define GLUT_WORLD_H

#include "vector"

#include "GlutFramework.h"
#include "FieldDrawer.h"
#include "RobotDrawer.h"
#include "Pose.h"

class GlutWorld : public GlutFramework {
public:

	Pose ball;
	std::vector<Pose> yellowTeam;
	std::vector<Pose> blueTeam;

	FieldDrawer fieldDrawer;
	RobotDrawer robotDrawer;

	GlutWorld();

	void display() override;
};

#endif // GLUT_WORLD_H

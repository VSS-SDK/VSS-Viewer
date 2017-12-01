/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef ROBOT_DRAWER_H
#define ROBOT_DRAWER_H

#include "Pose.h"
#include "Material.h"

class RobotDrawer {
public:

	Material material;
	GLUquadric* qobj;

	RobotDrawer();

	void draw( Pose pose, int colorTeam, int colorRobot );
};

#endif // ROBOT_DRAWER_H

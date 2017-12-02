/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef ROBOT_DRAWER_H
#define ROBOT_DRAWER_H

#include "../Interfaces/IRobotDrawer.h"
#include "../Domain/ColorEnum.h"
#include "../Domain/Pose.h"
#include "../Domain/Material.h"

class RobotDrawer : public IRobotDrawer {
public:

	Material *material;
	Pose *pose;
	ColorName teamColor;
	ColorName robotColor;
	GLUquadric *qobj;

	float robotWidth;
	float robotDepth;
	float robotHeight;
	const float colorLabelSize = 3.5;
	const float thickOfThings = 2.5;

	RobotDrawer();

	void draw() override;
	void setPose( Pose *pose ) override;
	void setTeamColor( ColorName teamColor ) override;
	void setRobotColor( ColorName robotColor ) override;
};

#endif // ROBOT_DRAWER_H

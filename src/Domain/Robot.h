/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Pose.h"
#include "ColorEnum.h"

class Robot {
public:

	Pose *pose;
	ColorName teamColor;
	ColorName robotColor;

	Robot();
	Robot( Pose *pose, ColorName teamColor, ColorName robotColor );
	Robot( Robot *robot );
};

#endif // ROBOT_H

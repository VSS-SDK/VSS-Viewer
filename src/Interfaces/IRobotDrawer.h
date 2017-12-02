/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef IROBOT_DRAWER_H
#define IROBOT_DRAWER_H

#include "Robot.h"

class IRobotDrawer {
public:

	IRobotDrawer();
	void virtual draw();
	void virtual setRobot( Robot *robot );
};

#endif // IROBOT_DRAWER_H

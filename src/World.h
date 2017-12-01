/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>

#include "../VSS-Interface/interface.h"
#include "Framework/GlutFramework.h"
#include "Interfaces/IFieldDrawer.h"
#include "Interfaces/IRobotDrawer.h"
#include "Interfaces/ICamera.h"
#include "Domain/Pose.h"
#include "Domain/AsciiEnum.h"

class World : public GlutFramework {
public:

	IFieldDrawer *fieldDrawer;
	IRobotDrawer *robotDrawer;
	ICamera *camera;

	World( IFieldDrawer *fieldDrawer, IRobotDrawer *robotDrawer, ICamera *camera );

	void display() override;
	void keyboardDown( unsigned char key, int x, int y ) override;

	// Strategies
	void closeStrategy();
	void changeCameraStrategy();
};

#endif // WORLD_H

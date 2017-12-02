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

#include "Framework/GlutFramework.h"
#include "../VSS-Interface/interface.h"
#include "Interfaces/IFieldDrawer.h"
#include "Interfaces/IRobotDrawer.h"
#include "Interfaces/ICamera.h"
#include "Domain/Pose.h"
#include "Domain/AsciiEnum.h"
#include "Domain/ColorEnum.h"
#include "Domain/Material.h"

class World : public GlutFramework {
public:

	bool *paused;
	IFieldDrawer *fieldDrawer;
	IRobotDrawer *robotDrawer;
	ICamera *camera;
	Pose *ball;
	std::vector<Pose> *robots;
	Material *material;

	World( IFieldDrawer *fieldDrawer, IRobotDrawer *robotDrawer, ICamera *camera, Pose *ball, std::vector<Pose> *robots, bool *paused );

	void display() override;
	void keyboardDown( unsigned char key, int x, int y ) override;

	// Strategies
	void closeStrategy();
	void changeCameraStrategy();
	void pauseStrategy();
	void startStrategy();
};

#endif // WORLD_H

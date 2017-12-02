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

#include "GlutFramework.h"
#include "interface.h"
#include "IFieldDrawer.h"
#include "IRobotDrawer.h"
#include "IBallDrawer.h"
#include "ICamera.h"
#include "Pose.h"
#include "AsciiEnum.h"
#include "ColorEnum.h"
#include "Material.h"

class World : public GlutFramework {
public:

	bool *paused;
	IFieldDrawer *fieldDrawer;
	IRobotDrawer *robotDrawer;
	IBallDrawer *ballDrawer;
	ICamera *camera;
	Pose *ball;
	std::vector<Robot> *robots;
	Material *material;

	World( IFieldDrawer *fieldDrawer, IRobotDrawer *robotDrawer, IBallDrawer *ballDrawer, ICamera *camera, Pose *ball, std::vector<Robot> *robots, bool *paused );

	void display() override;
	void keyboardDown( unsigned char key, int x, int y ) override;

	// Strategies
	void closeStrategy();
	void changeCameraStrategy();
	void pauseStrategy();
	void startStrategy();
};

#endif // WORLD_H

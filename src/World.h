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
#include "FieldDrawerBase.h"
#include "RobotDrawerBase.h"
#include "BallDrawerBase.h"
#include "CameraBase.h"
#include "Pose.h"
#include "AsciiEnum.h"
#include "ColorEnum.h"
#include "Material.h"
#include "Math.h"
#include "ControlSender.h"

class World : public GlutFramework {
public:

	MouseAction mouseAction;
	MouseState mouseState;

	string sendControlAddress;

	bool *paused;
	FieldDrawerBase *fieldDrawer;
	RobotDrawerBase *robotDrawer;
	BallDrawerBase *ballDrawer;
	CameraBase *camera;
	ControlSender *controlSender;
	Pose *ball;
	std::vector<Robot> *robots;
	Material *material;

	World( FieldDrawerBase *fieldDrawer, RobotDrawerBase *robotDrawer, BallDrawerBase *ballDrawer, CameraBase *camera, Pose *ball, std::vector<Robot> *robots, bool *paused );

	void display() override;
	void keyboardDown( unsigned char key, int x, int y ) override;
	void mouseButtonPress( int button, int state, int x, int y ) override;
	void reshape( int width, int height ) override;
	void mouseMove( int x, int y ) override;
	void specialKeyboardDown( int key, int x, int y ) override;

	// Strategies
	void closeStrategy();
	void changeCameraStrategy();
	void pauseStrategy();
	void startStrategy();
	void toggleSelectedRobotStrategy( Pose *pose );
	void moveRobotStrategy( Pose *pose );
	void rotateRobotStrategy( bool direction );
};

#endif // WORLD_H

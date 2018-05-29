/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef KERNEL_H
#define KERNEL_H

#include "mutex"
#include "thread"
#include "functional"

#include "CompetitionEnum.h"
#include "SimpleRobotDrawer.h"
#include "SimpleBallDrawer.h"
#include "FieldDrawerVerySmallSize.h"
#include "OriginalDebugDrawer.h"

#include "StateReceiver.h"
#include "DebugReceiver.h"

#include "TopCamera.h"
#include "World.h"

#include "Pose.h"
#include "Robot.h"
#include "Path.h"

class Kernel {
private:

	int argc;
	char **argv;

	Pose ball;
	std::vector<Robot> robots;
	std::vector<Pose> teamOneFinalPoses;
	std::vector<Pose> teamOneStepPoses;
	std::vector<Path> teamOnePaths;
	std::vector<Pose> teamTwoFinalPoses;
	std::vector<Pose> teamTwoStepPoses;
	std::vector<Path> teamTwoPaths;

	std::thread *worldThread;
	std::thread *receiveStateThread;
	std::thread *receiveDebugTeam1Thread;
	std::thread *receiveDebugTeam2Thread;

	std::string receiveStateAddress;

    std::mutex mutexDebugTeamYellow;
    std::mutex mutexDebugTeamBlue;

public:

	Kernel( int argc, char **argv );

	void init();
	void initialMessage();
	void instanceRobots();
	void instanceDebug();
	void worldThreadWrapper();
	void receiveStateThreadWrapper();
	void receiveDebugTeam1ThreadWrapper();
	void receiveDebugTeam2ThreadWrapper();

};

#endif // KERNEL_H

/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Domain/TeamType.h>
#include "DebugReceiver.h"

DebugReceiver::DebugReceiver( std::vector<Path> *paths, std::vector<Pose> *stepPoses, std::vector<Pose> *finalPoses, std::mutex *mutexDebug ){
	this->paths = paths;
	this->stepPoses = stepPoses;
	this->finalPoses = finalPoses;
	this->mutexDebug = mutexDebug;
}

void DebugReceiver::loop( vss::TeamType teamType ){
	this->teamType = teamType;
	this->interface = new Interface();

	if(teamType == vss::TeamType::Yellow)
		interface->createReceiveDebugTeam1( &global_debug );
	else
		interface->createReceiveDebugTeam2( &global_debug );

	while(true) {
		if(teamType == vss::TeamType::Blue)
			interface->receiveDebugTeam1();
		else
			interface->receiveDebugTeam2();

		mutexDebug->lock();

		for(int i = 0; i < global_debug.step_poses_size(); i++) {
			stepPoses->at( i ).x = global_debug.step_poses( i ).y() - (130 / 2.0);
			stepPoses->at( i ).y = global_debug.step_poses( i ).x() - (170 / 2.0);
			stepPoses->at( i ).yaw = global_debug.step_poses( i ).yaw() * 180.0 / M_PI;
		}

		for(int i = 0; i < global_debug.final_poses_size(); i++) {
			finalPoses->at( i ).x = global_debug.final_poses( i ).y() - (130 / 2.0);
			finalPoses->at( i ).y = global_debug.final_poses( i ).x() - (170 / 2.0);
			finalPoses->at( i ).yaw = global_debug.final_poses( i ).yaw() * 180.0 / M_PI;
		}

		for(int i = 0; i < global_debug.paths_size(); i++) {
			Path path;
			for(int j = 0; j < global_debug.paths( i ).poses_size(); j++) {
				Pose pose;
				pose.x = global_debug.paths( i ).poses( j ).y() - (130 / 2.0);
				pose.y = global_debug.paths( i ).poses( j ).x() - (170 / 2.0);
				pose.yaw = global_debug.paths( i ).poses( j ).yaw() * 180.0 / M_PI;

				path.poses.push_back( pose );
			}
			paths->at( i ) = path;
		}

		mutexDebug->unlock();
	}
}

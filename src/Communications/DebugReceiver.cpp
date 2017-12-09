/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "DebugReceiver.h"

DebugReceiver::DebugReceiver( std::vector<Path> *paths, std::vector<Pose> *stepPoses, std::vector<Pose> *finalPoses, bool *paused ){
	this->paths = paths;
	this->stepPoses = stepPoses;
	this->finalPoses = finalPoses;
	this->paused = paused;
}

void DebugReceiver::loop( TeamIndex teamIndex ){
	this->teamIndex = teamIndex;
	this->interface = new Interface();

	if(teamIndex == TeamIndex::TeamOne)
		interface->createReceiveDebugTeam1( &global_debug );
	else
		interface->createReceiveDebugTeam2( &global_debug );

	while(true) {
		paths->erase( paths->begin(), paths->end() );
		stepPoses->erase( stepPoses->begin(), stepPoses->end() );
		finalPoses->erase( finalPoses->begin(), finalPoses->end() );

		if(teamIndex == TeamIndex::TeamOne)
			interface->receiveDebugTeam1();
		else
			interface->receiveDebugTeam2();

		for(int i = 0; i < global_debug.step_poses_size(); i++) {
			Pose pose;
			pose.x = global_debug.step_poses( i ).y() - (130 / 2.0);
			pose.y = global_debug.step_poses( i ).x() - (170 / 2.0);
			pose.yaw = global_debug.step_poses( i ).yaw() * 180.0 / M_PI;
			stepPoses->push_back( pose );
		}

		for(int i = 0; i < global_debug.final_poses_size(); i++) {
			Pose pose;
			pose.x = global_debug.final_poses( i ).y() - (130 / 2.0);
			pose.y = global_debug.final_poses( i ).x() - (170 / 2.0);
			pose.yaw = global_debug.final_poses( i ).yaw() * 180.0 / M_PI;
			finalPoses->push_back( pose );
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
			paths->push_back( path.poses );
		}
	}
}

/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef DEBUG_RECEIVER_H
#define DEBUG_RECEIVER_H

#include "vector"
#include "interface.h"
#include "Pose.h"
#include "Path.h"
#include "TeamEnum.h"

class DebugReceiver {
public:

	Interface *interface;
	vss_debug::Global_Debug global_debug;
	std::vector<Pose> *finalPoses;
	std::vector<Pose> *stepPoses;
	std::vector<Path> *paths;
	TeamIndex teamIndex;
	bool *paused;

	DebugReceiver( std::vector<Path> *paths, std::vector<Pose> *stepPoses, std::vector<Pose> *finalPoses, bool *paused );
	void loop( TeamIndex teamIndex );
};

#endif // DEBUG_RECEIVER_H

/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef STATE_RECEIVER_H
#define STATE_RECEIVER_H

#include "vector"
#include "interface.h"
#include "Robot.h"

class StateReceiver {
public:

	Interface *interface;
	vss_state::Global_State global_state;
	Pose *ball;
	std::vector<Robot> *robots;

	StateReceiver( Pose *ball, std::vector<Robot> *robots );
	void loop( std::string address );
};

#endif

/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef CONTROL_SENDER_H
#define CONTROL_SENDER_H

#include "vector"
#include "interface.h"
#include "Robot3d.h"

class ControlSenderAdapter {
public:

	Interface interface;
	vss_control::User_Control user_control;
	vss::Pose *ball;
	std::vector<Robot3d> *robots;

	ControlSenderAdapter( vss::Pose *ball, std::vector<Robot3d> *robots );
	void send( bool paused );
};

#endif // CONTROL_SENDER_H

/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "ControlSender.h"
#include "Math.h"

ControlSender::ControlSender( Pose *ball, std::vector<Robot> *robots ){
	this->ball = ball;
	this->robots = robots;
	user_control = vss_control::User_Control();
	interface.createSendControl( &user_control );
}

void ControlSender::send( bool paused ){
	user_control = vss_control::User_Control();

	user_control.set_paused( paused );

	user_control.mutable_new_ball_pose()->set_x( ball->x );
	user_control.mutable_new_ball_pose()->set_y( ball->y );

	for(int i = 0; i < 3; i++) {
		vss_control::Pose *new_robots_blue_pose = user_control.add_new_robots_blue_pose();

		new_robots_blue_pose->set_x( robots->at( i ).x );
		new_robots_blue_pose->set_y( robots->at( i ).y );
		new_robots_blue_pose->set_yaw( robots->at( i ).yaw );
	}

	for(int i = 0; i < 3; i++) {
		vss_control::Pose *new_robots_yellow_pose = user_control.add_new_robots_yellow_pose();

		new_robots_yellow_pose->set_x( robots->at( i + 3 ).x );
		new_robots_yellow_pose->set_y( robots->at( i + 3 ).y );
		new_robots_yellow_pose->set_yaw( robots->at( i + 3 ).yaw );
	}

	interface.sendControl();
}

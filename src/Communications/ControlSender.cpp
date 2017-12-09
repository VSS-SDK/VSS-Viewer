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

	auto ball_n = Core::glutToBullet( ball );
	user_control.mutable_new_ball_pose()->set_x( ball_n.x );
	user_control.mutable_new_ball_pose()->set_y( ball_n.y );

	for(int i = 0; i < 3; i++) {
		vss_control::Pose *new_robots_blue_pose = user_control.add_new_robots_blue_pose();
		auto robot_n = Core::glutToBullet( robots->at( i + 3 ).pose );
		std::cout << robot_n.x << ", " << robot_n.y << std::endl;

		new_robots_blue_pose->set_x( robot_n.x );
		new_robots_blue_pose->set_y( robot_n.y );
		new_robots_blue_pose->set_yaw( robot_n.yaw );
	}

	for(int i = 0; i < 3; i++) {
		vss_control::Pose *new_robots_yellow_pose = user_control.add_new_robots_yellow_pose();
		auto robot_n = Core::glutToBullet( robots->at( i ).pose );

		new_robots_yellow_pose->set_x( robot_n.x );
		new_robots_yellow_pose->set_y( robot_n.y );
		new_robots_yellow_pose->set_yaw( robot_n.yaw );
	}

	interface.sendControl();
}

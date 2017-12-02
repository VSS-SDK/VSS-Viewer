/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "StateReceiver.h"

StateReceiver::StateReceiver( Pose *ball, std::vector<Robot> *robots ){
	this->ball = ball;
	this->robots = robots;
}

void StateReceiver::loop( string address ){
	this->interface = new Interface();
	interface->createSocketReceiveState( &global_state, address );

	while(true) {
		interface->receiveState();
		global_state.id();

		ball->x = global_state.balls( 0 ).pose().y() - (130 / 2.0);
		ball->y = global_state.balls( 0 ).pose().x() - (170 / 2.0);

		for(int i = 0; i < 3; i++) {
			robots->at( i ).pose->x = global_state.robots_yellow( i ).pose().y() - (130 / 2.0);
			robots->at( i ).pose->y = global_state.robots_yellow( i ).pose().x() - (170 / 2.0);
			robots->at( i ).pose->yaw = global_state.robots_yellow( i ).pose().yaw() * 180.0 / M_PI;

			robots->at( i + 3 ).pose->x = global_state.robots_blue( i ).pose().y() - (130 / 2.0);
			robots->at( i + 3 ).pose->y = global_state.robots_blue( i ).pose().x() - (170 / 2.0);
			robots->at( i + 3 ).pose->yaw = global_state.robots_blue( i ).pose().yaw() * 180.0 / M_PI;
		}
	}
}

/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "StateReceiver.h"
#include "Math.h"

StateReceiver::StateReceiver( Pose *ball, std::vector<Robot> *robots, bool *paused ){
	this->ball = ball;
	this->robots = robots;
	this->paused = paused;
}

void StateReceiver::loop( string address ){
	this->interface = new Interface();
	interface->createSocketReceiveState( &global_state, address );

	while(true) {
		interface->receiveState();
		global_state.id();
		*paused = global_state.paused();

		ball->setPose( Core::bulletToGlut( new Pose( global_state.balls( 0 ).pose().x(), global_state.balls( 0 ).pose().y(), 0.0 ) ) );

		for(int i = 0; i < 3; i++) {
			robots->at( i ).setPose( Core::bulletToGlut( new Pose( global_state.robots_yellow( i ).pose().x(), global_state.robots_yellow( i ).pose().y(), global_state.robots_yellow( i ).pose().yaw())));
			robots->at( i + 3 ).setPose( Core::bulletToGlut( new Pose( global_state.robots_blue( i ).pose().x(), global_state.robots_blue( i ).pose().y(), global_state.robots_blue( i ).pose().yaw())));
		}
	}
}

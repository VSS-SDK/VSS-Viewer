#include "Core.h"

Core::Core(){
}

void Core::init( int argc, char **argv ){
	this->argc = argc;
	this->argv = argv;
	this->address = "tcp://localhost:5555";

	worldThread = new thread( std::bind( &Core::worldThreadWrapper, this ));
	receiveStateThread = new thread( std::bind( &Core::receiveStateThreadWrapper, this ));
	worldThread->join();
	receiveStateThread->join();

	for(int i = 0; i < 6; i++)
		robots.push_back( new Pose( 0, 0, 0 ));
}

void Core::worldThreadWrapper(){
	auto fieldDrawerFactory = new FieldDrawerFactory();
	auto robotDrawer = new RobotDrawer();
	auto camera = new TvCamera();

	world = new World( fieldDrawerFactory->factory( CompetitionName::VerySmallSize ), robotDrawer, camera );
	world->start( argc, argv );
}

void Core::receiveStateThreadWrapper(){
	this->interface = new Interface();

	interface->createSocketReceiveState( &global_state, address );
	while(true) {
		cout << "asd" << endl;
		//! Recebe um novo pacote
		interface->receiveState();
		global_state.id();

		//! Atualiza a posição da bola
		ball.x = global_state.balls( 0 ).pose().y() - (130 / 2.0);
		ball.y = global_state.balls( 0 ).pose().x() - (170 / 2.0);

		//! Atualiza as posições dos robôs
		for(int i = 0; i < 3; i++) {
			robots.at( i ).x = global_state.robots_yellow( i ).pose().y() - (130 / 2.0);
			robots.at( i ).y = global_state.robots_yellow( i ).pose().x() - (170 / 2.0);
			robots.at( i ).yaw = global_state.robots_yellow( i ).pose().yaw() * 180.0 / M_PI;

			robots.at( i + 3 ).x = global_state.robots_blue( i ).pose().y() - (130 / 2.0);
			robots.at( i + 3 ).y = global_state.robots_blue( i ).pose().x() - (170 / 2.0);
			robots.at( i + 3 ).yaw = global_state.robots_blue( i ).pose().yaw() * 180.0 / M_PI;
		}
	}
}

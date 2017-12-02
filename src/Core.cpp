#include "Core.h"

Core::Core( int argc, char **argv ){
	this->paused = true;
	this->argc = argc;
	this->argv = argv;
	this->receiveStateAddress = "tcp://localhost:5555";

	ball = new Pose( 0, 0, 0 );
	robots.push_back( new Pose( -20, -40, 0 ));
	robots.push_back( new Pose( -20, -20, 0 ));
	robots.push_back( new Pose( -20, -60, 0 ));
	robots.push_back( new Pose( 20, 40, 0 ));
	robots.push_back( new Pose( 20, 20, 0 ));
	robots.push_back( new Pose( 20, 60, 0 ));
}

void Core::init(){
	worldThread = new thread( std::bind( &Core::worldThreadWrapper, this ));
	receiveStateThread = new thread( std::bind( &Core::receiveStateThreadWrapper, this ));
	worldThread->join();
	receiveStateThread->join();
}

void Core::worldThreadWrapper(){
	auto fieldDrawerFactory = new FieldDrawerFactory();
	auto fieldDrawer = fieldDrawerFactory->factory( CompetitionName::VerySmallSize );
	auto robotDrawer = new RobotDrawer();
	auto camera = new TvCamera();

	auto world = new World( fieldDrawer, robotDrawer, camera, &ball, &robots, &paused );
	world->start( argc, argv );
}

void Core::receiveStateThreadWrapper(){
	auto stateReceiver = new StateReceiver( &ball, &robots );
	stateReceiver->loop( receiveStateAddress );
}

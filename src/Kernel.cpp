#include "Kernel.h"

Kernel::Kernel( int argc, char **argv ){
	this->paused = true;
	this->argc = argc;
	this->argv = argv;
	this->receiveStateAddress = "tcp://localhost:5555";

	ball = new Pose( 0, 0, 0 );

	for(int i = 0; i < 6; i++) {
		robots.push_back( new Robot());
		if(i > 2)
			robots.at( i ).teamColor = ColorName::Blue;
	}

	robots.at( 0 ).setPose( new Pose( 0, 70, 0 ));
	robots.at( 0 ).robotColor = ColorName::Red;

	robots.at( 1 ).setPose( new Pose( -10, 10, 0 ));
	robots.at( 1 ).robotColor = ColorName::Green;

	robots.at( 2 ).setPose( new Pose( 30, 10, 0 ));
	robots.at( 2 ).robotColor = ColorName::Purple;

	robots.at( 3 ).setPose( new Pose( 0, -70, 0 ));
	robots.at( 3 ).robotColor = ColorName::Red;

	robots.at( 4 ).setPose( new Pose( 10, -10, 0 ));
	robots.at( 4 ).robotColor = ColorName::Green;

	robots.at( 5 ).setPose( new Pose( -30, -10, 0 ));
	robots.at( 5 ).robotColor = ColorName::Purple;

	initialMessage();
}

void Kernel::init(){
	worldThread = new thread( std::bind( &Kernel::worldThreadWrapper, this ));
	receiveStateThread = new thread( std::bind( &Kernel::receiveStateThreadWrapper, this ));
	receiveDebugTeam1Thread = new thread( std::bind( &Kernel::receiveDebugTeam1ThreadWrapper, this ));
	//receiveDebugTeam2Thread = new thread( std::bind( &Kernel::receiveDebugTeam2ThreadWrapper, this ));

	worldThread->join();
	receiveStateThread->join();
	receiveDebugTeam1Thread->join();
	//receiveDebugTeam2Thread->join();
}

void Kernel::worldThreadWrapper(){
	auto fieldDrawer = new FieldDrawerVerySmallSize();
	auto robotDrawer = new SimpleRobotDrawer();
	auto ballDrawer = new SimpleBallDrawer();
	auto debugDrawer = new OriginalDebugDrawer();
	auto camera = new TopCamera();

	auto world = new World( debugDrawer, fieldDrawer, robotDrawer, ballDrawer, camera, &ball, &robots, &paths, &stepPoses, &finalPoses, &paused );
	world->start( argc, argv );
}

void Kernel::receiveStateThreadWrapper(){
	auto stateReceiver = new StateReceiver( &ball, &robots, &paused );
	stateReceiver->loop( receiveStateAddress );
}

void Kernel::receiveDebugTeam1ThreadWrapper(){
	auto debugReceiver = new DebugReceiver( &paths, &stepPoses, &finalPoses, &paused );
	debugReceiver->loop( TeamIndex::TeamOne );
}

void Kernel::receiveDebugTeam2ThreadWrapper(){
	//auto debugReceiver = new DebugReceiver( &paths, &stepPoses, &finalPoses, &paused );
	//debugReceiver->loop( TeamIndex::TeamTwo );
}

void Kernel::initialMessage(){
	std::cout << "VSS-Viewer" << std::endl;
	std::cout << "[Info]: Waiting VSS-Simulator..." << std::endl;
	std::cout << "[Info]: Waiting debug messages..." << std::endl;
	std::cout << "[Info]: Simulation is paused by default and camera exchange is disabled. Press <space> to start simulation and enable camera exchange." << std::endl;
	std::cout << "[Info]: To exchange between cameras press <c>." << std::endl;
}

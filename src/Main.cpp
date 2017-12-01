/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Domain/CompetitionEnum.h"
#include "Factories/FieldDrawerFactory.h"
#include "Robots/RobotDrawer.h"
#include "Cameras/TvCamera.h"
#include "World.h"

int main( int argc, char *argv[] ) {
	auto fieldDrawerFactory = new FieldDrawerFactory();
	auto robotDrawer = new RobotDrawer();
	auto camera = new TvCamera();

	auto world = new World( fieldDrawerFactory->factory( CompetitionName::VerySmallSize ), robotDrawer, camera );

	world->startFramework( argc, argv );

	return 0;
}

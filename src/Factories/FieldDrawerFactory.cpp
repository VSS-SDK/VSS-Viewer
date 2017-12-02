/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "FieldDrawerFactory.h"
#include "../Drawers/FieldDrawers/FieldDrawerVerySmallSize.h"

FieldDrawerFactory::FieldDrawerFactory(){

}

IFieldDrawer* FieldDrawerFactory::factory( CompetitionName competitionName ){
	switch (competitionName) {
	  case CompetitionName::VerySmallSize:
		  return new FieldDrawerVerySmallSize();
	  case CompetitionName::MirosotMedium:
		  return new FieldDrawerVerySmallSize();
	  case CompetitionName::MirosotLarge:
		  return new FieldDrawerVerySmallSize();
	  default:
		  return new FieldDrawerVerySmallSize();
	}
}

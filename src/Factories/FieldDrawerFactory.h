/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef FIELD_DRAWER_FACTORY_H
#define FIELD_DRAWER_FACTORY_H

#include "../Domain/CompetitionEnum.h"
#include "../Interfaces/IFieldDrawer.h"

class FieldDrawerFactory {
public:

	FieldDrawerFactory();

	IFieldDrawer* factory( CompetitionName competitionName );
};

#endif // FIELD_DRAWER_FACTORY_H

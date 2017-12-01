/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef WORLD_H
#define WORLD_H

#include "vector"

#include "Framework/GlutFramework.h"
#include "Interfaces/IFieldDrawer.h"
#include "Interfaces/IRobotDrawer.h"
#include "Domain/Pose.h"

class World : public GlutFramework {
public:

	IFieldDrawer *fieldDrawer;
	IRobotDrawer *robotDrawer;

	World( IFieldDrawer *fieldDrawer, IRobotDrawer *robotDrawer );

	void display() override;
};

#endif // WORLD_H

/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef ORIGINAL_DEBUG_DRAWER_H
#define ORIGINAL_DEBUG_DRAWER_H

#ifdef _WIN32
#include <windows.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#elif __linux
#include <GL/glut.h>
#endif

#include "Pose.h"
#include "Path.h"
#include "ColorEnum.h"
#include "Material.h"
#include "IDebugDrawer.h"

class OriginalDebugDrawer : public IDebugDrawer {
public:

	Material *material;

	OriginalDebugDrawer();
	void virtual drawPath( Pose *actPose, Path *path, ColorName color ) override;
	void virtual drawStep( Pose *actPose, Pose *stepPose, ColorName color ) override;
	void virtual drawFinal( Pose *actPose, Pose *finalPose, ColorName teamColor, ColorName robotColor ) override;
};

#endif // ORIGINAL_DEBUG_DRAWER_H

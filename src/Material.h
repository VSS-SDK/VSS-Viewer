/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include <math.h>

#define FIELD_WIDTH   150.0
#define FIELD_DEPTH   130.0
#define GOAL_WIDTH    40.0
#define GOAL_DEPTH    10.0
#define WALL_HEIGHT   5.0
#define WALL_TOPS_B   45.0
#define THICK_THINGS   2.5
#define SIZE_ROBOT   8.0
#define SIZE_SQUARE   3.5

#ifdef _WIN32
#include <windows.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#elif __linux
#include <GL/glut.h>
#endif

enum { ORANGE = 0, BLUE = 1, YELLOW = 2, RED = 3, GREEN = 4, PURPLE = 5, PINK = 6, BROWN = 7, WHITE = 8, GRAY = 9, BLACK = 10, BLACK2 = 11, BLACK3 = 12, GRAY2 = 13 };

class Material {
private:

protected:

public:

	Material();
	void applyMaterial( int i );
};

#endif // MATERIAL_H

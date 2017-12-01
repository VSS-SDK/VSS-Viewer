/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef POINT_H
#define POINT_H

class Point {
public:

	float x, y, z;

	Point();
	Point( float x, float y, float z );
	Point( Point *point );
};

#endif // POINT_H

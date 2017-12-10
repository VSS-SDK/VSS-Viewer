/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef PATH_H
#define PATH_H

#include "vector"
#include "Pose.h"
#include "iostream"

class Path {
public:

	std::vector<Pose> poses;

	Path();
	Path( std::vector<Pose> poses );
	Path( Path *path );

	void setPath( Path *path );
	void setPath( std::vector<Pose> poses );

	friend std::ostream& operator<<( std::ostream& os, const Path& path );
};

#endif // PATH_H

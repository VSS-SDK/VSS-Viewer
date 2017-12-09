/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Path.h"

Path::Path(){

}

Path::Path( std::vector<Pose> poses ){
	this->poses = poses;
}

Path::Path( Path *path ){
	poses = path->poses;
}

void Path::setPath( Path *path ){
	poses = path->poses;
}

void Path::setPath( std::vector<Pose> poses ){
	this->poses = poses;
}

void Path::show(){
	std::cout << "Path" << std::endl;
	for(unsigned int i = 0; i < poses.size(); i++) {
		poses.at( i ).show();
	}
}

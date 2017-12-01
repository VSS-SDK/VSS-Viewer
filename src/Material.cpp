/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Material.h"

Material::Material(){

}

void Material::applyMaterial( int color ){
	GLfloat diffuse[4];
	GLfloat ambient[4];
	GLfloat specular[4];
	GLfloat shininess;

	switch(color) {
	case ORANGE: {
		diffuse[0] = 1.0;   diffuse[1] = 0.4;   diffuse[2] = 0.2;   diffuse[3] = 1.0;
		ambient[0] = 1.0;   ambient[1] = 0.4;   ambient[2] = 0.2;   ambient[3] = 1.0;
		specular[0] = 1.0;  specular[1] = 0.4;  specular[2] = 0.2;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case BLUE: {
		diffuse[0] = 0.2;   diffuse[1] = 0.2;   diffuse[2] = 0.7;   diffuse[3] = 1.0;
		ambient[0] = 0.2;   ambient[1] = 0.2;   ambient[2] = 0.7;   ambient[3] = 1.0;
		specular[0] = 0.2;  specular[1] = 0.2;  specular[2] = 0.7;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case YELLOW: {
		diffuse[0] = 0.85;   diffuse[1] = 0.75;   diffuse[2] = 0.25;   diffuse[3] = 1.0;
		ambient[0] = 0.85;   ambient[1] = 0.75;   ambient[2] = 0.25;   ambient[3] = 1.0;
		specular[0] = 0.85;  specular[1] = 0.75;  specular[2] = 0.25;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case RED: {
		diffuse[0] = 0.7;   diffuse[1] = 0.2;   diffuse[2] = 0.2;   diffuse[3] = 1.0;
		ambient[0] = 0.7;   ambient[1] = 0.2;   ambient[2] = 0.2;   ambient[3] = 1.0;
		specular[0] = 0.7;  specular[1] = 0.2;  specular[2] = 0.2;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case GREEN: {
		diffuse[0] = 0.2;   diffuse[1] = 0.7;   diffuse[2] = 0.2;   diffuse[3] = 1.0;
		ambient[0] = 0.2;   ambient[1] = 0.7;   ambient[2] = 0.2;   ambient[3] = 1.0;
		specular[0] = 0.2;  specular[1] = 0.7;  specular[2] = 0.2;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case PURPLE: {
		diffuse[0] = 0.45;   diffuse[1] = 0.1;   diffuse[2] = 0.7;   diffuse[3] = 1.0;
		ambient[0] = 0.45;   ambient[1] = 0.1;   ambient[2] = 0.7;   ambient[3] = 1.0;
		specular[0] = 0.45;  specular[1] = 0.1;  specular[2] = 0.7;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case PINK: {
		diffuse[0] = 0.8;   diffuse[1] = 0.5;   diffuse[2] = 0.5;   diffuse[3] = 1.0;
		ambient[0] = 0.8;   ambient[1] = 0.5;   ambient[2] = 0.5;   ambient[3] = 1.0;
		specular[0] = 0.8;  specular[1] = 0.5;  specular[2] = 0.5;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case BROWN: {
		diffuse[0] = 0.4;   diffuse[1] = 0.2;   diffuse[2] = 0.1;   diffuse[3] = 1.0;
		ambient[0] = 0.4;   ambient[1] = 0.2;   ambient[2] = 0.1;   ambient[3] = 1.0;
		specular[0] = 0.4;  specular[1] = 0.2;  specular[2] = 0.1;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case BLACK: {
		diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
		ambient[0] = 0.1;   ambient[1] = 0.1;   ambient[2] = 0.1;   ambient[3] = 1.0;
		specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case BLACK2: {
		diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
		ambient[0] = 0.1;   ambient[1] = 0.1;   ambient[2] = 0.1;   ambient[3] = 1.0;
		specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case BLACK3: {
		diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
		ambient[0] = 0.0;   ambient[1] = 0.0;   ambient[2] = 0.0;   ambient[3] = 1.0;
		specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case WHITE: {
		diffuse[0] = 1.0;   diffuse[1] = 1.0;   diffuse[2] = 1.0;   diffuse[3] = 1.0;
		ambient[0] = 1.0;   ambient[1] = 1.0;   ambient[2] = 1.0;   ambient[3] = 1.0;
		specular[0] = 1.0;  specular[1] = 1.0;  specular[2] = 1.0;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case GRAY: {
		diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
		ambient[0] = 0.2;   ambient[1] = 0.2;   ambient[2] = 0.2;   ambient[3] = 1.0;
		specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	case GRAY2: {
		diffuse[0] = 0.4;   diffuse[1] = 0.4;   diffuse[2] = 0.4;   diffuse[3] = 1.0;
		ambient[0] = 0.4;   ambient[1] = 0.4;   ambient[2] = 0.4;   ambient[3] = 1.0;
		specular[0] = 0.1;  specular[1] = 0.1;  specular[2] = 0.1;  specular[3] = 1.0;
		shininess = 10.0;
	} break;
	}

	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambient );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular );
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );
}

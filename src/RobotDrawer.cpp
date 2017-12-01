/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "RobotDrawer.h"

RobotDrawer::RobotDrawer(){
	qobj = gluNewQuadric();
	gluQuadricNormals( qobj, GLU_SMOOTH );
}

void RobotDrawer::draw( Pose pose, int colorTeam, int colorRobot ){

	glPushMatrix();
	//! Desenha o corpo do robô
	glTranslatef( THICK_THINGS * 1.4, pose.x, pose.y );
	glRotatef( -pose.yaw, 1, 0, 0 );
	glScalef( SIZE_ROBOT, SIZE_ROBOT, SIZE_ROBOT );
	material.applyMaterial( BLACK3 );
	glutSolidCube( 1 );

	//! Desenha a etiqueta do time. Azul ou Amarelo
	glPushMatrix();
	glTranslatef( 0.5, -0.2, -0.2 );
	glScalef( 0.1f, SIZE_SQUARE / SIZE_ROBOT, SIZE_SQUARE / SIZE_ROBOT );
	material.applyMaterial( colorTeam );
	glutSolidCube( 1 );
	glPopMatrix();

	//! Desenha a segunda etiqueta do robô
	glPushMatrix();
	glTranslatef( 0.5, 0.2, 0.2 );
	glScalef( 0.1f, SIZE_SQUARE / SIZE_ROBOT, SIZE_SQUARE / SIZE_ROBOT );
	material.applyMaterial( colorRobot );
	glutSolidCube( 1 );
	glPopMatrix();

	//! Desenha as rodas de um robô
	glPushMatrix();
	glRotatef( 90.0, 1, 0, 0 );
	glTranslatef( -0.10, 0.0, -0.61 );
	material.applyMaterial( WHITE );
	gluCylinder( qobj, 0.2f, 0.2f, 1.2f, 16.0, 16.0 ); // Radius 1, Radius 2, Lenght, Precision1, Precision2
	glPopMatrix();

	glPopMatrix();
}

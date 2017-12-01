/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "FieldDrawer.h"

FieldDrawer::FieldDrawer(){

}

void FieldDrawer::draw(){
	glPushMatrix();
	glScalef( 1, FIELD_DEPTH, FIELD_WIDTH );
	material.applyMaterial( BLACK );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( 0, 0, -FIELD_WIDTH / 1.88 );
	glScalef( 1, GOAL_WIDTH + 2.0, GOAL_DEPTH + 2.0 );
	material.applyMaterial( BLACK );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 0.0, (-FIELD_WIDTH / 1.88) - (THICK_THINGS) * 1.9 );
	glScalef( WALL_HEIGHT, GOAL_WIDTH + 2.0, 0.1 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 38, (-FIELD_WIDTH / 2.0) + 0.1 );
	glScalef( WALL_HEIGHT, 34, 0.1 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -37.7, (-FIELD_WIDTH / 2.0) + 0.1 );
	glScalef( WALL_HEIGHT, 34.2, 0.1 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( 0, 0, FIELD_WIDTH / 1.88 );
	glScalef( 1, GOAL_WIDTH + 2.0, GOAL_DEPTH + 2.0 );
	material.applyMaterial( BLACK );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 0.0, (FIELD_WIDTH / 1.88) + (THICK_THINGS) * 1.9 );
	glScalef( WALL_HEIGHT, GOAL_WIDTH + 2.0, 0.1 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 38, (FIELD_WIDTH / 2.0) - 0.1 );
	glScalef( WALL_HEIGHT, 34, 0.1 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -38, (FIELD_WIDTH / 2.0) - 0.1 );
	glScalef( WALL_HEIGHT, 34, 0.1 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -FIELD_DEPTH / 2.0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, FIELD_WIDTH );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -FIELD_DEPTH / 2.0 + (THICK_THINGS / 2.0), 0 );
	glScalef( WALL_HEIGHT, 0.1, FIELD_WIDTH - (9.0 * 2.0));
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, FIELD_DEPTH / 2.0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, FIELD_WIDTH );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, FIELD_DEPTH / 2.0 - (THICK_THINGS / 2.0), 0 );
	glScalef( WALL_HEIGHT, 0.1, FIELD_WIDTH - (9.0 * 2.0));
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 43.2, -FIELD_WIDTH / 1.97 );
	glScalef( WALL_HEIGHT, WALL_TOPS_B, THICK_THINGS );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -43.2, -FIELD_WIDTH / 1.97 );
	glScalef( WALL_HEIGHT, WALL_TOPS_B, THICK_THINGS );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 0, (-FIELD_WIDTH / 1.98) - GOAL_DEPTH );
	glScalef( WALL_HEIGHT, GOAL_WIDTH + 1.25, THICK_THINGS );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -22, -FIELD_WIDTH / 1.85 );
	glScalef( WALL_HEIGHT, THICK_THINGS, GOAL_DEPTH + 1.35 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -20.6, -FIELD_WIDTH / 1.85 );
	glScalef( WALL_HEIGHT, 0.1, GOAL_DEPTH + 1.35 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 22, -FIELD_WIDTH / 1.85 );
	glScalef( WALL_HEIGHT, THICK_THINGS, GOAL_DEPTH + 1.35 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 20.6, -FIELD_WIDTH / 1.875 );
	glScalef( WALL_HEIGHT, 0.1, GOAL_DEPTH + 0.5 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 20.6, FIELD_WIDTH / 1.875 );
	glScalef( WALL_HEIGHT, 0.1, GOAL_DEPTH + 0.5 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -20.6, FIELD_WIDTH / 1.875 );
	glScalef( WALL_HEIGHT, 0.1, GOAL_DEPTH + 0.5 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 44.0, FIELD_WIDTH / 1.97 );
	glScalef( WALL_HEIGHT, WALL_TOPS_B, THICK_THINGS );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -44.0, FIELD_WIDTH / 1.97 );
	glScalef( WALL_HEIGHT, WALL_TOPS_B, THICK_THINGS );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 0, FIELD_WIDTH / 1.98 + GOAL_DEPTH );
	glScalef( WALL_HEIGHT, GOAL_WIDTH + 1.25, THICK_THINGS );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -22, FIELD_WIDTH / 1.85 );
	glScalef( WALL_HEIGHT, THICK_THINGS, GOAL_DEPTH + 1.35 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, 22, FIELD_WIDTH / 1.85 );
	glScalef( WALL_HEIGHT, THICK_THINGS, GOAL_DEPTH + 1.35 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 4.5, (FIELD_WIDTH / 2.0) - 4.5 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 14.1 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 5.5, (FIELD_WIDTH / 2.0) - 5.5 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, 0.1, 14.5 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 3.0, (FIELD_WIDTH / 2.0) - 3.0 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 9.5 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 1.5, (FIELD_WIDTH / 2.0) - 1.5 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 5.5 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 5.5, -(FIELD_WIDTH / 2.0) + 5.5 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, 0.1, 14.5 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 4.5, -(FIELD_WIDTH / 2.0) + 4.5 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 14.1 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 3.0, -(FIELD_WIDTH / 2.0) + 3.0 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 9.5 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 1.5, -(FIELD_WIDTH / 2.0) + 1.5 );
	glRotatef( 45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 5.5 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 5.5, (FIELD_WIDTH / 2.0) - 5.5 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, 0.1, 14.5 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 4.5, (FIELD_WIDTH / 2.0) - 4.5 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 14.1 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 3.0, (FIELD_WIDTH / 2.0) - 3.0 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 9.5 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, -(FIELD_DEPTH / 2.0) + 1.5, (FIELD_WIDTH / 2.0) - 1.5 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 5.5 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 5.5, -(FIELD_WIDTH / 2.0) + 5.5 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, 0.1, 14.5 );
	material.applyMaterial( WHITE );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 4.5, -(FIELD_WIDTH / 2.0) + 4.5 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 14.1 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 3.0, -(FIELD_WIDTH / 2.0) + 3.0 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 9.5 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glTranslatef( THICK_THINGS, (FIELD_DEPTH / 2.0) - 1.5, -(FIELD_WIDTH / 2.0) + 1.5 );
	glRotatef( -45.0, 1, 0, 0 );
	glScalef( WALL_HEIGHT, THICK_THINGS, 5.5 );
	material.applyMaterial( BLACK2 );
	glutSolidCube( 1 );
	glPopMatrix();

	glPushMatrix();
	glLineWidth( 5.0f );
	material.applyMaterial( WHITE );
	glBegin( GL_LINES );
	glVertex3f( 0.7, -FIELD_DEPTH / 2.0, 0 );
	glVertex3f( 0.7, FIELD_DEPTH / 2.0, 0 );
	glEnd();

	// CIRCLE CENTER
	float radius = 20.0;
	for(float arco = 0; arco < 2 * M_PI; arco += 0.05) {
		glBegin( GL_LINES );
		glVertex3f( 1, radius * cos( arco ), radius * sin( arco ));
		glVertex3f( 1, radius * cos((arco + 0.1)), radius * sin((arco + 0.1)) );
		glEnd();
	}

	// CIRCLE GOAL
	radius = 10.0;
	for(float arco = M_PI * 1.15; arco < 1.85 * M_PI; arco += 0.05) {
		glBegin( GL_LINES );
		glVertex3f( 1, radius * cos( arco ), 64.5 + radius * sin( arco ));
		glVertex3f( 1, radius * cos((arco + 0.1)), 64.5 + radius * sin((arco + 0.1)) );
		glEnd();
	}

	// CIRCLE GOAL
	radius = 10.0;
	for(float arco = 0.4; arco < M_PI * 0.85; arco += 0.05) {
		glBegin( GL_LINES );
		glVertex3f( 1, radius * cos( arco ), -64.5 + radius * sin( arco ));
		glVertex3f( 1, radius * cos((arco + 0.1)), -64.5 + radius * sin((arco + 0.1)) );
		glEnd();
	}

	// GOAL LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, -20, 75.5 );
	glVertex3f( 0.7, 20, 75.5 );
	glEnd();

	// AREA LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, -35, 60.5 );
	glVertex3f( 0.7, 35, 60.5 );
	glEnd();

	// AREA BOTTOM LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, 35, 60.5 );
	glVertex3f( 0.7, 35, 75 );
	glEnd();

	// AREA TOP LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, -35, 60.5 );
	glVertex3f( 0.7, -35, 75 );
	glEnd();

	// GOAL LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, -20, -75.5 );
	glVertex3f( 0.7, 20, -75.5 );
	glEnd();

	// AREA BOTTOM LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, 35, -60.5 );
	glVertex3f( 0.7, 35, -75 );
	glEnd();

	// AREA TOP LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, -35, -60.5 );
	glVertex3f( 0.7, -35, -75 );
	glEnd();

	// AREA LINE
	glBegin( GL_LINES );
	glVertex3f( 0.7, -35, -60.5 );
	glVertex3f( 0.7, 35, -60.5 );
	glEnd();

	// CROSS MIDDLE RIGHT
	glBegin( GL_LINES );
	glVertex3f( 0.7, 0, 37.5 - 2.5 );
	glVertex3f( 0.7, 0, 37.5 + 2.5 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.7, -2.5, 37.5 );
	glVertex3f( 0.7, 2.5, 37.5 );
	glEnd();

	// CROSS DOWN RIGHT
	glBegin( GL_LINES );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25, 37.5 - 2.5 );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25, 37.5 + 2.5 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25 - 2.5, 37.5 );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25 + 2.5, 37.5 );
	glEnd();

	// CROSS UP RIGHT
	glBegin( GL_LINES );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25, 37.5 - 2.5 );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25, 37.5 + 2.5 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25 - 2.5, 37.5 );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25 + 2.5, 37.5 );
	glEnd();

	// CROSS MIDDLE LEFT
	glBegin( GL_LINES );
	glVertex3f( 0.7, 0, -37.5 - 2.5 );
	glVertex3f( 0.7, 0, -37.5 + 2.5 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.7, -2.5, -37.5 );
	glVertex3f( 0.7, 2.5, -37.5 );
	glEnd();

	// CROSS DOWN LEFT
	glBegin( GL_LINES );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25, -37.5 - 2.5 );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25, -37.5 + 2.5 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25 - 2.5, -37.5 );
	glVertex3f( 0.7, (FIELD_DEPTH / 2.0) - 25 + 2.5, -37.5 );
	glEnd();

	// CROSS UP LEFT
	glBegin( GL_LINES );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25, -37.5 - 2.5 );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25, -37.5 + 2.5 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25 - 2.5, -37.5 );
	glVertex3f( 0.7, -(FIELD_DEPTH / 2.0) + 25 + 2.5, -37.5 );
	glEnd();
	glPopMatrix();
}

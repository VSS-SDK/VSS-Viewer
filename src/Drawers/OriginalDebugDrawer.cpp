/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "OriginalDebugDrawer.h"

OriginalDebugDrawer::OriginalDebugDrawer(){
	material = new Material();
}

void OriginalDebugDrawer::drawPath( const Robot &robot, const Path &path ){

}

void OriginalDebugDrawer::drawStep( const Robot &robot, const Pose &stepPose ){
	glPushMatrix();
	material->applyMaterial( robot.robotColor );

	std::cout << robot << std::endl;
	std::cout << stepPose << std::endl;

	glBegin( GL_LINES );
	glVertex3f( 2, robot.pose.x, robot.pose.y );
	glVertex3f( 2, stepPose.x, stepPose.y );
	glEnd();
	glPopMatrix();
}

void OriginalDebugDrawer::drawFinal( const Robot &robot, const Pose &finalPose ){

}

/*void OriginalDebugDrawer::drawDebugFinalRobot(){
   if(robots.at( i ).has_final) {
   glPushMatrix();
   //! Desenha o corpo do robô transladado
   glTranslatef( 1.5, robots.at( i ).final_pose.x, robots.at( i ).final_pose.y );
   glRotatef( -robots.at( i ).final_pose.yaw, 1, 0, 0 );
   glScalef( 0.1f, SIZE_ROBOT, SIZE_ROBOT );
   material( GRAY );
   glLineWidth( 4.0f );
   glutWireCube( 1 );

   //! Desenha a etiqueta do time
   glPushMatrix();
   glTranslatef( 0.1, -0.2, -0.2 );
   glScalef( 0.1f, SIZE_SQUARE / SIZE_ROBOT, SIZE_SQUARE / SIZE_ROBOT );
   material( robots.at( i ).team );
   glutSolidCube( 1 );
   glPopMatrix();

   //! Desenha a etiqueta secundária do robô
   glPushMatrix();
   glTranslatef( 0.1, 0.2, 0.2 );
   glScalef( 0.1f, SIZE_SQUARE / SIZE_ROBOT, SIZE_SQUARE / SIZE_ROBOT );
   if(robots.at( i ).rgb_color.rgb[0] == 0 && robots.at( i ).rgb_color.rgb[1] == 0 && robots.at( i ).rgb_color.rgb[2] == 0) {
   //! Utiliza cores pré-definidas. Utilizado se obtém dados do VSS-Simulator
   material( robots.at( i ).color );
   }else{
   //! Utiliza cores RGB. Utilizado se obtém os dados do VSS-Vision
   material( robots.at( i ).rgb_color );
   }
   glutSolidCube( 1 );
   glPopMatrix();

   glPopMatrix();
   }
   }*/

/*void OriginalDebugDrawer::drawDebugPath(){
   glPushMatrix();
   if(robots.at( i ).path.poses.size() >= 2) {
   if(robots.at( i ).rgb_color.rgb[0] == 0 && robots.at( i ).rgb_color.rgb[1] == 0 && robots.at( i ).rgb_color.rgb[2] == 0) {
   material( robots.at( i ).color );
   }else{
   material( robots.at( i ).rgb_color );
   }
   for(unsigned int j = 0; j < robots.at( i ).path.poses.size() - 1; j++) {
   glBegin( GL_LINES );
   glVertex3f( 1, robots.at( i ).path.poses.at( j ).x, robots.at( i ).path.poses.at( j ).y );
   glVertex3f( 1, robots.at( i ).path.poses.at( j + 1 ).x, robots.at( i ).path.poses.at( j + 1 ).y );
   glEnd();
   }
   }
   glPopMatrix();
   }*/

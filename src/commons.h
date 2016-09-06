/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */


#ifndef _COMMONS_H_
#define _COMMONS_H_

#include "iostream"

using namespace std;

//! This namespace contains all custom datatypes used on the software, like: Pixel, Pose and Robot
namespace common{
	enum{ ORANGE = 0, BLUE = 1, YELLOW = 2, RED = 3, GREEN = 4, PURPLE = 5, PINK = 6, BROWN = 7, WHITE = 8, GRAY = 9, BLACK = 10, BLACK2 = 11, BLACK3 = 12, GRAY2 = 13 };
	enum{ SQUARE = 0, CIRCLE = 1 };

	//! This is a simple structure responsible for represent a color: RGB
	struct Pixel{
	    float rgb[3];  
	    Pixel(){
	    	rgb[0] = 0;
	    	rgb[1] = 0;
	    	rgb[2] = 0;
	    };
	    Pixel(float r, float g, float b){
	        rgb[0] = r;
	        rgb[1] = g;
	        rgb[2] = b;
	    };
	    Pixel(float rgb[3]){
	        for(int i = 0 ; i < 3 ; i++){
	            this->rgb[i] = rgb[i];
	        }
	    };
	    Pixel(Pixel *p){
	        for(int i = 0 ; i < 3 ; i++){
	            rgb[i] = p->rgb[i];
	        }
	    };
	    void show(){
	    	printf("Pixel(%.2f, %.2f, %.2f)\n", rgb[0], rgb[1], rgb[2]);
	    };
	};

	//! This is a simple structure responsible for represent a pose: X, Y and Orientation "Rotation". 
	struct Pose{
		float x;
		float y;
		float yaw;
		Pose(){
			x = 0;
			y = 0;
			yaw = 0;
		};
		Pose(float x, float y, float yaw){
			this->x = x;
			this->y = y;
			this->yaw = yaw;
		};
		Pose(Pose *p){
			x = p->x;
			y = p->y;
			yaw = p->yaw;
		};
		void show(){
			cout << "(" << x << ", " << y << ", " << yaw << ")" << endl;
		}
	};

	//! This is a simple structure responsible for represent a path: vector of poses. 
	struct Path{
		vector<Pose> poses;
		Path(){};
		Path(Path *path){
			poses = path->poses;
		};
		void show(){
			for(int i = 0 ; i < poses.size() ; i++)
			cout << "(" << poses.at(i).x << ", " << poses.at(i).y << ", " << poses.at(i).yaw << ")" << endl;
		}
	};

	//! This is a simple structure responsible for represente a robot: id, pose, team, color and etc.
	struct Robot{
		int id;
		Pose pose;
		Pose v_pose;
		Pose k_pose;
		Pose k_v_pose;
		Pose step_pose, final_pose;
		Path path;
		int team;
		int color;
		Pixel rgb_color;
		int team_label;
		int color_label;
		float radius;
		Robot(){
			id = 0;
			pose = v_pose = k_pose = k_v_pose = step_pose = final_pose = Pose(0, 0, 0);
			team = BLUE;
			color = WHITE;
			rgb_color = Pixel(0, 0, 0);
			team_label = SQUARE;
			color_label = SQUARE;
			radius = 1.0;
		};
		Robot(Robot *r){
			id = r->id;
			pose = r->pose;
			v_pose = r->v_pose;
			k_pose = r->k_pose;
			k_v_pose = r->k_v_pose;
			step_pose = r->step_pose;
			final_pose = r->final_pose;
			path = r->path;
			team = r->team;
			color = r->color;
			rgb_color = r->rgb_color;
			team_label = r->team_label;
			color_label = r->color_label;
			radius = r->radius;
		};
		void show(){
			cout << "-- Robot --" << endl;
			cout << "id: " << id << endl;
			cout << "team: " << team << endl;
			cout << "color: " << color << endl;
			cout << "team_label: " << team_label << endl;
			cout << "color_label: " << color_label << endl;
			cout << "radius: " << radius << endl;
			cout << "Pose" << endl;
			pose.show();
			cout << "Step" << endl;
			step_pose.show();
			cout << "Final" << endl;
			final_pose.show();
		}
	};
}

#define FIELD_WIDTH			150.0
#define FIELD_DEPTH 		130.0
#define GOAL_WIDTH 			40.0
#define GOAL_DEPTH 			10.0
#define WALL_HEIGHT 		5.0
#define WALL_TOPS_B			45.0
#define THICK_THINGS 		2.5
#define SIZE_ROBOT			8.0
#define SIZE_SQUARE			3.5

#endif
#ifndef _COMMONS_H_
#define _COMMONS_H_

namespace common{
	enum{ ORANGE = 0, BLUE = 1, YELLOW = 2, RED = 3, GREEN = 4, PURPLE = 5, PINK = 6, BROWN = 7, WHITE = 8, GRAY = 9, BLACK = 10, BLACK2 = 11, BLACK3 = 12 };
	enum{ SQUARE = 0, CIRCLE = 1 };

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
	};

	struct Robot{
		int id;
		Pose pose;
		int team;
		int color;
		Pixel rgb_color;
		int team_label;
		int color_label;
		float radius;
		Robot(){
			id = 0;
			pose = Pose(0, 0, 0);
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
			team = r->team;
			color = r->color;
			rgb_color = r->rgb_color;
			team_label = r->team_label;
			color_label = r->color_label;
			radius = r->radius;
		};
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
#ifndef _COMMONS_H_
#define _COMMONS_H_

namespace common{
	enum{ ORANGE = 0, BLUE = 1, YELLOW = 2, RED = 3, GREEN = 4, PURPLE = 5, PINK = 6, BROWN = 7, WHITE = 8, GRAY = 9, BLACK = 10, BLACK2 = 11, BLACK3 = 12 };
	enum{ SQUARE = 0, CIRCLE = 1 };

	struct Pose{
		int x;
		int y;
		float yaw;
		Pose(){
			x = 0;
			y = 0;
			yaw = 0;
		};
		Pose(int x, int y, int yaw){
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
		int team_label;
		int color_label;
		float radius;
		Robot(){
			id = 0;
			pose = Pose(0, 0, 0);
			team = BLUE;
			color = WHITE;
			team_label = SQUARE;
			color_label = SQUARE;
			radius = 1.0;
		};
		Robot(Robot *r){
			id = r->id;
			pose = r->pose;
			team = r->team;
			color = r->color;
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
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
#include "vector"
#include "stdio.h"

using namespace std;

//! Esse namespace contém todos os tipos de dados passivos utilizados no software, como: Pixel, Pose e Robô
namespace common{
	//! Definição de cores
	enum{ ORANGE = 0, BLUE = 1, YELLOW = 2, RED = 3, GREEN = 4, PURPLE = 5, PINK = 6, BROWN = 7, WHITE = 8, GRAY = 9, BLACK = 10, BLACK2 = 11, BLACK3 = 12, GRAY2 = 13 };
	//! Definição das etiquetas
	enum{ SQUARE = 0, CIRCLE = 1 };

	//! Essa struct é responsável por representar uma cor em RGB
	struct Pixel{
		//! rgb[3]: rgb[r], rgb[g], rgb[b]
	    float rgb[3];
		//! Construtor DEFAULT
	    Pixel(){
	    	rgb[0] = 0;
	    	rgb[1] = 0;
	    	rgb[2] = 0;
	    };
		//! Construtor(r, g, b)
	    Pixel(float r, float g, float b){
	        rgb[0] = r;
	        rgb[1] = g;
	        rgb[2] = b;
	    };
		//! Construtor(rgb[3])
	    Pixel(float rgb[3]){
	        for(int i = 0 ; i < 3 ; i++){
	            this->rgb[i] = rgb[i];
	        }
	    };
		//! Construtor cópia
	    Pixel(Pixel *p){
	        for(int i = 0 ; i < 3 ; i++){
	            rgb[i] = p->rgb[i];
	        }
	    };
		//! Método de debug no terminal
	    void show(){
	    	printf("Pixel(%.2f, %.2f, %.2f)\n", rgb[0], rgb[1], rgb[2]);
	    };
	};

	//! Essa struct é responsável por representar uma Pose, isto é, Posição e Orientação de um corpo rígido do espaço do futebol de robôs
	struct Pose{
		//! Posição em X
		float x;
		//! Posição em Y
		float y;
		//! Orientação em Z
		float yaw;
		//! Construtor DEFAULT
		Pose(){
			x = 0;
			y = 0;
			yaw = 0;
		};
		//! Construtor(x, y, yaw)
		Pose(float x, float y, float yaw){
			this->x = x;
			this->y = y;
			this->yaw = yaw;
		};
		//! Construtor cópia
		Pose(Pose *p){
			x = p->x;
			y = p->y;
			yaw = p->yaw;
		};
		//! Método de debug no terminal
		void show(){
			cout << "(" << x << ", " << y << ", " << yaw << ")" << endl;
		}
	};

	//! Essa struct é responsável por representar um caminho.
	struct Path{
		//! Um caminho é tido como uma sequência de poses
		vector<Pose> poses;
		//! Construtor DEFAULT
		Path(){};
		//! Construtor cópia
		Path(Path *path){
			poses = path->poses;
		};
		//! Método de debug no terminal
		void show(){
			for(unsigned int i = 0 ; i < poses.size() ; i++)
			cout << "(" << poses.at(i).x << ", " << poses.at(i).y << ", " << poses.at(i).yaw << ")" << endl;
		}
	};

	//! Essa struct é responsável por representar um robô
	struct Robot{
		//! Id do robô
		int id;
		//! Pose de um robô no campo
		Pose pose;
		//! Velocidades linear, tangencial e angular de um robô no campo
		Pose v_pose;
		//! Estimação da pose do robô pelo filtro de kalman. Utilizado somente com pacote vindo do VSS-Vision
		Pose k_pose;
		//! Estimação das velocidades linear, tangencial e angular pelo filtro de kalman. Utilizado somente com pacote vindo do VSS-Vision
		Pose k_v_pose;
		//! Vetor de movimentação, isto é, para onde o robô irá
		Pose step_pose;
		//! Pose final do robô
		Pose final_pose;
		//! Caminho que um robô irá executar.
		Path path;
		//! Id do time: 0 = amarelo, 1 = azul
		int team;
		//! Cor do robô, com base no enum de cores. Utilizado com o VSS-Simulator
		int color;
		//! Cor do robô, com base no valor RGB. Utilizado com o VSS-Vision
		Pixel rgb_color;
		//! TODO
		int team_label;
		//! TODO
		int color_label;
		//! Raio do robô
		float radius;
		//! Booleano que define se o pacote de debug possui um vetor de movimentação
		bool has_step;
		//! Booleano que define se o pacote de debug possui uma pose final
		bool has_final;
		//! Construtor DEFAULT
		Robot(){
			id = 0;
			pose = v_pose = k_pose = k_v_pose = step_pose = final_pose = Pose(0, 0, 0);
			team = BLUE;
			color = WHITE;
			rgb_color = Pixel(0, 0, 0);
			team_label = SQUARE;
			color_label = SQUARE;
			radius = 1.0;
			has_step = has_final = false;
		};
		//! Construtor cópia
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
			has_step = r->has_step;
			has_final = r->has_final;
		};
		//! Método de debug no terminal
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

/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <GL/glut.h>
#include <GL/freeglut.h>
#include "math.h"
#include "iostream"
#include "vector"
#include "thread"

#include "interface.h"
#include "commons.h"

using namespace common;
using namespace std;

//! Essa classe é responsável por desenhar o mundo 3D e receber os estados do VSS-Simulator e VSS-Vision
class Graphics{
protected:
    //! Parâmetro utilizado pela Glut
    int argc;
    //! Parâmetro utilizado pela Glut
    char** argv;
    //! Define se debug está ligado ou não
    bool debug;
    //! Câmera utilizada: TV ou TOPO
    string camera;
    //! Ip do PC que esteja rodando o VSS-Vision ou VSS-Simulator. Por DEFAULT é localhost ou 127.0.0.1
    string ip;
    //! Define se a tela de ajuda deve ser mostrada
    bool help;

    //! Largura da janela de desenho
    float width;
    //! Altura da janela de desenho
    float height;

    //! Thread responsável para desenhar o ambiente
    thread *thread_draw;
    //! Thread responsável por receber os estados do VSS-Vision e VSS-Simulator
    thread *thread_state;
    //! Thread responsável por receber os pacotes de debug do time amarelo
    thread *thread_debug_team1;
    //! Thread responsável por receber os pacotes de debug do time azul
    thread *thread_debug_team2;

    //! Interface de comunicação responsável por receber estados do VSS-Vision e VSS-Simulator
    Interface interface_state;
    //! Interface de comunicação responsável por receber os pacotes de debug do time amarelo
    Interface interface_debug_team1;
    //! Interface de comunicação responsável por receber os pacotes de debug do time azul
    Interface interface_debug_team2;

    //! Pacote que carrega os estados do VSS-Vision e VSS-Simulator
    vss_state::Global_State global_state;
    //! Pacote que carrega as informações de debug do time amarelo
    vss_debug::Global_Debug global_debug_team1;
    //! Pacote que carrega as informações de debug do time azul
    vss_debug::Global_Debug global_debug_team2;

    //! Nome dos times amarelo e azul
    string name_team_1, name_team_2;
    //! Placar
    int score_team_1, score_team_2;
    //! Situação de jogo
    int situation;
public:
    //! Construtor DEFAULT
    Graphics();

    //! Método responsável por inicializar o software
    void init(int argc, char** argv, bool debug, string camera, string ip);

    //! Método responsável por carregar a thread de desenho.
    void draw_thread();

    //! Metodo responsável por carregar a thread de recebimento de estados do VSS-Vision e VSS-Simulator
    void state_thread();

    //! Método responsável por carregar a thread de recebimento de informações de debug do time1
    void debug_thread_team1();

    //! Método responsável por carregar a thread de recebimento de informações de debug do time2
    void debug_thread_team2();

    //! Método responsável por desenhar o ambiente 3D
    static void drawWorld();

    //! Método responsável por definir a luz ambiente, difusa, especular e a posição
    static void initLight();

    //! Método (Callback) responsável por redesenhar o mundo 3D mantendo ao menos 30 Fps
    static void timerHandler(int v);

    //! Método (Callback) responsável por atualizar as váriaveis de controle se o usuário mudar o tamanho da janela
    static void changeWindowSize(GLsizei w, GLsizei h);

    //! Método (Callback) responsável por pela leitura do teclado
    static void getKeyDown(unsigned char tecla, int x, int y);

    //! Método responsável for definir a cor 3D do material: ORANGE, BLUE, YELLOW, RED, GREEN, PURPLE, PINK, BROWN, WHITE, GRAY, BLACK, BLACK2, BLACK3.
    static void material(int color = BLACK);

    //! Método responsável por definir a cor 3D do material, recebendo um valor RGB
    static void material(Pixel);

    //! Método responsável por desenhar o campo: chão e paredes
    static void drawField();

    //! Método responsável desenhar um robô: corpo e rodas
    static void drawRobot(int);

    //! Método responsável por desenhar a pose final de um robô
    static void drawDebugFinalRobot(int);

    //! Método responsável por desenhar o vetor de movimento de um robô
    static void drawDebugStepRobot(int);

    //! Método responsável por desennhar um caminho de um robô
    static void drawDebugPath(int);

    //! Método responsável por desenhar a bola
    static void drawBall();

    //! Método responsável por desenhar a bola no futuro
    static void drawDebugFutureBall();

    //! Método responsável por desenhar o referencial global Pose(0, 0, 0)
    static void drawGlobalReferential();

    //! Método responsável por desenhar o placar do jogo
    static void drawScoreboard();
};

#endif  // _GRAPHICS_H_

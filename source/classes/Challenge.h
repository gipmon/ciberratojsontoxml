#include <iostream>
#include "Maze.h"

class Challenge {
    private:
    char* challenge_name;
    char* challenge_type; /* "competitive" ou "collaborative". */
    int cycle_time; /* e um numero inteiro e indica o perıodo de simulacao
em milissegundos. */
    int duration; /* e um numero inteiro e indica a duracao total da simulacao em numero de ciclos. */

    //ExtraParamList *pm = new ExtraParamList();
    /* Na ExtraParamList estão presentes 3 classes:
        - A entrada "robot modelling parameters" indica os valores de par
        ametros usados para caraterizar os sensores e os atuadores dos corpos virtuais dos robos e para caraterizar o acesso que os agentes tem aos sensores.
        - A entrada "scoring parameters" indica os valores de parametros usados para calcular a pontuacao dos robos.
        - A entrada "debugging parameters" indica os valores de parametros que permitem o acesso a informacao extra durante a fase de desenvolvimento. */

	public:
    Maze *maze; /* descreve o cenario de atuacao dos robos */

    Challenge(char* ct, char* cn, int t, int d){
        challenge_name = cn;
        challenge_type = ct;
        cycle_time = t;
        duration = d;
        maze = new Maze();
    }
    Challenge(){
        maze = new Maze();
    }

    void setChallengeName(char*);
    void setChallengeType(char*);
    void setCycleTime(int);
    void setDuration(int);

    void printTest();

    void addParameter();
};
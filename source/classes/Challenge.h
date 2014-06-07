#include <iostream>
#include <fstream>
#include "Maze.h"
#include "ExtraParamList.h"

using namespace std;

class Challenge {
    private:
    char* challenge_name;
    char* challenge_type; /* "competitive" ou "collaborative". */
    int cycle_time; /* e um numero inteiro e indica o perıodo de simulacao
em milissegundos. */
    int duration; /* e um numero inteiro e indica a duracao total da simulacao em numero de ciclos. */

    /* Na ExtraParamList estão presentes 3 classes:
        - A entrada "robot modelling parameters" indica os valores de par
        ametros usados para caraterizar os sensores e os atuadores dos corpos virtuais dos robos e para caraterizar o acesso que os agentes tem aos sensores.
        - A entrada "scoring parameters" indica os valores de parametros usados para calcular a pontuacao dos robos.
        - A entrada "debugging parameters" indica os valores de parametros que permitem o acesso a informacao extra durante a fase de desenvolvimento. */

	public:
    Maze *maze; /* descreve o cenario de atuacao dos robos */
    ExtraParamList *pm;

    Challenge(char* ct, char* cn, int t, int d){
        challenge_name = cn;
        challenge_type = ct;
        cycle_time = t;
        duration = d;
        maze = new Maze();
        pm = new ExtraParamList();
    }
    Challenge(){
        maze = new Maze();
        pm = new ExtraParamList();
    }

    void setChallengeName(char*);
    void setChallengeType(char*);
    void setCycleTime(int);
    void setDuration(int);

    char* getChallengeName();
    char* getChallengeType();
    int getCycleTime();
    int getDuration();

    void printTest();

    void validateDefaultValues();
    void validateScenarioDescription();
    void validateIntType(char* num);
    bool is_digits(const std::string &str);

    void gridOutputXML(ofstream& file);
    void labOutputXML(ofstream& file);
    void paramOutputXML(ofstream& paramFile, ParamTable *param_table);
    void URDFOutputRotate(ofstream& file);
    void URDFOutputFixed(ofstream& file);

};

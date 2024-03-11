#ifndef SOLVER_H
#define SOLVER_H

#include "Parser.h"

class Solver {

    Parser *parser;

public:

    vector<vector<double>> COORD;

    Solver(Parser *parser);
    ~Solver();

    void solve(Parser *parser, int N);

};

Solver::Solver(Parser *parser) {

    COORD.push_back( parser->get_X() );
    COORD.push_back( parser->get_Y() );

    /*for (int i = 0; i < COORD.size(); i++) {
        for (int j = 0; j < COORD[i].size(); j++)
            cout << COORD[i][j] << " ";
        cout << endl;
    }*/
}

Solver::~Solver() {

    COORD[0].clear();
    COORD[1].clear();

}

double length(vector <vector <double> > COORD, int i, int j) {

    return sqrt((COORD[0][i] - COORD[0][j])*(COORD[0][i] - COORD[0][j]) + (COORD[1][i] - COORD[1][j])*(COORD[1][i] - COORD[1][j]));

}

void Solver::solve(Parser *parser, int N) {

    int i, j;
    vector<int> ROUTE;
    for (i = 0; i < N; i++) {

        ROUTE.push_back(i);

    }

    for (i = 0; i < N-1; i++) {


    for (j = i+1; j < N-1; j++) {

            if (length(COORD,ROUTE[i],ROUTE[i+1]) + length(COORD,ROUTE[j],ROUTE[j+1]) > length(COORD,ROUTE[i],ROUTE[j]) + length(COORD,ROUTE[i+1],ROUTE[j+1])) {

                iter_swap(ROUTE.begin()+i+1,ROUTE.begin()+j+1);

            }

    }

    }

    for (i = 0; i < N; i++) cout << ROUTE[i] << " ";

    return;

}

#endif

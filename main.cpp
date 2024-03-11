#include<iostream>
#include "Parser.h"
#include "Solver.h"

int main() {


    Parser parser("tsp_1889_1");
    parser.set_N();
    vector<double> new_vector_X, new_vector_Y;
    parser.Parse(new_vector_X,new_vector_Y);

    Solver solver(&parser);
    solver.solve(&parser,parser.get_N());

    return 0;
}

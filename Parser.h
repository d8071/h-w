#ifndef PARSER_H
#define PARSER_H


#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class Parser{

public:

    Parser(string STR);
    ~Parser();

    vector<double> X, Y;

    void Parse(vector<double> X, vector<double> Y);

    int get_N();
    void set_N();
    vector<double> get_X();
    vector<double> get_Y();

private:

    string filename;
    fstream f_in;
    int N;

};

Parser::Parser(string STR) {

    filename = STR;
    f_in.open(filename);

}

Parser::~Parser()
{

    filename.clear();
    f_in.close();

    X.clear();
    Y.clear();

}

int Parser::get_N()
{
    return N;
}

void Parser::set_N()
{

    string STR;
    N = 0;
    getline(f_in,STR,'\n');
    N = stoi(STR);
    cout << N << endl;
    f_in.clear();

}

vector<double> Parser::get_X() { return X; }
vector<double> Parser::get_Y() { return Y; }

void Parser::Parse(vector<double> new_X, vector<double> new_Y)
{
    string STR, x, y;

    int i = 0;
    char div = ' ';

    while( i < N ){

        getline(f_in,x,div);
        getline(f_in,y,'\n');

        new_X.push_back(stod(x));
        new_Y.push_back(stod(y));

        i++;

    }

    X = new_X;
    Y = new_Y;

    return;

}

#endif

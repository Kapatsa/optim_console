//
//  Function.hpp
//  optimization_console
//
//  Created by David Kapatsa on 08.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef Function_hpp
#define Function_hpp

#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

class Function {
public:
    int dim;
    Function(){};
    ~Function(){};
    virtual long double eval(long double *x) = 0;
    virtual long double grad(long double *x, int varInd) = 0;
    //what to do with this one??
    //virtual long double eval(long double x, long double y, long double z) = 0;
};

class f1: public Function{
public:
    f1(){
        dim = 2;
    };
    ~f1(){};
    long double eval(long double *x) override {
        return x[0]*exp(x[1]) + x[0]*x[1];
    };
    long double grad(long double *x, int varInd) override {
        if (varInd == 1) return exp(x[1]) + x[1];
        if (varInd == 2) return x[0]*exp(x[1]) + x[0];
        cout << "index error";
        return -10000000;
    };
};

class f2: public Function{
public:
    f2(){
        dim = 2;
    };
    ~f2(){};
    long double eval(long double *x) override {
        return 0.10 * cos(10*(x[0]*x[0] + x[1]*x[1]));
    };
    long double grad(long double *x, int varInd) override {
        if (varInd == 1) return 2*x[0]*cos(10*(x[0]*x[0]+x[1]*x[1]));
        if (varInd == 2) return 2*x[1]*cos(10*(x[0]*x[0]+x[1]*x[1]));
        cout << "index error";
        return -10000000;
    };
};

class f3: public Function{
public:
    f3(){
        dim = 3;
    };
    ~f3(){};
    long double eval(long double *x) override {
        return x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
    };
    long double grad(long double *x, int varInd) override {
        if (varInd == 1) return 2*x[0];
        if (varInd == 2) return 2*x[1];
        if (varInd == 3) return 2*x[2];
        cout << "index error";
        return -10000000;
    };
};

#endif /* Function_hpp */

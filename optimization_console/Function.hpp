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
    long double h = 1e-5;
    Function(){};
    ~Function(){};
    
    virtual long double eval(long double *x) = 0;
    long double grad(long double *x, int varInd){
        long double gr;
        long double * x_h = new long double [dim];
        for(int i = 0; i < dim; ++i) {i == varInd ? (x_h[i] = x[i] + h) : (x_h[i] = x[i]);}
        gr = (eval(x_h) - eval(x))/h;
        delete [] x_h;
        return gr;
    };
};


class f1: public Function{
public:
    f1(){
        dim = 2;
    };
    ~f1(){};
    long double eval(long double *x) override {
        return 0.10 * cos(10*(x[0]*x[0] + x[1]*x[1]));
    };
};

class f2: public Function{
public:
    f2(){
        dim = 3;
    };
    ~f2(){};
    long double eval(long double *x) override {
        return ((x[0]-0.5)*(x[0]-0.5) + x[1]*x[1] + x[2]*x[2] + 1);
    };
};

#endif /* Function_hpp */

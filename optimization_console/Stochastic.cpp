//
//  Stochastic.cpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include "OptMethod.hpp"
#include "Stochastic.hpp"
std::mt19937 gen;
std::uniform_real_distribution<> draw{0,1};
using namespace std;

/**
 * Stochastic constructor
 *
 * Constructor which sets the starting point and the dimension for the stochastic method
 * @param xstart is a starting point, @param dimen is the dimension
 **/
Stochastic::Stochastic(double long * xstart, int dimen){
    dim = dimen;
    xFin = new double long [dim]{};
    x0 = new double long [dim];
    for (int i = 0; i < dim; ++i){
        x0[i] = xstart[i];
    }
};

/**
 * Stochastic Optimization
 * Optimizes a given function inside a bounded area using the stochastic method.
 * @param area is a bounded area, @param func is a function, @param stopCrit is a chosen stop criterion
 * @return Minimal value is returned, argmin is set inside class
 **/
long double Stochastic::optimize(Area * area, Function * func, StopCriterion * stopCrit) {
    gen.seed(1);
    nIter = 0;
    int dim = func -> dim;
    std::uniform_real_distribution<> ** u  = new std::uniform_real_distribution<>*[dim];
    for (int i = 0; i < dim; ++i){
        u[i] = new std::uniform_real_distribution<>{static_cast<double>(area -> getRange()[2*i]), static_cast<double>(area -> getRange()[2*i+1])} ;
    }
    
    double long * xCur = new double long [dim];
    for(int i = 0; i < dim; ++i) xCur[i] = x0[i];
    double long fCur = func -> eval(xCur);
    double long * temp = new double long [dim];
    //for(int i = 0; i < dim; ++i) temp[i] = x0[i];
    double long * grad = new double long [dim];
    
    for(int i = 0; i < dim; ++i) grad[i] = func -> grad(x0, i);
    
    if ((stopCrit -> checkGrad(grad))){
        for( ; stopCrit -> stop(nIter, grad); ++nIter){
            for (int i = 0; i < dim; ++i){
                temp[i] = (*u[i])(gen);
                //cout << temp[i] << " " ;
            }
            //cout << endl;
            if( func -> eval(temp) < func -> eval(xCur) ){
                for (int i = 0; i < dim; ++i){
                    xCur[i] = temp[i];
                }
                    for(int i = 0; i < dim; ++i) grad[i] = func -> grad(xCur, i);
            }
        }
    }
    
    fCur = func -> eval(xCur);
    for (int i = 0; i < dim; ++i) xFin[i] = xCur[i];
    //cout << endl << "Num of iterations: " << nIter << endl;
    
    delete [] xCur;
    delete [] temp;
    delete [] grad;
    
    for (int i = 0; i < dim;  ++i){
        delete u[i];
    }
    delete [] u;
    
    return fCur;
};

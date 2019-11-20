//
//  GradDesc.cpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include "GradDesc.hpp"
#include "opt_tools.hpp"
#include <iostream>
using namespace std;

/**
 * GradDesc constructor
 *
 * Constructor which sets the starting point and the dimension
 * @param xstart is a starting point, @param dimen is the dimension
 **/
GradDesc::GradDesc(double long * xstart, int dimen){
    dim = dimen;
    xFin = new double long [dim]{};
    x0 = new double long [dim];
    for (int i = 0; i < dim; ++i){
        x0[i] = xstart[i];
    }
};

/**
 * Gradient Descent Optimization
 * Optimizes a given function inside a bounded area using the gradient descent method.
 * @param area is a bounded area,
 * @param func is a function,
 * @param stopCrit is a chosen stop criterion
 * @return Minimal value is returned, argmin is set inside class
 **/
double long GradDesc::optimize(Area * area, Function * func, StopCriterion * stopCrit){
    nIter = 0;
    double long * xCur = new double long [dim];
    double long * xPrev = new double long [dim];
    for(int i = 0; i < dim; ++i) xCur[i] = x0[i];
    double long fCur = func -> eval(xCur);
    double long * tempLeft = new double long [dim];
    double long * tempRight = new double long [dim];
    double long * tempBest = new double long [dim];
    for(int i = 0; i < dim; ++i) tempLeft[i] = x0[i];
    double long * grad = new double long [dim];
    int splitSize = 4; //Number of intervals. TODO(?): Include as a parameter
    long double lambdaM;
    //long double * lambdaSplit = new long double [splitSize + 1];
    int j{};
    for(int i = 0; i < dim; ++i) grad[i] = - func -> grad(x0, i);
    //checking grad at x0
    if(stopCrit -> checkGrad(grad)){
        //TODO: WHAT TO DO IF X0 IS AT THE BOUNDARY?
        do {//OPTIMIZE ALONG THE NEGATIVE GRADIENT UNTIL THE BORDER
            for(int i = 0; i < dim; ++i) grad[i] = - func -> grad(xCur, i);
            ++nIter;
            xPrev[j] = xCur[j];
            //CALCULATE LAMBDA AT BORDER
            //cout << "grad: "; //printing
            //print(grad, dim);
            //cout << endl;
            for(int i = 0; i < dim; ++i) tempBest[i] = xCur[i]; //??
            lambdaM = lambdaMax(area, xCur, grad);
            //for (int i = 0; i < splitSize + 1; ++i) lambdaSplit[i] = lambdaM/splitSize*i; //!
            for (int i = 0; i < splitSize; ++i){
                for (int j = 0; j < dim; ++j) tempLeft[j] = xCur[j] +  lambdaM/splitSize * i * grad[j];
                for (int j = 0; j < dim; ++j) tempRight[j] = xCur[j] +  lambdaM/splitSize * (i+1) * grad[j];
                 //print(temp, dim); //printing
                if( terOpt(func, tempLeft, tempRight, 1e-6) < func -> eval(tempBest)){
                    for (int k = 0; k < dim; ++k) tempBest[k] = tempLeft[k];
                } //TODO: epsilon!
            }
            //WE FOUND THE BEST VALUE ALONG THE GRADIENT
            for (int i = 0; i < dim; ++i) xCur[i] = tempBest[i];
            //cout << endl << nIter << ". " << "gradNorm: " << norm(grad, dim) << " МaxLam: " << lambdaM << endl;
            //cout << endl << "Current iteration: ";
            //print(xCur, dim);
        } while (stopCrit -> stop(xCur, xPrev, grad, nIter));
    }
    fCur = func -> eval(xCur);
    for (int i = 0; i < dim; ++i) xFin[i] = xCur[i];
    delete [] xPrev;
    delete [] tempLeft;
    delete [] tempRight;
    delete [] tempBest;
    //delete [] lambdaSplit;
    return fCur;
};

/*
 nIter = 0;
 double long * xCur = new double long [dim];
 double long * xPrev = new double long [dim];
 for(int i = 0; i < dim; ++i) xCur[i] = x0[i];
 double long fCur = func -> eval(xCur);
 //cout<< fCur;
 double long * temp = new double long [dim];
 for(int i = 0; i < dim; ++i) temp[i] = x0[i];
 double long * grad = new double long [dim];
 
 int j{};
 
 for(int i = 0; i < dim; ++i) grad[i] = func -> grad(x0, i);
 
 if ((stopCrit -> checkGrad(grad))){
 do {
 j = 0;
 
 for(int i = 0; i < dim; ++i) xPrev[i] = xCur[i] ;
 for(int i = 0; i < dim; ++i) grad[i] = func -> grad(xPrev, i);
 
 do {
 ++j;
 for (int i = 0; i < dim; ++i) { xCur[i] -= j * step * grad[i]; };
 if( func -> eval(xCur) < func -> eval(temp) ){
 ++nIter;
 for (int i = 0; i < dim; ++i) temp[i] = xCur[i];
 //for (int i = 0; i < dim; ++i) cout << temp[i] << " ";
 //cout << endl;
 }
 
 } while (area -> isIn(xCur));
 
 if (!(area -> isIn(temp))){ //if temp is outside, move back along the gradient and set it as the current one
 for (int i = 0; i < dim; ++i) { xCur[i] += step * grad[i]; };
 break;
 //TODO: SOME FLAG IF OUTSIDE THE AREA
 }
 
 //if temp is inside all is well, make it current
 else {
 for (int i = 0; i < dim; ++i) { xCur[i] = temp[i]; };
 }
 
 } while (stopCrit -> stop(xCur, xPrev, grad, nIter));
 }
 
 fCur = func -> eval(xCur);
 for (int i = 0; i < dim; ++i) xFin[i] = xCur[i];
 //cout << endl << "Num of iterations: " << nIter << endl;
 
 
 delete [] xCur;
 delete [] xPrev;
 delete [] temp;
 return fCur;
 
 */

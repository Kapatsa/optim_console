//
//  GradDesc.cpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include "GradDesc.hpp"

#include <iostream>

/**
 * Gradient Descent Optimization
 * Optimizes a given function inside a bounded area using the gradient descent method.
 * @param area is a bounded area, @param func is a function, @param stopCrit is a chosen stop criterion
 * @return Minimal value is returned, argmin is set inside class
**/
double long GradDesc::optimize(Area * area, Function * func, StopCriterion * stopCrit){
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
                ++nIter;
                ++j;
                for (int i = 0; i < dim; ++i) { xCur[i] -= j * step * grad[i]; };
                if( func -> eval(xCur) < func -> eval(temp) ){
                    for (int i = 0; i < dim; ++i) temp[i] = xCur[i];
                    //for (int i = 0; i < dim; ++i) cout << temp[i] << " ";
                    //cout << endl;
                }
                
            } while (area -> isIn(xCur));
            
            if (!(area -> isIn(temp))){ //if temp is outside, move back along the gradient and set it as the current one
                for (int i = 0; i < dim; ++i) { xCur[i] += step * grad[i]; };
            }
            
            //if temp is inside all is well, make it current
            else {
                for (int i = 0; i < dim; ++i) { xCur[i] = temp[i]; };
            }
            
        } while (stopCrit -> stop(xCur, xPrev, grad, nIter));
    }
    
    fCur = func -> eval(xCur);
    for (int i = 0; i < dim; ++i) xFin[i] = xCur[i];
    cout << endl << "Num of iterations: " << nIter << endl;
    
    
    delete [] xCur;
    delete [] xPrev;
    delete [] temp;
    return fCur;
};

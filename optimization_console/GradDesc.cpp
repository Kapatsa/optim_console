//
//  GradDesc.cpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include "GradDesc.hpp"
#include <iostream>

double long GradDesc::optimize(Area * area, Function * func, StopCriterion * stopCrit){
    double long * xCur = new double long [dim];
    double long * xPrev = new double long [dim];
    for(int i = 0; i < dim; ++i) xPrev[i] = x0[i];
    double long fPrev = func -> eval(xPrev);
    double long fCur{};
    double long * temp = new double long [dim];
    double long * grad = new double long [dim];
    //double long * xCandidate = new double long [dim];
    //double long fCandidate{};
    
    do {
        ++nIter;
        for(int i = 0; i < dim; ++i){
            temp[i] = xPrev[i];
        }
            for(int i = 0; i < dim; ++i){ //
                grad[i] = func -> grad(xPrev, i);
                xCur[i] = xPrev[i] - step * grad[i];
                //std::cout << xCur[i] << endl;
            }
            //std::cout << endl;
            fCur = func -> eval(xCur);
            for (int i = 0; i < dim; ++i ) xPrev[i] = xCur[i];
            fPrev = fCur;
    } while ((stopCrit -> stop(xCur, temp, grad, nIter)) && (area -> isIn(xCur)));
   if (!(area -> isIn(xCur))){
        fCur = fPrev;
        for (int i = 0; i < dim; ++i) xCur[i] = xPrev[i];
    }
    for (int i = 0; i < dim; ++i) xFin[i] = xCur[i];
    
    delete [] xCur;
    delete [] xPrev;
    return fCur;
};

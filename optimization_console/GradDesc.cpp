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
    for(int i = 0; i < dim; ++i) xCur[i] = x0[i];
    double long fCur = func -> eval(xCur);
    //cout<< fCur;
    double long * temp = new double long [dim];
    for(int i = 0; i < dim; ++i) temp[i] = x0[i];
    double long * grad = new double long [dim];
    //double long * xCandidate = new double long [dim];
    //double long fCandidate{};
    int j{};
    
    for(int i = 0; i < dim; ++i) grad[i] = func -> grad(x0, i);
    if ((stopCrit -> checkGrad(grad))){
        do {
            ++nIter;
            j = 0;
            
            for(int i = 0; i < dim; ++i) xPrev[i] = xCur[i] ;
            for(int i = 0; i < dim; ++i) grad[i] = func -> grad(xPrev, i);
            //what if grad is zero??
            
            do {
                ++j;
                for (int i = 0; i < dim; ++i) { xCur[i] -= j * step * grad[i]; };
                if( func -> eval(xCur) < func -> eval(temp) ){
                    for (int i = 0; i < dim; ++i) temp[i] = xCur[i];
                    for (int i = 0; i < dim; ++i) cout << temp[i] << " ";
                    cout << endl;
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
    
//    do {
//        ++nIter;
//        for(int i = 0; i < dim; ++i){
//            temp[i] = xPrev[i];
//        }
//            for(int i = 0; i < dim; ++i){ //
//                grad[i] = func -> grad(xPrev, i);
//                //while(area -> isIn(xCur)) {step a little; if f(xCur) is better than f(xPrev), make xPrev = xCur, fPrev = fCur, xCur = newx, fCur = newf}
//                //
//                xCur[i] = xPrev[i] - step * grad[i];
//                //std::cout << xCur[i] << endl;
//            }
//            //std::cout << endl;
//            fCur = func -> eval(xCur);
//            for (int i = 0; i < dim; ++i ) xPrev[i] = xCur[i];
//            fPrev = fCur;
//    } while ((stopCrit -> stop(xCur, temp, grad, nIter)) && (area -> isIn(xCur)));
//   if (!(area -> isIn(xCur))){
//        fCur = fPrev;
//        for (int i = 0; i < dim; ++i) xCur[i] = xPrev[i];
//    }
//    for (int i = 0; i < dim; ++i) xFin[i] = xCur[i];
    
    
    
    delete [] xCur;
    delete [] xPrev;
    delete [] temp;
    return fCur;
};

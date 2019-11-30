//
//  Stochastic.cpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include "Stochastic.hpp"
#include "opt_tools.hpp"

std::mt19937 gen;
std::uniform_real_distribution<> draw{0,1};
using namespace std;

/**
 * Stochastic constructor
 *
 * Constructor which sets the starting point and the dimension for the stochastic method
 * @param xstart is a starting point, @param dimen is the dimension
 **/
Stochastic::Stochastic(double long * xstart, int dimen, long double localProb, long double deltaIn, long double iterSc){
    dim = dimen;
    xFin = new double long [dim]{};
    x0 = new double long [dim];
    for (int i = 0; i < dim; ++i){
        x0[i] = xstart[i];
    }
    localProbability = localProb;
    deltaInit = deltaIn;
    iterScale = iterSc;
};

//(!!!) TODO: MAKE LOCAL OPTIMIZATION

/**
 * Stochastic Optimization
 * Optimizes a given function inside a bounded area using the stochastic method.
 * @param area is a bounded area,
 * @param func is a function,
 * @param stopCrit is a chosen stop criterion,
 * @return Minimal value is returned, argmin is set inside class
 **/
double long Stochastic::optimize(Area * area, Function * func, StopCriterion * stopCrit) {
    gen.seed(1);
    nIter = 0;
    int dim = func -> dim;
    
    //CREATING A DISTRIBUTION FOR THE GLOBAL AREA
    std::uniform_real_distribution<> ** u  = new std::uniform_real_distribution<>*[dim];
    for (int i = 0; i < dim; ++i){
        u[i] = new std::uniform_real_distribution<>{static_cast<double>(area -> getRange()[2*i]), static_cast<double>(area -> getRange()[2*i+1])} ;
    }
    std::discrete_distribution<int> d {static_cast<double>(localProbability),static_cast<double>(1-localProbability)};
    
    // randInside TEST
    {
        //double long * pt = new double long [dim];
        //for (int i = 0; i < 100; ++i) randomInside(pt, dim, u, gen);
        //delete [] pt;
    }
    // rangeAroundEps TEST
    {
        //double long * localRange = new double long[2*dim];
        //print(rangeAroundEps(localRange, x0, 0.2, dim, area->getRange()), 2*dim);
        //delete [] localRange;
    }
    // discrete distribution TEST
    /*
    TODO: Check that discrete works properly from the beginning
    {
        std::cout << std::endl << d.probabilities()[1] << " diss 1 " << d(gen) << " " << d(gen) << std::endl;
    for (int i = 0; i < 100; ++i){
        std::cout << d(gen);
    }
    std::cout << std::endl;
    }
    */
    
    
    double long * xLocal = new double long [dim];
    for(int i = 0; i < dim; ++i) xLocal[i] = x0[i];
    double long fLocal = func -> eval(xLocal);
    
    double long * xGlobal = new double long [dim];
    double long fGlobal;
    
    double long * xBest = new double long [dim];
    double long * grad = new double long [dim];
    

    double long currentDelta;
    
    
    //TODO:: HERE IS THE LATEST CHANGE
    for( ; stopCrit -> stop(nIter, grad); ++nIter){
     
        switch (d(gen)) {
            case 0: //LOCAL
                //create new distributions
                //
                
                
                //if there is improvement, decrease delta
                break;
                
            case 1: //GLOBAL
                
                break;
                
            default:
                break;
        }
        
        
        
    }
    
    
   /*
    
    
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
    
    */
    
    return xBest;
    
    
};

/*long double Stochastic::optimize(Area * area, Function * func, StopCriterion * stopCrit) {
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
*/

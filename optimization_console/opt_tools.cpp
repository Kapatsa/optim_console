//
//  opt_tools.cpp
//  optimization_console
//
//  Created by David Kapatsa on 13.11.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include "opt_tools.hpp"

void eq(double long * x, double long * y, int dim){
    for (int i = 0; i < dim; ++i){
        x[i] = y[i];
    }
}

double long norm(double long *vector, int dim){
    double long dist = 0;
    for (int i = 0; i < dim; ++i){
        dist += vector[i]*vector[i];
    }
    return sqrt(dist);
};

double long terOpt(Function *f, double long *xCur, double long *grad, double long lambdaMax, double long eps){
    int dim = f -> dim;
    double long *lCur = new double long [dim];
    double long *rCur = new double long [dim];
    double long *lCand = new double long [dim];
    double long *rCand = new double long [dim];
    double long *diff = new double long [dim];
    
    for(int i = 0; i < dim; ++i){
        lCur[i] = xCur[i];
    }
    for(int i = 0; i < dim; ++i){
        rCur[i] = xCur[i] + grad[i]*lambdaMax;
    }
    for(int i = 0; i < dim; ++i){
        diff[i] = rCur[i] - lCur[i];
    }
    
    while ( norm(diff, dim) > eps) {
        
        //the interval is cut into three parts
        for(int i = 0; i < dim; ++i){
            lCand[i] = (2*lCur[i] + rCur[i])/3;
            rCand[i] = (lCur[i] + 2*rCur[i])/3;
        }
        
        //compare f values at new nodes, assign new nodes
        if( f->eval(lCand) < f->eval(rCand) ){
            //rCur = rCand, lCur stays the same
            for(int i = 0; i < dim; ++i){
                rCur[i] = rCand[i];
            }
        }
        else {
            //lCur = lCand, rCur stays the same
            for(int i = 0; i < dim; ++i){
                lCur[i] = lCand[i];
            }
        }
        
        //recalculate the difference for the current interval
        for(int i = 0; i < dim; ++i){
            diff[i] = rCur[i] - lCur[i];
        }
        
    }
    
    //out of the cycle, make some assignments
    //xCur is our new optimal point
    for (int i = 0; i < dim; ++i){
        xCur[i] = (lCur[i] + rCur[i])/2;
    }
    
    delete [] lCur;
    delete [] rCur;
    delete [] lCand;
    delete [] rCand;
    delete [] diff;
    return f -> eval(xCur);
};

double long lambdaMax(RectArea * rect, double long *xCur, double long *grad){
    int dim = rect -> dim;
    
    double long alphaCur{};
    double long alphaCand{};
    
    for (int i = 0; i < dim; ++i) {
        if (grad[i] > 0){
            alphaCand = (rect->getRange()[2*i + 1]-xCur[i])/grad[i];
        }
        else {
            alphaCand = (rect->getRange()[2*i]-xCur[i])/grad[i];
        }
        if (i == 0) alphaCur = alphaCand;
        else if ( alphaCand < alphaCur ) alphaCur = alphaCand;
    }
    return alphaCur;
}

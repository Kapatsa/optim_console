//
//  Abs.hpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef Abs_hpp
#define Abs_hpp

#include <stdio.h>
#include <cmath>

//-------------
//#include "stuff.hpp"
#include "StopCriterion.hpp"
//-------------

double long norm(double long *vector, int dim);

class Abs : public StopCriterion {
public:
    Abs(){};
    Abs(int dimen){
        dim = dimen;
    };
    ~Abs(){};
    bool stop(double long * xCurrent, double long * xPrev,/*, double long *fCurr, double long *fPrev, double long *grad,*/int numOfIter) override {
        double long * diff = new double long [dim]{};
        for (int i = 0; i < dim; ++i){
            diff[i] = xCurrent[i] - xPrev[i];
        }
        if (/*less than eps*/ (norm(diff, dim) < eps) || (numOfIter > N) ){
            delete [] diff;
            return 0;
        }
        else
        {
            delete [] diff;
            return 1;
        }
    };
};

#endif /* Abs_hpp */

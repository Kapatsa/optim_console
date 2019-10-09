//
//  StopCriterion.hpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef StopCriterion_hpp
#define StopCriterion_hpp

#include <stdio.h>

class StopCriterion {
public:
    double long eps = 10e-4;
    int N = 10e5;
    int dim;
    StopCriterion(){};
    StopCriterion(int dim) : dim(dim) {};
    ~StopCriterion(){};
    virtual bool stop(double long * xCurrent, double long * xPrev,/*, double long *fCurr, double long *fPrev, double long *grad,*/int numOfIter) = 0;
};

#endif /* StopCriterion_hpp */

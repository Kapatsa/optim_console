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
    double long eps = 1e-8;
    int N = 5000;
    int dim;
    StopCriterion(){};
    ~StopCriterion(){};
    virtual bool stop(int numOfIter, double long *grad) = 0;
    virtual bool stop(double long * xCurrent, double long * xPrev,/*, double long *fCurr, double long *fPrev,*/ double long *grad, int numOfIter) = 0;
    virtual bool checkGrad(double long *grad) = 0;
};

#endif /* StopCriterion_hpp */
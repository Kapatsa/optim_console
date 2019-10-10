//
//  OptMethod.hpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef OptMethod_hpp
#define OptMethod_hpp

#include <stdio.h>
// ----------------
#include "Area.hpp"
#include "RectArea.hpp"
#include "Function.hpp"
#include "StopCriterion.hpp"
#include "Abs.hpp"
// ----------------

class OptMethod {
protected:
    //Area * area;
    //Function * f;
    double long *x0;
    double long *xFin{};
    long int nIter = 0;
    long double step = 10e-3;
    int dim;
    //StopCriterion stop;
public:
    OptMethod(){};
    ~OptMethod(){};
    virtual double long optimize(Area * area, Function * function, StopCriterion * stopCrit) = 0;
    virtual double long * getXFin() = 0;
    void SetX0(double long * num){x0 = num;}; //TODO: deep!
};
#endif /* OptMethod_hpp */

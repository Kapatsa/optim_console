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
/**
 * Optimization Method Class
 * Main objective of this class is to provide a virtual function optimize(), which currently is being overridden by the corresponding functions in GradDesc and Stochastic classes
 **/
class OptMethod {
protected:
    double long *x0;
    double long *xFin{};
    int nIter = 0;
    long double step = 10e-4; 
    int dim;
public:
    OptMethod(){};
    ~OptMethod(){};
    virtual double long optimize(Area * area, Function * function, StopCriterion * stopCrit) = 0;
    /**
     * GetXFin
     * @return Final iteration value is returned.
     **/
    virtual double long * getXFin() = 0;
    /**
     * SetX0
     * @param num vector of values of the same dimension as dim
     **/
    void SetX0(double long * num){for (int i = 0; i < dim; ++i) x0[i] = num[i];};
    int GetnIter(){return nIter;}
};
#endif /* OptMethod_hpp */

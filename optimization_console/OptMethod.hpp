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
    double long *xFin;
    //long int nIter;
    //?include? int dim;
    //StopCriterion stop;
public:
    //!TODO: constructor for all data
    OptMethod(){};
    OptMethod(double long *x0) : x0(x0) {
    };
    ~OptMethod(){};
    virtual long double optimize(Area * area, Function * function, StopCriterion * stopCrit) = 0;
    long double GetXFin(){return *xFin;};
};
#endif /* OptMethod_hpp */

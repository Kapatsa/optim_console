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
// ----------------

class OptMethod {
protected:
    Area * area;
    Function * f;
    double long *x0;
    double long *xFin;
    long int nIter;
    
    //StopCriterion stop;
public:
    //!TODO: constructor for all data
    OptMethod(){};
    OptMethod(Function * f, Area * area, double long *x0) : f(f), area(area), x0(x0) {
        
    };
    ~OptMethod(){};
    virtual long double optimize() = 0;
    long double GetXFin(){return *xFin;};
};
#endif /* OptMethod_hpp */

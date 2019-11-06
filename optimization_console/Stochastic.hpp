//
//  Stochastic.hpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef Stochastic_hpp
#define Stochastic_hpp

#include <stdio.h>
#include <fstream>
#include <random>
#include <ctime>

// ----------------
#include "OptMethod.hpp"
// ----------------

class Stochastic : public OptMethod{
public:
    Stochastic(){};
    Stochastic(double long * xstart, int dimen);
    ~Stochastic(){delete [] x0; delete [] xFin;};
    long double optimize(Area * area, Function * function, StopCriterion * stopCrit) override;
    long double * getXFin() override { return xFin;};
};


#endif /* Stochastic_hpp */

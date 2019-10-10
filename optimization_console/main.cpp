//
//  main.cpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

//---------------
#include "Area.hpp"
#include "RectArea.hpp"
#include "OptMethod.hpp"
#include "GradDesc.hpp"
#include "Stochastic.hpp"
#include "StopCriterion.hpp"
#include "Iterative.hpp"
#include "Abs.hpp"
#include "Function.hpp"
//---------------

using namespace std;

int main(int argc, const char * argv[]) {
    
    //functions
    f1 f1; // xe^y + xy (2 vars)
    f2 f2; // 0.10*cos(10*(x^2 + y^2)) (2 vars)
    f3 f3; // x^2 + y^2 + z^2 (3 vars)
    
    //areas
    double long range1[4] = {0,1,0,1  };
    double long range2[4] = {-1,1,-1,1};
    double long range3[6] = {0,1,0,1,0,1   };
    double long range4[6] = {-1,1,-1,1,-1,1};
    RectArea area1(range1, 2);
    RectArea area2(range2, 2);
    RectArea area3(range3, 3);
    RectArea area4(range4, 3);
    
    //starting points
    double long x0_1[2] = {0.5,0.5};
    double long x0_2[2] = {0, 0};
    double long x0_3[3] = {0.5, 0.5, 0.5};
    //methods
    int dim = 3;
    GradDesc grad1(x0_3, dim);
  //Stochastic stoc1;
    
    //stop criterion
    Abs stop1(dim);
    
    //pointers
    
    Function * f = &f3;
    RectArea * area = &area3;
    OptMethod * method = &grad1;
    StopCriterion * stop = &stop1;
    
    
    cout << "min is: " << method -> optimize(area, f, stop) << endl;
    cout << "argmin is: " << (method -> getXFin())[0] << endl;
    
    
    return 0;
}

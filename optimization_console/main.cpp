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
    f1 f1;
    f2 f2;
    f3 f3;
    
    //areas
    double long range1[6] = {0,1,0,1,0,1};
    double long range2[6] = {-1,1,-1,1,-1,1};
    double long range3[4] = {0,1,0,1};
    RectArea area1(range1, 3);
    RectArea area2(range2, 3);
    RectArea area3(range3, 2);
    
    //methods
    GradDesc grad1;
  //Stochastic stoc1;
    
    //starting iterations
    double long x0_1[2] = {0.5,0.5};
    double long x0_2[2] = {0, 0};
    
    //pointers
    int dim = 2;
    Function * f = &f1;
    RectArea * area = &area1;
    OptMethod * method = &grad1;
    
    
    
    
    
    

    double long x[2]{};

    cout << f->eval(x);
    //starting point
    
    //while(Stop())

    
    
    
    
    
    
    
    return 0;
}

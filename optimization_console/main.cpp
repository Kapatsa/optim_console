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
    
    //some area
    RectArea area1(0,0,1,1);
    //some function
    f1 f1;
    f2 f2;
    f3 f3;
    Function * f = &f1;
    //method choice
    long double x[2]{};
    //stop criterion choice
    cout << f->eval(x);
    //starting point
    
    //while(Stop())
    

    
    
    
    
    
    
    return 0;
}

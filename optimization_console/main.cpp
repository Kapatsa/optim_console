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
#include "Abs.hpp"
#include "Function.hpp"
//---------------

using namespace std;

int main(int argc, const char * argv[]) {
    
    char ans = 'y';
    

    //functions
    f1 f1; // 0.10*cos(10*(x^2 + y^2)) (2 vars)
    f2 f2; // x^2 + y^2 + z^2 (3 vars)

    
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
    //double long x0_1[2] = {0.01,0.01};
    //double long x0_2[2] = {0, 0};
    //double long x0_3[3] = {0.5, 0.5, 0.5};

    //WHEN CHANGING FUNCTIONS BEWARE OF AREA CHOICE
    Function * f = &f1;
    int dim = f->dim;
    double long * x0 = new double long [dim]{};
    
    RectArea * area = nullptr;
    if (dim == 2) area = &area1;
    if (dim == 3) area = &area3;
    else area = &area4;
    
    double long eps = 1e-5;
    int iter = 5000;
    Abs stop1(dim, eps, iter);
    StopCriterion * stop;
    stop = &stop1;
    GradDesc grad1(x0, dim);
    Stochastic stoc1(x0, dim);
    OptMethod * method;

    char methodChoice = 'g';
    bool initialIn;
    //int finIter;

    
    cout << endl << "OPTIMIZATION. CONSOLE EDITION. version 1.2." << endl;
    
    cout << endl << "The function chosen is" << f -> getExpr() << endl;
    //TODO:: The area is ...
    
    do {
        cout << endl << "Please choose method (type g for gradient descent, s or smth else for stochastic): ";
        cin >> methodChoice;
        methodChoice == 'g' ? method = &grad1 : method = &stoc1;
        do {
            cout << endl << "Enter x_0 (" << dim << " numbers): ";
            for (int i = 0; i < dim; ++i){cin >> x0[i];}
            initialIn = area -> isIn(x0);
            if (!initialIn) cout << endl << "Initial guess out of bounds. Try again.";
        } while(!initialIn);
        method -> SetX0(x0);
        
        double long min = method -> optimize(area, f, stop);
        cout << "min is: " << min << endl;
        cout << "argmin is: ";
        for (int i = 0; i < dim; ++i){
            cout << method -> getXFin()[i] << " ";
        }
        cout << endl << "Number of iterations: " << method -> GetnIter();
        cout << endl;
        
        
        cout << "continue? (y/n): ";
        cin >> ans;
    } while(ans == 'y');
    
    
    delete [] x0;
    return 0;
}

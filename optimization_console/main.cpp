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
#include <limits>

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

//TODO:: remove namespace std
using namespace std;

int main(int argc, const char * argv[]) {
    
    char ans = 'y';
    
    //functions
    f1 f1; // 0.10*cos(10*(x^2 + y^2)) (2 vars)
    f2 f2; // x^2 + y^2 + z^2 (3 vars)
    f3 f3; // х + y (2 vars)
    f4 f4; // (1-x)^2 + 100 * (y-x^2)^2 (2 vars)
    int numberOfFunctions = 4;
    int dim;
    //areas
    double long range1[4] = {0,2,0,2  };
    double long range2[4] = {-1,1,-1,1};
    double long range3[6] = {0,1,0,1,0,1   };
    double long range4[6] = {-1,1,-1,1,-1,1};
    RectArea area1(range1, 2);
    RectArea area2(range2, 2);
    RectArea area3(range3, 3);
    RectArea area4(range4, 3);

    Function * f = &f1;
    double long * x0{};
    double long * range{};
    
    RectArea * area = nullptr;
    
    //TODO:: set eps & noOfIters & MaxDifference
    double long eps = 1e-5;
    int N = 5000;
    double long localProb = 0.5;
    int maxItersAfterSuccess = 500;
    Abs stop1;
    StopCriterion * stop;
    stop = &stop1;
    GradDesc grad1;
    Stochastic stoc1;
    OptMethod * method;

    char methodChoice = 'g';
    char levelChoice = 'b';
    char stopChoice = 'i';
    int functionChoice{};
    int rangeIncorrect = 0;
    
    {
    //TEST
    
    //long double gradt[2] = {-0.09, -0.191};
    //long double xcurt[2] = {0.1, 0.2};
    //cout << "Lambda is" << lambdaMax(area, xcurt, gradt) << endl;
    
    } //TEST FOR BOUNDARY LAMBDA CALCULATION
    
    bool initialIn;
    
    cout << endl << "OPTIMIZATION. CONSOLE EDITION. version 1.3." << endl;
    
    //TODO:: The area is ...
    
    
    do {
        
        cout << endl  << "Type 'b' for beginner, 'a' for advanced: " ;
        do {
                cin >> levelChoice;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            if(levelChoice != 'a' && levelChoice != 'b'){
                cout << endl << "Please enter 'b' or 'a': ";
            }
        } while (levelChoice != 'a' && levelChoice != 'b');
        
        
        cout << endl  << "Please choose a function by typing its number:" << endl;
       {cout << "1. " << f1.getExpr() << endl;
        cout << "2. " << f2.getExpr() << endl;
        cout << "3. " << f3.getExpr() << endl;
        cout << "4. " << f4.getExpr() << endl;} //functions list
        
        do {
            cout  << "Function number: ";
            cin >> functionChoice;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            if ((functionChoice < 1)
                ||
                (functionChoice > numberOfFunctions)){
                cout << "Oh, very funny. Please try again.";
            }
            else {
                switch (functionChoice) {
                    case 1:
                        f = &f1;
                        break;
                    case 2:
                        f = &f2;
                        break;
                    case 3:
                        f = &f3;
                        break;
                    case 4:
                        f = &f4;
                    break;
                        
                    default:
                        cout << "This was not supposed to happen!";
                        break;
                } //function assignment
            }
        } while((functionChoice < 1)
                ||
                (functionChoice > numberOfFunctions));
        
        cout << "The function chosen is" << f -> getExpr();
        dim = f -> dim;
    
        if (dim == 2) area = &area1;
        if (dim == 3) area = &area3;
        if (levelChoice == 'b'){
            cout << "The area I chose for you is ";
            area -> printExpr();
            cout << ". You're welcome.";
        }
        else if(levelChoice == 'a'){
            //create range, delete later
            range = new long double [2*dim];
            do{
                rangeIncorrect = 0;
                cout << endl << "Please enter range (" << 2*dim << " numbers): " ;
                for (int i = 0; i < 2*dim; ++i){
                    cin >> range[i];
                }
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                for (int i = 0; i < dim; ++i){
                    if (range[2*i] > range[2*i + 1]){
                        rangeIncorrect = 1;
                        cout << endl << "Range is incorrect! Try again.";
                    }
                }
            } while(rangeIncorrect);
        }
        area -> setDim(dim);
        area -> setRange(range);
        cout << "Chosen range: ";
        area -> printExpr();
        
        cout << endl << "Please choose method (type 'g' for gradient descent, 's' for stochastic): ";
        do {
            cin >> methodChoice;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            switch (methodChoice) {
                case 'g':
                    method = &grad1;
                    stop -> SetStopChoice('g'); //default choice
                    break;
                case 's':
                    method = &stoc1;
                    stop -> SetStopChoice('i');
                    break;
                default:
                    method = &stoc1; // just for initialization
                    cout << "I see you enjoy breaking rules. I like it.";
                    cout << endl << "Please enter 'g' or 's': ";
                    break;
            }
        } while (methodChoice != 'g' && methodChoice != 's');
        
        //TODO:: INPUT SHOULD BE CONTROLLED --- HOWEVER FOR READABILITY I OMITTED do-whiles
        //ADVANCED SETTINGS
        if(levelChoice == 'a'){
            //STOCHASTIC ADVANCED SETTINGS
            if(methodChoice == 's'){
                cout << "Choose stop criterion (type 'i' for iterative, 'l' for local): ";
                cin >> stopChoice;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                switch (stopChoice) {
                    case 'i':
                        stop -> SetStopChoice('i');
                        cout << "Enter max number of iterations after last success: ";
                        cin >> maxItersAfterSuccess;
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        stop -> SetMaxItersAfterLast(maxItersAfterSuccess);
                        break;
                    case 'l':
                        stop -> SetStopChoice('l');
                        break;
                    default:
                        break;
                }
                cout << endl << "Enter local search probability for the method (0 < p < 1): ";
                cin >> localProb;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                method -> SetLocalProb(localProb);
            }
            //GRAD DESCENT ADVANCED SETTINGS
            if(methodChoice == 'g'){
                cout << "Choose stop criterion (type 'g' for gradient, 'x' for x-value difference): ";
                cin >> stopChoice;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                switch (stopChoice) {
                    case 'g':
                        stop -> SetStopChoice('g');
                        break;
                    case 'x':
                        stop -> SetStopChoice('x');
                        break;
                    default:
                        break;
                }
            }
                if (stopChoice != 'i'){
                cout << "Enter eps for stop criterion: ";
                cin >> eps;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                stop -> SetEps(eps);
                }
                
                cout << "Enter N (max number of iterations) for stop criterion: ";
                cin >> N;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                stop -> SetN(N);
        }
        
        x0 = new double long [dim]{};
        
        do {
            cout << "Enter x_0 (" << dim << " numbers): ";
            for (int i = 0; i < dim; ++i){cin >> x0[i];}
             cin.ignore(numeric_limits<streamsize>::max(),'\n');
            initialIn = area -> isIn(x0);
            if (!initialIn) cout << "Initial guess out of bounds. Try again.";
        } while(!initialIn);
        method -> SetDim(dim);
        method -> SetX0(x0);
        stop -> SetDim(dim);
        
        double long min = method -> optimize(area, f, stop);
        cout << "|| min is: " << min << endl;
        cout << "|| argmin is: ";
        for (int i = 0; i < dim; ++i){
            cout << method -> getXFin()[i] << " ";
        }
        cout << endl << "|| Number of iterations: " << method -> GetnIter();
        cout << endl;
        delete [] x0;
        delete [] range;
        
        cout << endl << "continue? (y/n): ";
        cin >> ans;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    } while(ans == 'y');
    
    
    
    return 0;
}

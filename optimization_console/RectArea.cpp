//
//  RectArea.cpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include "RectArea.hpp"

RectArea::RectArea(double long *x, int dimen){
    dim = dimen;
    range = new double long [2*dim];
    for (int i = 0; i < 2*dim; ++i) range[i] = x[i];
    };

bool RectArea::isIn(double long *point){
    bool temp = 1;
    for (int i = 0; i < dim; ++i){
        if ((point[i] <= range[2*i])||(point[i] >= range[2*i+1])){
            return temp = 0;
        }
    }
    return temp;
};

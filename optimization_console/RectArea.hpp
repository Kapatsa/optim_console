//
//  RectArea.hpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef RectArea_hpp
#define RectArea_hpp

#include <stdio.h>
#include "Area.hpp"

class RectArea : public Area {
protected:
    int dim;
    double long *range; // [( , );( , );( , )]  // 4 when dim = 2, 6 when dim = 3
public:
    RectArea(){};
    ~RectArea(){ delete [] range; };
    RectArea(double long *x, int dimen){
        dim = dimen;
        range = new double long [2*dim];
        for (int i = 0; i < 2*dim; ++i) range[i] = x[i];
    };
    bool isIn(double long *point) override {
        bool temp = 1;
            for (int i = 0; i < dim; ++i){
                if ((point[i] < range[2*i])||(point[i] > range[2*i+1])){
                   return temp = 0;
                }
            }
        return temp;
    };
};

#endif /* RectArea_hpp */

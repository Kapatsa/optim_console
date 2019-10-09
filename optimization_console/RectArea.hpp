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

class RectArea : protected Area {
protected:
    double x1;
    double y1; // (x1, y1) - lower left point of rect
    double x2;
    double y2; // (x2, y2) - upper right point of rect
public:
    RectArea(){};
    ~RectArea(){};
    RectArea(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2)  {
    };
    bool isIn(double x, double y) override {
        return ((x>x1)&&(x<x2)&&(y>y1)&&(y<y2));
    };
};

#endif /* RectArea_hpp */

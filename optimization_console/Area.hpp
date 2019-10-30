//
//  Area.hpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef Area_hpp
#define Area_hpp

#include <stdio.h>

class Area {

public:
    Area(){};
    ~Area(){};
    virtual bool isIn(double long *point) = 0;
    virtual double long * getRange() = 0;
    //virtual bool isBorder();
};

#endif /* Area_hpp */

//
//  GradDesc.hpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef GradDesc_hpp
#define GradDesc_hpp

#include <stdio.h>
// ----------------
#include "Area.hpp"
#include "RectArea.hpp"
#include "Function.hpp"
#include "OptMethod.hpp"
#include "StopCriterion.hpp"
// ----------------
class GradDesc : public OptMethod {

public:
    GradDesc(){};
    ~GradDesc(){};
    long double optimize(Area * area, Function * function, StopCriterion * stopCrit) override;
};


#endif /* GradDesc_hpp */

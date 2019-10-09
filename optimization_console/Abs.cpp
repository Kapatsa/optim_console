//
//  Abs.cpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include "Abs.hpp"

double long norm(double long *vector, int dim){
double long dist = 0;
for (int i = 0; i < dim; ++i){
    dist += vector[i]*vector[i];
}
return sqrt(dist);
};

//
//  Point.hpp
//  1.25_kubic_Acima_estestv_gnaich_usl_Peresdacha
//
//  Created by Arsenii Klevakin on 05.09.2023.
//

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>
#include "Function.hpp"

class Point{
public:
    double x, y;
    Point();
    void findY();
};

double fn(Point A);

#endif /* Point_hpp */

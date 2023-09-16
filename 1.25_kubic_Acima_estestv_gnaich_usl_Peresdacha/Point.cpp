//
//  Point.cpp
//  1.25_kubic_Acima_estestv_gnaich_usl_Peresdacha
//
//  Created by Arsenii Klevakin on 05.09.2023.
//

#include "Point.hpp"

Point::Point(){};

void Point::findY(){
    y=fn(x);
}

double fn(Point A){
    return fn(A.x);
}

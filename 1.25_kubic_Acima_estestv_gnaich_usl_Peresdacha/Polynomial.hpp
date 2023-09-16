//
//  Polynomial.hpp
//  1.25_kubic_Acima_estestv_gnaich_usl_Peresdacha
//
//  Created by Arsenii Klevakin on 05.09.2023.
//

#ifndef Polynomial_hpp
#define Polynomial_hpp

#include "Point.hpp"
#include "Function.hpp"
#include <stdio.h>

class Polinomial{
public:
    int i;
    double xi;
    double c1, c2, c3, c4;
    double Pf(double x);
    Polinomial(int _i, double _xi, double _c1,double _c2,double _c3,double _c4);
};

#endif /* Polynomial_hpp */

//
//  Polynomial.cpp
//  1.25_kubic_Acima_estestv_gnaich_usl_Peresdacha
//
//  Created by Arsenii Klevakin on 05.09.2023.
//

#include "Polynomial.hpp"
using namespace std;

double Polinomial::Pf(double x){
    return  c1+c2*(x-xi)+c3*pow((x-xi), 2)+c4*pow((x-xi), 3);
}

Polinomial::Polinomial(int _i, double _xi, double _c1,double _c2,double _c3,double _c4){
    i=_i;
    xi=_xi;
    c1=_c1;
    c2=_c2;
    c3=_c3;
    c4=_c4;
};

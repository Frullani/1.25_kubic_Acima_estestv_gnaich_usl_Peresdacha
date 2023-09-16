/*
 (1.25) Кусочная интерполяция кубическими многочленами методом Акимы с определением недостающих граничных условий из естественных граничных условий.
 
 Алгоритм
 
 1. Данн отрезок a b, мы разбиваем его равно на n-1, с помощью n точек
    x1=a, xn=b
 2. Находим wj j = 2 ... n-1
 3. Находим di i = 3 ... n-2
 4. Находим оставшиеся di исходя из недостающих гран усл
 4. Строим n-1 полином, строя с4, i
 5. Интерполируем функцию на всем a b
 6. Выводим точки в файл
 */

#include <iostream>
#include <vector>
#include <fstream>
#include "Function.hpp"
#include "Point.hpp" 
#include "Polynomial.hpp"
using namespace std;

double computeDevDif(double xi, double xip1){
    return (fn(xip1)-fn(xi))/(xip1-xi);
}

//Разбиваем отрезок на n-1 часть
vector<double> splitSegment(double a, double b, int NumPoints){
    int n=NumPoints;
    double l=b-a;
    double h=l/(n-1);
    vector<double> x;
    for(int i=0; i<=n-1; i++){
        x.push_back(a+i*h);
    }
    return x;
}

//Вычисляем wj, со 2го по n-1й
vector<double> computeWj(vector<double> x){
    long long n = x.size()-1;
    vector<double> w;
    w.push_back(0); w.push_back(0);
    for(int j=2; j<=n-1; j++){
        double res=abs(computeDevDif(x[j], x[j+1])-computeDevDif(x[j-1], x[j]));
        w.push_back(res);
    }
    w.push_back(0);
    return w;
}

//Вычисляем di, i = 3... n-2
vector<double> computeDi(vector<double> x, vector<double> w){
    long long n = x.size()-1;
    vector<double> d;
    
    d.push_back(0); d.push_back(0); d.push_back(0);
    
    for(int i=3; i<=n-2; i++){
        double devDif1, devDif2;
        devDif1=computeDevDif(x[i-1], x[i]);
        devDif2=computeDevDif(x[i], x[i+1]);
        
        if((w[i+1]==0)&&(w[i-1]==0)){
            double up, down;
            up=(x[i+1]-x[i])*devDif1+(x[i]-x[i-1])*devDif2;
            down=x[i+1]-x[i-1];
            d.push_back(up/down);
        }
        else{
            double up, down;
            up=w[i+1]*devDif1+w[i-1]*devDif2;
            down = w[i+1]+w[i-1];
            d.push_back(up/down);
        }
    }
    
    d.push_back(0); d.push_back(0);
    
    return d;
}

vector<Polinomial> computePolinomials(vector<double> x, vector<double> d){
    vector<Polinomial> P;
    long long n = x.size()-1;
    Polinomial Zero(0, 0, 0, 0, 0, 0);
    P.push_back(Zero);
    
    for(int i=1; i<=n-1; i++){
        double c1, c2, c3, c4, div;
        div = computeDevDif(x[i], x[i+1]);
        c1=fn(x[i]);
        c2=d[i];
        c3=(3*div-2*d[i]-d[i+1])/(x[i+1]-x[i]);
        c4=(d[i]+d[i+1]-2*div)/(x[i+1]-x[i])/(x[i+1]-x[i]);
        Polinomial H(i, x[i], c1, c2, c3, c4);
        P.push_back(H);
    }
    
    return P;
}

void writePointstoFile(vector<Point> P, string filename){
    ofstream file(filename);
    if (file.is_open()){
        for(unsigned long i=0; i<P.size(); i++){
            file << P[i].x << " " << P[i].y << endl;
        }
        cout << P.size() << " Points writen to " << filename << endl;
    }
    else{
        cout << "Wrong, file is not open" << endl;
    }
}

vector<Point> computeAproxPoints(vector<Polinomial> P, vector<double> x, int depth){
    vector<Point> AproxPoints;
    long long n = x.size()-1;
    
    for(int i=1; i<=n-1; i++){
        vector<double> h;
        h=splitSegment(x[i], x[i+1], depth);
        
        for(unsigned long j=0; j<h.size(); j++){
            Point XY;
            XY.x = h[j];
            XY.y = P[i].Pf(h[j]);
            AproxPoints.push_back(XY);
        }
    }
    
    return AproxPoints;
}

vector<Point> computeRealPoints(vector<Point> AproxPoints){
    vector<Point> RealPoints;
    for(unsigned long i=0; i<AproxPoints.size(); i++){
        Point XY;
        XY.x=AproxPoints[i].x;
        XY.y=fn(XY.x);
        RealPoints.push_back(XY);
    }
    return RealPoints;
}


int main() {
    double a=-5, b=5;
    int depth = 100;
    vector<double> x;
    
    
    x=splitSegment(a, b, 10); //Последний параметр отвечает за колличество известных точек
    x.insert(x.begin(), 0); // для удобства индексации считаем первый элемент нулевым
    
    long long n = x.size()-1;
    
    vector<double> w;
    w=computeWj(x);
    
    vector<double> d;
    d = computeDi(x, w);
    
    //Найдем d1 d2 dn-1 dn из естественных граничных условий
    d[1] = 0;
    d[2] = 3*computeDevDif(x[1], x[2]);
    d[n-1] = 3*computeDevDif(x[n-1], x[n]);
    d[n]=0;
    
    vector<Polinomial> Polinomials;
    Polinomials = computePolinomials(x, d);
    
    vector<Point> AproxPoints;
    AproxPoints = computeAproxPoints(Polinomials, x, depth);
    
    vector<Point> RealPoints;
    RealPoints = computeRealPoints(AproxPoints);
    
    writePointstoFile(AproxPoints, "aproxPoints.txt");
    writePointstoFile(RealPoints, "realPoints.txt");
    
    vector<Point> Nodes;
    for(int i=1; i<=n; i++){
        Point XY;
        XY.x = x[i];
        XY.y = fn(x[i]);
        Nodes.push_back(XY);
    }
    
    writePointstoFile(Nodes, "nodesPoints.txt");
    return 0;
}

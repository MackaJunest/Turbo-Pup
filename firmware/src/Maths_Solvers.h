#ifndef MATHS_SOLVER_H
#define MATHS_SOLVER_H

#include<cmath>


class Solver
{
    public:
    void FK_Solver(double ham_angle, double shank_angle, float &x1, float &y1);
    void IK_Solver(double x, double y, float &shank_angle, float &ham_angle);
    private:
    const int L1 = 150; //shank
    const int L2 = 106; //ham
    double L3=0;
    double L4=0;
    double theta1=0;
    double theta3=0;
    double theta4=0;
    double theta5=0;
    double ham_angle=0;
    double shank_angle=0;
    double xh1;
    double x1;
    double y1;
};

#endif
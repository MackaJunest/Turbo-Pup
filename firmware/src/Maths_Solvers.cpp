#include"Maths_Solvers.h"

void Solver::IK_Solver(double x, double y, float &shank_angle, float &ham_angle)
{
    double L3 = sqrt(pow(x, 2) + pow(y, 2));
    double theta1 = acos((pow(L1, 2) + pow(L2, 2) - pow(L3, 2)) / (2 * L1 * L2));
    shank_angle = (M_PI - theta1) * 180 / M_PI;
    double L4 = sqrt(pow(L3, 2) - pow(x, 2));
    double theta3 = asin((sin(theta1) / L3) * L1);
    double theta4 = atan(L4 / x);
    ham_angle = (theta4 - theta3) * 180 / M_PI;
}

void Solver::FK_Solver(double ham_angle, double shank_angle, float &x1, float &y1)
{
    ham_angle= ham_angle * M_PI / 180;
    shank_angle = shank_angle * M_PI / 180;
    double xh1 = cos(shank_angle);
    double theta4 = M_PI - shank_angle;
    double L3 = sqrt(pow(L1, 2) + pow(L2, 2) - 2 * L1 * L2 * cos(theta4));
    double theta3 = asin(sin(theta4) / L3 * L1);
    double theta5 = theta3 + ham_angle;
    x1 = cos(theta5) * L3;
    y1 = sin(theta5) * L3;
}

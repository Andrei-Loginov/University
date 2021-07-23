#define _USE_MATH_DEFINES
#include <iostream>
#include <functional>
#include <cmath>

/*
Предыстория
Пусть целевая функция вычисляет вертикальную скорость самолета. В качестве параметра x передается угол атаки. 
Требуется найти угол атаки, при котором произойдет сваливание самолета.  
*/


inline bool is_equal_sign(double left, double right) {
    return ((left > 0) == (right > 0));
}

bool bisection(std::function<double(double)> pf, double &ans, double left_x, double right_x, double eps = 0.0001) {
    double left_y = pf(left_x), right_y = pf(right_x), mid_y;
    if (is_equal_sign(left_y, right_y))
        return false;
    ans = left_x + (right_x - left_x) / 2;
    while ((right_x - left_x) > eps) {
        mid_y = pf(ans);
        if (is_equal_sign(left_y, mid_y))
            left_x = ans;
        else
            right_x = ans;
        ans = left_x + (right_x - left_x) / 2;
    }

    return true;
}

double func(double x) {
    return (pow(x, 5) - 12*pow(x,4) + 25 * pow(x, 3) - 4*pow(x,2) + 3*x);
}

int main(){
    double ans;
    if (bisection(func, ans, 0.5, 10, 0.00000001))
        std::cout << ans << "\n";
    else
        std::cout << "Can't find\n";
    return 0;
}


/*
fabs((mid_y = pf(ans))) > eps
*/

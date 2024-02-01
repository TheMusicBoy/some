#ifndef _TYPES_H_
#define _TYPES_H_

#include <Eigen/Core>
#include <Eigen/Dense>
#include <istream>
#include <functional>

using Mtx = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
using Vec = Eigen::Matrix<double, Eigen::Dynamic, 1>;

using EigenSolver = Eigen::EigenSolver<Mtx>;

using SFunc = std::function<double(const Vec&)>;
using Func = std::function<Vec(const Vec&)>;

std::istream& operator>>(std::istream& in, Mtx& mas) {
    for (int x = 0; x < mas.cols(); x++)
        for (int y = 0; y < mas.rows(); y++) {
            double value;
            in >> value;
            mas(x, y) = value;
        }
    return in;
}

std::istream& operator>>(std::istream& in, Vec& vec) {
    for (int x = 0; x < vec.rows(); x++)
        in >> vec(x);
    return in;
}

Vec Grad(const Func& f, const Vec& x) {
    static double eps = 1e-9;

    Vec epsv = x;
    epsv.setConstant(eps);

    return (f(x + epsv) - f(x)) / eps;
}

Vec Grad(const SFunc& f, const Vec& x) {
    using value_t = long double;
    static value_t eps = 1e-12;

    Vec result(x.size());

    for (int i = 0; i < x.rows(); i++) {
        Vec new_x = x;
        new_x(i) += eps;
        result(i) = (value_t(f(new_x)) - value_t(f(x))) / eps;
    }

    return result;
}


#endif // _TYPES_H_

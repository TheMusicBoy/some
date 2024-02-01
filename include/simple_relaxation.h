#ifndef _SIMPLE_ITER_H_
#define _SIMPLE_ITER_H_

#include <types.h>
#include <tuple>
#include <iostream>
#include <chrono>

namespace my {

class SimpleRelaxation {
 private:
    size_t iter_max_ = 10000;
    double eps_ = 1e-9;

    Mtx a_mtx;
    Vec b_vec;
    double w;

    Vec RelaxIter(const Mtx& x) {
        Mtx x_new = x;

        for (int i = 0; i < x.rows(); i++) {
            x_new(i) = (1 - w) * x(i);

            double sum = b_vec(i);

            for (int j = 0; j < i; j++)
                sum -= a_mtx(i, j) * x_new(j);
            for (int j = i + 1; j < x.rows(); j++)
                sum -= a_mtx(i, j) * x(j);

            x_new(i) += w / a_mtx(i, i) * sum;
        }

        return x_new;
    }

 public:
    struct State {
        Vec res;
        size_t iters = 0;
        double err = 0;
        long long time = 0;
    };

    SimpleRelaxation(Mtx A, Mtx b, double w_) : a_mtx(A), b_vec(b), w(w_) {}

    void setMaxIter(size_t new_max) { iter_max_ = new_max; }
    void setEps(double eps) { eps_ = eps; }

    State execute(Vec x0) {
        State s;
        auto start = std::chrono::system_clock().now().time_since_epoch();

        s.res = RelaxIter(x0);

        for (; s.iters < iter_max_ && (a_mtx * s.res - b_vec).norm() > eps_; s.iters++)
            s.res = RelaxIter(x0 = s.res);

        s.time = (std::chrono::system_clock().now().time_since_epoch() - start).count();
        s.err = (a_mtx * s.res - b_vec).norm();
        return s;
    }
};

} // namespace my

#endif // _SIMPLE_ITER_H_

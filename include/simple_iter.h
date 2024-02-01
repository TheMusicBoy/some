#ifndef _SIMPLE_ITER_H_
#define _SIMPLE_ITER_H_

#include <types.h>
#include <tuple>
#include <iostream>
#include <chrono>

namespace my {

class SimpleIteration {
 private:
    size_t iter_max_ = 10000;
    double eps_ = 1e-9;

    Mtx a_mtx;
    Vec b_vec;

 public:
    struct State {
        Vec res;
        size_t iters = 0;
        double err = 0;
        long long time = 0;
    };

    SimpleIteration(Mtx A, Mtx b) : a_mtx(A), b_vec(b) {}

    void setMaxIter(size_t new_max) { iter_max_ = new_max; }
    void setEps(double eps) { eps_ = eps; }

    State execute(Vec x0) {
        Mtx A = a_mtx;
        Vec b = b_vec;
        State s;
        s.res = Vec::Random(b.rows());

        auto start = std::chrono::system_clock().now().time_since_epoch();
        
        for (int i = 0; i < A.rows(); i++) {
            b(i) /= A(i, i);
            A.row(i) /= -A(i, i);
            A(i, i) = 0;
        }

        for (s.iters = 0; (a_mtx * s.res - b_vec).norm() > eps_ && s.iters < iter_max_; s.iters++)
            x0 = b + A * (s.res = x0);

        s.time = (std::chrono::system_clock().now().time_since_epoch() - start).count();
        s.err = (a_mtx * s.res - b_vec).norm();
        return s;
    }
};

} // namespace my

#endif // _SIMPLE_ITER_H_

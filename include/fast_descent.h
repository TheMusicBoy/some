#ifndef _SIMPLE_ITER_H_
#define _SIMPLE_ITER_H_

#include <types.h>
#include <tuple>
#include <iostream>
#include <chrono>

namespace my {

class FastDescent {
 private:
    size_t iter_max_ = 10000;
    double eps_ = 1e-9;

    Mtx a_mtx;
    Vec b_vec;
    int size;

    Mtx aat_() const {
        const Mtx& A = a_mtx;
        Mtx m = Mtx::Zero(size, size);
        for (int i = 0; i < A.rows(); i++) 
            for (int j = i; j < A.cols(); j++)
                m(j, i) = m(i, j) = A.row(i) * A.row(j).transpose();
        return m;
    }

    Vec error(const Vec& x) { return a_mtx * x - b_vec; }
    double errorNorm(const Vec& x) { return error(x).norm(); }

 public:
    struct State {
        Vec res;
        size_t iters = 0;
        double err = 0;
        long long time = 0;
    };

    FastDescent(Mtx A, Mtx b) : a_mtx(A), b_vec(b) {
        size = A.rows();
    }

    void setMaxIter(size_t new_max) { iter_max_ = new_max; }
    void setEps(double eps) { eps_ = eps; }

    State execute(Vec x0) {
        const Mtx& A = a_mtx;
        Vec b = b_vec;
        State s;
        s.res = x0;
        Vec r = error(s.res);
        s.err = r.norm();
        Vec wwr = aat_() * r;
        double mu = (wwr.transpose() * r).value() / (wwr.transpose() * wwr).value();
        
        auto start = std::chrono::system_clock().now().time_since_epoch();
        
        for (; s.iters < iter_max_ && r.norm() > eps_; s.iters++) {
            s.res = s.res - A.transpose() * r * mu;
            r = error(s.res);
            wwr = aat_() * r;
            mu = (wwr.transpose() * r).value() / (wwr.transpose() * wwr).value();
        }

        s.time = (std::chrono::system_clock().now().time_since_epoch() - start).count();
        s.err = errorNorm(s.res);
        return s;
    }
};

} // namespace my

#endif // _SIMPLE_ITER_H_

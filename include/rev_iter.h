#ifndef _REV_ITER_H_
#define _REV_ITER_H_

#include <tuple>
#include <types.h>
#include <lu_dec.h>

namespace my {

const double EPS = 1e-12;
const int MAX_ITER = 10000;


std::tuple<Vec, double, int> RevIter(const Mtx& A, Vec x) {
    double alpha = 1 / x.maxCoeff();
    double alpha_prev = alpha + 10;

    int it;
    for (it = 0; it < MAX_ITER && std::fabs(alpha - alpha_prev) >= EPS; it++) {
        alpha_prev = alpha;
        x = LuDec(A, x * alpha);
        alpha = 1 / x.maxCoeff();
    }

    return {x, alpha, it};
}

} // namespace my

#endif // _REV_ITER_H_

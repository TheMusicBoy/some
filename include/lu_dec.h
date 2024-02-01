#ifndef _LU_DEC_H_
#define _LU_DEC_H_

#include <types.h>

namespace my {

Mtx LuDec(const Mtx& a, Vec x) {
    Mtx l = Mtx::Zero(a.rows(), a.cols());
    Mtx u = Mtx::Zero(a.rows(), a.cols());
    
    for (int i = 0; i < a.rows(); i++) {
        u(0, i) = a(0, i);
        l(i, 0) = a(i, 0) / u(0, 0);
    }

    for (int i = 1; i < a.rows(); i++)
        for (int j = i; j < a.rows(); j++) {
            double sum = 0;
            for (int r = 0; r < i; r++)
                sum += l(i, r) * u(r, j);

            u(i, j) = a(i, j) - sum;
            sum = 0;
            for (int r = 0; r < i; r++)
                sum += l(j, r) * u(r, i);
            l(j, i) = (a(j, i) - sum) / u(i, i);
        }

    for (int i = 0; i < a.rows(); i++) 
        for (int j = 0; j < i; j++)
            x(i) -= l(i, j) * x(j);

    for (int i = a.rows() - 1; i >= 0; i--) {
        for (int j = i + 1; j < a.rows(); j++)
            x(i) -= u(i, j) * x(j);
        x(i) /= u(i, i);
    }

    return x;
}

} // namespace my

#endif // _LU_DEC_H_

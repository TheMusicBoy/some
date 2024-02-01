#ifndef _GAUS_H_
#define _GAUS_H_

#include <types.h>

#include <tuple>
#include <set>
#include <vector>

namespace my {

std::tuple<Mtx, Vec> Gaus(Mtx A, Vec b) {
    std::set<int> rows;
    for (int i = 0; i < A.rows(); i++)
        rows.insert(i);

    Vec res(A.rows());
    std::vector<int> mapping(A.rows());

    while (!rows.empty()) {
        int mx = 0, my = *rows.begin();

        for (auto y : rows)
            for (int x = 0; x < A.cols(); x++)
                if (std::abs(A(y, x)) > std::abs(A(my, mx))) {
                    my = y;
                    mx = x;
                }


        for (int y = 0; y < A.rows(); y++) {
            if (y == my) continue;

            double coef = A(y, mx) / A(my, mx);
            b(y) -= coef * b(my);
            for (int x = 0; x < A.cols(); x++)
                A(y, x) -= coef * A(my, x);
        }

        res(mx) = A(my, mx);
        mapping[mx] = my;
        rows.erase(my);
    }

    for (int i = 0; i < res.rows(); i++) 
        res(i) = b(mapping[i]) / res(i);

    return {A, res};
}

} // namespace my


#endif // _GAUS_H_

#ifndef _LATEX_H_
#define _LATEX_H_

#include <cstdint>
#include <types.h>
#include <string>
#include <sstream>
#include <iomanip>


namespace ltx {

int PRECISION = 3;

std::string fixed(double value) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(PRECISION) << value;
    
    std::string result = ss.str();
    if (result.find('.') != uint32_t(-1))
        while(result.back() == '0') result.pop_back();
    if (result.back() == '.')
        result.pop_back();
    return result;
}

std::string latex(const Mtx& matrix) {
    std::ostringstream ss;
    ss << "\\begin{pmatrix}" << std::endl;
    for (int y = 0; y < matrix.rows(); y++) {
        ss << '\t';
        for (int x = 0; x < matrix.cols(); x++) {
            if (x) ss << " & ";
            ss << fixed(matrix(y, x));
        }
        if (y + 1 < matrix.rows())
            ss << " \\\\";
        ss << std::endl;
    }
    ss << "\\end{pmatrix}" << std::flush;
    return ss.str();
}

std::string latex(double number) {
    std::stringstream ss;
    ss << number << std::flush;
    if (ss.str().find('e') != UINT32_MAX) {
        ss = std::stringstream();
        double p = std::floor(std::log10(std::fabsl(number)));
        if (p > 2 || p < 0)
            ss << fixed(number / std::pow(10, p)) << " \\cdot 10^{" << p << '}' << std::flush;
        else
            ss << fixed(number) << std::flush;
    }
    return ss.str();
}

} // namespace ltx

#endif // _LATEX_H_

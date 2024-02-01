#include <types.h>
#include <gaus.h>

#include <iostream>
#include <string>
#include <list>

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]), m = atoi(argv[2]);

    std::cout << "Creating data set" << std::endl;
    std::srand(std::chrono::system_clock::now().time_since_epoch().count());

    std::vector<Mtx> A;
    for (int i = 0; i < m; i++)
        A.push_back(Mtx::Random(n, n));

    std::vector<Vec> b;
    for (int i = 0; i < m; i++)
        b.push_back(Vec::Random(n));

    auto start = std::chrono::system_clock::now();
    auto start_timestamp = start.time_since_epoch().count();
    
    std::cout << "Start calculation" << std::endl;   
    double max_error = 0;
    for (int i = 0; i < m; i++) {
        auto [matrix, res] = my::Gaus(A[i], b[i]);
        max_error = std::max(max_error, (A[i] * res - b[i]).norm());
    }
    
    auto finish = std::chrono::system_clock::now();
    auto finish_timestamp = finish.time_since_epoch().count();

    std::cout << "Max error = " << max_error << std::endl;
    std::cout << "Time = " << finish_timestamp - start_timestamp << "mcs" << std::endl;
    std::cout << "Avg Time = " << (finish_timestamp - start_timestamp) / m << "mcs" << std::endl;
    
}

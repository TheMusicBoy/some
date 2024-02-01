#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

int main(int argc, char** argv) {

    auto start = std::chrono::system_clock::now();
    std::srand(start.time_since_epoch().count());

    int n = std::stoi(argv[1]);
    int m = std::stoi(argv[2]);

    for(int i = 0; i < m; i++) {
        std::stringstream prompt;

        prompt << n << std::endl;
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++)
                prompt << std::rand() << ' ';
            prompt << std::endl;
        }

        for (int y = 0; y < n; y++)
            prompt << std::rand() << ' ';

        std::system(("echo '" + prompt.str() + "' | ./app > /dev/null").c_str());
    }

    std::cout << std::chrono::system_clock::now().time_since_epoch().count() - start.time_since_epoch().count() << "ms " << std::endl;
}

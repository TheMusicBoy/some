#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    namespace fs = std::filesystem;

    fs::path test_path = fs::absolute("");

    std::string args;
    for (int i = 1; i < argc; i++)
        args += " " + std::string(argv[i]);

    for (auto entry : fs::recursive_directory_iterator(test_path)) {
        if (fs::is_directory(entry) || fs::is_symlink(entry))
            continue;

        fs::path file = entry;
        std::cout << std::endl;
        std::cout << "Test " << file.lexically_relative(test_path) 
                << "\n" + std::string(30, '-') << std::endl;

        std::system(("cat '" + file.string() + "' | ./app" + args).c_str());
        std::cout << std::endl;
    }

}

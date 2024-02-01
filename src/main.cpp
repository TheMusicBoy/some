#include <types.h>
#include <options.h>
#include <latex.h>
#include <fast_descent.h>

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    int PRECISION = 4;
    
    // Options processing

    op::OpController ops;
    bool latex = false;

    ops.addParser({"-l", "--latex"}, [&latex](op::OptionState st){
        latex = true;
    });

    ops.addParser({"-p", "--precision"}, [&PRECISION](op::OptionState st){
        int value = -1;
        for (int i = st.pos + 1; i < st.args.size(); i++) {
            if (st.argstate[i] == 0) {
                value = std::stoi(st.args[i]);
                st.argstate[i] = 1;
                break;
            }
        }
        if (value == -1)
            throw op::OpController::Exception{ "Not enough arguments" };
        
        ltx::PRECISION = value;
        PRECISION = value;
    });

    try {
        ops.ProcessArgs(argc, argv);
    } catch (op::OpController::Exception e) {
        std::cout << "OptionError: " << e.msg << std::endl;
        throw;
    }

    // Data input

    int n;
    std::cin >> n;


    Mtx A(n, n);
    Vec b(n);
    std::cin >> A >> b;

    // Processing

    auto state = my::FastDescent(A, b).execute(Vec::Random(n));

    // Result output

    if (latex) {
        std::cout << ltx::latex(A) << " \\cdot b = " << ltx::latex(b) << std::endl;
        std::cout << "x = " << ltx::latex(state.res.transpose()) << std::endl;
        std::cout << "k = " << ltx::latex(state.iters) << std::endl;
        std::cout << "\\operatorname{error} = " << ltx::latex(state.err) << std::endl;
    } else {
        std::cout << "Roots : \n" << state.res.transpose() << std::endl;
        std::cout << "Iterations : " << state.iters << std::endl;
        std::cout << "Error : \n" << state.err << std::endl;
    }
}

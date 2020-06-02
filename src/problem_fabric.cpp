#include "problem_fabric.h"

Problem *ProblemFabric::create(const char *filename, std::string problemName) {
    try {
        if (problemName.compare("scp") == 0) {
            return new SetCoveringProblem(filename);
        } else if (problemName.compare("mcp") == 0) {
            return new MaximumCliqueProblem(filename);
        } else if (problemName.compare("mkp") == 0) {
            return new MKnapsackProblem(filename);
        } else if (problemName.compare("stp") == 0) {
            return nullptr;
        } else {
            std::string msg = "Problema \"";
            msg += std::string(filename);
            msg += "\" não reconhecido";
            throw std::runtime_error(msg);
        }
    } catch (std::exception &e) {
        std::cerr << "ProblemFabric(" << filename << ","
                  << problemName << "): " << e.what() << std::endl;
    }
}

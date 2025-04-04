#include "Tests.h"
#include <windows.h>

int main(int argc, char* argv[]) {
    if (argc > 4) {
        std::cerr << "Usage: <test_number> <algorithm_type> <output_file_prefix>" << std::endl;
        return 1;
    }

    int testNumber = std::stoi(argv[1]);
    std::string algorithmType = argv[2];
    Sleep(5000);
    std::string fileName = "test" + std::to_string(testNumber) + "_" + algorithmType + ".csv";
    std::cout << "Results saved in file '" << fileName << "'\n";

    switch (testNumber) {
    case 1:
        test1(testNumber, algorithmType);
        break;
    case 2:
        test2(testNumber, algorithmType);
        break;
    case 3:
        test3(testNumber, algorithmType);
        break;
    case 4:
        test4(testNumber, algorithmType);
        break;
    default:
        std::cerr << "Invalid test number!" << std::endl;
        return 1;
    }
    return 0;
}
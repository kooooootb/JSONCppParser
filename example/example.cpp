#include <iostream>
#include <fstream>

#include "JSON/Parser.h"

int main(){
    std::ifstream ifs("example.json");

    JSON::Parser parser(ifs);
    std::cout << *parser.getRoot();

    return 0;
}

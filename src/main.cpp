#include <iostream>
#include <cstdlib>
int main(int argc, const char** argv){
    if(argc != 2){
        std::cerr<<"Incorrect input......"<<std::endl;
        std::cerr<<"Correct usage: DLang input.dl"<<std::endl;
        return EXIT_FAILURE;
    }
    std::cout<<"Hello World"<<std::endl;
    return EXIT_SUCCESS;
}

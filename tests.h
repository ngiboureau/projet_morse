#include "encoder.h"
#include <cstdlib>
#include <iostream>

inline void test_convert_1()
{
    std::cout << "test conversion 'hello' in morse";
    std::string mess = "hello";
    std::string t = convert(mess);
    std::string answ = ". . . .   .   . _ . .   . _ . .   _ _ _   ";
    std::cout << std::boolalpha <<  " *** " << (t == answ) << std::endl;
    
}

inline void test_convert_2()
{
    std::cout << "test conversion 'hello world' in morse";
    std::string mess = "hello world";
    std::string t = convert(mess);
    std::string answ = ". . . .   .   . _ . .   . _ . .   _ _ _       . _ _   _ _ _   . _ .   . _ . .   _ . .   ";
    std::cout << std::boolalpha <<  " *** " << (t == answ) << std::endl;
    
}
#pragma once
// vr: pour protéger un fichier d'entête (.h) contre une inclusion multiple lors d'une même chaine de compilation, on peut mettre soit le #ifndef/define/endif soit le #pragma (dans ce fichier vous n'en avez pas besoin puisque vous ne définissez pas de classes

#include "encoder.h"
#include <cstdlib>
#include <iostream>

// vr: inline super !
// vr: vos tests passent
inline void test_convert_1()
{
    std::cout << "test conversion 'hello' in morse\n";
    std::string mess = "hello";
    std::string t = convert(mess);
    // vr: attention à bien avoir l'espace  en fin de lettre dans le dernier mots sinon == donnera faux
    std::string answ = ".... . .-.. .-.. --- ";
    std::cout << t << std::endl;
    std::cout << answ << std::endl;
    std::cout << std::boolalpha <<  " *** " << (t == answ) << std::endl;
    
}
// vr: vos tests passent
inline void test_convert_2()
{
    std::cout << "test conversion 'hello world' in morse\n";
    std::string mess = "hello world";
    std::string t = convert(mess);
    // vr: attention à bien avoir l'espace en fin de lettre dans le dernier mot pour la chaine morse témoin
    std::string answ = ".... . .-.. .-.. ---  .-- --- .-. .-.. -.. ";
    std::cout << answ << std::endl;
    std::cout << t << std::endl;
    std::cout << std::boolalpha <<  " *** " << (t == answ) << std::endl;
    
}

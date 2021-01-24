#include <iostream>
#include <string>
#include <cstdlib>
#include "encoder.h"



int main()
{
    bool i = true;
    std::string rep;
    while (i == true)
    {
        std::cout << "encoder/décoder ?" << std::endl;
        getline(std::cin, rep);
        if (rep == "encoder")
        {
            i = false;
            std::string mess;
            std::string messMorse;
            std::cout << "Quel est le message à encoder ?" << std::endl;
            getline(std::cin, mess);
            messMorse = convert(mess);
            writing(messMorse);
        }
        else if (rep == "décoder")
        {
            std::cout << "la fonction de décodage n'a pas été codée" << std::endl;
            i = false;
        }
        else
        {
            std::cout << "Requête incomprise, veuillez reformuler." << std::endl;
        }
    }
    return 0;  
}
#include <iostream>
#include <string>
#include <cstdlib>
#include "encoder.h"


// vr: ne mettez pas de code directement dans votre main, appelez-y des fonctions définies ailleurs là je la définis ici mais elle devrait être dans un fichier lié au programme morse 
void menu_morse ()
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
	    // vr: pour du debug je rajoute la traduction en morse
	    std::cout << "morse is: " << messMorse << std::endl;
            writing(messMorse);
        }
        else if (rep == "decoder")
        {
            std::cout << "la fonction de décodage n'a pas été codée" << std::endl;
            i = false;
        }
        else
        {
            std::cout << "Requête incomprise, veuillez reformuler." << std::endl;
        }
    }
}

// vr le main doit être tout petit et très lisible (comme celui de vos tests)
int main()
{
  // vr: j'ai ajouté une exception lorsque la lettre à encoder n'est pas dans l'alphabet considéré, alors je l'attrape 
  try {
    menu_morse();
  }
  catch (const char* msg) {
    std::cout << msg << std::endl;
  }
  return 0;  
}

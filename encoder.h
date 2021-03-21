#include <iostream>
#include <string>

// vr: passez l'argument par référence pour ne pas le recopier à chaque fois que vous voulez simplement le lire et passez le const pouer dire que vous ne le modifiez pas
std::string convert(const std::string& mess);
void writing(const std::string& messMorse);

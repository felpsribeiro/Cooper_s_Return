
#ifndef _COOPER_MENU_H_
#define _COOPER_MENU_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include "Font.h"
#include <sstream>
using std::stringstream;

// --------------------------------------------------------------------------------

class Menu : public Object
{
private:
    Sprite * logo;          // logotipo do jogo
    Sprite * panel;         // painel do jogo

    Font* font = nullptr;              // fonte para exibi��o normal
    stringstream text1;                 // texto tempor�rio
    stringstream text2;                 // texto tempor�rio
    stringstream text3;                 // texto tempor�rio

    // define cor do texto
    Color textColor{ 1.0f, 1.0f, 1.0f, 1.0f };

public:
    Menu();                // construtor
    ~Menu();               // destrutor

    void Update();          // atualiza��o
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif

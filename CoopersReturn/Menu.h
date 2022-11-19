
#ifndef _GEOWARS_MENU_H_
#define _GEOWARS_MENU_H_

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
    bool played;            // intro n�o tocada ainda

    Font* font = nullptr;              // fonte para exibi��o normal
    Font* bold = nullptr;              // fonte para exibi��o negrito
    stringstream text1;                 // texto tempor�rio
    stringstream text2;                 // texto tempor�rio
    stringstream text3;                 // texto tempor�rio

    // define cor do texto
    Color textColor{ 0.7f, 0.7f, 0.7f, 1.0f };

public:
    Menu();                // construtor
    ~Menu();               // destrutor

    void Update();          // atualiza��o
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif

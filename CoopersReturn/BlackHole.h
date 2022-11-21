
#ifndef _COOPER_HOLE_H_
#define _COOPER_HOLE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                        // objetos do jogo
#include "Sprite.h"                        // desenho de sprites
#include "Animation.h"                     // sistema de animações

// ---------------------------------------------------------------------------------

class BlackHole : public Object
{
private:
    Sprite * hole;                      // sprite do buraco
    TileSet * eventHorizon;             // horizonte de eventos
    Animation * anim;                   // animação do horizonte de eventos

public:
    BlackHole();                           // construtor
    ~BlackHole();                          // destrutor
    
    void Update();                      // atualiza��o
    void Draw();                        // desenho
}; 
// ---------------------------------------------------------------------------------

#endif
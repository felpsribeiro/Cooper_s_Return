
#ifndef _GEOWARS_DELAY_H_
#define _GEOWARS_DELAY_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"

// --------------------------------------------------------------------------------

class Delay : public Object
{
private:
    Sprite * logo;          // logotipo do jogo
    Timer timer;            // medidor de tempo
    bool notPlayed;         // intro n�o tocada ainda

public:
    Delay();                // construtor
    ~Delay();               // destrutor

    void Update();          // atualiza��o
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif

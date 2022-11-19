
#ifndef _GEOWARS_MISSILE_H_
#define _GEOWARS_MISSILE_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h" 

// --------------------------------------------------------------------------------

class Missile : public Object
{
private:
    const float MaxDistance = 4406; // dist�ncia m�xima para o jogador
    const float BaseVolume = 0.8f;  // volume base para explos�o

    static Player* & player;        // refer�ncia para o player
    Sprite * sprite;                // sprite do m�ssil
    Vector speed;                   // velocidade do m�ssil    
    
public:
    Missile();                      // construtor
    ~Missile();                     // destrutor

    Vector& Speed();                // retona vetor velocidade
    void Update();                  // atualiza��o
    void Draw();                    // desenho
}; 

// ------------------------------------------------------------------------------

inline Vector& Missile::Speed()
{ return speed; }

inline void Missile::Draw()
{ sprite->Draw(x, y, Layer::UPPER, scale, rotation); }

// ------------------------------------------------------------------------------

#endif
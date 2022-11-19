
#ifndef _GEOWARS_COMET_H_
#define _GEOWARS_COMET_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

// ---------------------------------------------------------------------------------

class Comet : public Object
{
private:
    Sprite * sprite;                    // sprite do objeto
    Vector * speed;                     // velocidade e dire��o
    Player * player;                    // ponteiro para jogador
    Particles * tail;                   // calda da nave laranja
    float multiplier;                   // multiplicador da velocidade
    
public:
    Comet(Player * p);                 // construtor
    ~Comet();                          // destrutor
    
    void OnCollision(Object* obj);      // resolu��o da colis�o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
}; 

// ---------------------------------------------------------------------------------


#endif
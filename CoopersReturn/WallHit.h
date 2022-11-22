
#ifndef _COOPER_WALLHIT_H_
#define _COOPER_WALLHIT_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Particles.h"
#include "Missile.h"

// ---------------------------------------------------------------------------------

class WallHit : public Object
{
private:
    TileSet* explosion;                   // explosão
    Animation* animExp;                   // animação da explosão
    
public:
    WallHit(float pX, float pY);        // construtor
    ~WallHit();                         // destrutor

    void Update();                      // atualiza��o
    void Draw();                        // desenho
}; 

// ---------------------------------------------------------------------------------

inline void WallHit::Draw()
{  animExp->Draw(X(), Y(), Layer::FRONT); }

// ---------------------------------------------------------------------------------


#endif
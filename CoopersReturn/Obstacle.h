
#ifndef _COOPER_OBSTACLE_H_
#define _COOPER_OBSTACLE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

// ---------------------------------------------------------------------------------

class Body : public Object
{
private:
    Sprite* sprite;                    // sprite do objeto
    Vector* speed;                     // velocidade e dire��o
    Particles* tail = nullptr;          // calda
    float multiplier;                   // multiplicador da velocidade

public:
    Body(uint t, Sprite* s, Geometry* bb, float m, bool hasTail = false);                             // construtor
    ~Body();                            // destrutor

    void OnCollision(Object* obj);      // resolu��o da colis�o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    Vector* Speed();
};

inline Vector* Body::Speed() { return speed; }

// ---------------------------------------------------------------------------------

class Comet : public Body
{
private:
    
public:
    Comet();                 // construtor
    ~Comet();                          // destrutor
}; 

// ---------------------------------------------------------------------------------

class Obstacle
{
private:
    Sprite* comet;
    Sprite* asteroid;
    Sprite* meteoroid;

public:
    Obstacle();
    ~Obstacle();

    void Generate(uint type, float m);
};


#endif
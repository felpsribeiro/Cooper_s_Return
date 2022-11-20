
#include "CoopersReturn.h"
#include "Obstacle.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Body::Body(uint t, Sprite * s, Geometry* bb, float m, bool hasTail) : sprite(s), speed(new Vector(0, 2.0f))
{
    BBox(bb);
    type = t;
    multiplier = m;

    // move para uma posi��o aleat�ria pelos cantos

    RandF pos{ 0, CoopersReturn::Height() };
    MoveTo(CoopersReturn::Width(), pos.Rand());

    // ajusta �ngulo do vetor na dire��o do jogador
    speed->RotateTo(Line::Angle(Point(x, y), Point(CoopersReturn::player->X(), CoopersReturn::player->Y())));

    if (hasTail)
    {
        // configura��o do emissor de part�culas
        Generator emitter;
        emitter.imgFile = "Resources/Spark.png";    // arquivo de imagem
        emitter.angle = speed->Angle() + 180;       // �ngulo base do emissor
        emitter.spread = 30;                        // espalhamento em graus
        emitter.lifetime = 2.5f;                    // tempo de vida em segundos
        emitter.frequency = 0.00001f;                // tempo entre gera��o de novas part�culas
        emitter.percentToDim = 0.7f;                // desaparece ap�s 60% da vida
        emitter.minSpeed = 50.0f;                   // velocidade m�nima das part�culas
        emitter.maxSpeed = 100.0f;                  // velocidade m�xima das part�culas
        emitter.color.r = 0.0f;                     // componente Red da part�cula 
        emitter.color.g = 0.0F;                      // componente Green da part�cula 
        emitter.color.b = 1.0f;                     // componente Blue da part�cula 
        emitter.color.a = 0.4f;                     // transpar�ncia da part�cula

        // cria sistema de part�culas
        tail = new Particles(emitter);
    }
}

// ---------------------------------------------------------------------------------

Body::~Body()
{
    delete speed;
    delete tail;
}

// -------------------------------------------------------------------------------

void Body::OnCollision(Object * obj)
{
    if (obj->Type() == MISSILE)
        CoopersReturn::scene->Delete(this, MOVING);
}

// -------------------------------------------------------------------------------

void Body::Update()
{
    // movimenta objeto pelo seu vetor velocidade
    Translate(speed->XComponent() * multiplier * gameTime, -speed->YComponent() * multiplier * gameTime);

    // ajusta �ngulo do vetor na dire��o do jogador
    if (x < -30 || y < -40 || x > game->Width() + 30 || y > game->Height() + 40)
    {
        CoopersReturn::scene->Delete(this, MOVING);
    }

    // atualiza calda da nave
    if (tail)
    {
        tail->Config().angle = speed->Angle();
        tail->Generate(x - 10 * cos(speed->Radians()), y + 10 * sin(speed->Radians()));
        tail->Update(gameTime);
    }
}

// ---------------------------------------------------------------------------------

void Body::Draw()
{
    sprite->Draw(x, y, Layer::LOWER, scale, rotation);
    if (tail)
        tail->Draw(Layer::LOWER, 1.0f);
}

// -------------------------------------------------------------------------------

Obstacle::Obstacle() :
    comet(new Sprite("Resources/Cometa.png")), 
    asteroid(new Sprite("Resources/Asteroide.png")), 
    meteoroid(new Sprite("Resources/Meteoroide.png"))
{
    
}

// -------------------------------------------------------------------------------

Obstacle::~Obstacle() 
{
    delete comet;
    delete asteroid;
    delete meteoroid;
}

// -------------------------------------------------------------------------------

void Obstacle::Generete(uint type, float m)
{
    Sprite* sprite = nullptr;
    Geometry* bb = nullptr;
    bool hasTail = false;

    switch (type) {
    case COMET: 
    {
        sprite = comet;
        bb = new Circle(20.0f);
        hasTail = true;
        break;
    }
    case ASTEROID:
    {
        sprite = asteroid;
        bb = new Circle(20.0f);
        break;
    }
    case METEOROID:
    {
        sprite = meteoroid;
        bb = new Circle(20.0f);
        break;
    }
    }
    
    Body * body = new Body(type, sprite, bb, m, hasTail);

    CoopersReturn::scene->Add(body, MOVING);
}

#include "CoopersReturn.h"
#include "Obstacle.h"
#include "Random.h" 
#include "WallHit.h"

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
        emitter.spread = 20;                        // espalhamento em graus
        emitter.lifetime = 2.5f;                    // tempo de vida em segundos
        emitter.frequency = 0.00001f;                // tempo entre gera��o de novas part�culas
        emitter.percentToDim = 0.7f;                // desaparece ap�s 60% da vida
        emitter.minSpeed = 50.0f;                   // velocidade m�nima das part�culas
        emitter.maxSpeed = 100.0f;                  // velocidade m�xima das part�culas
        emitter.color.r = 1.0f;                     // componente Red da part�cula 
        emitter.color.g = 1.0F;                      // componente Green da part�cula 
        emitter.color.b = 0.0f;                     // componente Blue da part�cula 
        emitter.color.a = 0.7f;                     // transpar�ncia da part�cula

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
    if (obj->Type() == MISSILE || obj->Type() == PLAYER) {
        if(type != COMET) 
            CoopersReturn::scene->Add(new WallHit(X(), Y()), STATIC);
        CoopersReturn::scene->Delete(this, MOVING);
    }
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

void Obstacle::Generate(uint type, float m)
{
    Sprite* sprite = nullptr;
    Geometry* bb = nullptr;
    bool hasTail = false;

    switch (type) {
    case COMET: 
    {
        sprite = comet;
        bb = new Circle(10.0f);
        hasTail = true;
        break;
    }
    case ASTEROID:
    {
        sprite = asteroid;
        Point vertex[20] = {
            Point(-3, -39),
            Point(- 13, -39),
            Point(- 20, -33),
            Point(- 24, -29),
            Point(- 29, -18),
            Point(- 29, 12),
            Point(- 24, 23),
            Point(- 15, 32),
            Point(- 11, 37),
            Point(- 5, 40),
            Point(4, 40),
            Point(11, 38),
            Point(27, 14),
            Point(27, 9),
            Point(28, -2),
            Point(29, -4),
            Point(29, -15),
            Point(12, -38),
            Point(13, -40),
            Point(3, -40),
        };

        bb = new Poly(vertex, 20);

        break;
    }
    case METEOROID:
    {
        sprite = meteoroid;

        Point vertex[17] = {
            Point(8, -24),
            Point(2, -24),
            Point(-2, -21),
            Point(-6, -20),
            Point(-11, -12),
            Point(-11, -3),
            Point(-9, 2),
            Point(-7, 22),
            Point(-3, 27),
            Point(4, 26),
            Point(13, 15),
            Point(16, 6),
            Point(15, -8),
            Point(19, -12),
            Point(19, -19),
            Point(11, -25),
            Point(9, -25)
        };
        
        bb = new Poly(vertex, 17);

        break;
    }
    }
    
    Body * body = new Body(type, sprite, bb, m, hasTail);

    CoopersReturn::scene->Add(body, MOVING);
}

#include "CoopersReturn.h"
#include "Comet.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Comet::Comet(Player * p) : player (p)
{
    sprite = new Sprite("Resources/Orange.png");
    speed  = new Vector(0, 2.0f);
    BBox(new Circle(20.0f));

    // ajusta �ngulo do vetor na dire��o do jogador
    speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
    RotateTo(-speed->Angle());
    
    // move para uma posi��o aleat�ria (canto superior esquerdo)
    RandF pos{ 100, 150 };
    MoveTo(pos.Rand(), pos.Rand());

    multiplier = 70.0f;
    type = COMET;

    // configura��o do emissor de part�culas
    Generator emitter;
    emitter.imgFile = "Resources/Spark.png";    // arquivo de imagem
    emitter.angle = speed->Angle() + 180;       // �ngulo base do emissor
    emitter.spread = 10;                        // espalhamento em graus
    emitter.lifetime = 0.2f;                    // tempo de vida em segundos
    emitter.frequency = 0.010f;                 // tempo entre gera��o de novas part�culas
    emitter.percentToDim = 0.7f;                // desaparece ap�s 60% da vida
    emitter.minSpeed = 50.0f;                   // velocidade m�nima das part�culas
    emitter.maxSpeed = 100.0f;                  // velocidade m�xima das part�culas
    emitter.color.r = 1.0f;                     // componente Red da part�cula 
    emitter.color.g = 0.5;                      // componente Green da part�cula 
    emitter.color.b = 0.0f;                     // componente Blue da part�cula 
    emitter.color.a = 1.0f;                     // transpar�ncia da part�cula

    // cria sistema de part�culas
    tail = new Particles(emitter);
}

// ---------------------------------------------------------------------------------

Comet::~Comet()
{
    delete sprite;
    delete speed;
    delete tail;
}

// -------------------------------------------------------------------------------

void Comet::OnCollision(Object * obj)
{
    if (obj->Type() == MISSILE)
        CoopersReturn::scene->Delete(this, MOVING);
}

// -------------------------------------------------------------------------------

void Comet::Update()
{
    // movimenta objeto pelo seu vetor velocidade
    Translate(speed->XComponent() * multiplier * gameTime, -speed->YComponent() * multiplier * gameTime);

    // ajusta �ngulo do vetor na dire��o do jogador
    if (x < 100 || y < 100 || x > game->Width() - 100 || y > game->Height() - 100)
    {
        multiplier = 200;
        speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
        RotateTo(-speed->Angle());
    }

    // atualiza calda da nave
    tail->Config().angle = speed->Angle();
    tail->Generate(x - 10 * cos(speed->Radians()), y + 10 * sin(speed->Radians()));
    tail->Update(gameTime);
}

// ---------------------------------------------------------------------------------

void Comet::Draw()
{
    sprite->Draw(x, y, Layer::LOWER, scale, rotation);
    tail->Draw(Layer::LOWER, 1.0f);
}

// -------------------------------------------------------------------------------
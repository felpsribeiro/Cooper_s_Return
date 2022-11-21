
#include "CoopersReturn.h"
#include "WallHit.h"
#include "Random.h"

// ---------------------------------------------------------------------------------

WallHit::WallHit(float pX, float pY)
{
    // calcula �ngulo base e ajusta coordenadas da explos�o
    float base;
    if (pX < 0)
    {
        base = 0.0f;
        pX = 0;
    }
    else if (pX > game->Width())
    {
        base = 180.0f;
        pX = game->Width();
    }
    else if (pY < 0)
    {
        base = 270.0f;
        pY = 0;
    }
    else
    {
        base = 90.0f;
        pY = game->Height();
    }

    // n�mero aleat�rio entre 0 e 1
    RandF color{ 0, 1 };
    
    // configura emissor de part�culas
    Generator explosion;
    explosion.imgFile   = "Resources/Spark.png";    // arquivo de imagem
    explosion.angle     = base;                     // dire��o da explos�o
    explosion.spread    = 160.0f;                   // espalhamento em graus
    explosion.lifetime  = 1.0f;                     // tempo de vida em segundos
    explosion.frequency = 0.000f;                   // tempo entre gera��o de novas part�culas
    explosion.percentToDim = 0.6f;                  // desaparece ap�s 60% da vida
    explosion.minSpeed  = 25.0f;                    // velocidade m�nima das part�culas
    explosion.maxSpeed  = 250.0f;                   // velocidade m�xima das part�culas
    explosion.color.r   = color.Rand();             // cor da part�cula entre 0 e 1
    explosion.color.g   = color.Rand();             // cor da part�cula entre 0 e 1
    explosion.color.b   = color.Rand();             // cor da part�cula entre 0 e 1
    explosion.color.a   = 1.0f;                     // transpar�ncia da part�cula

    // cria sistema de part�culas
    sparks = new Particles(explosion);

    // gera 25 part�culas na posi��o de contato
    sparks->Generate(pX, pY, 25);
    //type = WALLHIT;
}

// ---------------------------------------------------------------------------------

WallHit::~WallHit()
{
    delete sparks;
}

// -------------------------------------------------------------------------------

void WallHit::Update()
{
    // atualiza posi��o de cada part�cula
    sparks->Update(gameTime);

    // remove da cena quando todas as part�culas est�o inativas
    if (sparks->Inactive())
        CoopersReturn::scene->Delete();
}

// -------------------------------------------------------------------------------
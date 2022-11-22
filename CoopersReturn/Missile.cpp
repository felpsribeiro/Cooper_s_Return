
#include "Missile.h"
#include "WallHit.h"
#include "CoopersReturn.h"

// ------------------------------------------------------------------------------

Player* & Missile::player = CoopersReturn::player;        // refer�ncia para o player

// ------------------------------------------------------------------------------

Missile::Missile()
{
    // inicializa sprite
    sprite = new Sprite("Resources/Missile.png");

    // cria bounding box
    BBox(new Circle(8));
    
    // inicializa velocidade
    speed.RotateTo(player->speed->Angle());
    speed.ScaleTo(15.0f);
    
    // move para posi��o
    MoveTo(player->X() + 35 * cos(speed.Radians()), 
            player->Y() - 35 * sin(speed.Radians()));
    
    RotateTo(-player->speed->Angle() + 180.0f);

    // define tipo
    type = MISSILE;
}

// ------------------------------------------------------------------------------

Missile::~Missile()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void Missile::Update()
{
    // move m�ssel com vetor resultante
    Translate(speed.XComponent() * 90.0f * gameTime, -speed.YComponent() * 90.0f * gameTime);

    // remove m�ssil da cena se ele sair da �rea de jogo
    if (x > game->Width() || x < 0 || y > game->Height() || y < 0)
    {
        // volume do som de destrui��o depende da dist�ncia para o jogador
        float distance = Point::Distance(Point(x, y), Point(player->X(), player->Y()));
        float level = (MaxDistance - distance) / MaxDistance * BaseVolume;

        // adiciona explos�o na cena
        //CoopersReturn::scene->Add(new WallHit(x,y), STATIC);

        // remove m�ssil da cena
        CoopersReturn::scene->Delete();
    }
}

// -------------------------------------------------------------------------------

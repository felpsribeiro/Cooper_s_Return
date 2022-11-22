
#include "CoopersReturn.h"
#include "WallHit.h"
#include "Random.h"

// ---------------------------------------------------------------------------------

WallHit::WallHit(float pX, float pY)
{
    explosion = new TileSet("Resources/exp_asteroide.png", 391.5f, 403.5f, 3, 6);
    animExp = new Animation(explosion, 0.05f, true);
}

// ---------------------------------------------------------------------------------

WallHit::~WallHit()
{
    delete explosion;
    delete animExp;
}

// -------------------------------------------------------------------------------

void WallHit::Update()
{
    animExp->NextFrame();

    // remove da cena quando todas as part�culas est�o inativas
    /*if (animExp->Inactive())
        CoopersReturn::scene->Delete();*/
}

// -------------------------------------------------------------------------------
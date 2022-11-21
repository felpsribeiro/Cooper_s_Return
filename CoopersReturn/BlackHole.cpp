
#include "BlackHole.h"
#include "CoopersReturn.h"

// -------------------------------------------------------------------------------

BlackHole::BlackHole()
{
    // configura��o do objeto
    hole = new Sprite("Resources/Black.jpg");
    eventHorizon = new TileSet("Resources/Gangantua.png", 2100, 345, 1, 5);
    anim = new Animation(eventHorizon, 0.060f, true);
    type = HOLE;
    
    BBox(new Line(0.0f, -346.0f, game->Width(), -346.0f));

    MoveTo(game->CenterX(), -173.0f);
}

// -------------------------------------------------------------------------------

BlackHole::~BlackHole()
{
    delete hole;
    delete eventHorizon;
    delete anim;
}

// -------------------------------------------------------------------------------

void BlackHole::Update()
{
    if (y < 1354.0f)
    {
        float accel = 40.0f * gameTime;
        Translate(0, accel);
    }
    else
    {
        CoopersReturn::Restart();
        CoopersReturn::scene->Delete(this, MOVING);
    }

    anim->NextFrame();
}

// ---------------------------------------------------------------------------------

void BlackHole::Draw()
{

    anim->Draw(x, y, Layer::LOWER);

    if (y > 173.0f)
       hole->Draw(x, y - 762.0f, Layer::FRONT);
}

// -------------------------------------------------------------------------------


#include "Player.h"
#include "Missile.h"
#include "CoopersReturn.h"

// -------------------------------------------------------------------------------

Player::Player()
{
    // configura��o do objeto
    sprite = new Sprite("Resources/Ranger.png");
    BBox(new Circle(18.0f));
    type = PLAYER;
    engine = new TileSet("Resources/Propellant.png", 50, 32, 1, 8);
    anim = new Animation(engine, 0.120f, true);
    speed = new Vector(0.0f, 0.0f);

    //// configura��o do gerador de part�culas
    // Generator emitter;
    // emitter.imgFile = "Resources/Spark.png";    // arquivo de imagem
    // emitter.angle = 270.0f;                     // �ngulo base do emissor
    // emitter.spread = 50;                        // espalhamento em graus
    // emitter.lifetime = 0.3f;                    // tempo de vida em segundos
    // emitter.frequency = 0.010f;                 // tempo entre gera��o de novas part�culas
    // emitter.percentToDim = 0.6f;                // desaparece ap�s 60% da vida
    // emitter.minSpeed = 50.0f;                   // velocidade m�nima das part�culas
    // emitter.maxSpeed = 100.0f;                  // velocidade m�xima das part�culas
    // emitter.color.r = 1.0f;                     // componente Red da part�cula
    // emitter.color.g = 1.0f;                     // componente Green da part�cula
    // emitter.color.b = 1.0f;                     // componente Blue da part�cula
    // emitter.color.a = 1.0f;                     // transpar�ncia da part�cula

    //// cria sistema de part�culas
    // tail = new Particles(emitter);
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete sprite;
    delete speed;
    // delete tail;
    delete engine;
    delete anim;
}

// -------------------------------------------------------------------------------

void Player::Init()
{
    speed = new Vector(0.0f, 0.0f);
    MoveTo(game->CenterX(), game->CenterY());
}

// -------------------------------------------------------------------------------

void Player::Move(Vector &&v)
{
    speed->Add(v);

    // limita velocidade m�xima
    if (speed->Magnitude() > 10.0f)
        speed->ScaleTo(10.0f);
}

// -------------------------------------------------------------------------------

void Player::Update()
{
    // jogo ainda não iniciou
    if (CoopersReturn::active)
    {
        // magnitude do vetor acelera��o
        float accel = 40.0f * gameTime;

        // modifica vetor velocidade do player
        if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_UP))
            Move(Vector(45.0f, accel));
        else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_UP))
            Move(Vector(135.0f, accel));
        else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_DOWN))
            Move(Vector(225.0f, accel));
        else if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_DOWN))
            Move(Vector(315.0f, accel));
        else if (window->KeyDown(VK_RIGHT))
            Move(Vector(0.0f, accel));
        else if (window->KeyDown(VK_LEFT))
            Move(Vector(180.0f, accel));
        else if (window->KeyDown(VK_UP))
            Move(Vector(90.0f, accel));
        else if (window->KeyDown(VK_DOWN))
            Move(Vector(270.0f, accel));

        // movimenta objeto pelo seu vetor velocidade
        Translate(speed->XComponent() * 50.0f * gameTime, -speed->YComponent() * 50.0f * gameTime);

        // dispara m�ssil
        if (window->KeyPress(VK_SPACE))
        {
            CoopersReturn::audio->Play(FIRE);
            CoopersReturn::scene->Add(new Missile(), STATIC);
        }

        //// atualiza calda do jogador
        // tail->Config().angle = speed->Angle() + 180;
        // tail->Generate(x - 10 * cos(speed->Radians()), y + 10 * sin(speed->Radians()));
        // tail->Update(gameTime);

        // restringe a �rea do jogo
        if (x < 50)
            MoveTo(50, y);
        if (y < 50)
            MoveTo(x, 50);
        if (x > game->Width() - 50)
            MoveTo(game->Width() - 50, y);
        if (y > game->Height() - 50)
            MoveTo(x, game->Height() - 50);
    }
    else
    {
        anim->NextFrame();
    }
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    if (CoopersReturn::active)
    {
        sprite->Draw(x, y, Layer::MIDDLE, scale, -speed->Angle());
    }
    else
    {
        sprite->Draw(x, y);
        anim->Draw(x - 53.0f, y, Layer::FRONT);
    }
    // tail->Draw(Layer::LOWER, 1.0f);
}

// -------------------------------------------------------------------------------

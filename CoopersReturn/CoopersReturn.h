
#ifndef _COOPERSRETURN_H_
#define _COOPERSRETURN_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Background.h"
#include "Player.h"
#include "Controller.h"
#include "Obstacle.h"
#include "BlackHole.h"

// ------------------------------------------------------------------------------

enum ObjectIds { PLAYER, MISSILE, COMET, ASTEROID, METEOROID, HOLE };

// ------------------------------------------------------------------------------

enum SoundIds { THEME, START, FIRE, EXPLODE, HITWALL };

// ------------------------------------------------------------------------------

enum GameState { INIT, PLAY, FINALIZE };

// ------------------------------------------------------------------------------

class CoopersReturn : public Game
{
private:
    Background * backg = nullptr;   // pano de fundo
    bool viewBBox = false;          // visualiza��o das bouding boxes
    Obstacle* obstacle;
    Timer auxTimer;

public:
    static Player * player;         // nave controlada pela jogador
    static Audio * audio;           // sitema de �udio
    static Scene * scene;           // cena do jogo
    static uint state;             // jogo iniciou
    static Timer timer;            // medidor de tempo
    static Controller * gamepad;    // controlador de jogo
    static bool ctrl;
    static bool lost;
    static void Restart();

    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif
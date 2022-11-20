
#ifndef _COOPERSRETURN_H_
#define _COOPERSRETURN_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Background.h"
#include "Player.h"
#include "Obstacle.h"

// ------------------------------------------------------------------------------

enum ObjectIds { PLAYER, MISSILE, COMET, ASTEROID, METEOROID };

// ------------------------------------------------------------------------------

enum SoundIds { THEME, START, FIRE, EXPLODE, HITWALL };

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
    static bool active;             // jogo iniciou
    static Timer timer;            // medidor de tempo

    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif
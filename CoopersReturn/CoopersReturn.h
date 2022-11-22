
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
#include "Font.h" 
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

enum ObjectIds { PLAYER, MISSILE, COMET, ASTEROID, METEOROID, HOLE };

// ------------------------------------------------------------------------------

enum SoundIds { INTRO, END };

// ------------------------------------------------------------------------------

enum GameState { INIT, MESG, PLAY, CLIMAX, FINALIZE, LOST, RESTART };

// ------------------------------------------------------------------------------

class CoopersReturn : public Game
{
private:
    Background * backg1 = nullptr;   // pano de fundo 1
    Background * backg2 = nullptr;   // pano de fundo 2
    float backVelocity = -100;
    bool viewBBox = false;          // visualiza��o das bouding boxes
    Obstacle* obstacle;
    Timer auxTimer;
    Font* font1 = nullptr;
    Font* font2 = nullptr;
    stringstream text;                 // texto tempor�rio
    Color textColor{ 1.0f, 1.0f, 1.0f, 1.0f };

public:
    static Player * player;         // nave controlada pela jogador
    static Audio * audio;           // sitema de �udio
    static Scene * scene;           // cena do jogo
    static uint state;             // estado do jogo
    static Timer timer;            // medidor de tempo
    static Controller * gamepad;    // controlador de jogo
    static bool ctrl;
    static void Restart();

    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif
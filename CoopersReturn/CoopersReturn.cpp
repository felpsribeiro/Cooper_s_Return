
#include "Resources.h"
#include "CoopersReturn.h"
#include "Engine.h"
#include "Menu.h"

// ------------------------------------------------------------------------------

Player * CoopersReturn::player  = nullptr;
Audio  * CoopersReturn::audio   = nullptr;
Scene  * CoopersReturn::scene   = nullptr;
bool     CoopersReturn::active  = false;
Timer    CoopersReturn::timer;
Controller * CoopersReturn::gamepad = new Controller();
bool         CoopersReturn::ctrl = false;
bool         CoopersReturn::lost = false;

// ------------------------------------------------------------------------------

void CoopersReturn::Init() 
{
    // cria sistema de �udio
    audio = new Audio();
    audio->Add(THEME, "Resources/Theme.wav");
    audio->Add(FIRE, "Resources/Fire.wav");
    audio->Add(HITWALL, "Resources/Hitwall.wav");
    audio->Add(EXPLODE, "Resources/Explode.wav");
    audio->Add(START, "Resources/Start.wav");

    // ajusta volumes
    audio->Volume(FIRE, 0.2f);
    audio->Volume(START, 0.8f);

    // carrega/incializa objetos
    backg   = new Background("Resources/Space.jpg");
    player  = new Player();
    player->Init();
    scene   = new Scene();

    // adiciona objetos na cena
    scene->Add(new Menu(), STATIC);
    scene->Add(player, MOVING);

    obstacle = new Obstacle();

    // ----------------------
    // inicializa a viewport
    // ----------------------

    // calcula posi��o para manter viewport centralizada
    float difx = (game->Width() - window->Width()) / 2.0f;
    float dify = (game->Height() - window->Height()) / 2.0f;

    // inicializa viewport para o centro do mundo
    viewport.left = 0.0f + difx;
    viewport.right = viewport.left + window->Width();
    viewport.top = 0.0f + dify;
    viewport.bottom = viewport.top + window->Height();

    ctrl = gamepad->XboxInitialize();
    lost = false;
}

// ------------------------------------------------------------------------------

void CoopersReturn::Update()
{
    //// toca m�sica do jogo
    //CoopersReturn::audio->Play(THEME, true);
    //CoopersReturn::viewHUD = true;

    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza cena e calcula colis�es
    scene->Update();
    scene->CollisionDetection();

    // ativa ou desativa a bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // ativa ou desativa o heads up display
    if (window->KeyPress(VK_RETURN))
    {
        active = true;
        auxTimer.Start();
    }

    // --------------------
    // atualiza a viewport
    // --------------------

    viewport.left   = player->X() - window->CenterX();
    viewport.right  = player->X() + window->CenterX();
    viewport.top    = player->Y() - window->CenterY();
    viewport.bottom = player->Y() + window->CenterY();
            
    if (viewport.left < 0)
    {
        viewport.left  = 0;
        viewport.right = window->Width();
    }
    else if (viewport.right > game->Width())
    {  
        viewport.left  = game->Width() - window->Width();
        viewport.right = game->Width();
    }
                  
    if (viewport.top < 0)
    {
        viewport.top  = 0;
        viewport.bottom = window->Height();
    }
    else if (viewport.bottom > game->Height())
    {
        viewport.top = game->Height() - window->Height();
        viewport.bottom = game->Height();
    }

    // ------------------------------------------------
    // gerencia elementos de acordo com o tempo de jogo
    // ------------------------------------------------

    if (!timer.Elapsed(60.0f)) // primeira etapa do jogo -> 0:00 à 0:59
    {
        if (auxTimer.Elapsed(3.0f))
        {
            obstacle->Generate(ASTEROID, 50.0f);
            auxTimer.Reset();
        }
    }
    else if (!timer.Elapsed(120.0f)) // segunda etapa do jogo -> 1:00 à 1:59
    {
        if (auxTimer.Elapsed(3.0f))
        {
            obstacle->Generate(ASTEROID, 50.0f);
            obstacle->Generate(METEOROID, 30.0f);
            auxTimer.Reset();
        }
    }
    else if (!timer.Elapsed(180.0f)) // terceira etapa do jogo -> 2:00 à 2:59
    {
        if (auxTimer.Elapsed(3.0f))
        {
            //obstacle->Generate(ASTEROID, 30.0f);
            obstacle->Generate(ASTEROID, 50.0f);
            obstacle->Generate(METEOROID, 30.0f);
            obstacle->Generate(COMET, 200.0f);
            auxTimer.Reset();
        }
    }
    else if (!timer.Elapsed(240.0f))
    {

    }
} 

// ------------------------------------------------------------------------------

void CoopersReturn::Draw()
{
    // desenha pano de fundo
    backg->Draw(viewport);

    // desenha a cena
    scene->Draw();

    // desenha bounding box
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void CoopersReturn::Finalize()
{
    delete audio;
    delete scene;
    delete backg;
    delete gamepad;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor do jogo
    Engine * engine = new Engine();

    // configura motor
    //engine->window->Mode(WINDOWED);
    //engine->window->Size(1152, 648);
    engine->window->Mode(BORDERLESS);
    engine->window->Color(0, 0, 0);
    engine->window->Title("CoopersReturn");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(true);
    //engine->graphics->VSync(true);

    // cria o jogo
    Game * game = new CoopersReturn();

    // configura o jogo
    game->Size(2100, 1181);
    
    // inicia execu��o
    int status = engine->Start(game);

    // destr�i motor e encerra jogo
    delete engine;
    return status;
}

// ----------------------------------------------------------------------------
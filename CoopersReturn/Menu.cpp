/**********************************************************************************
// Delay (C�digo Fonte)
//
// Cria��o:     02 Ago 2019
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Sincroniza uma a��o
//
**********************************************************************************/

#include "Menu.h"
#include "CoopersReturn.h"

// ------------------------------------------------------------------------------

Menu::Menu()
{
    logo = new Sprite("Resources/Logo.png");
    panel = new Sprite("Resources/Panel.png");

    font = new Font("Resources/SimSun16.png");
    font->Spacing("Resources/SimSun16.dat");
}

// ------------------------------------------------------------------------------

Menu::~Menu()
{
    delete logo;
    delete panel;
    delete font;
}

// -------------------------------------------------------------------------------

void Menu::Update()
{
    text1.str("");
    text2.str("");
    text3.str("");

    switch (CoopersReturn::state)
    {
    case INIT:
        text1 << "Precione Enter para iniciar o jogo..."; break;
    case MESG:
    case PLAY:
    {
        if (!CoopersReturn::timer.Elapsed(5.0f))
        {
            text1 << "Cooper precisa voltar para o buraco";
            text2 << "negro Gargantua... sua filha Murphy";
            text3 << "espera-o na terra.";
        }
        else if (!CoopersReturn::timer.Elapsed(8.0f))
        {
            text1 << "O motor principal da nave Ranger falhou";
            text2 << "devido uma onda gravitacional intensa.";
        }
        else if (!CoopersReturn::timer.Elapsed(11.0f))
        {
            text1 << "Por sorte, a nave ja entrou no campo";
            text2 << "gravitacional do buraco negro Gargantua";
            text3 << "e esta sendo atraido por ele.";
        }
        else if (!CoopersReturn::timer.Elapsed(14.0f))
        {
            text1 << "Ajude Cooper a guiar a nave ate o ";
            text2 << "Gargantua. desviando dos objetos que";
            text3 << "aparecerem pelo caminho.";
        }
        else if (!CoopersReturn::timer.Elapsed(20.0f))
        {
            CoopersReturn::scene->Delete();
        }
    }
    }
}

// -------------------------------------------------------------------------------

void Menu::Draw()
{
    logo->Draw(game->viewport.left + window->CenterX() , game->viewport.top + 200.0f, Layer::UPPER);
    panel->Draw(game->viewport.left + window->CenterX() , game->viewport.bottom - 63.0f, Layer::UPPER);

    // desenha texto
    font->Draw(500, 700, text1.str(), textColor);
    font->Draw(500, 720, text2.str(), textColor);
    font->Draw(500, 740, text3.str(), textColor);
}

// -------------------------------------------------------------------------------

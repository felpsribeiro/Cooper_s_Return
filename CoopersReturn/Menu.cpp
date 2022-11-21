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

    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");
    bold = new Font("Resources/Tahoma14b.png");
    bold->Spacing("Resources/Tahoma14b.dat");

    CoopersReturn::audio->Play(START);
}

// ------------------------------------------------------------------------------

Menu::~Menu()
{
    delete logo;
    delete panel;
    delete font;
    delete bold;
}

// -------------------------------------------------------------------------------

void Menu::Update()
{
    text1.str("");
    text2.str("");
    text3.str("");

    if (CoopersReturn::state == INIT)
    {
        text1 << "Precione Enter para iniciar o jogo...";
    }
    else if (CoopersReturn::state == PLAY)
    {
       if (!CoopersReturn::timer.Elapsed(5.0f))
       {
           text1 << "Cooper precisa voltar para o buraco ";
           text2 << "negro Gargantua... sua filha Murphy o";
           text3 << "está esperando na terra.";
       }
       else if (!CoopersReturn::timer.Elapsed(10.0f))
       {
           text1 << "O motor principal da nave Ranger falhou devido a uma onda gravitacional intensa.";
           text2 << "Por sorte, a nave já entrou no campo gravitacional do buraco negro Gargantua e";
           text3 << "esta sendo atraído por ele.";
       }
       else if (!CoopersReturn::timer.Elapsed(15.0f))
       {
           text1 << "Ajude Cooper a guiar a nave até o Gargantua, desviando dos objetos que aparecerem";
           text2 << "pelo caminho. Lembre-se da Lei de Murphy: \"Qualquer coisa que possa ocorrer mal,";
           text3 << "ocorrerá mal, no pior momento possível\"";
       }
       else if (!CoopersReturn::timer.Elapsed(20.0f))
       {
           CoopersReturn::scene->Delete();
       }
    }
}

// -------------------------------------------------------------------------------

void Menu::Draw()
{
    logo->Draw(game->viewport.left + window->CenterX() , game->viewport.top + 200.0f, Layer::UPPER);
    panel->Draw(game->viewport.left + window->CenterX() , game->viewport.bottom - 63.0f, Layer::UPPER);

    // desenha texto
    bold->Draw(500, 700, text1.str(), textColor);
    bold->Draw(500, 720, text2.str(), textColor);
    bold->Draw(500, 740, text3.str(), textColor);
}

// -------------------------------------------------------------------------------

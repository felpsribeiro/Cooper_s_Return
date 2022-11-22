/**********************************************************************************
// Background (Arquivo de Cabeçalho)
// 
// Criação:     07 Dez 2011
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Representa um pano de fundo maior que a janela
//
**********************************************************************************/

#ifndef _PROGJOGOS_BACKGROUND_H_
#define _PROGJOGOS_BACKGROUND_H_

// -------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Image.h"                      // carregamento de imagens
#include "Sprite.h"                     // desenho de sprites
#include <string>                       // biblioteca string da STL
using std::string;                      // permite usar string sem std::

// -------------------------------------------------------------------------------

class Background
{
private:
    SpriteData spriteData;              // informações do sprite 
    const Image * image;                // imagem de fundo
    float x, y;

public:
    Background(string filename, float x, float y);        // construtor    
    ~Background();                      // destrutor

    void Draw(ViewPort & sourceRect);   // desenha uma porção da imagem 
    uint Width();                       // retorna a largura do pano de fundo
    uint Height();                      // retorna a altura do pano de fundo
    float Right();
    void TranslateX(float x);
}; 

// ---------------------------------------------------------------------------------

// retorna a largura do sprite
inline uint Background::Width() 
{ return image->Width(); }

// retorna a altura do sprite
inline uint Background::Height() 
{ return image->Height(); }

// retorna posição x da sprite
inline float Background::Right()
{ return spriteData.x + Width()/2.0f; }

// desloca a sprite no eixo X
inline void Background::TranslateX(float x)
{ spriteData.x += x; }

// -------------------------------------------------------------------------------


#endif
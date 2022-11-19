
#include "Particles.h"
#include "Geometry.h"
#include <cmath>

// ---------------------------------------------------------------------------------

Particles::Particles(const Generator & generator) : config(generator)
{
    sprite = new Sprite(config.imgFile);
    timer.Start();
}

// ---------------------------------------------------------------------------------

Particles::~Particles()
{
    delete sprite;
    for (const auto & p : particles)
        delete p;
}

// ---------------------------------------------------------------------------------

void Particles::Build(float posX, float posY)
{
    // cria nova part�cula
    Particle * particle = new Particle();

    // ajusta posi��o
    particle->x = posX;
    particle->y = posY;
    
    // pega um �ngulo aleat�rio a partir do �ngulo base e espalhamento
    float angle = config.angle + spread.Rand();

    // mant�m �ngulo na faixa 0 a 359 graus
    if (angle > 360)
        angle -= 360;
    else 
        if (angle < 0)
        angle += 360;
    
    // ajusta vetor velocidade da part�cula
    particle->speed.RotateTo(angle);    
    particle->speed.ScaleTo(speed.Rand());
    particle->timestamp = timer.Stamp();

    // insere part�cula no lista de part�culas
    particles.push_back(particle);
}

// ---------------------------------------------------------------------------------

void Particles::Generate(float x, float y, int count)
{
    if (count == 1)
    {
        // gera uma part�cula por vez
        if (timer.Elapsed(config.frequency)) 
        {
            Build(x, y);
            timer.Start();
        }
    } 
    else 
    {    
        // gera todas as part�culas de uma vez
        for (int i = 0; i < count; ++i)
            Build(x, y);
    }
}

// ---------------------------------------------------------------------------------

void Particles::Update(float delta)
{
    float lifePercent = 0;
    float timeElapsed = 0;

    // percorre a lista de part�culas
    auto it = particles.begin();
    while (it != particles.end())
    {
        // para cada part�cula
        Particle * p = *it;

        // atualiza a posi��o da part�cula usando seu vetor velocidade
        p->x += p->speed.XComponent() * delta;
        p->y -= p->speed.YComponent() * delta;
        
        // calcula o percentual de vida da part�cula
        timeElapsed = timer.Elapsed(p->timestamp);
        lifePercent = timeElapsed/config.lifetime;

        // torna a part�cula transparente com o passar do tempo
        if (lifePercent > config.percentToDim)
        {
            // transpar�ncia cresce cubicamente com o tempo de vida
            config.color.a = 1.0f - pow(lifePercent, 3.0f);
        }

        if (timeElapsed > config.lifetime)
        {
            // remove a part�cula sem vida
            delete p;
            it = particles.erase(it);
        }
        else
        {
            // passa para pr�xima part�cula
            ++it;
        }
    }
}

// ---------------------------------------------------------------------------------

void Particles::Draw(float z, float factor)
{
    float lifePercent = 0.0f;
    float timeElapsed = 0.0f;
    
    // para cada part�cula da lista
    for (Particle * p : particles)
    {
        // calcula o percentual de vida da part�cula
        timeElapsed = timer.Elapsed(p->timestamp);
        lifePercent = timeElapsed/config.lifetime;

        // escala cresce quadraticamente com o tempo de vida
        float scale = 1.0f + pow(lifePercent, 2.0f) * factor;

        // desenha part�cula
        sprite->Draw(p->x, p->y, z, scale, -p->speed.Angle(), config.color);
    }    
}

// ---------------------------------------------------------------------------------

#include "ponto.h"

/**
 * @brief Construtor da classe ponto no r2
 * 
 * @param x coordenada x
 * @param y coordenada y
 */
Ponto::Ponto(double x, double y)
:x{x+400},y{y+400}
{
}

Ponto::Ponto()
{
    
}
Ponto::Ponto(const Ponto & p){
    x = p.x;
    y = p.y;
}


ostream & operator<< (ostream &out, const Ponto &p)
{
    out << "(" << p.x << "," << p.y << ")";
    return out;
}


#include "ponto3.h"

Ponto3::Ponto3(double x, double y, double z )
:x{x},y{y}, z{z}
{

}

Ponto3::Ponto3()
:x{0},y{0}, z{10}
{

}

ostream & operator<< (ostream &out, const Ponto3 &p)
{
    out << "(" << p.x << "," << p.y << ")";
    return out;
}
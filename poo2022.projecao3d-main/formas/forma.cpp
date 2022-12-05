#include "forma.h"
#include "../pontos/ponto3.h"

Forma::Forma(Ponto3 posicao, double tamanho)
:posicao{posicao},angulo{Ponto3(0.0,0.0,0.0)},tamanho{tamanho}
{
}

void Forma::calcular_pontos_2D(){
    int dist_f = 500;
    double y1,y2;
    Ponto* projecaoTemp = (Ponto*)malloc(sizeof(Ponto) * quantidadePontos);
    for( int i = 0 ; i < quantidadePontos ; i++ ){
        y1 = ( ( dist_f*-1 / pontos[i].z ) * pontos[i].x );
	    y2 = ( ( dist_f*-1 / pontos[i].z ) * pontos[i].y );
        projecaoTemp[i] = Ponto(y1,y2);
    }
	projecao = projecaoTemp;
}

void Forma::calcular_pontos_3D()
{
    double px = posicao.x;
    double py = posicao.y;
    double pz = posicao.z;
    double t = tamanho;
    

    Ponto3* pontosTemp = (Ponto3*)malloc(sizeof(Ponto3) * quantidadePontos);
    cout << 2 << endl;
    for(int i = 0 ; i < quantidadePontos ; i++ ){
        pontosTemp[i] = pontos_base[i];
        pontosTemp[i].x = px + pontosTemp[i].x * t;
        pontosTemp[i].y = py + pontosTemp[i].y * t;
        pontosTemp[i].z = pz + pontosTemp[i].z * t;
    }
   
    pontos = pontosTemp;
}

void Forma::girar(int rotacaoX, int rotacaoY, int rotacaoZ){

    angulo.x += rotacaoX;
    angulo.y += rotacaoY;
    angulo.z += rotacaoZ;
    double x,y,z,seno,cosseno;

    for( int i = 0 ; i < quantidadePontos ; i++ ){
        
        x = pontos_base[i].x;
        z = pontos_base[i].z;
        seno = sin( rotacaoX * M_PI / 180 );
        cosseno = cos( rotacaoX * M_PI / 180 );
        pontos_base[i].x = x * cosseno - z * seno;
        pontos_base[i].z = z * cosseno + x * seno;
        
        y = pontos_base[i].y;
        z = pontos_base[i].z;
        seno = sin( rotacaoY * M_PI / 180 );
        cosseno = cos( rotacaoY * M_PI / 180 );
        pontos_base[i].y = y * cosseno - z * seno;
        pontos_base[i].z = z * cosseno + y * seno;
        
        x = pontos_base[i].x;
        y = pontos_base[i].y;
        seno = sin( rotacaoZ * M_PI / 180 );
        cosseno = cos( rotacaoZ * M_PI / 180 );
        pontos_base[i].y = y * cosseno - x * seno;
        pontos_base[i].x = x * cosseno + y * seno;
    
    }
}

ostream & operator<< (ostream &out, const Forma &p)
{
    out << "posicao = Point3(" << p.posicao.x << "," << p.posicao.y << "," << p.posicao.z << ")" << endl;
    return out;
}

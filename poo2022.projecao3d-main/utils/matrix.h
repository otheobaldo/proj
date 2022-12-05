#pragma once
#include "Vec3.h"

class Matrix
{
private:

    int linhas, colunas; 
    double *valores;
    inline double& posicao(int l, int c) const { return valores[colunas * l + c];}
    
public:
    //Construtor
    Matrix(int linhas, int colunas);

    Matrix(int linhas, int colunas, double lista[]);

    //Copia
    Matrix(const Matrix &m);

    //Destrutor
    ~Matrix();

    //Retorna n de linhas
    inline int lin(void) const { return linhas; }

    //Retorna n de colunas 
    inline int col(void) const { return colunas; }

    void matrizAleatoria(void);

    double pegarValorEm(int l, int c) const;

    void definirValorEm(double v, int l, int c);
    
    void imprimirMatriz(const Matrix& m);

    Vec3 multiplicaMatriz(Vec3 &v, Matrix &m);
};



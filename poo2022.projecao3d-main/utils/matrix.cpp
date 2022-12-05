#include <iostream>
#include "matrix.h"
#include "Vec3.h"
#include <stdexcept>
#include <iomanip>

using namespace std;

// Construtor através de uma lista de valores para a matriz
Matrix::Matrix(int linhas, int colunas, double lista[])
:linhas{linhas},colunas{colunas}
{   
    valores = new double[linhas * colunas];

    int i=0;

    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            posicao(l,c) = lista[i];
            i+=1;
        }
    }
}

// Construtor caso seja passado por parametro somente linhas e colunas
Matrix::Matrix(int linhas, int colunas)
:linhas{linhas},colunas{colunas}
{
    valores = new double[linhas * colunas];
}

// Copia
Matrix:: Matrix(const Matrix &m)
:linhas{m.linhas},colunas{m.colunas}
{
    valores = new double[m.linhas * m.colunas];
    for (int i = 0; i < m.linhas * m.colunas; ++i) {
        valores[i] = m.valores[i];
    }
}

// Destrutor da classe
Matrix::~Matrix()
{
    delete[] valores;
}


// Função membro que gera matriz aleatória, dada a dimensão da matriz
void Matrix::matrizAleatoria(void)
{
    // Iterando por cada linha
    for (int l = 0; l < linhas; ++l) {
        // Depois por cada coluna
        for (int c = 0; c < colunas; ++c) {
            // Pegando a posição do elemento e dando um valor aleatório pra ele
            posicao(l, c) = (rand() % 100) / 10.0; 
        }
    }
}

// Método para imprimir a matriz de um jeito melhor
void Matrix::imprimirMatriz(const Matrix& m){
    // Definindo a precisão para uma casa após a vírgula
    cout << fixed << setprecision(1);
    for (int l = 0; l < m.lin(); ++l) {
        for (int c = 0; c < m.col(); ++c) {
            // Definindo a largura da exibição entre valores
            cout << (c > 0 ? " " : "") << setw(4);
            // Usando o método para mostrar o valor
            cout << m.pegarValorEm(l, c);
        }
        cout << endl;
    }
}

// Método que retorna o valor de um elemento da matriz, passando a linha e coluna
double Matrix::pegarValorEm(int l, int c) const
{
    // Verificação para saber se o valor requisitado existe na matriz
    if (l < 0 || l >= linhas || c < 0 || c >= colunas) {
        // Se não existir, retorna a excessão, mostrando que está fora de alcance
        throw out_of_range("Fora de alcance");
    }
        return posicao(l, c);
}


// Método que multiplica a matriz por um vetor de tamanho 3
Vec3 Matrix::multiplicaMatriz(Vec3 &v, Matrix &m){
    // A multiplicação só é possível caso a matriz tenha o mesmo número de colunas de que o vetor tem de linhas
    if (m.col()== 3){
        // Através de um vetor temporário, a multiplicação é feita usando o método para pegar o valor em determinada posição
        Vec3 tmp{0,0,0};
        tmp.x = v.x * m.pegarValorEm(0,0)+v.y * m.pegarValorEm(0,1)+v.z *m.pegarValorEm(0,2);
        tmp.y = v.x * m.pegarValorEm(1,0)+v.y * m.pegarValorEm(1,1)+v.z * m.pegarValorEm(1,2);
        tmp.z = v.x * m.pegarValorEm(2,0)+v.y * m.pegarValorEm(2,1)+v.z * m.pegarValorEm(2,2);
        // Retornando o vetor após as multiplicações
        return tmp;
    }
    // Se não tiver, retorna a excessão dizendo que não tem como realizar a multiplicação
    else{
        throw out_of_range("Impossível multiplicar.");
    }    
}


// Método para definir o valor de certo elemento da matriz
void Matrix::definirValorEm(double v, int l, int c)
// v = valor, l = linha, c = coluna
{
    // Verifica se o valor não existe dentro da matriz
    if (l < 0 || l >= linhas || c < 0 || c >= colunas) {
        // Caso não exista, retorna uma exceção 
        throw out_of_range("Fora de alcance");
}   
    // Caso exista, define o valor passado no parametro para o elemento da posição
    posicao(l, c) = v;
}

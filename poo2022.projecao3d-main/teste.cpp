//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include "utils/janela.h"
#include "pontos/ponto.h"
#include "pontos/ponto3.h"
#include "formas/cubo/cubo.h"
#include "formas/esfera/esfera.h"
#include "formas/cone/cone.h"
#include "formas/cilindro/cilindro.h"
#include "formas/forma.h"
#include "utils/Vec3.h"
#include <iostream>

using namespace std;

struct Planeta
{
	Esfera modelo;
	double angulo = 0;
	double distancia = 10;
	double velocidade = 1;
};

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main( int argc, char* args[] )
{
	//Eventos e loop principal
	bool quit = false;	
	SDL_Event ev;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		Window window = Window(SCREEN_WIDTH,SCREEN_HEIGHT);

		Cubo cuboX{Ponto3(5,5,10),1.0};
		Cubo cuboZ{Ponto3(0,5,10),1.0};
		Cubo cuboY{Ponto3(-5,5,10),1.0};
		// Cone cone{Ponto3(-5,0,10),10,2};

		Cilindro cilindro{Ponto3(-5,-1,10),20,3};



		struct Planeta{
			Forma* modelo;
			Forma* orbitar;
			double angulo;
			double raio;
			double velocidade;
		};

		Esfera sol{Ponto3(0,-10,50),2,60};
		sol.girar(10,10,10);
		sol.corR = 255;
		sol.corG = 255;
		sol.corB = 0;
		sol.comSombra = false;

		Esfera marte{Ponto3(0,-2,10),1.5,60};
		marte.girar(10,10,10);
		marte.corR = 255;
		marte.corG = 180;
		marte.corB = 180;
		Planeta planetaMarte;
		planetaMarte.modelo = &marte;
		planetaMarte.angulo = 0;
		planetaMarte.raio = 8;
		planetaMarte.velocidade = 1;
		planetaMarte.orbitar = &sol;

		Esfera terra{Ponto3(0,-2,10),1.5,60};
		terra.girar(10,10,10);
		terra.corR = 180;
		terra.corG = 180;
		terra.corB = 255;
		Planeta planetaTerra;
		planetaTerra.modelo = &terra;
		planetaTerra.angulo = 0;
		planetaTerra.raio = 20;
		planetaTerra.velocidade = 2;
		planetaTerra.orbitar = &sol;

		Esfera lua{Ponto3(0,-2,10),1,60};
		lua.girar(10,10,10);
		lua.corR = 255;
		lua.corG = 255;
		lua.corB = 255;
		Planeta planetaLua;
		planetaLua.modelo = &lua;
		planetaLua.angulo = 0;
		planetaLua.raio = 3;
		planetaLua.velocidade = -5;
		planetaLua.orbitar = &terra;

		

		struct Planeta planetas[3] = {planetaTerra,planetaLua,planetaMarte};
		Forma* render[4] = {&terra,&marte,&sol,&lua};

		double angulo = 0;
		double raio = 8;
		double npx,npz;
		double a[3] = {sol.posicao.x,sol.posicao.y,sol.posicao.z};
		double b[3];

		while (!quit)
		{

			window.limpar();

			///////////////////////////////////////////////////
			//DEMO PLANETARIO - INICIO

			//girar planetas ao redor do sol e atualizar sua iluminacao
			for( int i = 0 ; i < 3 ; i++ ){
				planetas[i].angulo += planetas[i].velocidade;

				npx = planetas[i].orbitar -> posicao.x + (planetas[i].raio * cos( (planetas[i].angulo + (100 * i)) * M_PI / 180 ));
				npz = planetas[i].orbitar -> posicao.z + (planetas[i].raio * sin( (planetas[i].angulo + (100 * i)) * M_PI / 180 ));

				planetas[i].modelo -> posicao.x = npx;
				planetas[i].modelo -> posicao.z = npz;
				planetas[i].modelo -> posicao.y = planetas[i].orbitar -> posicao.y;
				b[0] = planetas[i].modelo -> posicao.x;
				b[1] = planetas[i].modelo -> posicao.y;
				b[2] = planetas[i].modelo -> posicao.z;
				planetas[i].modelo -> iluminacao = Vec3(b,a);
			}	

			//ordenar a lista de planetas para começar renderizando de traz para frente
			Forma* swap;	
			for( int j = 0 ; j < 4 ; j++ ){
				for( int k = 0 ; k < 3 ; k++ ){
					if( render[k] -> posicao.z < render[k+1] -> posicao.z ){
						swap = render[k+1];
						render[k+1] = render[k];
						render[k] = swap;
					}
				}
			}	

			//renderizar objetos
			for( int l = 0 ; l < 4 ; l++ ){
				render[l] -> desenhar(window);
			}

			//DEMO PLANETARIO - FIM
			////////////////////////////////////q




			// cone.girar(1,1,1);
			cilindro.desenhar(window);

			cuboX.girar(5,0,0);
			cuboX.desenhar(window);

			cuboY.girar(0,5,0);
			cuboY.desenhar(window);

			cuboZ.girar(0,0,5);
			cuboZ.desenhar(window);




			while( SDL_PollEvent( &ev ) != 0 )
				{
					
					if( ev.type == SDL_KEYDOWN )
					{
						if (ev.key.keysym.sym == SDLK_q)
						{
							quit = true;
						}
					}
				}
	
				/*
					if (ev.key.keysym.sym == SDLK_a)
					{
						forma.posicao.x -= 1;
						//mover para esquerda
					}
					if (ev.key.keysym.sym == SDLK_d)
					{
						forma.posicao.x += 1;
						//mover para direita
					}
					if (ev.key.keysym.sym == SDLK_e)
					{
						forma.posicao.y -= 1;
						//mover para cima
					}
					if (ev.key.keysym.sym == SDLK_q)
					{
						forma.posicao.y += 1;
						//mover para baixo
					}
					if (ev.key.keysym.sym == SDLK_w)
					{
						forma.posicao.z -= 1;
						//mover para tras
					}
					if (ev.key.keysym.sym == SDLK_s)
					{
						forma.posicao.z += 1;
						//mover para frente
					}
					if (ev.key.keysym.sym == SDLK_t)
					{
						forma.girar(5,0,0);
						//girar para x
					}
					if (ev.key.keysym.sym == SDLK_y)
					{
						forma.girar(0,5,0);
						//girar para a y
					}
					if (ev.key.keysym.sym == SDLK_u)
					{
						forma.girar(0,0,5);
						//girar para a z
					}

					//Para a esfera
					if (ev.key.keysym.sym == SDLK_i)
					{
						forma.setLOD(1);
						//aumentar lod
					}
					if (ev.key.keysym.sym == SDLK_o)
					{
						forma.setLOD(0);
						//diminuir lod
					}
				*/

			window.atualiza();	
			SDL_Delay(1000/24);		


		
		}
	}
	return 0;
}

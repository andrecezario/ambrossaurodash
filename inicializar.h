//____________________________________________________________________________//

#define MAX_FRAME 10

//----------------------------------------------------------------------------//

typedef struct{	
	BITMAP *bmp[MAX_FRAME];
	int x, y; 			//Posicao na tela
	int dx, dy; 		//Deslocamento
	int modo, flip; 	//Condições do frame (tipo: ivertido, transparente, normal);
} SPRITE;

//____________________________________________________________________________//

#ifndef INICIALIZAR_H
#define INICIALIZAR_H

volatile int sair_do_jogo;
void saindo();
END_OF_FUNCTION(saindo);

//----------------------------------------------------------------------------//

volatile int tempo;
void timer();
END_OF_FUNCTION(timer);

//----------------------------------------------------------------------------//

volatile int milissegundos;
void mseg();
END_OF_FUNCTION(mseg);

//----------------------------------------------------------------------------//

int tela;

int tempotroca;

int frame_atual(int num_frames);

//----------------------------------------------------------------------------//

int max(int a, int b);
int min(int a, int b);

//----------------------------------------------------------------------------//

int colision(BITMAP* imagem1, int x1, int y1, BITMAP* imagem2, int x2, int y2);

//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//

void inicializacao();

//----------------------------------------------------------------------------//

#endif

//____________________________________________________________________________//

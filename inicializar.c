#include <allegro.h>
#include "inicializar.h"

void saindo()
{
	sair_do_jogo = TRUE;
}

void timer()
{
	tempo++;
}

void mseg()
{
	milissegundos++;
}

int frame_atual(int num_frames)
{
	return (milissegundos / tempotroca) % num_frames;
}

int max(int a, int b)
{
	return (a >= b) ? a : b;
}

int min(int a, int b)
{
	return (a <= b) ? a : b;
}

int colision(BITMAP* imagem1, int x1, int y1, BITMAP* imagem2, int x2, int y2)
{
	int colide = FALSE;
	
    if(!((x1 > (x2 + imagem2->w)) || (y1 > (y2 + imagem2->h)) || (x2 > (x1 + imagem1->w)) || (y2 > (y1 + imagem1->h) ))) //Verifica se os bitmaps  estão se intersectando
    {
    	int i, j;

   		int cima 	 = max(y1, y2);
	 	int baixo 	 = min(y1 + imagem1->h, y2 + imagem2->h);
	 	int esquerda = max(x1, x2);
     	int direita  = min(x1 + imagem1->w, x2 + imagem2->w);

	 	for(i = cima; i < baixo; i++)
	 	{
			for(j = esquerda; j < direita; j++)
			{
		  		if(getpixel(imagem1, j-x1, i-y1) != makecol(255,0,255) && getpixel(imagem2, j-x2, i-y2) != makecol(255,0,255))
		  		{
		  			colide = TRUE;
		  			j = direita;
		  			i = baixo;
		  		}
			}
	 	}
   	}

   	return colide;
}

void inicializacao()
{
	allegro_init();
	install_timer();
	install_keyboard();
	set_color_depth(16);
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,1000,600,0,0);
	set_window_title("AMBROSSAURO DASH");
	
	sair_do_jogo = FALSE;
	LOCK_FUNCTION(saindo);
	LOCK_VARIABLE(sair_do_jogo);
	set_close_button_callback(saindo);
	 
	tempo = 0;
	LOCK_FUNCTION(timer);
	LOCK_VARIABLE(tempo);
	install_int_ex(timer, BPS_TO_TIMER(60));

	milissegundos = 0;
	LOCK_FUNCTION(mseg);
	LOCK_VARIABLE(milissegundos);
	install_int_ex(mseg, MSEC_TO_TIMER(1));
	
	tela = 1;

	tempotroca = 100;
}

#include <stdio.h>
#include <allegro.h>
#include "inicializar.h"
#include "menu.h"
#include "modo_infinito.h"

int main()
{
	inicializacao();
	BITMAP* final = load_bitmap("Imagens/final.bmp",NULL);
	
	while (!sair_do_jogo)
  	{
     	if (tela == 1)
     	{
			mainmenu();
		}
     	else if (tela == 2)
       	{
			corrida_infinita();	
		}
			
		else if(tela ==4) {
			draw_sprite(screen, final, 0, 0);
		}
  	}
  	
	destroy_bitmap(final);
	allegro_exit();
	 
    return 0;	
}

END_OF_MAIN();

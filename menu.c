#include <stdio.h>
#include <allegro.h>
#include "inicializar.h"
#include "menu.h"

void mainmenu()
{
	int sair_do_menu = FALSE;
	int time = 0, flash = 0;
	
	///BITMAPS
	BITMAP* fundo_menu = load_bitmap("Imagens/menu.bmp", NULL);
  	BITMAP* buffer     = create_bitmap(SCREEN_W, SCREEN_H);
  	BITMAP* titulo     = load_bitmap("Imagens/titulo.bmp", NULL);
  	
  	FONT*   fonte1     = load_font("Fontes/fonte22.pcx", NULL, NULL);
  	FONT*   fonte2     = load_font("Fontes/arial12.pcx", NULL, NULL);
	FONT*   fonte3     = load_font("Fontes/chinese22.pcx", NULL, NULL);  	
  	///GAME LOOP
  	while (!(sair_do_jogo || sair_do_menu))
  	{
		while (tempo > 0 && !(sair_do_jogo || sair_do_menu))
		{
			if (key[KEY_SPACE]) 
			{
				tela = 2; //JOGO MODO CORRIDA INFINITA
				sair_do_menu = TRUE;
			}
			
			//INPUT
      		if(key[KEY_ESC]) saindo();
       		//UPDATE

      		//DRAW
      		draw_sprite(buffer, fundo_menu, 0, 0);
      		
      		if(time > 50) time = 0;
      		
      		if(time < 25)
      		{
				textout_centre_ex(buffer, fonte3, "Press SPACE to start!", SCREEN_W/2 + 15, SCREEN_H/3 - 15, makecol(255,255,0), -1);
			}
			else if (time > 25)
			{
      			textout_centre_ex(buffer, fonte3, "Press ESC to exit!", SCREEN_W/2, SCREEN_H/2 + 18, makecol(255,255,255), -1);
			}	
      			
      		draw_sprite(screen, buffer, 0, 0);
      		clear(buffer);
      	
			tempo--;
			time++;
		}
	}
	///FINALIZAÇÃO
	destroy_bitmap(fundo_menu);
  	destroy_bitmap(buffer);
  	destroy_bitmap(titulo);
  	destroy_font(fonte1);
  	destroy_font(fonte2);
}

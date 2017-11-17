#include <stdio.h>
#include <allegro.h>
#include "inicializar.h"
#include "modo_fases.h"

/* FAZER FASE 2 E CONFIGURAR FASE 1 NO MODO INFINITO*/
void fase()
{
	/* -------------------- VARIÁVEIS LOCAIS -------------------------------- */
	int sair_do_modo = FALSE;
	int dino_situacao; //decide que fazer
	int dino_parado;
	int i, j;	
	int marcador = 3000;
	int vai_tu = FALSE;
	int mostra_ptero = FALSE;
	
	/* --------------------------- SONS ------------------------------------- */
	SAMPLE* mordida    = load_sample("Sons/eat.wav");
	SAMPLE* chicote    = load_sample("Sons/chicote.wav");
	SAMPLE* garra      = load_sample("Sons/rasgo.wav");
	MIDI* music        = load_midi("Sons/musicjp.mid");
	//play_midi(music, 1);	
	
	/* ---------------------- SPRITES / BITMAPS ----------------------------- */
	
	SPRITE fundo; 
	fundo.bmp[0] = load_bitmap("Imagens/fundofase0.bmp", NULL);
	fundo.modo   = DRAW_SPRITE_NORMAL;
	fundo.flip   = DRAW_SPRITE_NO_FLIP;
	fundo.x      = 0;
	fundo.y      = 0;
	fundo.dx     = 5;
	fundo.dy     = 0;
	//__________________________________________________________________________
	
	SPRITE dino;
	dino.bmp[0] 	= load_bitmap("Imagens/Trex/trex_01.bmp", NULL);
	dino.bmp[1] 	= load_bitmap("Imagens/Trex/trex_02.bmp", NULL);
	dino.bmp[2] 	= load_bitmap("Imagens/Trex/trex_03.bmp", NULL);
	dino.bmp[3] 	= load_bitmap("Imagens/Trex/trex_04.bmp", NULL);
	dino.modo       = DRAW_SPRITE_NORMAL;
	dino.flip   	= DRAW_SPRITE_NO_FLIP;
	dino.x      	= 50;
	dino.y      	= 340;
	dino.dx     	= 5;
	dino.dy     	= 0;
	
	int num_frames_dino = 4;
	//__________________________________________________________________________
	
	SPRITE dino_atak[3];
	dino_atak[0].bmp[0] 	= load_bitmap("Imagens/Trex/trex_14.bmp", NULL);
	dino_atak[0].bmp[1] 	= load_bitmap("Imagens/Trex/trex_15.bmp", NULL);
	dino_atak[0].bmp[2] 	= load_bitmap("Imagens/Trex/trex_16.bmp", NULL);

	dino_atak[1].bmp[0] 	= load_bitmap("Imagens/Trex/trex_08.bmp", NULL);
	dino_atak[1].bmp[1] 	= load_bitmap("Imagens/Trex/trex_09.bmp", NULL);
	dino_atak[1].bmp[2] 	= load_bitmap("Imagens/Trex/trex_10.bmp", NULL);

	dino_atak[2].bmp[0] 	= load_bitmap("Imagens/Trex/trex_13.bmp", NULL);
	dino_atak[2].bmp[1] 	= load_bitmap("Imagens/Trex/trex_12.bmp", NULL);
	dino_atak[2].bmp[2] 	= load_bitmap("Imagens/Trex/trex_13.bmp", NULL);
	
	int num_frames_dino_atak = 3;
	//__________________________________________________________________________

	SPRITE inimigo;
	inimigo.bmp[0]  = load_bitmap("Imagens/Inimigo/veloci33.bmp", NULL);
	inimigo.bmp[1]  = load_bitmap("Imagens/Inimigo/veloci34.bmp", NULL);
	inimigo.bmp[2]  = load_bitmap("Imagens/Inimigo/veloci35.bmp", NULL);
	inimigo.modo    = DRAW_SPRITE_NORMAL;
	inimigo.flip   	= DRAW_SPRITE_NO_FLIP;
	inimigo.x      	= 700;
	inimigo.y      	= 380;
	inimigo.dx     	= 5;
	inimigo.dy     	= 0;
		
	int num_frames_inimigo = 3;
	
	SPRITE inim_atak;
	inim_atak.bmp[0]  = load_bitmap("Imagens/Inimigo/veloci75.bmp", NULL);
	inim_atak.bmp[1]  = load_bitmap("Imagens/Inimigo/veloci76.bmp", NULL);
	inim_atak.bmp[2]  = load_bitmap("Imagens/Inimigo/veloci77.bmp", NULL);
	inim_atak.bmp[3]  = load_bitmap("Imagens/Inimigo/veloci78.bmp", NULL);
	
	int num_frames_inim_atak = 4;
	
	SPRITE inim_corre;
	inim_corre.bmp[0]  = load_bitmap("Imagens/Inimigo/veloci92.bmp", NULL);
	inim_corre.bmp[1]  = load_bitmap("Imagens/Inimigo/veloci93.bmp", NULL);
	inim_corre.bmp[2]  = load_bitmap("Imagens/Inimigo/veloci94.bmp", NULL);
	inim_corre.bmp[3]  = load_bitmap("Imagens/Inimigo/veloci95.bmp", NULL);
	inim_corre.bmp[4]  = load_bitmap("Imagens/Inimigo/veloci96.bmp", NULL);
	inim_corre.bmp[5]  = load_bitmap("Imagens/Inimigo/veloci97.bmp", NULL);
	
	int num_frames_inim_corre = 6;
	
	SPRITE inim_morre;
	inim_morre.bmp[0]  = load_bitmap("Imagens/Inimigo/veloci53.bmp", NULL);
	inim_morre.bmp[1]  = load_bitmap("Imagens/Inimigo/veloci54.bmp", NULL);
	inim_morre.bmp[2]  = load_bitmap("Imagens/Inimigo/veloci55.bmp", NULL);
	inim_morre.bmp[3]  = load_bitmap("Imagens/Inimigo/veloci56.bmp", NULL);
	
	int num_frames_inim_morre = 4;

	//_________________________________________________________________________

	SPRITE ptero;
	ptero.bmp[0] 	 = load_bitmap("Imagens/Ptero/ptero1.bmp", NULL);
	ptero.bmp[1]	 = load_bitmap("Imagens/Ptero/ptero2.bmp", NULL);
	ptero.bmp[2] 	 = load_bitmap("Imagens/Ptero/ptero3.bmp", NULL);
	ptero.bmp[3]     = load_bitmap("Imagens/Ptero/ptero4.bmp", NULL);
	ptero.bmp[4]	 = load_bitmap("Imagens/Ptero/ptero5.bmp", NULL);
	ptero.bmp[5]	 = load_bitmap("Imagens/Ptero/ptero6.bmp", NULL);
	ptero.modo   	 = DRAW_SPRITE_NORMAL;
	ptero.flip   	 = DRAW_SPRITE_NO_FLIP;
	ptero.x     	 = -140;
	ptero.y     	 = -140;
	
	int num_frames_ptero = 6;
	
	SPRITE ptero_sombra;
	ptero_sombra.bmp[0] 	= load_bitmap("Imagens/Ptero/sombra1.bmp", NULL);
	ptero_sombra.bmp[1] 	= load_bitmap("Imagens/Ptero/sombra2.bmp", NULL);
	ptero_sombra.bmp[2] 	= load_bitmap("Imagens/Ptero/sombra3.bmp", NULL);
	ptero_sombra.bmp[3] 	= load_bitmap("Imagens/Ptero/sombra4.bmp", NULL);
	ptero_sombra.bmp[4] 	= load_bitmap("Imagens/Ptero/sombra5.bmp", NULL);
	ptero_sombra.bmp[5] 	= load_bitmap("Imagens/Ptero/sombra6.bmp", NULL);
	ptero_sombra.x 			= ptero.x;
	ptero_sombra.y 			= 310;
	
	SPRITE pedra;
	pedra.bmp[0] 	= load_bitmap("Imagens/Ptero/bb.bmp", NULL);
	pedra.x 		= ptero.x + 40;
	pedra.y 		= ptero.y + 100;
	
	///__________________________________________________________________________///
	
	BITMAP* garra_imagem  = load_bitmap("Imagens/Trex/gaa.bmp", NULL);
	
	BITMAP* vida 		  = load_bitmap("Imagens/vida_score1.bmp", NULL);
	
	BITMAP* buffer        = create_bitmap(SCREEN_W, SCREEN_H);
	/* -------------------------------------------------------------------------- */
	
	srand(time(NULL));
	
	dino_situacao = 3;

	//------------------------------- GAME LOOP ----------------------------------//

	while (!(sair_do_jogo || sair_do_modo)) 
	{
		//60 FPS
	 	while (tempo > 0 && !(sair_do_jogo || sair_do_modo))
		{
			
			dino_parado = TRUE;
				
			/* ----------------------------- BOTÃO MENU --------------------------------- */

	 		if (key[KEY_ENTER])
			{
				tela = 1;
				stop_midi ();
				sair_do_modo = TRUE;
				clear_keybuf();	
			}			
			
			/* -------------------------- LÓGICA BOTÃO DIREITO -------------------------- */

			if (key[KEY_RIGHT])
			{
				dino_situacao = 3;
				
				dino_parado = FALSE;

				dino.modo =  DRAW_SPRITE_NORMAL;
				dino.flip =  DRAW_SPRITE_NO_FLIP;
				
				if (dino.x < 370 && fundo.x != -1200)
				{
					dino.x += dino.dx;
				}
				else if (fundo.x > -1200)
				{
					fundo.x -= fundo.dx;
				}
				else if (fundo.x == -1200 && dino.x < 780)
				{
					dino.x += dino.dx;
				}
				clear_keybuf();
			}
						
			/* -------------------------- LÓGICA BOTÃO ESQUERDO ------------------------- */

			if (key[KEY_LEFT])
			{
				dino_situacao = 3;
				
				dino_parado = FALSE;

				dino.modo =  DRAW_SPRITE_NORMAL;
				dino.flip =  DRAW_SPRITE_H_FLIP;
				
				if (dino.x > 400 && fundo.x != 0)
				{
					dino.x -= dino.dx;
				}
				else if (fundo.x < 0)
				{
					fundo.x += fundo.dx;
				}
				else if (fundo.x == 0 && dino.x > 0)
				{
					dino.x -= dino.dx;
				}
				clear_keybuf();
			}			
			
			/* ------------------------ LÓGICA BOTÃO A, ATAQUE 0 ------------------------ */

			if (key[KEY_A])
			{
				dino_situacao = 0;
				dino_parado = FALSE;
				midi_pause();
				play_sample(garra, 200, 128, 1000, 0);
				midi_resume();
				clear_keybuf();
			}
			
			/* ------------------------- LÓGICA BOTÃO S, ATAQUE 1 ----------------------- */

			if (key[KEY_S])
			{
				dino_situacao = 1;
				dino_parado = FALSE;
				midi_pause();
				play_sample(chicote, 200, 128, 1000, 0);
				midi_resume();
				clear_keybuf();
			}
			
			/* ------------------------- LÓGICA BOTÃO D, ATAQUE 2 ----------------------- */

			if (key[KEY_D])
			{
				dino_situacao = 2;
				dino_parado = FALSE;
				midi_pause();
				play_sample(mordida, 200, 255, 1000, 0);
				midi_resume();
				clear_keybuf();
			}
			
			///________________________________ INIMIGO _________________________________///
		
			if (inimigo.x < dino.x && dino.x - inimigo.x > 200)
			{
				inimigo.x += 8;
				inimigo.modo    = DRAW_SPRITE_NORMAL;
				inimigo.flip   	= DRAW_SPRITE_NO_FLIP;	
			}
			else if (inimigo.x > dino.x && inimigo.x - dino.x > 100)
			{
				inimigo.x -= 8;
				inimigo.modo    = DRAW_SPRITE_NORMAL;
				inimigo.flip   	= DRAW_SPRITE_H_FLIP;
			}
						
			
			/* ---------------------------------- PTERO --------------------------------- */
			
			if (milissegundos % marcador > 2980)
			{
				if (rand() % 3 == 1)	vai_tu	= TRUE;
			}
			if (vai_tu)
			{
				mostra_ptero = TRUE;
				ptero.x 	   +=  6;
				ptero_sombra.x	= ptero.x;	
				if (ptero.y <= 20)
				{
					ptero.y        += 4;
					pedra.x 		= ptero.x + 96;
					pedra.y 		= ptero.y + 97;
				}
				else if (milissegundos % marcador > 2000)
				{
					ptero.y -= 4;
				}
			}
			if (ptero.y < - 150)
			{
				vai_tu   = FALSE;
				mostra_ptero = FALSE;
				ptero.x  = (rand() % 1500) - 200;
				ptero.y  = -140;
				ptero_sombra.x = ptero.x;
			}
			
			
			/* -------------------------------- FUNDO ----------------------------------- */

			draw_sprite_ex(buffer, fundo.bmp[0], fundo.x, fundo.y, fundo.modo, fundo.flip); 
			
			if (colision(dino.bmp[frame_atual(num_frames_dino)], dino.x, dino.y, inimigo.bmp[frame_atual(num_frames_inimigo)], inimigo.x + fundo.x, inimigo.y) == TRUE)
			{
				//tocou = 'X';
				textprintf_ex(buffer, font,  SCREEN_W/2 + 5, 15, makecol(255, 0, 0), -1, "XXX");
			}
			
			// -------------------------------- PTERO ------------------------------------//

			
			if (mostra_ptero)
			{
				draw_sprite_ex(buffer, ptero.bmp[frame_atual(num_frames_ptero)], ptero.x + fundo.x, ptero.y, ptero.modo, ptero.flip);

				draw_sprite_ex(buffer, ptero_sombra.bmp[frame_atual(num_frames_ptero)], ptero_sombra.x, ptero_sombra.y, ptero.modo, ptero.flip);
			
				draw_sprite(buffer, pedra.bmp[0], pedra.x + fundo.x, pedra.y);		
			}
			//---------------------------------- INIMIGO ---------------------------------//

			draw_sprite_ex(buffer, inimigo.bmp[frame_atual(num_frames_inimigo)], fundo.x + inimigo.x, inimigo.y, inimigo.modo, inimigo.flip);

			//--------------------------------- DINO -------------------------------------//

			switch (dino_situacao)
 		 	{
 		 		case 0 :
				{
       				draw_sprite_ex(buffer, dino_atak[0].bmp[frame_atual(num_frames_dino_atak)], dino.x , dino.y, dino.modo, dino.flip);
       				if (dino.flip == DRAW_SPRITE_H_FLIP)
					{
						draw_sprite_ex(buffer, garra_imagem, dino.x -40, dino.y + 20, dino.modo, dino.flip);
					}
					else{
       					draw_sprite_ex(buffer, garra_imagem, dino.x + 170, dino.y + 20, dino.modo, dino.flip);
					}
 		 		}
     			break;

     			case 1:
				{
					if (dino.flip == DRAW_SPRITE_H_FLIP && frame_atual(num_frames_dino_atak) == 2)
					{
						draw_sprite_ex(buffer, dino_atak[1].bmp[2], dino.x - 90, dino.y, dino.modo, dino.flip);
					}
					else
					{
       					draw_sprite_ex(buffer, dino_atak[1].bmp[frame_atual(num_frames_dino_atak)], dino.x, dino.y, dino.modo, dino.flip);
					} 
				}
     			break;

     			case 2:
       				draw_sprite_ex(buffer, dino_atak[2].bmp[frame_atual(num_frames_dino_atak)], dino.x, dino.y, dino.modo, dino.flip);
     			break;

     			case 3:
				{
					if (!dino_parado)
					{
       					draw_sprite_ex(buffer, dino.bmp[frame_atual(num_frames_dino)], dino.x, dino.y, dino.modo, dino.flip);
					}
					else
					{
						draw_sprite_ex(buffer, dino.bmp[1], dino.x, dino.y, dino.modo, dino.flip);
					}
				}
     			break;
     		}
     		
     		draw_sprite(buffer, vida, SCREEN_W - 30, 20);
			//----------------------------------------------------------------------------//			
			textprintf_ex(buffer, font, SCREEN_W - 75, 15, makecol(255, 0, 0), -1, "%d", tempo); // SE TEMPO = 1 O FPS ESTÁ CONTROLADO	
		 	
		 	textprintf_ex(buffer, font, 15, 15, makecol(255, 20, 20), -1, "Press ENTER to Menu!");

		 	//textprintf_ex(buffer, font,  SCREEN_W/2 - 5, 15, makecol(255, 0, 0), -1, "%c", tocou);
		 	
			draw_sprite(screen, buffer, 0, 0);
			
			
	 		clear(buffer);
	 		
	 		tempo--;
		}
	}

	/* -----------------------------  FINALIZAR  -------------------------------- */

	destroy_sample(mordida);
	destroy_sample(chicote);
	destroy_sample(garra);
	destroy_midi(music);
	
	for (i = 0; i < 3; i++)
	{
		destroy_bitmap(inimigo.bmp[i]);
		for (j = 0; j < 3; j++)
		{
			destroy_bitmap(dino_atak[i].bmp[j]);
		}
	}
	for (i = 0; i < 4; i++)
	{
		destroy_bitmap(dino.bmp[i]);
		destroy_bitmap(inim_atak.bmp[i]);
		destroy_bitmap(inim_morre.bmp[i]);
	}
	for (i = 0; i < 6; i++)
	{	
		destroy_bitmap(ptero.bmp[i]);
		destroy_bitmap(ptero_sombra.bmp[i]);
		destroy_bitmap(inim_corre.bmp[i]);
	}
	destroy_bitmap(garra_imagem);
	destroy_bitmap(vida);
	destroy_bitmap(pedra.bmp[0]);
	destroy_bitmap(fundo.bmp[0]);
	destroy_bitmap(buffer);
}

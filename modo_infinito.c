#include <stdio.h>
#include <allegro.h>
#include "inicializar.h"
#include "modo_infinito.h"

void corrida_infinita()
{
//----------------------------------- SOM ------------------------------------//
	
	SAMPLE* jump = load_sample("Sons/jump1.wav");
	SAMPLE* coin = load_sample("Sons/coins.wav");
	SAMPLE* life_lost = load_sample("Sons/dino.wav");
	MIDI* music = load_midi("Sons/music13.mid");
	
	play_midi(music, 1);
	
//----------------------------- DINOSSAURO EM PE -----------------------------//
	
	SPRITE dino;
	dino.bmp[0] = load_bitmap("Imagens/dino1.bmp",NULL);
	dino.bmp[1] = load_bitmap("Imagens/dino2.bmp",NULL);
	dino.bmp[2] = load_bitmap("Imagens/dino3.bmp",NULL);
	dino.bmp[3] = load_bitmap("Imagens/dino4.bmp",NULL);

//---------------------------- SOMBRA DO DINOSSAURO --------------------------//
	
	SPRITE sombra;
	sombra.bmp[0] = load_bitmap("Imagens/sombra1.bmp", NULL);
	sombra.bmp[1] = load_bitmap("Imagens/sombra2.bmp", NULL);
	sombra.bmp[2] = load_bitmap("Imagens/sombra3.bmp", NULL);
	sombra.bmp[3] = load_bitmap("Imagens/sombra4.bmp", NULL);
		
//---------------------------- DINOSSAURO ABAIXADO ---------------------------//
	
	SPRITE abaixa;
	abaixa.bmp[0] = load_bitmap("Imagens/dino21.bmp",NULL);
	abaixa.bmp[1] = load_bitmap("Imagens/dino22.bmp",NULL);
	abaixa.bmp[2] = load_bitmap("Imagens/dino23.bmp",NULL);
	abaixa.bmp[3] = load_bitmap("Imagens/dino24.bmp",NULL);
	
//----------------------------- DINOSSAURO COLISAO ---------------------------//
	
	BITMAP* colisao = load_bitmap("Imagens/colidiu.bmp",NULL);
	BITMAP* vida_score = load_bitmap("Imagens/vida_score.bmp",NULL);
	BITMAP* vida_caminho = load_bitmap("Imagens/vida_caminho.bmp",NULL);
	
//--------------------------------- TUBARÃO ----------------------------------//
	
	SPRITE shark;
	shark.bmp[0] = load_bitmap("Imagens/shark1.bmp",NULL);
	shark.bmp[1] = load_bitmap("Imagens/shark2.bmp",NULL);
	shark.bmp[2] = load_bitmap("Imagens/shark3.bmp",NULL);
	shark.bmp[3] = load_bitmap("Imagens/shark4.bmp",NULL);
	
//----------------------------------- TRICERATOPS ----------------------------//
	
	SPRITE trice;
	trice.bmp[0] = load_bitmap("Imagens/trice1.bmp",NULL);
	trice.bmp[1] = load_bitmap("Imagens/trice2.bmp",NULL);
	trice.bmp[2] = load_bitmap("Imagens/trice3.bmp",NULL);
	trice.bmp[3] = load_bitmap("Imagens/trice4.bmp",NULL);	
	
//---------------------------------- PTEROSSAURO -----------------------------//
	
	SPRITE ptero;
	ptero.bmp[0] = load_bitmap("Imagens/ptero1.bmp",NULL);
	ptero.bmp[1] = load_bitmap("Imagens/ptero2.bmp",NULL);
	ptero.bmp[2] = load_bitmap("Imagens/ptero3.bmp",NULL);
	ptero.bmp[3] = load_bitmap("Imagens/ptero4.bmp",NULL);
	ptero.bmp[4] = load_bitmap("Imagens/ptero5.bmp",NULL);
	
//-------------------------------- VELOCIRAPTOR ------------------------------//
	
	SPRITE velo;
	velo.bmp[0] = load_bitmap("Imagens/velo1.bmp",NULL);
	velo.bmp[1] = load_bitmap("Imagens/velo2.bmp",NULL);
	velo.bmp[2] = load_bitmap("Imagens/velo3.bmp",NULL);
	velo.bmp[3] = load_bitmap("Imagens/velo4.bmp",NULL);
	velo.bmp[4] = load_bitmap("Imagens/velo6.bmp",NULL);
	//velo[5] = load_bitmap("Imagens/velo6.bmp",NULL);
	
//---------------------------------CENARIO------------------------------------//
	 	 
	BITMAP* espinho = load_bitmap("Imagens/espinho.bmp",NULL);
	BITMAP* espinho2 = load_bitmap("Imagens/espinho2.bmp",NULL);
	
	BITMAP* cena_0  = load_bitmap("Imagens/chao.bmp",NULL);
	BITMAP* cena_1  = load_bitmap("Imagens/fundo.bmp",NULL);
	
	BITMAP* buffer  = create_bitmap(SCREEN_W, SCREEN_H);

//-------------------------------- VARIAVEIS ---------------------------------//
	
	FONT* font  = load_font("Fontes/chinese16.pcx", NULL, NULL);
	int y = 350; // MANIPULAR O EIXO y;
	int cx_0 = 0, cx_1 = 0; // MANIPULAR O MOVIMENTO DA TELA DE FUNDO
	int a = 0, cond_pular = 0, stop_fut = 0; //MANIPULAR OS MOVIMENTOS DO PERSONAGEM
	int c = 0, b = 0, vai_tu = 7; // OBSTACULOS
	int i, j;

	int num_frames = 4;
	int n_frames_ptero = 5;
	int n_frames_trice = 4;
	int n_frames_velo = 5;
	
	int frame_atual = 0;
	int frame_ptero = 0;
	int frame_trice = 0;
	int frame_velo = 0;
	
	int tempo_troca = 100;
	int tempo_troca_velo = 50;
	int cond_ptero = 0;
	
	int speed = 0;
	int valor_aumento = 500;
	int speed_floor = 12;
	int speed_mountains = 4;
	
	int sair_do_modo = FALSE;
		
	int diminui = 0;
	int vidas = 3;
	int colidindo = 0;
	int score = 0;
	
	srand(time(NULL));
	
// --------------------------------- GAME LOOP -------------------------------//
	
	while (!(sair_do_jogo || sair_do_modo)) 
	{
		//60 FPS
	 	while (tempo > 0 && !(sair_do_jogo || sair_do_modo))
		{				
				
	 		if (key[KEY_ENTER])
			{
				tela = 1;
				stop_midi ();
				sair_do_modo = TRUE;	
			}
			//------------------FINAL---------------------//
			if(score==1000)
			{
				tela = 4;
				stop_midi ();
				sair_do_modo = TRUE;	
			}
			
			//-----------------------------VIDA-------------------------------//
			if(diminui && c==0)
			{				
				vidas--;
				diminui = 0;
				colidindo = 0;
			}
			
			if(vidas==0) 
			{		
				tela = 1;
				stop_midi ();
				sair_do_modo = TRUE;	
			}	
			
			else {	
				//---------------AUMENTA A VELOCIDADE DO CENARIO--------------//				
				speed++;
				if(speed%valor_aumento==0) {
					speed_floor += 1; 
					speed_mountains += 1; 
					speed = 0;
				}
		 		
		 		if(stop_fut == 0) frame_atual = (milissegundos / tempo_troca) % num_frames; //stop_fut serve para os pés do personagem pararem de mexer quando ele pula.
				
				frame_ptero = (milissegundos / tempo_troca) % n_frames_ptero;
				frame_trice = (milissegundos / tempo_troca) % n_frames_trice;
				frame_velo = (milissegundos / tempo_troca_velo) % n_frames_velo;
					
//--------------------------- MOVIMENTO DO CENÁRIO ---------------------------//

		 		if(cx_0 < -1000)
				{
					cx_0 = 0;
					c = 0;//AUTORIZA O SORTEIO DE UM NOVO OBSTACULO
				}
		 		else
				{
					cx_0 -= speed_floor;
					c = 1;//IMPEDE QUE HAJA OUTRO SORTEIO DE OBSTACULOS ENQUANTO A TELA NÃO CHEGAR AO FIM
				}
		 		if(cx_1 < -1000) cx_1 = 0;
		 		else cx_1 -= speed_mountains;
		 		
		 		draw_sprite(buffer,cena_1,cx_1,0);
		 		draw_sprite(buffer,cena_1,cx_1+998,0);
		 		draw_sprite(buffer,cena_0,cx_0,0);
		 		draw_sprite(buffer,cena_0,cx_0+998,0);
			
//------------------------------ SOMBRA DO DINO ------------------------------//

				draw_sprite(buffer, sombra.bmp[frame_atual], 100, 350);
			
//------------------------------- SE ABAIXAR ---------------------------------//

				if(key[KEY_DOWN] && !colidindo)
				{
					draw_sprite(buffer, abaixa.bmp[frame_atual], 100, y+70);
					cond_ptero = 0;
				}
			
//------------------------- IMPRIMI O DINO(T-rex) ----------------------------//

				if(!key[KEY_DOWN] && !colidindo)
				{
					//SOMBRA
					draw_sprite(buffer, sombra.bmp[frame_atual], 100, 350);
		 			draw_sprite(buffer, dino.bmp[frame_atual], 100, y);
		 			cond_ptero = 1;
				}
			
				//PULO
				if(cond_pular == 0 && key[KEY_UP])
				{	
					cond_pular = 1;
					stop_fut = 1; //FAZ COM QUE AS PERNAS DO PERSONAGEM PAREM DE MEXER DURANTE O PULO
					play_sample(jump, 200, 128, 1000, 0);
				}
			
				//MANTENDO O PULO MAIS ESTÁTICO
				if(cond_pular == 1)
				{
					y -= 12;
					if(y == 122 && cond_pular == 1) cond_pular = 2;
				}
				if(key[KEY_DOWN] && cond_pular == 1) cond_pular = 4;
				
				else if(cond_pular == 2)
				{
					y -= 3;
					if(y == 98) cond_pular = 3;
				}
				if(key[KEY_DOWN] && cond_pular == 2) {
					cond_pular = 3; y = 122;
				}
				
				else if(cond_pular == 3)
				{
					if(y == 122) cond_pular = 4;
					else y += 3;
				}
				
				else if(cond_pular == 4)
				{
					y += 12;
					if(y == 350 && cond_pular == 4){
						cond_pular = 0; stop_fut = 0;
					}
				}
			
//------------------------------- OBSTACULOS ---------------------------------//

				if(c == 0)  {
					vai_tu = rand() %15;
				}
				
				if(vai_tu == 0 || vai_tu == 1)
				{
					draw_sprite(buffer, espinho, cx_0+1000, 400);
					
					//COLISAO ESPINHO1
					if (colision(dino.bmp[frame_atual], 140, y, espinho2, cx_0 + 1000, 350) == TRUE) 
					{
						draw_sprite(buffer,colisao,100,y);
						diminui = 1;
						colidindo = 1;		
					}
				}
				
				else if(vai_tu == 2 || vai_tu == 3)
				{
					draw_sprite(buffer, ptero.bmp[frame_ptero], cx_0+1000, 320);
					
					//COLISAO PTEROSSAURO
					if((((y > 330 && y < 370) && cond_ptero == 1) && (cx_0+1000 < 300)) && (colision(dino.bmp[frame_atual], 140, y, ptero.bmp[frame_ptero], cx_0 + 1000, 320) == TRUE))
					{
						draw_sprite(buffer,colisao,100,y);
						diminui = 1;		
						colidindo = 1;
					}			
				}
	
				else if(vai_tu == 4 || vai_tu == 5)
				{
					if(cx_0+SCREEN_W > 0 && cx_0+SCREEN_W < 500)
					{
						b = frame_atual;
						if(frame_atual == 0) b++;				
					}
					else b = 0;
					draw_sprite(buffer, shark.bmp[b], cx_0+1000, 400);
				
					//COLISAO TUBARAO
					if (colision(dino.bmp[frame_atual], 140, y, shark.bmp[b], cx_0 + 1000, 400) == TRUE)					
					{
						draw_sprite(buffer, colisao, 100, y);
						diminui = 1;							
						colidindo = 1;	
					}		
				}
							
				else if(vai_tu == 6 || vai_tu ==7)
				{
					draw_sprite(buffer, trice.bmp[frame_trice], cx_0+1000, 420); 
						
					//COLISAO TRICERAPTOS
					if (colision(dino.bmp[frame_atual], 140, y, trice.bmp[frame_trice], cx_0 + 1000, 420) == TRUE)
					{
						draw_sprite(buffer,colisao,100,y);
						diminui = 1;	
						colidindo = 1;			
					}
				}
				
				else if(vai_tu == 8 || vai_tu ==9)
				{
					draw_sprite(buffer, espinho2, cx_0+1000, 350);
					
					//COLISAO ESPINHO2 
					if (colision(dino.bmp[frame_atual], 140, y, espinho2, cx_0 + 1000, 350) == TRUE)
					{
						draw_sprite(buffer,colisao,100,y);
						diminui = 1;
						colidindo = 1;		
					}
				}
				
				else if(vai_tu == 10|| vai_tu == 11)
				{
					draw_sprite(buffer, velo.bmp[frame_velo], cx_0+1000, 420);
					
					//COLISAO VELOCIRAPTOR
					if (colision(dino.bmp[frame_atual], 140, y, velo.bmp[frame_velo], cx_0 + 1000, 420) == TRUE)
					{
						draw_sprite(buffer,colisao,100,y);
						diminui = 1;
						colidindo = 1;		
					}		
				}
				
				else if((vai_tu == 12 || vai_tu == 13) && vidas < 2)
				{
					draw_sprite(buffer, vida_score, cx_0+1000, 440);
					
					//VIDA
					if(y+95 > 435 && cx_0+1000 < 300)
					{
						play_sample(coin, 200, 128, 1000, 0);
						vidas++;
					}
				}
				
				if(colidindo == 1) play_sample(life_lost, 200, 128, 1000, 0);
				
//------------------------------ MOSTRANDO VIDAS -----------------------------//

				//textprintf_ex(buffer, font, SCREEN_W - 30, 15, makecol(255, 0, 0), -1, "%d", vidas);
				int incremento = 80;
				for (i = 0; i < vidas; i++) 
				{
					draw_sprite(buffer, vida_score, SCREEN_W - incremento, 40);
					incremento += 80; 
				}
//-----------------------------------SCORE--------=---------------------------//
				
				if(speed%10==0) score++;
				textprintf_ex(buffer, font, SCREEN_W - 200, 15, makecol(255, 255, 255), -1, "Score: %d", score); //SCORE	
				
	
			 	textprintf_ex(buffer, font, 15, 15, makecol(255, 255, 255), -1, "Press ENTER to Menu!");
			 	
				draw_sprite(screen,buffer,0,0);
		 		clear(buffer);
		 		
		 		tempo--;
			}
		}
	}

//------------------------------ FINALIZAR -----------------------------------//
	destroy_sample(jump);
	destroy_sample(coin);
	destroy_sample(life_lost);
	destroy_midi(music);
	destroy_bitmap(vida_score);
	destroy_bitmap(vida_caminho);
	
	for (i = 0; i < 4; i++)
	{
		destroy_bitmap(dino.bmp[i]);
		destroy_bitmap(sombra.bmp[i]);
		destroy_bitmap(abaixa.bmp[i]);
		destroy_bitmap(trice.bmp[i]);
		destroy_bitmap(shark.bmp[i]);
	}
	for (i = 0; i < 5; i++)
	{
		destroy_bitmap(ptero.bmp[i]); 
		destroy_bitmap(velo.bmp[i]);
	}
		
	destroy_bitmap(espinho);  
	destroy_bitmap(espinho2);
	destroy_bitmap(colisao);
	destroy_bitmap(cena_0);
	destroy_bitmap(cena_1);
	 
	destroy_bitmap(buffer);
	
}


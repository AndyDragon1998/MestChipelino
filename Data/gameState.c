/*****************************************************************************/
/*  Автор         		: Дракончик				        					 */
/*  Приставка     		: Sony PlayStation 2								 */
/*  ОС			  		: OSDSYS											 */
/*  Язык	      		: GNU C                                       		 */
/*                                                                           */
/*  Содержимое файла	: Стадия игровой детельности                         */
/*  Атрибут файла		: SOURCE                                             */
/*  Имя файла     		: gameState.c	                               		 */
/*                                                                           */
/*****************************************************************************/

#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"
#include "include/pad.h"
#include "include/musicManager.h"
#include "include/textToGraphics.h"
#include "include/player.h"
#include "include/enemy.h"
#include <math.h>

extern StateMachine GameMachineState;

/****** User External Files ********/
#include "extern/gameState.ext"

/****** User Table Files ***********/
#define PLAYERSHOT "/Graphics/Sprites/Shot.png"
#define WIN "/Graphics/Sprites/final.png"

/****** User Define Files ***********/
#include "define/gameState.def"


// Graphics Synthesizer Texture structs
GSTEXTURE BackgroundImage;
GSTEXTURE PlayerShot;
GSTEXTURE Win;

BGM BackgroundMusic;

Player chipelino;
Enemy potato[30];

PlayerBullet Bullet[36];

int bulletCount;
int counter=0;

void GameStart(GSGLOBAL* gsGlobal)//
{
	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, BACKGROUND_1);
	gsKit_texture_png(gsGlobal, &BackgroundImage,tempy);
	
	char temp[4096];
	strcpy(temp, relativePath);
	strcat(temp, "/Audio/BGM/LaCaution.wav");
	BackgroundMusic.fileName = temp;
	LoadMusic(&BackgroundMusic);
	SetUpFont(gsGlobal);
	
	InitializePlayer(&chipelino, gsGlobal);
	InitializeEnemyTexture(gsGlobal);
	for(int i = 0; i < 30; i++)
	{
		InitializeEnemy(&potato[i], gsGlobal);
	}
	
	char tempz[4096];
	strcpy(tempz, relativePath);
	strcat(tempz, PLAYERSHOT);
	gsKit_texture_png(gsGlobal, &PlayerShot,tempz);
	
	char tempw[4096];
	strcpy(tempw, relativePath);
	strcat(tempw, WIN);
	gsKit_texture_png(gsGlobal, &Win,tempw);

}

void GameUpdate(GSGLOBAL* gsGlobal)
{
	// This part here plays the music
	PlayMusic(&BackgroundMusic);
	
	for(int i = 0; i < 30; i++)
	{
		UpdateEnemy(&potato[i],gsGlobal, chipelino.posX1, chipelino.posY1);
	}
	
	if(PlaystationGamePad.UP_KEY_DOWN)
	{
	
	chipelino.posY1=chipelino.posY1+3;
	chipelino.posU=52;
	chipelino.direction=0;
	}
	
	if(PlaystationGamePad.DOWN_KEY_DOWN)
	{

 	chipelino.posY1=chipelino.posY1-3;
 	chipelino.posU=156;
 	chipelino.direction=2;
	}
	
	if(PlaystationGamePad.LEFT_KEY_DOWN)
	{
	
	chipelino.posX1=chipelino.posX1+3;
	chipelino.posU=104;
	chipelino.direction=3;
	}	
	
	if(PlaystationGamePad.RIGHT_KEY_DOWN)
	{
	
	chipelino.posX1=chipelino.posX1-3;
	chipelino.posU=0;
	chipelino.direction=1;
	}
	
	if(PlaystationGamePad.BUTTON_X_KEY_TAP)
	{
		switch(chipelino.direction)
		{
			case 0:
				Bullet[bulletCount].direction=1;
			break;
			
			case 1:
				Bullet[bulletCount].direction=2;
			break;
			
			case 2:
				Bullet[bulletCount].direction=3;
			break;
			
			case 3:
				Bullet[bulletCount].direction=0;
			break;
		}
		Bullet[bulletCount].posX = 340;
		Bullet[bulletCount].posY = 307;
		Bullet[bulletCount].isAlive = true;
		bulletCount++;
		
	}
	
	if(PlaystationGamePad.BUTTON_O_KEY_DOWN)
	{

	}
	printf("%d", counter);

	if(chipelino.posX1 > 0)
	{
		chipelino.posX1 =0;
	}
	if(chipelino.posY1 > 0)
	{
		chipelino.posY1 =0;
	}
	if(chipelino.posX1 < -1272)
	{
		chipelino.posX1 =-1272;
	}
	if(chipelino.posY1 < -1014)
	{
		chipelino.posY1 =-1014;
	}
	
	
	
	for(int z = 0; z < bulletCount; z++)
	{
		UpdateBullets(&Bullet[z]);
	}
	
	for(int i = 0; i < bulletCount; i++)
	{		
		if(Bullet[i].posY > (BackgroundImage.Width  * 6)+chipelino.posY1 || !Bullet[i].isAlive || Bullet[i].posY < 0+chipelino.posY1 || Bullet[i].posX > (BackgroundImage.Width  * 6)+chipelino.posX1 || Bullet[i].posX < 0+chipelino.posX1)
		{
			for (int j = i; j < bulletCount; j++)  
			{  
			    Bullet[j] = Bullet[j+1]; 
			}  
			bulletCount--;
		}
	}
	
	if(chipelino.Health==0){
	StateMachineChange(&GameMachineState, &OverState, gsGlobal);
	}
	
	
	
	
	for(int i = 0; i < bulletCount; i++)
	{
		for(int j = 0; j < 30; j++)
		{
			int A=sqrt(pow(potato[j].posX+25-Bullet[i].posX,2)+pow(potato[j].posY+25-Bullet[i].posY,2));
			
			if(A < 50)
			{
				potato[j].isAlive = 0;
				Bullet[i].isAlive = 0;
				counter++;
			}
		}
	}
	
}


void GameDraw(GSGLOBAL* gsGlobal, u64 colour)
{
	
	
	gsKit_prim_sprite_texture(gsGlobal, &BackgroundImage,0+chipelino.posX1,  // X1
										0+chipelino.posY1,  // Y1
										0,  // U1
										0.0f,  // V1
										(BackgroundImage.Width  * 6)+chipelino.posX1, // X2
										(BackgroundImage.Height * 6)+chipelino.posY1, // Y2
										BackgroundImage.Width  * 2, // U2
										BackgroundImage.Height * 2, // V2
										2,
										colour);	
	
	
	DrawPlayer(&chipelino,gsGlobal, colour);
	
	for(int i = 0; i < 30; i++)
	{
		DrawEnemy(&potato[i],gsGlobal, colour);
	}
	
	
	for(int i = 0; i < bulletCount; i++)
	{
		gsKit_prim_sprite_texture(gsGlobal, &PlayerShot,Bullet[i].posX,  // X1
								Bullet[i].posY,  // Y1
								0,  // U1
								0.0f,  // V1
								PlayerShot.Width + Bullet[i].posX, // X2
								PlayerShot.Height + Bullet[i].posY, // Y2
								PlayerShot.Width, // U2
								PlayerShot.Height, // V2
								2,
								colour);	
	}
	
	if(counter>=10){
	gsKit_prim_sprite_texture(gsGlobal, &Win,
								0,  // X1
								0,  // Y1
								0,  // U1
								0.0f,  // V1
								Win.Width  * 2, // X2
								Win.Height * 2, // Y2
								Win.Width  * 2, // U2
								Win.Height * 2, // V2
								2,
								colour);	
		
	}
}


void GameEnd(GSGLOBAL* gsGlobal)
{
	gsKit_vram_clear(gsGlobal);
}

StateManager GameState =
{
	GameStart,
	GameUpdate,
	GameDraw,
	GameEnd
};

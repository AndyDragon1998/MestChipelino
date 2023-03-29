/*****************************************************************************/
/*  Автор         		: Дракончик				        					 */
/*  Приставка     		: Sony PlayStation 2								 */
/*  ОС			  		: OSDSYS				        					 */
/*  Язык	      		: GNU C                                       		 */
/*                                                                           */
/*  Содержимое файла	: Главний пкрсонаж	                       			 */
/*  Атрибут файла		: SOURCE                                      		 */
/*  Имя файла     		: player.c	                               			 */
/*                                                                           */
/*****************************************************************************/

#include "include/enemy.h"
#include <gsKit.h>
#include <dmaKit.h>
#include <gsToolkit.h>

#define ENEMYSPRITE "/Graphics/Sprites/enemy.png"



extern char relativePath[];

GSTEXTURE EnemyTexture;

void InitializeEnemyTexture(GSGLOBAL* gsGlobal)
{
    char tempo[4096];
    strcpy(tempo, relativePath);
    strcat(tempo, ENEMYSPRITE);
    gsKit_texture_png(gsGlobal, &EnemyTexture,tempo);
}

void InitializeEnemy(Enemy* enemy, GSGLOBAL* gsGlobal)
{
	

    enemy->defX = rand() % 1920;
    enemy->defY = rand() % 1536;
    enemy->Health = 1;
    enemy->isAlive = 1;
    
}


void UpdateEnemy(Enemy* enemy,GSGLOBAL* gsGlobal, int Gx, int Gy)
{
	enemy->posX = enemy->defX + Gx;
	enemy->posY = enemy->defY + Gy;
}


void DrawEnemy(Enemy* enemy, GSGLOBAL* gsGlobal, u64 colour)
{
	if (enemy->isAlive){
    gsKit_prim_sprite_texture(gsGlobal, &EnemyTexture,enemy->posX,  // X1
                                        enemy->posY,  // Y1
                                        0,  // U1
                                        0.0f,  // V1
                                        EnemyTexture.Width * 2+enemy->posX, // X2
										EnemyTexture.Height * 2+enemy->posY, // Y2
										EnemyTexture.Width * 2, // U2
										EnemyTexture.Height * 2,// V2
                                        2,
                                        colour);
	}                                        
}

void DeleteEnemy(Enemy* enemy)
{
	enemy->Health=0;
}


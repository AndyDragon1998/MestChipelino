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

#include "include/player.h"
#include <gsKit.h>
#include <dmaKit.h>
#include <gsToolkit.h>

#define PLAYERSPRITE "/Graphics/Sprites/Player.png"



extern char relativePath[];

GSTEXTURE PlayerTexture;

void InitializePlayer(Player* player, GSGLOBAL* gsGlobal)
{
    player->posX = 340;
    player->posY = 307;
    player->posX1 = 0;
    player->posY1 = 0;
    player->posU = 0;
    player->direction;
    player->Health = 3;
    player->moveSpeed;
    player->isAlive;
    player->isShooting;
    player->bulletCount;
    player->reloadTime;


    char tempy[4096];
    strcpy(tempy, relativePath);
    strcat(tempy, PLAYERSPRITE);
    gsKit_texture_png(gsGlobal, &PlayerTexture,tempy);
    }


void UpdatePlayer(Player* player, GSGLOBAL* gsGlobal)
{

}

void UpdateBullets(PlayerBullet* bullet)
{
        switch(bullet->direction)
        {
            case 0:
                bullet->posX -= 7;
            break;

            case 1:
                bullet->posY -= 7;
            break;

            case 2:
                bullet->posX += 7;
            break;

            case 3:
                bullet->posY += 7;
            break;
        }
}

void DrawPlayer(Player* player, GSGLOBAL* gsGlobal, u64 colour)
{
    gsKit_prim_sprite_texture(gsGlobal, &PlayerTexture,300,  // X1
                                        240,  // Y1
                                        player->posU,  // U1
                                        0.0f,  // V1
                                        372, // X2
                                        374, // Y2
                                        player->posU+36, // U2
                                        67, // V2
                                        2,
                                        colour);


}


void DeletePlayer(Player* player)
{

}


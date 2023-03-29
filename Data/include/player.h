#ifndef PLAYER
#define PLAYER
#include <gsKit.h>
#include <dmaKit.h>
#include <gsToolkit.h>


typedef struct
{
    float posX;
    float posY;
    float posX1;
    float posY1;
    float posU;
    int direction;
    int Health;
    float moveSpeed;
    int isAlive;
    int isShooting;
    int bulletCount;
    int reloadTime;
}Player;

typedef struct
{
    float posX;
    float posY;
    float posU;
    int isAlive;
    int direction;
}PlayerBullet;


void InitializePlayer(Player* player, GSGLOBAL* gsGlobal);
void UpdatePlayer(Player* player,GSGLOBAL* gsGlobal);
void DrawPlayer(Player* player, GSGLOBAL* gsGlobal, u64 colour);
void UpdateBullets(PlayerBullet* bullet);
void DeletePlayer(Player* player);

#endif


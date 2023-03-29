#ifndef ENEMY
#define ENEMY
#include <gsKit.h>
#include <dmaKit.h>
#include <gsToolkit.h>

typedef struct 
{
	float posX;
    float posY;
    float defX;
    float defY;
    int Health;
    float moveSpeed;
    int isAlive;
}Enemy;

void InitializeEnemyTexture(GSGLOBAL* gsGlobal);
void InitializeEnemy(Enemy* enemy, GSGLOBAL* gsGlobal);

void UpdateEnemy(Enemy* enemy,GSGLOBAL* gsGlobal, int Gx, int Gy);
void DrawEnemy(Enemy* enemy, GSGLOBAL* gsGlobal, u64 colour);
void DeleteEnemy(Enemy* enemy);

#endif


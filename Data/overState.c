/*****************************************************************************/
/*  Автор         		: Дракончик				                             */
/*  Приставка     		: Sony PlayStation 2					             */
/*  ОС			  		: OSDSYS											 */
/*  Язык	      		: GNU C                                              */
/*                                                                           */
/*  Содержимое файла	: Стадия завершение Игри	                         */
/*  Атрибут файла		: SOURCE                                             */
/*  Имя файла     		: overState.c	                                     */
/*                                                                           */
/*****************************************************************************/

#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"

#include "extern/introState.ext"

#define PLAYERDEATH "/Graphics/Sprites/Death.png"

GSTEXTURE PlayerDeath;

extern StateMachine GameMachineState;

void OverStart(GSGLOBAL* gsGlobal)
{
	char tempD[4096];
	strcpy(tempD, relativePath);
	strcat(tempD, PLAYERDEATH);
	gsKit_texture_png(gsGlobal, &PlayerDeath,tempD);
}

void OverUpdate(GSGLOBAL* gsGlobal)
{

}

void OverDraw(GSGLOBAL* gsGlobal, u64 colour)
{
gsKit_prim_sprite_texture(gsGlobal, &PlayerDeath,0,  // X1
										0,  // Y1
										0,  // U1
										0.0f,  // V1
										PlayerDeath.Width  * 6, // X2
										PlayerDeath.Height * 6, // Y2
										PlayerDeath.Width  * 2, // U2
										PlayerDeath.Height * 2, // V2
										2,
										colour);	
}

void OverEnd(GSGLOBAL* gsGlobal)
{

}

StateManager OverState =
{
	OverStart,
	OverUpdate,
	OverDraw,
	OverEnd
};

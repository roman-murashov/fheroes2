/*
    freeHeroes2 engine
    turn-based game engine (clone of Heroes Of the Might and Magic II)
    Copyright (C) 2006

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    3DO, New World Computing, Heroes of Might and Magic, and the related
    3DO logos are trademarks and or registered trademarks of 3DO Company.
    All other trademarks belong to their respective owners.

    Web: http://sourceforge.net/projects/fheroes2

    Description:
*/

#include <stdlib.h>
#include "SDL.h"

#include "gamedefs.h"
#include "tools.h"
#include "cursor.h"
#include "debug.h"
#include "config.h"
#include "actionevent.h"
#include "monster.h"
#include "kingdom.h"
#include "castle.h"
#include "castleinfo.h"
#include "castleaction.h"
#include "recrutmonster.h"

ACTION ActionOverCastle(void){

    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();

    if(castle->castle){ message = "Castle"; }else{ message = "Tent"; }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionOverCaptain(void){

    const char *message = GetStringCapitan();

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionOverStatue(void){

    const char *message = GetStringStatue();

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionOverMarketplace(void){

    const char *message = GetStringMarketplace();

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionOverMoat(void){

    const char *message = GetStringMoat();

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionOverDock(void){

    const char *message = GetStringShipyard();

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionOverWell(void){

    const char *message = GetStringWell();

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionOverTavern(void){

    const char *message = GetStringTavern();

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionOverThievesGuild(void){

    const char *message = GetStringThievesGuild();

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionOverMageGuild(void){

    const char *message = GetStringMageGuild();

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionOverSpec(void){

    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();

    message = GetStringSpec(castle->race);

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}


ACTION ActionOverWel2(void){

    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();

    message = GetStringWel2(castle->race);

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionOverDwelling1(void){

    const S_CASTLE *castle = GetCurrentCastle();
    const S_MONSTER *monster = NULL;

    switch(castle->race){
	case BARBARIAN:
	    monster = GetStatMonster(GOBLIN);
	    break;
	case KNIGHT:
	    monster = GetStatMonster(PEASANT);
	    break;
	case WARLOCK:
	    monster = GetStatMonster(CENTAUR);
	    break;
	case SORCERESS:
	    monster = GetStatMonster(SPRITE);
	    break;
	case NECROMANCER:
	    monster = GetStatMonster(SKELETON);
	    break;
	case WIZARD:
	    monster = GetStatMonster(HALFLING);
	    break;
	default:
	    return NONE;
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(monster->descriptions) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(monster->descriptions);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, monster->descriptions, FONT_BIG);

    return NONE;
}

ACTION ActionOverDwelling2(void){

    const S_CASTLE *castle = GetCurrentCastle();
    const S_MONSTER *monster = NULL;

    switch(castle->race){
	case BARBARIAN:
	    if(castle->dwelling & DWELLING_UPGRADE2)
		monster = GetStatMonster(CHIEF_ORC);
	    else
		monster = GetStatMonster(ORC);
	    break;
	case KNIGHT:
	    if(castle->dwelling & DWELLING_UPGRADE2)
		monster = GetStatMonster(ARCHER);
	    else
		monster = GetStatMonster(RANGER);
	    break;
	case WARLOCK:
	    monster = GetStatMonster(GARGOYLE);
	    break;
	case SORCERESS:
	    if(castle->dwelling & DWELLING_UPGRADE2)
		monster = GetStatMonster(DWARF);
	    else
		monster = GetStatMonster(BATTLE_DWARF);
	    break;
	case NECROMANCER:
	    if(castle->dwelling & DWELLING_UPGRADE2)
		monster = GetStatMonster(ZOMBIE);
	    else
		monster = GetStatMonster(MUTANT_ZOMBIE);
	    break;
	case WIZARD:
	    monster = GetStatMonster(BOAR);
	    break;
	default:
	    return NONE;
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(monster->descriptions) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(monster->descriptions);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, monster->descriptions, FONT_BIG);

    return NONE;
}

ACTION ActionOverDwelling3(void){

    const S_CASTLE *castle = GetCurrentCastle();
    const S_MONSTER *monster = NULL;

    switch(castle->race){
	case BARBARIAN:
	    monster = GetStatMonster(WOLF);
	    break;
	case KNIGHT:
	    if(castle->dwelling & DWELLING_UPGRADE3)
		monster = GetStatMonster(PIKEMAN);
	    else
		monster = GetStatMonster(VETERAN_PIKEMAN);
	    break;
	case WARLOCK:
	    monster = GetStatMonster(GRIFFIN);
	    break;
	case SORCERESS:
	    if(castle->dwelling & DWELLING_UPGRADE3)
		monster = GetStatMonster(ELF);
	    else
		monster = GetStatMonster(GRAND_ELF);
	    break;
	case NECROMANCER:
	    if(castle->dwelling & DWELLING_UPGRADE3)
		monster = GetStatMonster(MUMMY);
	    else
		monster = GetStatMonster(ROYAL_MUMMY);
	    break;
	case WIZARD:
	    if(castle->dwelling & DWELLING_UPGRADE3)
		monster = GetStatMonster(IRON_GOLEM);
	    else
		monster = GetStatMonster(STEEL_GOLEM);
	    break;
	default:
	    return NONE;
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(monster->descriptions) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(monster->descriptions);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, monster->descriptions, FONT_BIG);

    return NONE;
}

ACTION ActionOverDwelling4(void){

    const S_CASTLE *castle = GetCurrentCastle();
    const S_MONSTER *monster = NULL;

    switch(castle->race){
	case BARBARIAN:
	    if(castle->dwelling & DWELLING_UPGRADE4)
		monster = GetStatMonster(OGRE);
	    else
		monster = GetStatMonster(LORD_OGRE);
	    break;
	case KNIGHT:
	    if(castle->dwelling & DWELLING_UPGRADE4)
		monster = GetStatMonster(SWORDSMAN);
	    else
		monster = GetStatMonster(MASTER_SWORDSMAN);
	    break;
	case WARLOCK:
	    if(castle->dwelling & DWELLING_UPGRADE4)
		monster = GetStatMonster(MINOTAUR);
	    else
		monster = GetStatMonster(KNIGHT_MINOTAUR);
	    break;
	case SORCERESS:
	    if(castle->dwelling & DWELLING_UPGRADE4)
		monster = GetStatMonster(DRUID);
	    else
		monster = GetStatMonster(GREATER_DRUID);
	    break;
	case NECROMANCER:
	    if(castle->dwelling & DWELLING_UPGRADE4)
		monster = GetStatMonster(VAMPIRE);
	    else
		monster = GetStatMonster(LORD_VAMPIRE);
	    break;
	case WIZARD:
	    monster = GetStatMonster(ROC);
	    break;
	default:
	    return NONE;
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(monster->descriptions) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(monster->descriptions);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, monster->descriptions, FONT_BIG);

    return NONE;
}

ACTION ActionOverDwelling5(void){

    const S_CASTLE *castle = GetCurrentCastle();
    const S_MONSTER *monster = NULL;

    switch(castle->race){
	case BARBARIAN:
	    if(castle->dwelling & DWELLING_UPGRADE5)
		monster = GetStatMonster(TROLL);
	    else
		monster = GetStatMonster(WAR_TROLL);
	    break;
	case KNIGHT:
	    if(castle->dwelling & DWELLING_UPGRADE5)
		monster = GetStatMonster(CAVALIRY);
	    else
		monster = GetStatMonster(CHAMPION);
	    break;
	case WARLOCK:
	    monster = GetStatMonster(HIDRA);
	    break;
	case SORCERESS:
	    monster = GetStatMonster(UNICORN);
	    break;
	case NECROMANCER:
	    if(castle->dwelling & DWELLING_UPGRADE5)
		monster = GetStatMonster(LICH);
	    else
		monster = GetStatMonster(POWER_LICH);
	    break;
	case WIZARD:
	    if(castle->dwelling & DWELLING_UPGRADE5)
		monster = GetStatMonster(MAGE);
	    else
		monster = GetStatMonster(ARCHMAGE);
	    break;
	default:
	    return NONE;
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(monster->descriptions) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(monster->descriptions);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, monster->descriptions, FONT_BIG);

    return NONE;
}

ACTION ActionOverDwelling6(void){

    const S_CASTLE *castle = GetCurrentCastle();
    const S_MONSTER *monster = NULL;

    switch(castle->race){
	case BARBARIAN:
	    monster = GetStatMonster(CYCLOPS);
	    break;
	case KNIGHT:
	    if(castle->dwelling & DWELLING_UPGRADE6)
		monster = GetStatMonster(PALADIN);
	    else
		monster = GetStatMonster(CRUSADER);
	    break;
	case WARLOCK:
	    if(castle->dwelling & DWELLING_UPGRADE7)
		monster = GetStatMonster(BLACK_DRAGON);
	    else if(castle->dwelling & DWELLING_UPGRADE6)
		monster = GetStatMonster(RED_DRAGON);
	    else
		monster = GetStatMonster(GREEN_DRAGON);
	    break;
	case SORCERESS:
	    monster = GetStatMonster(PHOENIX);
	    break;
	case NECROMANCER:
	    monster = GetStatMonster(BONE_DRAGON);
	    break;
	case WIZARD:
	    if(castle->dwelling & DWELLING_UPGRADE6)
		monster = GetStatMonster(GIANT);
	    else
		monster = GetStatMonster(TITAN);
	    break;
	default:
	    return NONE;
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(monster->descriptions) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(monster->descriptions);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, monster->descriptions, FONT_BIG);

    return NONE;
}

ACTION ActionOverExit(void){
    
    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();
                
    if(castle->castle){ message = "Exit Castle"; }else{ message = "Exit Town"; }
    
    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);
                
    return NONE;
}               
                    
ACTION ActionOverHeroes(void){

    const char *message = "View Hero";

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;

    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;

    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionClickCastle(void){

    const S_CASTLE *castle = GetCurrentCastle();
    
    if(castle->castle)
	ShowCastleInfo();
    else if(castle->allowCastle)
	fprintf(stderr, "Allow build Castle\n");
    else
	fprintf(stderr, "Not allow build Castle\n");

    return NONE;
}

ACTION ActionClickCaptain(void){
    fprintf(stderr, "ClickCaptain\n");
    return NONE;
}

ACTION ActionClickMageGuild(void){
    fprintf(stderr, "ClickMageGuild\n");
    return NONE;
}

ACTION ActionClickStatue(void){
    fprintf(stderr, "ClickStatue\n");
    return NONE;
}

ACTION ActionClickWell(void){
    fprintf(stderr, "ClickWell\n");
    return NONE;
}

ACTION ActionClickThievesGuild(void){
    fprintf(stderr, "ClickThievesGuild\n");
    return NONE;
}

ACTION ActionClickTavern(void){
    fprintf(stderr, "ClickTavern\n");
    return NONE;
}

ACTION ActionClickDock(void){
    fprintf(stderr, "ClickDock\n");
    return NONE;
}

ACTION ActionClickMarketplace(void){
    fprintf(stderr, "ClickMarketplace\n");
    return NONE;
}

ACTION ActionClickMoat(void){
    fprintf(stderr, "ClickMoat\n");
    return NONE;
}

ACTION ActionClickSpec(void){
    fprintf(stderr, "ClickSpec\n");
    return NONE;
}

ACTION ActionClickWel2(void){
    fprintf(stderr, "ClickWel2\n");
    return NONE;
}

ACTION ActionClickDwelling1(void){

    const Uint8 levelMonster = 1;

    const S_CASTLE *castle = GetCurrentCastle();
    if(! castle) return NONE;

    if(	BuyMonsterFromCastle(castle, levelMonster, 
	DialogRecrutMonster(GetMonsterFromCastle(castle, levelMonster), levelMonster, castle->monster[levelMonster - 1])) ){
	    RedrawCastleMonster();
	    RedrawCastleInfoResource();
    }else
	ErrorDialogRecrutMonster(castle);

    return NONE;
}

ACTION ActionClickDwelling2(void){

    const Uint8 levelMonster = 2;

    const S_CASTLE *castle = GetCurrentCastle();
    if(! castle) return NONE;

    if(	BuyMonsterFromCastle(castle, levelMonster, 
	DialogRecrutMonster(GetMonsterFromCastle(castle, levelMonster), levelMonster, castle->monster[levelMonster - 1])) ){
	    RedrawCastleMonster();
	    RedrawCastleInfoResource();
    }else
	ErrorDialogRecrutMonster(castle);

    return NONE;
}

ACTION ActionClickDwelling3(void){

    const Uint8 levelMonster = 3;

    const S_CASTLE *castle = GetCurrentCastle();
    if(! castle) return NONE;

    if(	BuyMonsterFromCastle(castle, levelMonster, 
	DialogRecrutMonster(GetMonsterFromCastle(castle, levelMonster), levelMonster, castle->monster[levelMonster - 1])) ){
	    RedrawCastleMonster();
	    RedrawCastleInfoResource();
    }else
	ErrorDialogRecrutMonster(castle);

    return NONE;
}

ACTION ActionClickDwelling4(void){

    const Uint8 levelMonster = 4;

    const S_CASTLE *castle = GetCurrentCastle();
    if(! castle) return NONE;

    if(	BuyMonsterFromCastle(castle, levelMonster, 
	DialogRecrutMonster(GetMonsterFromCastle(castle, levelMonster), levelMonster, castle->monster[levelMonster - 1])) ){
	    RedrawCastleMonster();
	    RedrawCastleInfoResource();
    }else
	ErrorDialogRecrutMonster(castle);

    return NONE;
}

ACTION ActionClickDwelling5(void){

    const Uint8 levelMonster = 5;

    const S_CASTLE *castle = GetCurrentCastle();
    if(! castle) return NONE;

    if(	BuyMonsterFromCastle(castle, levelMonster, 
	DialogRecrutMonster(GetMonsterFromCastle(castle, levelMonster), levelMonster, castle->monster[levelMonster - 1])) ){
	    RedrawCastleMonster();
	    RedrawCastleInfoResource();
    }else
	ErrorDialogRecrutMonster(castle);

    return NONE;
}

ACTION ActionClickDwelling6(void){

    const Uint8 levelMonster = 6;

    const S_CASTLE *castle = GetCurrentCastle();
    if(! castle) return NONE;

    if(	BuyMonsterFromCastle(castle, levelMonster, 
	DialogRecrutMonster(GetMonsterFromCastle(castle, levelMonster), levelMonster, castle->monster[levelMonster - 1])) ){
	    RedrawCastleMonster();
	    RedrawCastleInfoResource();
    }else
	ErrorDialogRecrutMonster(castle);

    return NONE;
}

ACTION ActionCastleOverExit(void){
    
    const char *message = "Exit Castle Options";

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;

    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);
                
    return NONE;
}               

ACTION ActionCastleClickExit(void){
            
    return CANCEL;      
}

ACTION ActionCastleOverTavern(void){
    
    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildTavern(castle)){

	case BUILD_OK:
	    message = "Build Tavern";
	    break;
	
	case CANNOT_BUILD:
	    message = "Cannot build Tavern";
	    break;
	
	case ALREADY_BUILD:
	    message = "Tavern is already build";
	    break;
	
	case END_TUR:
	    message = "Cannot build. Already build here this turn.";
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverStatue(void){
    
    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildStatue(castle)){

	case BUILD_OK:
	    message = "Build Statue";
	    break;
	
	case CANNOT_BUILD:
	    message = "Cannot build Statue";
	    break;
	
	case ALREADY_BUILD:
	    message = "Statue is already build";
	    break;
	
	case END_TUR:
	    message = "Cannot build. Already build here this turn.";
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverWell(void){
    
    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildWell(castle)){

	case BUILD_OK:
	    message = "Build Well";
	    break;
	
	case CANNOT_BUILD:
	    message = "Cannot build Well";
	    break;
	
	case ALREADY_BUILD:
	    message = "Well is already build";
	    break;
	
	case END_TUR:
	    message = "Cannot build. Already build here this turn.";
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverMoat(void){
    
    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildMoat(castle)){

	case BUILD_OK:
	    message = "Build Moat";
	    break;
	
	case CANNOT_BUILD:
	    message = "Cannot build Moat";
	    break;
	
	case ALREADY_BUILD:
	    message = "Moat is already build";
	    break;
	
	case END_TUR:
	    message = "Cannot build. Already build here this turn.";
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverMarketplace(void){
    
    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildMarketplace(castle)){

	case BUILD_OK:
	    message = "Build Marketplace";
	    break;
	
	case CANNOT_BUILD:
	    message = "Cannot build Marketplace";
	    break;
	
	case ALREADY_BUILD:
	    message = "Marketplace is already build";
	    break;
	
	case END_TUR:
	    message = "Cannot build. Already build here this turn.";
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverThievesGuild(void){
    
    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildThievesGuild(castle)){

	case BUILD_OK:
	    message = "Build Thieves Guild";
	    break;
	
	case CANNOT_BUILD:
	    message = "Cannot build Thieves Guild";
	    break;
	
	case ALREADY_BUILD:
	    message = "Thieves Guild is already  build";
	    break;
	
	case END_TUR:
	    message = "Cannot build. Already build here this turn.";
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverLeftTurret(void){
    
    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildLeftTurret(castle)){

	case BUILD_OK:
	    message = "Build Left Turret";
	    break;
	
	case CANNOT_BUILD:
	    message = "Cannot build Left Turret";
	    break;
	
	case ALREADY_BUILD:
	    message = "Left Turret is already build";
	    break;
	
	case END_TUR:
	    message = "Cannot build. Already build here this turn.";
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverRightTurret(void){
    
    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildRightTurret(castle)){

	case BUILD_OK:
	    message = "Build Right Turret";
	    break;
	
	case CANNOT_BUILD:
	    message = "Cannot build Right Turret";
	    break;
	
	case ALREADY_BUILD:
	    message = "Right Turret is already build";
	    break;
	
	case END_TUR:
	    message = "Cannot build. Already build here this turn.";
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverMageGuild(void){
    
    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildMageGuild(castle)){

	case BUILD_OK:
	    message = "Build Mage Guild";
	    break;
	
	case CANNOT_BUILD:
	    message = "Cannot build Mage Guild";
	    break;
	
	case ALREADY_BUILD:
	    message = "Mage Guild is already build";
	    break;
	
	case END_TUR:
	    message = "Cannot build. Already build here this turn.";
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverShipyard(void){
    
    const char *message = NULL;
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildShipyard(castle)){

	case BUILD_OK:
	    message = "Build Shipyard";
	    break;
	
	case CANNOT_BUILD:
	    message = "Cannot build Shipyard";
	    break;
	
	case ALREADY_BUILD:
	    message = "Shipyard is already build";
	    break;
	
	case END_TUR:
	    message = "Cannot build. Already build here this turn.";
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverWel2(void){
    
    char message[64];
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildWel2(castle)){

	case BUILD_OK:
	    sprintf(message, "Build %s", GetStringWel2(castle->race));
	    break;
	
	case CANNOT_BUILD:
	    sprintf(message, "Cannot build %s", GetStringWel2(castle->race));
	    break;
	
	case ALREADY_BUILD:
	    sprintf(message, "%s is already build", GetStringWel2(castle->race));
	    break;
	
	case END_TUR:
	    sprintf(message, "Cannot build. Already build here this turn.");
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverSpec(void){
    
    char message[64];
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildSpec(castle)){

	case BUILD_OK:
	    sprintf(message, "Build %s", GetStringSpec(castle->race));
	    break;
	
	case CANNOT_BUILD:
	    sprintf(message, "Cannot build %s", GetStringSpec(castle->race));
	    break;
	
	case ALREADY_BUILD:
	    sprintf(message, "%s is already build", GetStringSpec(castle->race));
	    break;
	
	case END_TUR:
	    sprintf(message, "Cannot build. Already build here this turn.");
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverDwelling1(void){
    
    char message[64];
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildDwelling1(castle)){

	case BUILD_OK:
	    sprintf(message, "Build %s", GetStringDwelling(castle->race, DWELLING_MONSTER1));
	    break;
	
	case CANNOT_BUILD:
	    sprintf(message, "Cannot build %s", GetStringDwelling(castle->race, DWELLING_MONSTER1));
	    break;
	
	case ALREADY_BUILD:
	    sprintf(message, "%s is already build", GetStringDwelling(castle->race, DWELLING_MONSTER1));
	    break;
	
	case END_TUR:
	    sprintf(message, "Cannot build. Already build here this turn.");
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverDwelling2(void){
    
    char message[64];
    const S_CASTLE *castle = GetCurrentCastle();
    
    
    switch(AllowBuildDwelling2(castle)){

	case BUILD_OK:
	    castle->dwelling & DWELLING_MONSTER2 ? sprintf(message, "Build %s", GetStringDwelling(castle->race, DWELLING_UPGRADE2)) :
		sprintf(message, "Build %s", GetStringDwelling(castle->race, DWELLING_MONSTER2));
	    break;

	case CANNOT_BUILD:
	    castle->dwelling & DWELLING_MONSTER2 ? sprintf(message, "Cannot build %s", GetStringDwelling(castle->race, DWELLING_UPGRADE2)) :
		sprintf(message, "Cannot build %s", GetStringDwelling(castle->race, DWELLING_MONSTER2));
	    break;

	case ALREADY_BUILD:
	    if(castle->dwelling & DWELLING_UPGRADE2)
		sprintf(message, "%s is already build", GetStringDwelling(castle->race, DWELLING_UPGRADE2));
	    else
		sprintf(message, "%s is already build", GetStringDwelling(castle->race, DWELLING_MONSTER2));
	    break;

	case END_TUR:
	    sprintf(message, "Cannot build. Already build here this turn.");
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverDwelling3(void){
    
    char message[64];
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildDwelling3(castle)){

	case BUILD_OK:
	    castle->dwelling & DWELLING_MONSTER3 ? sprintf(message, "Build %s", GetStringDwelling(castle->race, DWELLING_UPGRADE3)) :
		sprintf(message, "Build %s", GetStringDwelling(castle->race, DWELLING_MONSTER3));
	    break;
	
	case CANNOT_BUILD:
	    castle->dwelling & DWELLING_MONSTER3 ? sprintf(message, "Cannot build %s", GetStringDwelling(castle->race, DWELLING_UPGRADE3)) :
		sprintf(message, "Cannot build %s", GetStringDwelling(castle->race, DWELLING_MONSTER3));
	    break;
	
	case ALREADY_BUILD:
	    if(castle->dwelling & DWELLING_UPGRADE3)
		sprintf(message, "%s is already build", GetStringDwelling(castle->race, DWELLING_UPGRADE3));
	    else
		sprintf(message, "%s is already build", GetStringDwelling(castle->race, DWELLING_MONSTER3));
	    break;
	
	case END_TUR:
	    sprintf(message, "Cannot build. Already build here this turn.");
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverDwelling4(void){
    
    char message[64];
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildDwelling4(castle)){

	case BUILD_OK:
	    castle->dwelling & DWELLING_MONSTER4 ? sprintf(message, "Build %s", GetStringDwelling(castle->race, DWELLING_UPGRADE4)) :
		sprintf(message, "Build %s", GetStringDwelling(castle->race, DWELLING_MONSTER4));
	    break;
	
	case CANNOT_BUILD:
	    castle->dwelling & DWELLING_MONSTER4 ? sprintf(message, "Cannot build %s", GetStringDwelling(castle->race, DWELLING_UPGRADE4)) :
		sprintf(message, "Cannot build %s", GetStringDwelling(castle->race, DWELLING_MONSTER4));
	    break;
	
	case ALREADY_BUILD:
	    if(castle->dwelling & DWELLING_UPGRADE4)
		sprintf(message, "%s is already build", GetStringDwelling(castle->race, DWELLING_UPGRADE4));
	    else
		sprintf(message, "%s is already build", GetStringDwelling(castle->race, DWELLING_MONSTER4));
	    break;
	
	case END_TUR:
	    sprintf(message, "Cannot build. Already build here this turn.");
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverDwelling5(void){
    
    char message[64];
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildDwelling5(castle)){

	case BUILD_OK:
	    castle->dwelling & DWELLING_MONSTER5 ? sprintf(message, "Build %s", GetStringDwelling(castle->race, DWELLING_UPGRADE5)) :
		sprintf(message, "Build %s", GetStringDwelling(castle->race, DWELLING_MONSTER5));
	    break;
	
	case CANNOT_BUILD:
	    castle->dwelling & DWELLING_MONSTER5 ? sprintf(message, "Cannot build %s", GetStringDwelling(castle->race, DWELLING_UPGRADE5)) :
		sprintf(message, "Cannot build %s", GetStringDwelling(castle->race, DWELLING_MONSTER5));
	    break;
	
	case ALREADY_BUILD:
	    if(castle->dwelling & DWELLING_UPGRADE5)
		sprintf(message, "%s is already build", GetStringDwelling(castle->race, DWELLING_UPGRADE5));
	    else
		sprintf(message, "%s is already build", GetStringDwelling(castle->race, DWELLING_MONSTER5));
	    break;
	
	case END_TUR:
	    sprintf(message, "Cannot build. Already build here this turn.");
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}

ACTION ActionCastleOverDwelling6(void){
    
    char message[64];
    const S_CASTLE *castle = GetCurrentCastle();
    
    switch(AllowBuildDwelling6(castle)){

	case BUILD_OK:
	    if(castle->race == WARLOCK && castle->dwelling & DWELLING_UPGRADE6)
		sprintf(message, "Build %s", GetStringDwelling(castle->race, DWELLING_UPGRADE7));
	    else if(castle->dwelling & DWELLING_MONSTER6)
		sprintf(message, "Build %s", GetStringDwelling(castle->race, DWELLING_UPGRADE6));
	    else
		sprintf(message, "Build %s", GetStringDwelling(castle->race, DWELLING_MONSTER6));
	    break;
	
	case CANNOT_BUILD:
	    if(castle->race == WARLOCK && castle->dwelling & DWELLING_UPGRADE6)
		sprintf(message, "Cannot build %s", GetStringDwelling(castle->race, DWELLING_UPGRADE7));
	    else if(castle->dwelling & DWELLING_MONSTER6)
		sprintf(message, "Cannot build %s", GetStringDwelling(castle->race, DWELLING_UPGRADE6));
	    else
		sprintf(message, "Cannot build %s", GetStringDwelling(castle->race, DWELLING_MONSTER6));
	    break;
	
	case ALREADY_BUILD:
	    if(castle->dwelling & DWELLING_UPGRADE7)
		sprintf(message, "%s is already build", GetStringDwelling(castle->race, DWELLING_UPGRADE7));
	    else if(castle->dwelling & DWELLING_UPGRADE6)
		sprintf(message, "%s is already build", GetStringDwelling(castle->race, DWELLING_UPGRADE6));
	    else if(castle->dwelling & DWELLING_MONSTER6)
		sprintf(message, "%s is already build", GetStringDwelling(castle->race, DWELLING_MONSTER6));
	    break;
	
	case END_TUR:
	    sprintf(message, "Cannot build. Already build here this turn.");
	    break;
    }

    SDL_Surface *video = SDL_GetVideoSurface();
    SDL_Rect cur;
    
    cur.x = video->w / 2;
    cur.y = video->h / 2 + 240 - BORDERWIDTH;
    
    cur.x = cur.x - strlen(message) * FONT_WIDTHBIG / 2;
    cur.y = cur.y - 3;
    cur.w = FONT_WIDTHBIG * strlen(message);
    cur.h = FONT_HEIGHTBIG;
    PrintText(video, &cur, message, FONT_BIG);

    return NONE;
}


ACTION ActionCastleClickTavern(void){

    return NONE;
}

ACTION ActionCastleClickStatue(void){

    return NONE;
}

ACTION ActionCastleClickWell(void){

    return NONE;
}

ACTION ActionCastleClickMoat(void){

    return NONE;
}

ACTION ActionCastleClickMarketplace(void){

    return NONE;
}

ACTION ActionCastleClickThievesGuild(void){

    return NONE;
}

ACTION ActionCastleClickLeftTurret(void){

    return NONE;
}

ACTION ActionCastleClickRightTurret(void){

    return NONE;
}

ACTION ActionCastleClickMageGuild(void){

    return NONE;
}

ACTION ActionCastleClickShipyard(void){

    return NONE;
}

ACTION ActionCastleClickWel2(void){

    return NONE;
}

ACTION ActionCastleClickSpec(void){

    return NONE;
}

ACTION ActionCastleClickDwelling1(void){

    return NONE;
}

ACTION ActionCastleClickDwelling2(void){

    return NONE;
}

ACTION ActionCastleClickDwelling3(void){

    return NONE;
}

ACTION ActionCastleClickDwelling4(void){

    return NONE;
}

ACTION ActionCastleClickDwelling5(void){

    return NONE;
}

ACTION ActionCastleClickDwelling6(void){

    return NONE;
}

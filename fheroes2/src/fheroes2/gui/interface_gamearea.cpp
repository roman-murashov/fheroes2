/***************************************************************************
 *   Copyright (C) 2006 by Andrey Afletdinov                               *
 *   afletdinov@mail.dc.baikal.ru                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "agg.h"
#include "settings.h"
#include "world.h"
#include "maps.h"
#include "game.h"
#include "game_focus.h"
#include "game_interface.h"
#include "route.h"
#include "interface_gamearea.h"

namespace Game
{
    extern Cursor::themes_t GetCursor(const Maps::Tiles &);
    extern void MouseCursorAreaClickLeft(u16);
    extern void MouseCursorAreaPressRight(u16);
};

void	RedrawBoat(const Maps::Tiles &, s16, s16);
void	RedrawHeroes(const Maps::Tiles &);
void	RedrawMonster(const Maps::Tiles &, s16, s16);
void	RedrawClopOrClofSpriteFog(const u16 dst_index, const Point & dst);

Interface::GameArea & Interface::GameArea::Get(void)
{
    static Interface::GameArea ga;
    return ga;
}

Interface::GameArea::GameArea() : oldIndexPos(0), updateCursor(false)
{
}

const Rect & Interface::GameArea::GetArea(void) const
{ return rectArea; }

const Rect & Interface::GameArea::GetRectMaps(void) const
{ return rectMaps; }

/* fixed src rect image */
void Interface::GameArea::SrcRectFixed(Rect & src, Point & dst, const u16 rw, const u16 rh)
{
    src = Rect(0, 0, rw, rh);
    const Rect & rectArea = Interface::GameArea::Get().GetArea();

    if(dst.x < rectArea.x)
    {
        src.x = rectArea.x - dst.x;
        dst.x = rectArea.x;
    }

    if(dst.y < rectArea.y)
    {
        src.y = rectArea.y - dst.y;
        dst.y = rectArea.y;
    }

    if(dst.x + rw > rectArea.x + rectArea.w)
    {
	src.w = rectArea.x + rectArea.w - dst.x;
    }

    if(dst.y + rh > rectArea.y + rectArea.h)
    {
	src.h = rectArea.y + rectArea.h - dst.y;
    }
}

void Interface::GameArea::Build(void)
{

    if(Settings::Get().HideInterface())
    {
	rectArea.x = 0;
	rectArea.y = 0;
	rectArea.w = Display::Get().w();
	rectArea.h = Display::Get().h();
    }
    else
    {
	rectArea.x = BORDERWIDTH;
	rectArea.y = BORDERWIDTH;
	rectArea.w = Display::Get().w() - RADARWIDTH - 3 * BORDERWIDTH;
	rectArea.h = Display::Get().h() - 2 * BORDERWIDTH;
    }

    rectMaps.x = 0;
    rectMaps.y = 0;
    rectMaps.w = rectArea.w / TILEWIDTH;
    rectMaps.h = rectArea.h / TILEWIDTH;
}

void Interface::GameArea::Redraw(bool drawFog) const
{
    Display & display = Display::Get();

    // tile
    for(u8 oy = 0; oy < rectMaps.h; ++oy)
	for(u8 ox = 0; ox < rectMaps.w; ++ox)
	    world.GetTiles(rectMaps.x + ox, rectMaps.y + oy).RedrawTile();

    // bottom
    for(u8 oy = 0; oy < rectMaps.h; ++oy)
	for(u8 ox = 0; ox < rectMaps.w; ++ox)
	    world.GetTiles(rectMaps.x + ox, rectMaps.y + oy).RedrawBottom();

    // ext object
    for(u8 oy = 0; oy < rectMaps.h; ++oy)
	for(u8 ox = 0; ox < rectMaps.w; ++ox)
    {
	const Maps::Tiles & tile = world.GetTiles(rectMaps.x + ox, rectMaps.y + oy);

	switch(tile.GetObject())
	{
    	    // boat
    	    case MP2::OBJ_BOAT:		RedrawBoat(tile, rectArea.x + TILEWIDTH * ox, rectArea.y + TILEWIDTH * oy); break;
    	    // monster
    	    case MP2::OBJ_MONSTER:	RedrawMonster(tile, rectArea.x + TILEWIDTH * ox, rectArea.y + TILEWIDTH * oy); break;
    	    default: break;
	}
    }

    // top
    for(u8 oy = 0; oy < rectMaps.h; ++oy)
	for(u8 ox = 0; ox < rectMaps.w; ++ox)
	    world.GetTiles(rectMaps.x + ox, rectMaps.y + oy).RedrawTop();

    // ext object
    for(u8 oy = 0; oy < rectMaps.h; ++oy)
	for(u8 ox = 0; ox < rectMaps.w; ++ox)
    {
	const Maps::Tiles & tile = world.GetTiles(rectMaps.x + ox, rectMaps.y + oy);

	switch(tile.GetObject())
	{
    	    // heroes
    	    case MP2::OBJ_HEROES:	RedrawHeroes(tile); break;
    	    default: break;
	}
    }

    // route
    const Game::Focus & focus = Game::Focus::Get();

    if(Game::Focus::HEROES == focus.Type() &&
	focus.GetHeroes().GetPath().isShow())
    {
	const Heroes & hero = focus.GetHeroes();
	u16 from = Maps::GetIndexFromAbsPoint(hero.GetCenter());
	s16 green = hero.GetPath().GetAllowStep();

	const bool skipfirst = hero.isEnableMove() && 45 > hero.GetSpriteIndex() && 2 < (hero.GetSpriteIndex() % 9);

	Route::Path::const_iterator it1 = hero.GetPath().begin();
	Route::Path::const_iterator it2 = hero.GetPath().end();
	Route::Path::const_iterator it3 = it1;

	for(; it1 != it2; ++it1)
	{
	    from = Maps::GetDirectionIndex(from, (*it1).Direction());
    	    Point pointPos(from % world.w(), from / world.h());

	    ++it3;
	    --green;

            if(!(rectMaps & pointPos)) continue;
	    if(it1 == hero.GetPath().begin() && skipfirst) continue;

	    const u16 index = (it3 == it2 ? 0 : Route::Path::GetIndexSprite((*it1).Direction(), (*it3).Direction(), Maps::Ground::GetBasePenalty(from, hero.GetLevelSkill(Skill::Secondary::PATHFINDING))));

	    const Sprite & sprite = AGG::GetICN(0 > green ? ICN::ROUTERED : ICN::ROUTE, index);
    	    pointPos.x = rectArea.x + TILEWIDTH * (pointPos.x - rectMaps.x) + sprite.x() - 14;
    	    pointPos.y = rectArea.y + TILEWIDTH * (pointPos.y - rectMaps.y) + sprite.y();
	    display.Blit(sprite, pointPos);
	}
    }

    // redraw grid
    if(Settings::Get().Debug())
    {

	for(u8 oy = 0; oy < rectMaps.h; ++oy)
	    for(u8 ox = 0; ox < rectMaps.w; ++ox)
	{
    	    display.Lock();
    	    display.SetPixel(rectArea.x + TILEWIDTH * ox, rectArea.y + TILEWIDTH * oy, display.GetColor(0x40));
    	    display.Unlock();
	}
    }

    // redraw fog
    if(drawFog)
	for(u8 oy = 0; oy < rectMaps.h; ++oy)
	    for(u8 ox = 0; ox < rectMaps.w; ++ox)
    {
	const Maps::Tiles & tile = world.GetTiles(rectMaps.x + ox, rectMaps.y + oy);
    	const Point dst(rectArea.x + TILEWIDTH * ox, rectArea.y + TILEWIDTH * oy);
	if(tile.isFog(Settings::Get().MyColor())) RedrawClopOrClofSpriteFog(tile.GetIndex(), dst);
    }
}

/* scroll area */
void Interface::GameArea::Scroll(void)
{
    if(scrollDirection & SCROLL_LEFT && 0 < rectMaps.x) --rectMaps.x;
    else
    if(scrollDirection & SCROLL_RIGHT && world.w() - rectMaps.w > rectMaps.x) ++rectMaps.x;

    if(scrollDirection & SCROLL_TOP && 0 < rectMaps.y) --rectMaps.y;
    else
    if(scrollDirection & SCROLL_BOTTOM && world.h() - rectMaps.h > rectMaps.y) ++rectMaps.y;

    scrollDirection = 0;
}

/* scroll area to center point maps */
void Interface::GameArea::Center(const Point &pt)
{
    Center(pt.x, pt.y);
}

void Interface::GameArea::Center(s16 px, s16 py)
{
    Point pos;

    // center
    pos.x = (0 > px - rectMaps.w / 2 ? 0 : px - rectMaps.w / 2);
    pos.y = (0 > py - rectMaps.h / 2 ? 0 : py - rectMaps.h / 2);

    // our of range
    if(pos.y > world.h() - rectMaps.h) pos.y = world.h() - rectMaps.h;
    if(pos.x > world.w() - rectMaps.w) pos.x = world.w() - rectMaps.w;

    if(pos.x == rectMaps.x && pos.y == rectMaps.y) return;

    // possible fast scroll
    if(pos.y == rectMaps.y && 1 == (pos.x - rectMaps.x)) scrollDirection |= SCROLL_RIGHT;
    else
    if(pos.y == rectMaps.y && -1 == (pos.x - rectMaps.x)) scrollDirection |= SCROLL_LEFT;
    else
    if(pos.x == rectMaps.x && 1 == (pos.y - rectMaps.y)) scrollDirection |= SCROLL_BOTTOM;
    else
    if(pos.x == rectMaps.x && -1 == (pos.y - rectMaps.y)) scrollDirection |= SCROLL_TOP;
    else
    // diagonal
    if(-1 == (pos.y - rectMaps.y) && 1 == (pos.x - rectMaps.x))
    {
	scrollDirection |= SCROLL_TOP | SCROLL_RIGHT;
    }
    else
    if(-1 == (pos.y - rectMaps.y) && -1 == (pos.x - rectMaps.x))
    {
	scrollDirection |= SCROLL_TOP | SCROLL_LEFT;
    }
    else
    if(1 == (pos.y - rectMaps.y) && 1 == (pos.x - rectMaps.x))
    {
	scrollDirection |= SCROLL_BOTTOM | SCROLL_RIGHT;
    }
    else
    if(1 == (pos.y - rectMaps.y) && -1 == (pos.x - rectMaps.x))
    {
	scrollDirection |= SCROLL_BOTTOM | SCROLL_LEFT;
    }

    else
    {
	rectMaps.x = pos.x;
	rectMaps.y = pos.y;
	scrollDirection = 0;
    }

    if(scrollDirection) Scroll();
}

void RedrawBoat(const Maps::Tiles & tile, s16 px, s16 py)
{
    if(Settings::Get().Editor())
        Display::Get().Blit(AGG::GetICN(ICN::OBJNWAT2, 23), px, py);
    else
    {
        const Sprite & sprite = AGG::GetICN(ICN::BOAT32, 18);
        Point dst_pt(px + sprite.x(), py + sprite.y() + TILEWIDTH);
        Rect src_rt;
        Interface::GameArea::SrcRectFixed(src_rt, dst_pt, sprite.w(), sprite.h());
        Display::Get().Blit(sprite, src_rt, dst_pt);
    }
}

void RedrawHeroes(const Maps::Tiles & tile)
{
    const Heroes *hero = world.GetHeroes(tile.GetIndex());

    if(hero)
    {
	hero->Redraw();
    }
}

void RedrawMonster(const Maps::Tiles & tile, s16 px, s16 py)
{
    Display & display = Display::Get();
    const Monster monster(tile);
    Point dst_pt;
    Rect src_rt;
    u16 dst_index = MAXU16;

    // draw attack sprite
    if(Maps::ScanAroundObject(tile.GetIndex(), MP2::OBJ_HEROES, Settings::Get().Original(), &dst_index))
    {
	bool revert = false;

	switch(Direction::Get(tile.GetIndex(), dst_index))
	{
	    case Direction::TOP_LEFT:
	    case Direction::LEFT:
	    case Direction::BOTTOM_LEFT:	revert = true;
	    default: break;
	}

	const Sprite & sprite_first = AGG::GetICN(ICN::MINIMON, monster.GetSpriteIndex() * 9 + (revert ? 8 : 7));

	dst_pt.x = px + sprite_first.x() + 16;
	dst_pt.y = py + TILEWIDTH + sprite_first.y();

	Interface::GameArea::SrcRectFixed(src_rt, dst_pt, sprite_first.w(), sprite_first.h());
	display.Blit(sprite_first, src_rt, dst_pt);
    }
    else
    {
	// draw first sprite
	const Sprite & sprite_first = AGG::GetICN(ICN::MINIMON, monster.GetSpriteIndex() * 9);

	dst_pt.x = px + sprite_first.x() + 16;
	dst_pt.y = py + TILEWIDTH + sprite_first.y();

	Interface::GameArea::SrcRectFixed(src_rt, dst_pt, sprite_first.w(), sprite_first.h());
	display.Blit(sprite_first, src_rt, dst_pt);

	// draw second sprite
	const Sprite & sprite_next = AGG::GetICN(ICN::MINIMON, monster.GetSpriteIndex() * 9 + 1 + (Maps::AnimationTicket() % 6));

	dst_pt.x = px + sprite_next.x() + 16;
	dst_pt.y = py + TILEWIDTH + sprite_next.y();

	Interface::GameArea::SrcRectFixed(src_rt, dst_pt, sprite_next.w(), sprite_next.h());
	display.Blit(sprite_next, src_rt, dst_pt);

	if(Maps::isValidDirection(tile.GetIndex(), Direction::BOTTOM))
    	    world.GetTiles(Maps::GetDirectionIndex(tile.GetIndex(), Direction::BOTTOM)).RedrawTop();
    }
}

void RedrawClopOrClofSpriteFog(const u16 dst_index, const Point & dst)
{
    Display & display = Display::Get();
    const u16 around = Maps::GetDirectionAroundFog(dst_index, Settings::Get().MyColor());

    // TIL::CLOF32
    if(DIRECTION_ALL == around)
	display.Blit(AGG::GetTIL(TIL::CLOF32, dst_index % 4, 0), dst.x, dst.y);
    else
    {
	u8 index = 0;
	bool revert = false;

	// see ICN::CLOP32: sprite 6, 7, 8
	if(around & (Direction::CENTER | Direction::TOP) && !(around & (Direction::BOTTOM | Direction::LEFT | Direction::RIGHT)))
	{ index = 6; revert = false; }
	else
	if(around & (Direction::CENTER | Direction::RIGHT) && !(around & (Direction::TOP | Direction::BOTTOM | Direction::LEFT)))
	{ index = 7; revert = false; }
	else
	if(around & (Direction::CENTER | Direction::LEFT) && !(around & (Direction::TOP | Direction::BOTTOM | Direction::RIGHT)))
	{ index = 7; revert = true; }
	else
	if(around & (Direction::CENTER | Direction::BOTTOM) && !(around & (Direction::TOP | Direction::LEFT | Direction::RIGHT)))
	{ index = 8; revert = false; }
	else
	// see ICN::CLOP32: sprite 9, 29
	if(around & (DIRECTION_CENTER_COL) && !(around & (Direction::LEFT | Direction::RIGHT)))
	{ index = 9; revert = false; }
	else
	if(around & (DIRECTION_CENTER_ROW) && !(around & (Direction::TOP | Direction::BOTTOM)))
	{ index = 29; revert = false; }
	else
	// see ICN::CLOP32: sprite 10
	if((around & Direction::CENTER) && !(around & (Direction::TOP | Direction::BOTTOM | Direction::LEFT | Direction::RIGHT)))
	{ index = 10; revert = false; }
	else
	// see ICN::CLOP32: sprite 15, 22
	if(around == (DIRECTION_ALL & (~Direction::TOP_RIGHT)))
	{ index = 15; revert = false; }
	else
	if(around == (DIRECTION_ALL & (~Direction::TOP_LEFT)))
	{ index = 15; revert = true; }
	else
	if(around == (DIRECTION_ALL & (~Direction::BOTTOM_RIGHT)))
	{ index = 22; revert = false; }
	else
	if(around == (DIRECTION_ALL & (~Direction::BOTTOM_LEFT)))
	{ index = 22; revert = true; }
	else
	// see ICN::CLOP32: sprite 16, 17, 18, 23
	if(around == (DIRECTION_ALL & (~(Direction::TOP_RIGHT | Direction::BOTTOM_RIGHT))))
	{ index = 16; revert = false; }
	else
	if(around == (DIRECTION_ALL & (~(Direction::TOP_LEFT | Direction::BOTTOM_LEFT))))
	{ index = 16; revert = true; }
	else
	if(around == (DIRECTION_ALL & (~(Direction::TOP_RIGHT | Direction::BOTTOM_LEFT))))
	{ index = 17; revert = false; }
	else
	if(around == (DIRECTION_ALL & (~(Direction::TOP_LEFT | Direction::BOTTOM_RIGHT))))
	{ index = 17; revert = true; }
	else
	if(around == (DIRECTION_ALL & (~(Direction::TOP_LEFT | Direction::TOP_RIGHT))))
	{ index = 18; revert = false; }
	else
	if(around == (DIRECTION_ALL & (~(Direction::BOTTOM_LEFT | Direction::BOTTOM_RIGHT))))
	{ index = 23; revert = false; }
	else
	// see ICN::CLOP32: sprite 13, 14
	if(around == (DIRECTION_ALL & (~DIRECTION_TOP_RIGHT_CORNER)))
	{ index = 13; revert = false; }
	else
	if(around == (DIRECTION_ALL & (~DIRECTION_TOP_LEFT_CORNER)))
	{ index = 13; revert = true; }
	else
	if(around == (DIRECTION_ALL & (~DIRECTION_BOTTOM_RIGHT_CORNER)))
	{ index = 14; revert = false; }
	else
	if(around == (DIRECTION_ALL & (~DIRECTION_BOTTOM_LEFT_CORNER)))
	{ index = 14; revert = true; }
	else
	// see ICN::CLOP32: sprite 11, 12
	if(around & (Direction::CENTER | Direction::LEFT | Direction::BOTTOM_LEFT | Direction::BOTTOM) &&
	 !(around & (Direction::TOP | Direction::TOP_RIGHT | Direction::RIGHT)))
	{ index = 11; revert = false; }
	else
	if(around & (Direction::CENTER | Direction::RIGHT | Direction::BOTTOM_RIGHT | Direction::BOTTOM) &&
	 !(around & (Direction::TOP | Direction::TOP_LEFT | Direction::LEFT)))
	{ index = 11; revert = true; }
	else
	if(around & (Direction::CENTER | Direction::LEFT | Direction::TOP_LEFT | Direction::TOP) &&
	 !(around & (Direction::BOTTOM | Direction::BOTTOM_RIGHT | Direction::RIGHT)))
	{ index = 12; revert = false; }
	else
	if(around & (Direction::CENTER | Direction::RIGHT | Direction::TOP_RIGHT | Direction::TOP) &&
	 !(around & (Direction::BOTTOM | Direction::BOTTOM_LEFT | Direction::LEFT)))
	{ index = 12; revert = true; }
	else
	// see ICN::CLOP32: sprite 19, 20, 22
	if(around & (DIRECTION_CENTER_ROW | Direction::BOTTOM | Direction::TOP | Direction::TOP_LEFT) &&
	 !(around & (Direction::BOTTOM_LEFT | Direction::BOTTOM_RIGHT | Direction::TOP_RIGHT)))
	{ index = 19; revert = false; }
	else
	if(around & (DIRECTION_CENTER_ROW | Direction::BOTTOM | Direction::TOP | Direction::TOP_RIGHT) &&
	 !(around & (Direction::BOTTOM_LEFT | Direction::BOTTOM_RIGHT | Direction::TOP_LEFT)))
	{ index = 19; revert = true; }
	else
	if(around & (DIRECTION_CENTER_ROW | Direction::BOTTOM | Direction::TOP | Direction::BOTTOM_LEFT) &&
	 !(around & (Direction::TOP_RIGHT | Direction::BOTTOM_RIGHT | Direction::TOP_LEFT)))
	{ index = 20; revert = false; }
	else
	if(around & (DIRECTION_CENTER_ROW | Direction::BOTTOM | Direction::TOP | Direction::BOTTOM_RIGHT) &&
	 !(around & (Direction::TOP_RIGHT | Direction::BOTTOM_LEFT | Direction::TOP_LEFT)))
	{ index = 20; revert = true; }
	else
	if(around & (DIRECTION_CENTER_ROW | Direction::BOTTOM | Direction::TOP) &&
	 !(around & (Direction::TOP_RIGHT | Direction::BOTTOM_RIGHT | Direction::BOTTOM_LEFT | Direction::TOP_LEFT)))
	{ index = 22; revert = false; }
	else
	// see ICN::CLOP32: sprite 24, 25, 26, 30
	if(around & (DIRECTION_CENTER_ROW | Direction::BOTTOM | Direction::BOTTOM_LEFT) &&
	 !(around & (Direction::TOP | Direction::BOTTOM_RIGHT)))
	{ index = 24; revert = false; }
	else
	if(around & (DIRECTION_CENTER_ROW | Direction::BOTTOM | Direction::BOTTOM_RIGHT) &&
	 !(around & (Direction::TOP | Direction::BOTTOM_LEFT)))
	{ index = 24; revert = true; }
	else
	if(around & (DIRECTION_CENTER_COL | Direction::LEFT | Direction::TOP_LEFT) &&
	 !(around & (Direction::RIGHT | Direction::BOTTOM_LEFT)))
	{ index = 25; revert = false; }
	else
	if(around & (DIRECTION_CENTER_COL | Direction::RIGHT | Direction::TOP_RIGHT) &&
	 !(around & (Direction::LEFT | Direction::BOTTOM_RIGHT)))
	{ index = 25; revert = true; }
	else
	if(around & (DIRECTION_CENTER_COL | Direction::BOTTOM_LEFT | Direction::LEFT) &&
	 !(around & (Direction::RIGHT | Direction::TOP_LEFT)))
	{ index = 26; revert = false; }
	else
	if(around & (DIRECTION_CENTER_COL | Direction::BOTTOM_RIGHT | Direction::RIGHT) &&
	 !(around & (Direction::LEFT | Direction::TOP_RIGHT)))
	{ index = 26; revert = true; }
	else
	if(around & (DIRECTION_CENTER_ROW | Direction::TOP_LEFT | Direction::TOP) &&
	 !(around & (Direction::BOTTOM | Direction::TOP_RIGHT)))
	{ index = 30; revert = false; }
	else
	if(around & (DIRECTION_CENTER_ROW | Direction::TOP_RIGHT | Direction::TOP) &&
	 !(around & (Direction::BOTTOM | Direction::TOP_LEFT)))
	{ index = 30; revert = true; }
	else
	// see ICN::CLOP32: sprite 27, 28
	if(around & (Direction::CENTER | Direction::BOTTOM | Direction::LEFT) &&
	 !(around & (Direction::TOP | Direction::TOP_RIGHT | Direction::RIGHT | Direction::BOTTOM_LEFT)))
	{ index = 27; revert = false; }
	else
	if(around & (Direction::CENTER | Direction::BOTTOM | Direction::RIGHT) &&
	 !(around & (Direction::TOP | Direction::TOP_LEFT | Direction::LEFT | Direction::BOTTOM_RIGHT)))
	{ index = 27; revert = true; }
	else
	if(around & (Direction::CENTER | Direction::LEFT | Direction::TOP) &&
	 !(around & (Direction::TOP_LEFT | Direction::RIGHT | Direction::BOTTOM | Direction::BOTTOM_RIGHT)))
	{ index = 28; revert = false; }
	else
	if(around & (Direction::CENTER | Direction::RIGHT | Direction::TOP) &&
	 !(around & (Direction::TOP_RIGHT | Direction::LEFT | Direction::BOTTOM | Direction::BOTTOM_LEFT)))
	{ index = 28; revert = true; }
	else
	// see ICN::CLOP32: sprite 31, 32, 33
	if(around & (DIRECTION_CENTER_ROW | Direction::TOP) &&
	 !(around & (Direction::BOTTOM | Direction::TOP_LEFT | Direction::TOP_RIGHT)))
	{ index = 31; revert = false; }
	else
	if(around & (DIRECTION_CENTER_COL | Direction::RIGHT) &&
	 !(around & (Direction::LEFT | Direction::TOP_RIGHT | Direction::BOTTOM_RIGHT)))
	{ index = 32; revert = false; }
	else
	if(around & (DIRECTION_CENTER_COL | Direction::LEFT) &&
	 !(around & (Direction::RIGHT | Direction::TOP_LEFT | Direction::BOTTOM_LEFT)))
	{ index = 32; revert = true; }
	else
	if(around & (DIRECTION_CENTER_ROW | Direction::BOTTOM) &&
	 !(around & (Direction::TOP | Direction::BOTTOM_LEFT | Direction::BOTTOM_RIGHT)))
	{ index = 33; revert = false; }
	else
	// see ICN::CLOP32: sprite 0, 1, 2, 3, 4, 5
	if(around & (DIRECTION_CENTER_ROW | DIRECTION_BOTTOM_ROW) &&
	 !(around & (Direction::TOP)))
	{ index = dst_index % 2 ? 0 : 1; revert = false; }
	else
	if(around & (DIRECTION_CENTER_ROW | DIRECTION_TOP_ROW) &&
	 !(around & (Direction::BOTTOM)))
	{ index = dst_index % 2 ? 4 : 5; revert = false; }
	else
	if(around & (DIRECTION_CENTER_COL | DIRECTION_LEFT_COL) &&
	 !(around & (Direction::RIGHT)))
	{ index = dst_index % 2 ? 2 : 3; revert = false; }
	else
	if(around & (DIRECTION_CENTER_COL | DIRECTION_RIGHT_COL) &&
	 !(around & (Direction::LEFT)))
	{ index = dst_index % 2 ? 2 : 3; revert = true; }
	// unknown
	else
	{
	    display.Blit(AGG::GetTIL(TIL::CLOF32, dst_index % 4, 0), dst.x, dst.y);
	    return;
	}

	const Sprite & src = AGG::GetICN(ICN::CLOP32, index, revert);
	display.Blit(src, revert ? dst.x + src.x() + TILEWIDTH - src.w() : dst.x + src.x(), dst.y + src.y());
    }
}

void Interface::GameArea::GenerateUltimateArtifactAreaSurface(const u16 index, Surface & sf)
{
    if(Maps::isValidAbsIndex(index))
    {
	Display & display = Display::Get();
	Interface::GameArea & gamearea = GameArea::Get();
	const Rect & rectMaps = gamearea.GetRectMaps();
	const Rect & rectArea = gamearea.GetArea();
	Point pt(index % world.w(), index / world.h());

        const Point reserved(rectMaps);
        gamearea.Center(pt);
	gamearea.Redraw(false);

	// blit marker
	for(u8 ii = 0; ii < rectMaps.h; ++ii) if(index < Maps::GetIndexFromAbsPoint(rectMaps.x + rectMaps.w - 1, rectMaps.y + ii))
	{
	    pt.y = ii;
	    break;
	}
	for(u8 ii = 0; ii < rectMaps.w; ++ii) if(index == Maps::GetIndexFromAbsPoint(rectMaps.x + ii, rectMaps.y + pt.y))
	{
	    pt.x = ii;
	    break;
	}
	const Sprite & marker = AGG::GetICN(ICN::ROUTE, 0);
	const Point dst(rectArea.x + pt.x * TILEWIDTH, rectArea.y + pt.y * TILEWIDTH);
	display.Blit(marker, dst.x, dst.y + 8);

	Rect rt(dst.x - sf.w() / 2, dst.y - sf.h() / 2, sf.w(), sf.h());

	// fix align
	if(rt.x < rectArea.x) rt.x = rectArea.x;
	else
	if(rt.x > rectArea.x + rectArea.w - rt.w) rt.x = rectArea.x + rectArea.w - rt.w;
	if(rt.y < rectArea.y) rt.y = rectArea.y;
	else
	if(rt.y > rectArea.y + rectArea.h - rt.h) rt.y = rectArea.y + rectArea.h - rt.h;

	sf.Blit(display, rt, 0, 0);

        // restore position
        gamearea.rectMaps.x = reserved.x;
        gamearea.rectMaps.y = reserved.y;
	gamearea.Redraw();
    }
    else
    Error::Warning("Interface::GameArea::GenerateUltimateArtifactAreaSurface: artifact not found");
}

bool Interface::GameArea::NeedScroll(void) const
{
    return scrollDirection;
}

Cursor::themes_t Interface::GameArea::GetScrollCursor(void) const
{
    switch(scrollDirection)
    {
	case SCROLL_TOP:		  return Cursor::SCROLL_TOP;
	case SCROLL_BOTTOM:		  return Cursor::SCROLL_BOTTOM;
	case SCROLL_RIGHT:		  return Cursor::SCROLL_RIGHT;
	case SCROLL_LEFT:		  return Cursor::SCROLL_LEFT;
	case SCROLL_LEFT | SCROLL_TOP:	  return Cursor::SCROLL_TOPLEFT;
	case SCROLL_LEFT | SCROLL_BOTTOM: return Cursor::SCROLL_BOTTOMLEFT;
	case SCROLL_RIGHT | SCROLL_TOP:	  return Cursor::SCROLL_TOPRIGHT;
	case SCROLL_RIGHT | SCROLL_BOTTOM:return Cursor::SCROLL_BOTTOMRIGHT;

	default: break;
    }

    return Cursor::NONE;
}

void Interface::GameArea::SetScroll(scroll_t direct)
{
    switch(direct)
    {
	case SCROLL_LEFT:	if(0 < rectMaps.x)                      scrollDirection |= direct;	break;
	case SCROLL_RIGHT:	if(world.w() - rectMaps.w > rectMaps.x) scrollDirection |= direct;	break;
	case SCROLL_TOP:	if(0 < rectMaps.y)                      scrollDirection |= direct;	break;
	case SCROLL_BOTTOM:	if(world.h() - rectMaps.h > rectMaps.y) scrollDirection |= direct;	break;
	default: break;
    }
    SetUpdateCursor();
}

/* convert area point to index maps */
s16 Interface::GameArea::GetIndexFromMousePoint(const Point & pt) const
{
    s16 result = (rectMaps.y + (pt.y - rectArea.y) / TILEWIDTH) * world.w() + rectMaps.x + (pt.x - rectArea.x) / TILEWIDTH;
    const u16 & max = world.w() * world.h() - 1;

    return result > max || result < Maps::GetIndexFromAbsPoint(rectMaps.x, rectMaps.y) ? -1 : result;
}

void Interface::GameArea::SetUpdateCursor(void)
{
    updateCursor = true;
}

void Interface::GameArea::QueueEventProcessing(void)
{
    Cursor & cursor = Cursor::Get();
    LocalEvent & le = LocalEvent::Get();
    const Point & mp = le.GetMouseCursor();


    s16 index = (rectMaps.y + (mp.y - rectArea.y) / TILEWIDTH) * world.w() + rectMaps.x + (mp.x - rectArea.x) / TILEWIDTH;
    const u16 & max = world.w() * world.h() - 1;
    
    // out of range
    if(index > max || index < Maps::GetIndexFromAbsPoint(rectMaps.x, rectMaps.y)) return;

    const Maps::Tiles & tile = world.GetTiles(index);
    const Rect tile_pos(rectArea.x + ((u16) (mp.x - rectArea.x) / TILEWIDTH) * TILEWIDTH,
	                rectArea.y + ((u16) (mp.y - rectArea.y) / TILEWIDTH) * TILEWIDTH,
	                TILEWIDTH, TILEWIDTH);

    // change cusor if need
    if(updateCursor || index != oldIndexPos)
    {
	cursor.SetThemes(Game::GetCursor(tile));
	oldIndexPos = index;
	updateCursor = false;
	Interface::Basic::Get().SetRedraw(REDRAW_CURSOR);
    }

    if(le.MouseClickLeft(tile_pos) && Cursor::POINTER != cursor.Themes())
        Game::MouseCursorAreaClickLeft(index);
    else
    if(le.MousePressRight(tile_pos))
        Game::MouseCursorAreaPressRight(index);
}
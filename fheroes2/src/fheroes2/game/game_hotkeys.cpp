/***************************************************************************
 *   Copyright (C) 2010 by Andrey Afletdinov <fheroes2@gmail.com>          *
 *                                                                         *
 *   Part of the Free Heroes2 Engine:                                      *
 *   http://sourceforge.net/projects/fheroes2                              *
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

#include <algorithm>

#include "gamedefs.h"
#include "tinyconfig.h"
#include "settings.h"
#include "game.h"

namespace Game
{
    void HotKeysDefaults(void);
    void HotKeysLoad(const std::string &);
    const char* EventsName(events_t);

    events_t & operator++ (events_t & evnt)
    {
	return evnt = (EVENT_LAST == evnt ? EVENT_NONE : events_t(evnt + 1));
    }

    KeySym key_events[EVENT_LAST];
    static int key_groups = 0;
}

const char* Game::EventsName(events_t evnt)
{
    switch(evnt)
    {
	case EVENT_EXIT:		return "exit";
	case EVENT_ENDTURN:		return "end turn";
	case EVENT_NEXTHERO:		return "next hero";
	case EVENT_NEXTTOWN:		return "next town";
	case EVENT_CONTINUE:		return "continue move";
	case EVENT_SAVEGAME:		return "save game";
	case EVENT_LOADGAME:		return "load game";
	case EVENT_FILEOPTIONS:		return "show file dialog";
	case EVENT_SYSTEMOPTIONS:	return "show system options";
	case EVENT_PUZZLEMAPS:		return "show puzzle maps";
	case EVENT_INFOGAME:		return "show game info";
	case EVENT_DIGARTIFACT:		return "dig artifact";
	case EVENT_CASTSPELL:		return "cast spell";
	case EVENT_DEFAULTACTION:	return "default action";
	case EVENT_MOVELEFT:		return "move left";
	case EVENT_MOVERIGHT:		return "move right";
	case EVENT_MOVEUP:		return "move up";
	case EVENT_MOVEDOWN:		return "move down";
	case EVENT_OPENFOCUS:		return "open focus";
	case EVENT_SCROLLLEFT:		return "scroll left";
	case EVENT_SCROLLRIGHT:		return "scroll right";
	case EVENT_SCROLLUP:		return "scroll up";
	case EVENT_SCROLLDOWN:		return "scroll down";
	case EVENT_CTRLPANEL:		return "control panel";
	case EVENT_SHOWRADAR:		return "show radar";
	case EVENT_SHOWBUTTONS:		return "show buttons";
	case EVENT_SHOWSTATUS:		return "show status";
	case EVENT_SHOWICONS:		return "show icons";
        case EVENT_EMULATETOGGLE:	return "emulate mouse toggle";
	case EVENT_SWITCHGROUP:		return "switch group";
	default: break;
    }
    return NULL;
}

void Game::HotKeysDefaults(void)
{
    std::fill(&key_events[0], &key_events[EVENT_LAST], KEY_NONE);

    // system
    key_events[EVENT_EXIT] = KEY_ESCAPE;
    // end turn
    key_events[EVENT_ENDTURN] = KEY_e;
    // next hero
    key_events[EVENT_NEXTHERO] = KEY_h;
    // next town
    key_events[EVENT_NEXTTOWN] = KEY_t;
    // continue (move hero)
    key_events[EVENT_CONTINUE] = KEY_m;
    // save game
    key_events[EVENT_SAVEGAME] = KEY_s;
    // load game
    key_events[EVENT_LOADGAME] = KEY_l;
    // show file dialog
    key_events[EVENT_FILEOPTIONS] = KEY_f;
    // show system options
    key_events[EVENT_SYSTEMOPTIONS] = KEY_o;
    // show puzzle maps
    key_events[EVENT_PUZZLEMAPS] = KEY_p;
    // show game info
    key_events[EVENT_INFOGAME] = KEY_i;
    // dig artifact
    key_events[EVENT_DIGARTIFACT] = KEY_d;
    // cast spell
    key_events[EVENT_CASTSPELL] = KEY_a;
    // default action
    key_events[EVENT_DEFAULTACTION] = KEY_RETURN;
    // move hero
    key_events[EVENT_MOVELEFT] = KEY_LEFT;
    key_events[EVENT_MOVERIGHT] = KEY_RIGHT;
    key_events[EVENT_MOVEUP] = KEY_UP;
    key_events[EVENT_MOVEDOWN] = KEY_DOWN;
    // open focus
    // key_events[EVENT_OPENFOCUS] = KEY_NONE;
    // scroll
    // key_events[EVENT_SCROLLLEFT] = KEY_NONE;
    // key_events[EVENT_SCROLLRIGHT] = KEY_NONE;
    // key_events[EVENT_SCROLLUP] = KEY_NONE;
    // key_events[EVENT_SCROLLDOWN] = KEY_NONE;
    // control panel
    key_events[EVENT_CTRLPANEL] = KEY_1;
    key_events[EVENT_SHOWRADAR] = KEY_2;
    key_events[EVENT_SHOWBUTTONS] = KEY_3;
    key_events[EVENT_SHOWSTATUS] = KEY_4;
    key_events[EVENT_SHOWICONS] = KEY_5;
    // emulate mouse
    // key_events[EVENT_EMULATETOGGLE] = KEY_NONE;
    // switch group
    // key_events[EVENT_SWITCHGROUP] = KEY_NONE;
}

void Game::EventSwitchGroup(void)
{
    ++key_groups;
}

Game::events_t Game::HotKeysGetEvent(int sym)
{
    if(sym != KEY_NONE)
    {
	const KeySym* begin = &key_events[0];
	const KeySym* end = &key_events[EVENT_LAST];
	const KeySym* it = std::find(begin, end, sym);
	return it != end ? static_cast<events_t>(it - begin) : EVENT_NONE;
    }
    return  EVENT_NONE;
}

void Game::HotKeysLoad(const std::string & hotkeys)
{
    Tiny::Config config;
    const Tiny::Entry* entry = NULL;

    config.SetSeparator('=');
    config.SetComment('#');

    if(config.Load(hotkeys.c_str()))
    {
	for(events_t evnt = EVENT_NONE; evnt < EVENT_LAST; ++evnt)
	{
	    const char* name = EventsName(evnt);
	    if(name)
	    {
		entry = config.Find(name);
		if(entry)
		{
		    if(KEY_NONE != entry->IntParams())
			key_events[evnt] = KeySymFromInt(entry->IntParams());
		    else
		    {
			VERBOSE("Game::HotKeysLoad: events: " << EventsName(evnt) << ", unknown key: " << entry->IntParams());
		    }
		}
	    }
	}

#ifdef WITHOUT_MOUSE
	LocalEvent & le = LocalEvent::Get();

	entry = config.Find("emulate mouse up");
        if(entry) le.SetEmulateMouseUpKey(KeySymFromInt(entry->IntParams()));

        entry = config.Find("emulate mouse down");
        if(entry) le.SetEmulateMouseDownKey(KeySymFromInt(entry->IntParams()));

        entry = config.Find("emulate mouse left");
        if(entry) le.SetEmulateMouseLeftKey(KeySymFromInt(entry->IntParams()));

        entry = config.Find("emulate mouse right");
        if(entry) le.SetEmulateMouseRightKey(KeySymFromInt(entry->IntParams()));

        entry = config.Find("emulate press left");
        if(entry) le.SetEmulatePressLeftKey(KeySymFromInt(entry->IntParams()));

        entry = config.Find("emulate press right");
        if(entry) le.SetEmulatePressRightKey(KeySymFromInt(entry->IntParams()));
#endif
    }
}
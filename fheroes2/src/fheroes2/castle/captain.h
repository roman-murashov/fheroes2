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
#ifndef H2CAPTAIN_H
#define H2CAPTAIN_H

#include "race.h"
#include "morale.h"
#include "luck.h"
#include "skill.h"
#include "gamedefs.h"

class Castle;

class Captain : public Skill::Primary
{
    public:
	Captain(const Castle &);

	bool isValid(void) const;
        u8 GetAttack(void) const;
        u8 GetDefense(void) const;
        u8 GetPower(void) const;
        u8 GetKnowledge(void) const;
        Morale::morale_t GetMorale(void) const;
        Luck::luck_t GetLuck(void) const;

	const Castle & home;
};

#endif

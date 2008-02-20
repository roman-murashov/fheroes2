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
#include "localevent.h"
#include "button.h"
#include "cursor.h"
#include "config.h"
#include "background.h"
#include "dialog.h"

Dialog::answer_t Dialog::SystemOptions(void)
{
    Display & display = Display::Get();

    // preload
    const ICN::icn_t spanbkg = H2Config::EvilInterface() ? ICN::SPANBKGE : ICN::SPANBKG;
    const ICN::icn_t spanbtn = H2Config::EvilInterface() ? ICN::SPANBTNE : ICN::SPANBTN;

    AGG::PreloadObject(spanbkg);
    AGG::PreloadObject(spanbtn);

    // cursor
    Cursor & cursor = Cursor::Get();
    const Cursor::themes_t oldcursor = cursor.Themes();
    cursor.Hide();
    cursor.SetThemes(cursor.POINTER);

    // image box
    const Sprite &box = AGG::GetICN(spanbkg, 0);

    Rect rb((display.w() - box.w()) / 2, (display.h() - box.h()) / 2, box.w(), box.h());
    Background back(rb);
    back.Save();

    display.Blit(box, rb.x, rb.y);

    LocalEvent & le = LocalEvent::GetLocalEvent();

    Button buttonOk(rb.x + 113, rb.y + 362, spanbtn, 0, 1);

    buttonOk.Draw();

    cursor.Show();
    display.Flip();

    Dialog::answer_t result = Dialog::ZERO;

    // dialog menu loop
    while(le.HandleEvents())
    {
        le.MousePressLeft(buttonOk) ? buttonOk.PressDraw() : buttonOk.ReleaseDraw();

        if(le.MouseClickLeft(buttonOk)) { result = Dialog::OK; break; }
        if(le.KeyPress(SDLK_ESCAPE)){ result = Dialog::CANCEL; break; }
    }

    // restore background
    cursor.Hide();
    back.Restore();
    cursor.SetThemes(oldcursor);
    cursor.Show();
    display.Flip();

    return result;
}

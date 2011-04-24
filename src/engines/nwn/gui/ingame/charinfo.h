/* eos - A reimplementation of BioWare's Aurora engine
 *
 * eos is the legal property of its developers, whose names can be
 * found in the AUTHORS file distributed with this source
 * distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * The Infinity, Aurora, Odyssey and Eclipse engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 */

/** @file engines/nwn/gui/ingame/charinfo.h
 *  A NWN character info panel.
 */

#ifndef ENGINES_NWN_GUI_INGAME_CHARINFO_H
#define ENGINES_NWN_GUI_INGAME_CHARINFO_H

#include "engines/nwn/gui/gui.h"

namespace Common {
	class UString;
}

namespace Engines {

namespace NWN {

/** A NWN character info panel. */
class CharacterInfo : public GUI {
public:
	CharacterInfo();
	virtual ~CharacterInfo();

	/** Set the portrait image. */
	virtual void setPortrait(const Common::UString &portrait) = 0;

	/** Set the character name. */
	virtual void setName(const Common::UString &name);
	/** Set the area the character is in. */
	virtual void setArea(const Common::UString &area);

	/** Set the health bar color. */
	virtual void setHealthColor(float r, float g, float b, float a) = 0;
	/** Set the character health. */
	virtual void setHealth(int32 current, int32 max) = 0;
};

} // End of namespace NWN

} // End of namespace Engines

#endif // ENGINES_NWN_GUI_INGAME_CHARINFO_H

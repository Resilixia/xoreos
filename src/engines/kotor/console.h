/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  KotOR (debug) console.
 */

#ifndef ENGINES_KOTOR_CONSOLE_H
#define ENGINES_KOTOR_CONSOLE_H

#include "src/engines/aurora/console.h"

namespace Engines {

namespace KotOR {

class KotOREngine;

class Console : public ::Engines::Console {
public:
	Console(KotOREngine &engine);
	~Console();


private:
	KotOREngine *_engine;

	// Caches
	std::list<Common::UString> _modules; ///< All known modules.


	// Updating the caches
	void updateCaches();
	void updateModules();

	// The commands
	void cmdExitModule (const CommandLine &cl);
	void cmdListModules(const CommandLine &cl);
	void cmdLoadModule (const CommandLine &cl);
};

} // End of namespace KotOR

} // End of namespace Engines

#endif // ENGINES_KOTOR_CONSOLE_H

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

/** @file aurora/zipfile.h
 *  A ZIP archive.
 */

#ifndef AURORA_ZIPFILE_H
#define AURORA_ZIPFILE_H

#include <vector>

#include "common/types.h"

#include "aurora/types.h"
#include "aurora/archive.h"

namespace Common {
	class UString;
	class SeekableReadStream;
	class File;
	class ZipFile;
}

namespace Aurora {

/** A class encapsulating ZIP files for resource archive access. */
class ZIPFile : public Archive {
public:
	ZIPFile(const Common::UString &fileName);
	~ZIPFile();

	/** Clear the resource list. */
	void clear();

	/** Return the list of resources. */
	const ResourceList &getResources() const;

	/** Return a stream of the resource's contents. */
	Common::SeekableReadStream *getResource(uint32 index) const;

private:
	/** The actual zip file. */
	Common::ZipFile *_zipFile;

	/** External list of resource names and types. */
	ResourceList _resources;

	void load();
};

} // End of namespace Aurora

#endif // AURORA_ZIPFILE_H

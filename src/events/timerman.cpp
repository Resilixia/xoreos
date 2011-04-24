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

/** @file events/timerman.cpp
 *  The global timer manager.
 */

#include "common/error.h"

#include "events/timerman.h"

DECLARE_SINGLETON(Events::TimerManager)

namespace Events {

TimerHandle::TimerHandle() : _empty(true) {
}

TimerHandle::~TimerHandle() {
	TimerMan.removeTimer(*this);
}


TimerManager::TimerManager() {
}

TimerManager::~TimerManager() {
	for (std::list<TimerID>::iterator t = _timers.begin(); t != _timers.end(); ++t)
		removeTimer(*t);
}

void TimerManager::init() {
}

void TimerManager::addTimer(uint32 interval, TimerHandle &handle, const TimerFunc &func) {
	Common::StackLock lock(_mutex);

	removeTimer(handle);

	_timers.push_back(TimerID());

	std::list<TimerID>::iterator id = --_timers.end();

	handle._iterator = id;
	handle._empty    = false;

	id->_func = func;
	id->_id   = SDL_AddTimer(interval, &TimerManager::timerCallback, (void *) &handle);
	if (id->_id)
		return;

	handle._iterator = _timers.end();
	handle._empty    = true;

	_timers.erase(id);

	throw Common::Exception("Failed to add timer");
}

void TimerManager::removeTimer(TimerHandle &handle) {
	Common::StackLock lock(_mutex);

	if (handle._empty)
		return;

	removeTimer(*handle._iterator);

	_timers.erase(handle._iterator);

	handle._iterator = _timers.end();
	handle._empty    = true;
}

void TimerManager::removeTimer(TimerID &id) {
	if (id._id == 0)
		return;

	SDL_RemoveTimer(id._id);
}

uint32 TimerManager::timerCallback(uint32 interval, void *data) {
	TimerHandle &handle = *((TimerHandle *) data);

	if (handle._empty)
		return 0;

	uint32 newInterval = handle._iterator->_func(interval);
	if (newInterval == 0) {
		handle._iterator->_id = 0;
		TimerMan.removeTimer(handle);
		return 0;
	}

	return newInterval;
}

} // End of namespace Events

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

/** @file aurora/ncsscript.h
 *  Handling BioWare's NWN Compiled Scripts.
 */

#ifndef AURORA_NCS_SCRIPT_H
#define AURORA_NCS_SCRIPT_H

#include <vector>

#include "common/types.h"
#include "common/ustring.h"

#include "aurora/types.h"
#include "aurora/aurorafile.h"

namespace Common {
	class SeekableReadStream;
}

namespace Aurora {

/** A stack object for NCS scripts. */
class StackObject {
public:
	enum StackObjectType {
		kStackObjectNone,
		kStackObjectInt,
		kStackObjectFloat,
		kStackObjectString,
		kStackObjectObject,
		kStackObjectVector,
		kStackObjectStruct,
		kStackObjectEngineType
	};

	StackObject(StackObjectType type = kStackObjectNone);
	StackObject(int32 val, StackObjectType = kStackObjectInt);
	StackObject(float val);
	StackObject(const Common::UString &val);

	int32 getInt() const;
	float getFloat() const;
	const Common::UString &getString() const;
	uint32 getObject() const;

	bool operator==(StackObject &obj);
	bool operator!=(StackObject &obj) { return !operator==(obj); }

	StackObjectType getType() { return _type; }

private:
	StackObjectType _type;

	uint32 _intVal;
	float _floatVal;
	Common::UString _stringVal;
};

class NCSStack : public std::vector<StackObject> {
public:
	NCSStack();
	~NCSStack();

	StackObject top();
	StackObject pop();
	void push(StackObject obj);

	int32 getStackPtr();
	void setStackPtr(int32 pos);
	int32 getBasePtr();
	void setBasePtr(int32 pos);

private:
	int32 _stackPtr;
	int32 _basePtr;
};

#define DECLARE_OPCODE(x) void x(InstructionType type)

/** An NCS, BioWare's NWN Compile Script. */
class NCSScript : public AuroraBase {
public:
	NCSScript();
	~NCSScript() {}

	void load(Common::SeekableReadStream &ncs);
	void executeStep();
	void decompile();

	enum InstructionType {
		// Unary
		kInstTypeNone = 0,
		kInstTypeInt = 3,
		kInstTypeFloat = 4,
		kInstTypeString = 5,
		kInstTypeObject = 6,
		kInstTypeEffect = 16,
		kInstTypeEvent = 17,
		kInstTypeLocation = 18,
		kInstTypeTalent = 19,

		// Binary
		kInstTypeIntInt = 32,
		kInstTypeFloatFloat = 33,
		kInstTypeObjectObject = 34,
		kInstTypeStringString = 35,
		kInstTypeStructStruct = 36,
		kInstTypeIntFloat = 37,
		kInstTypeFloatInt = 38,
		kInstTypeEffectEffect = 48,
		kInstTypeEventEvent = 49,
		kInstTypeLocationLocation = 50,
		kInstTypeTalentTalent = 51,
		kInstTypeVectorVector = 58,
		kInstTypeVectorFloat = 59,
		kInstTypeFloatVector = 60
	};

private:
	NCSStack _stack;
	Common::SeekableReadStream *_script;
	int32 _savedBasePtr;

	typedef void (NCSScript::*OpcodeProc)(InstructionType type);
	struct Opcode {
		OpcodeProc proc;
		const char *desc;
	};
	const Opcode *_opcodes;
	uint32 _opcodeListSize;
	void setupOpcodes();

	// Opcode declarations
	DECLARE_OPCODE(o_nop);
	DECLARE_OPCODE(o_cpdownsp);
	DECLARE_OPCODE(o_rsadd);
	DECLARE_OPCODE(o_cptopsp);
	DECLARE_OPCODE(o_const);
	DECLARE_OPCODE(o_action);
	DECLARE_OPCODE(o_logand);
	DECLARE_OPCODE(o_logor);
	DECLARE_OPCODE(o_incor);
	DECLARE_OPCODE(o_excor);
	DECLARE_OPCODE(o_booland);
	DECLARE_OPCODE(o_eq);
	DECLARE_OPCODE(o_neq);
	DECLARE_OPCODE(o_geq);
	DECLARE_OPCODE(o_gt);
	DECLARE_OPCODE(o_lt);
	DECLARE_OPCODE(o_leq);
	DECLARE_OPCODE(o_shleft);
	DECLARE_OPCODE(o_shright);
	DECLARE_OPCODE(o_ushright);
	DECLARE_OPCODE(o_add);
	DECLARE_OPCODE(o_sub);
	DECLARE_OPCODE(o_mul);
	DECLARE_OPCODE(o_div);
	DECLARE_OPCODE(o_mod);
	DECLARE_OPCODE(o_neg);
	DECLARE_OPCODE(o_comp);
	DECLARE_OPCODE(o_movsp);
	DECLARE_OPCODE(o_storestateall);
	DECLARE_OPCODE(o_jmp);
	DECLARE_OPCODE(o_jsr);
	DECLARE_OPCODE(o_jz);
	DECLARE_OPCODE(o_retn);
	DECLARE_OPCODE(o_destruct);
	DECLARE_OPCODE(o_not);
	DECLARE_OPCODE(o_decsp);
	DECLARE_OPCODE(o_incsp);
	DECLARE_OPCODE(o_jnz);
	DECLARE_OPCODE(o_cpdownbp);
	DECLARE_OPCODE(o_cptopbp);
	DECLARE_OPCODE(o_decbp);
	DECLARE_OPCODE(o_incbp);
	DECLARE_OPCODE(o_savebp);
	DECLARE_OPCODE(o_restorebp);
	DECLARE_OPCODE(o_storestate);
};

#undef DECLARE_OPCODE

} // End of namespace Aurora

#endif // AURORA_NCS_SCRIPT_H

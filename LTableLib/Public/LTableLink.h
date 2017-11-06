#ifndef _LTABLELINK_H_INCLUDE_
#define _LTABLELINK_H_INCLUDE_

#ifdef _DEBUG
#include "../../MemDebug/LDebugDef.h"
#endif
#ifdef _WIN32
	#include "../OSFace/WIN32/GDI/LDrawer.cpp"
#else
	#include "../OSFace/Linux/GDI/LDrawer.cpp"
	//不支持的平台
#endif
#ifdef _WIN32
	#include "../OSFace/WIN32/LPlatform.cpp"
#else
	#include "../OSFace/Linux/LPlatform.cpp"
	//不支持的平台
#endif
#include "../../LComm/LCommBase.cpp"
#include "../../LComm/LLockMgr.cpp"

#include "../../ScriptEngine/ScriptEngine.cpp"
#include "../../ScriptEngine/src/interface.cpp"
#include "../../ScriptEngine/src/alanysis_tokens.cpp"
#include "../../ScriptEngine/src/press_computer.cpp"
#include "../../ScriptEngine/src/script_engine.cpp"
#include "../../ScriptEngine/src/script/script_rule.cpp"
#include "../../ScriptEngine/src/string_parse.cpp"
#include "../../LComm/LScript_Engine.cpp"
#include "../../LComm/LFont.cpp"

#endif
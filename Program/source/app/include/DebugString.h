/*!
*/
#pragma once

#ifdef _DEBUG

#include "Factor.h"
#include "FactorTask.h"
#include "ofTypes.h"

//#define DebugString(str) debug_string::addDebugString(__FILE__,__LINE__,str)
#define DebugString(fmt,...) debug_string::addDebugString(__FILE__,__LINE__,fmt,__VA_ARGS__)

namespace debug_string {
//void addDebugString(string f, string l, string str);	// do not use it directly. use DebugString(string)
void addDebugString(string f, long l, string fmt, ...);	// do not use it directly. use DebugString(fmt,...)

class DebugStringTask : public FactorTask
{
public:
	DebugStringTask();
	void setString(string key, string str, int duration);
	void update();
	void draw(int x, int y);
private:
	map<string, pair<string, int>> data_;
};

class DebugStringFactor : public Factor
{
public:
	DebugStringFactor();
	void proc();
	void draw(int prio);
private:
	DebugStringTask* task_;
};

}

#else // _DEBUG

#define DebugString(...) void(0)

#endif // _DEBUG
/* EOF */
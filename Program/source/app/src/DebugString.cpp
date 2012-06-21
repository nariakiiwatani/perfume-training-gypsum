/*!
*/
#pragma once

#ifdef _DEBUG

#include "DebugString.h"
#include "ofGraphics.h"

namespace debug_string {
DebugStringTask* debug_string_task_ = NULL;
DebugStringFactor* debug_string_factor_ = NULL;

void addDebugString(string f, long l, string fmt, ...)
{
	if(!debug_string_task_) {
		debug_string_task_ = new DebugStringTask();
		debug_string_factor_ = new DebugStringFactor();
	}
	static char ch[1024];
	va_list v;
	va_start(v,fmt);
	vsprintf(ch, fmt.c_str(), v);
	va_end(v);
	debug_string_task_->setString(f+"("+ofToString(l)+")",ch,60);
}

DebugStringTask::DebugStringTask()
:FactorTask("_debug_string_")
{
	data_.clear();
}

void DebugStringTask::update()
{
	map<string, pair<string, int>>::iterator it = data_.begin();
	while(it != data_.end()) {
		if((*it).second.second-- <= 0) {
			data_.erase(it++);
		}
		else {
			++it;
		}
	}
}

void DebugStringTask::draw(int x, int y)
{
	const int line_height = 20;
	ofEnableAlphaBlending();
	ofSetColor(128,128,128,128);
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofRect(0,0,1000,line_height*data_.size()+10);
	ofSetColor(255,255,255,255);
	map<string, pair<string, int>>::iterator it = data_.begin();
	while(it != data_.end()) {
		ofDrawBitmapString((*it).first+":"+(*it).second.first, x, y);
		++it;
		y += line_height;
	}
	ofDisableAlphaBlending();
}

void DebugStringTask::setString(string key, string str, int duration)
{
	data_[key] = pair<string, int>(str, duration);
}

DebugStringFactor::DebugStringFactor()
:Factor("_debug_string_")
,task_(debug_string_task_)
{
}

void DebugStringFactor::proc()
{
	getManager()->addDraw(0, this);
}

void DebugStringFactor::draw(int prio)
{
	task_->draw(10,20);
}


}
#endif // _DEBUG
/* EOF */
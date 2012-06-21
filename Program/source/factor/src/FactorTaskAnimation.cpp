/*!
*/

#include "FactorTaskAnimation.h"
#include "ofLog.h"

FactorTaskAnimation::FactorTaskAnimation()
:length_(0)
,current_id_("")
{
	sequences_.clear();
}

FactorTaskAnimation::~FactorTaskAnimation()
{
}

FactorTaskAnimation::Key::IpType FactorTaskAnimation::getIpType(string str)
{
	if(str == "step") {
		return Key::IP_STEP;
	}
	else if(str == "linear") {
		return Key::IP_LINEAR;
	}
	else if(str == "end") {
		return Key::IP_END;
	}
	return Key::IP_LINEAR;
}

void FactorTaskAnimation::beginSequence(string id, string type)
{
	if(type == "1f") {
		beginSequence(id, VALUE_FLOAT1);
	}
	else if(type == "2f") {
		beginSequence(id, VALUE_FLOAT2);
	}
	else if(type == "3f") {
		beginSequence(id, VALUE_FLOAT3);
	}
	else if(type == "4f") {
		beginSequence(id, VALUE_FLOAT3);
	}
	else if(type == "s1") {
		beginSequence(id, VALUE_STRING1);
	}
	else if(type == "s2") {
		beginSequence(id, VALUE_STRING2);
	}
	else if(type == "s3") {
		beginSequence(id, VALUE_STRING3);
	}
	else if(type == "s4") {
		beginSequence(id, VALUE_STRING4);
	}
}

void FactorTaskAnimation::beginSequence(string id, ValueType type)
{
	if(current_id_ != "") {
		ofLog(OF_LOG_ERROR, "FactorTaskAnimation::beginKeys: call endKeys() before\n");
		return;
	}
	Sequence seq;
	seq.type = type;
	sequences_.insert(std::pair<string, Sequence>(id, seq));
	current_id_ = id;
}

void FactorTaskAnimation::endSequence()
{
	current_id_ = "";
}

void FactorTaskAnimation::clearSequence()
{
	sequences_.clear();
}

#ifdef USE_OFX_XML
void FactorTaskAnimation::addKey(ofxXmlSettings& xml, int which)
{
	Key::IpType ip = getIpType(xml.getAttribute("Key", "ip", "", which));
	xml.pushTag("Key", which);
	int frame = xml.getValue("Frame", 0);
	xml.pushTag("Values");
	switch(sequences_[current_id_].type) {
		case VALUE_INT1:
			addKey(frame,	xml.getValue("Value", (int)0, 0), ip);
			break;
		case VALUE_INT2:
			addKey(frame,	xml.getValue("Value", (int)0, 0),
							xml.getValue("Value", (int)0, 1), ip);
			break;
		case VALUE_INT3:
			addKey(frame,	xml.getValue("Value", (int)0, 0),
							xml.getValue("Value", (int)0, 1),
							xml.getValue("Value", (int)0, 2), ip);
			break;
		case VALUE_INT4:
			addKey(frame,	xml.getValue("Value", (int)0, 0),
							xml.getValue("Value", (int)0, 1),
							xml.getValue("Value", (int)0, 2),
							xml.getValue("Value", (int)0, 3), ip);
			break;
		case VALUE_FLOAT1:
			addKey(frame,	(float)xml.getValue("Value", 0.f, 0), ip);
			break;
		case VALUE_FLOAT2:
			addKey(frame,	(float)xml.getValue("Value", 0.f, 0),
							(float)xml.getValue("Value", 0.f, 1), ip);
			break;
		case VALUE_FLOAT3:
			addKey(frame,	(float)xml.getValue("Value", 0.f, 0),
							(float)xml.getValue("Value", 0.f, 1),
							(float)xml.getValue("Value", 0.f, 2), ip);
			break;
		case VALUE_FLOAT4:
			addKey(frame,	(float)xml.getValue("Value", 0.f, 0),
							(float)xml.getValue("Value", 0.f, 1),
							(float)xml.getValue("Value", 0.f, 2),
							(float)xml.getValue("Value", 0.f, 3), ip);
			break;
		case VALUE_STRING1:
			addKey(frame,	xml.getValue("Value", "", 0));
			break;
		case VALUE_STRING2:
			addKey(frame,	xml.getValue("Value", "", 0),
							xml.getValue("Value", "", 1));
			break;
		case VALUE_STRING3:
			addKey(frame,	xml.getValue("Value", "", 0),
							xml.getValue("Value", "", 1),
							xml.getValue("Value", "", 2));
			break;
		case VALUE_STRING4:
			addKey(frame,	xml.getValue("Value", "", 0),
							xml.getValue("Value", "", 1),
							xml.getValue("Value", "", 2),
							xml.getValue("Value", "", 3));
			break;
	}
	xml.popTag();
	xml.popTag();
}
#endif // USE_OFX_XML
void FactorTaskAnimation::addKey(int frame, const Key& key)
{
	if(current_id_ == "") {
		ofLog(OF_LOG_ERROR, "FactorTaskAnimation::addKey: call beginKeys() before\n");
		return;
	}
	sequences_[current_id_].keys.insert(std::pair<int, Key>(frame, key));
}

void FactorTaskAnimation::addKey(int frame, int val0, Key::IpType ip)
{
	Key key;
	key.ip = ip;
	switch(sequences_[current_id_].type) {
		case VALUE_INT1:
		case VALUE_INT2:
		case VALUE_INT3:
		case VALUE_INT4:
			key.i[0] = val0;
			break;
		case VALUE_FLOAT1:
		case VALUE_FLOAT2:
		case VALUE_FLOAT3:
		case VALUE_FLOAT4:
			key.f[0] = (float)val0;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, int val0, int val1, Key::IpType ip)
{
	Key key;
	key.ip = ip;
	switch(sequences_[current_id_].type) {
		case VALUE_INT1:
		case VALUE_INT2:
		case VALUE_INT3:
		case VALUE_INT4:
			key.i[0] = val0;
			key.i[1] = val1;
			break;
		case VALUE_FLOAT1:
		case VALUE_FLOAT2:
		case VALUE_FLOAT3:
		case VALUE_FLOAT4:
			key.f[0] = (float)val0;
			key.f[1] = (float)val1;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, int val0, int val1, int val2, Key::IpType ip)
{
	Key key;
	key.ip = ip;
	switch(sequences_[current_id_].type) {
		case VALUE_INT1:
		case VALUE_INT2:
		case VALUE_INT3:
		case VALUE_INT4:
			key.i[0] = val0;
			key.i[1] = val1;
			key.i[2] = val2;
			break;
		case VALUE_FLOAT1:
		case VALUE_FLOAT2:
		case VALUE_FLOAT3:
		case VALUE_FLOAT4:
			key.f[0] = (float)val0;
			key.f[1] = (float)val1;
			key.f[2] = (float)val2;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, int val0, int val1, int val2, int val3, Key::IpType ip)
{
	Key key;
	key.ip = ip;
	switch(sequences_[current_id_].type) {
		case VALUE_INT1:
		case VALUE_INT2:
		case VALUE_INT3:
		case VALUE_INT4:
			key.i[0] = val0;
			key.i[1] = val1;
			key.i[2] = val2;
			key.i[3] = val3;
			break;
		case VALUE_FLOAT1:
		case VALUE_FLOAT2:
		case VALUE_FLOAT3:
		case VALUE_FLOAT4:
			key.f[0] = (float)val0;
			key.f[1] = (float)val1;
			key.f[2] = (float)val2;
			key.f[3] = (float)val3;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, float val0, Key::IpType ip)
{
	Key key;
	key.ip = ip;
	switch(sequences_[current_id_].type) {
		case VALUE_INT1:
		case VALUE_INT2:
		case VALUE_INT3:
		case VALUE_INT4:
			key.i[0] = (int)val0;
			break;
		case VALUE_FLOAT1:
		case VALUE_FLOAT2:
		case VALUE_FLOAT3:
		case VALUE_FLOAT4:
			key.f[0] = val0;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, float val0, float val1, Key::IpType ip)
{
	Key key;
	key.ip = ip;
	switch(sequences_[current_id_].type) {
		case VALUE_INT1:
		case VALUE_INT2:
		case VALUE_INT3:
		case VALUE_INT4:
			key.i[0] = (int)val0;
			key.i[1] = (int)val1;
			break;
		case VALUE_FLOAT1:
		case VALUE_FLOAT2:
		case VALUE_FLOAT3:
		case VALUE_FLOAT4:
			key.f[0] = val0;
			key.f[1] = val1;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, float val0, float val1, float val2, Key::IpType ip)
{
	Key key;
	key.ip = ip;
	switch(sequences_[current_id_].type) {
		case VALUE_INT1:
		case VALUE_INT2:
		case VALUE_INT3:
		case VALUE_INT4:
			key.i[0] = (int)val0;
			key.i[1] = (int)val1;
			key.i[2] = (int)val2;
			break;
		case VALUE_FLOAT1:
		case VALUE_FLOAT2:
		case VALUE_FLOAT3:
		case VALUE_FLOAT4:
			key.f[0] = val0;
			key.f[1] = val1;
			key.f[2] = val2;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, float val0, float val1, float val2, float val3, Key::IpType ip)
{
	Key key;
	key.ip = ip;
	switch(sequences_[current_id_].type) {
		case VALUE_INT1:
		case VALUE_INT2:
		case VALUE_INT3:
		case VALUE_INT4:
			key.i[0] = (int)val0;
			key.i[1] = (int)val1;
			key.i[2] = (int)val2;
			key.i[3] = (int)val3;
			break;
		case VALUE_FLOAT1:
		case VALUE_FLOAT2:
		case VALUE_FLOAT3:
		case VALUE_FLOAT4:
			key.f[0] = val0;
			key.f[1] = val1;
			key.f[2] = val2;
			key.f[3] = val3;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, const ofColor& color, Key::IpType ip)
{
	Key key;
	key.ip = ip;
	switch(sequences_[current_id_].type) {
		case VALUE_INT1:
		case VALUE_INT2:
		case VALUE_INT3:
		case VALUE_INT4:
			key.i[0] = color.r;
			key.i[1] = color.g;
			key.i[2] = color.b;
			key.i[3] = color.a;
			break;
		case VALUE_FLOAT1:
		case VALUE_FLOAT2:
		case VALUE_FLOAT3:
		case VALUE_FLOAT4:
			key.f[0] = color.r/255.f;
			key.f[1] = color.g/255.f;
			key.f[2] = color.b/255.f;
			key.f[3] = color.a/255.f;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, const ofPoint& point, Key::IpType ip)
{
	Key key;
	key.ip = ip;
	switch(sequences_[current_id_].type) {
		case VALUE_INT1:
		case VALUE_INT2:
		case VALUE_INT3:
		case VALUE_INT4:
			key.i[0] = (int)point.x;
			key.i[1] = (int)point.y;
			key.i[2] = (int)point.z;
			break;
		case VALUE_FLOAT1:
		case VALUE_FLOAT2:
		case VALUE_FLOAT3:
		case VALUE_FLOAT4:
			key.f[0] = point.x;
			key.f[1] = point.y;
			key.f[2] = point.z;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, string val0)
{
	Key key;
	switch(sequences_[current_id_].type) {
		case VALUE_STRING1:
		case VALUE_STRING2:
		case VALUE_STRING3:
		case VALUE_STRING4:
			key.s[0] = val0;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, string val0, string val1)
{
	Key key;
	switch(sequences_[current_id_].type) {
		case VALUE_STRING1:
		case VALUE_STRING2:
		case VALUE_STRING3:
		case VALUE_STRING4:
			key.s[0] = val0;
			key.s[1] = val1;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, string val0, string val1, string val2)
{
	Key key;
	switch(sequences_[current_id_].type) {
		case VALUE_STRING1:
		case VALUE_STRING2:
		case VALUE_STRING3:
		case VALUE_STRING4:
			key.s[0] = val0;
			key.s[1] = val1;
			key.s[2] = val2;
			break;
	}
	addKey(frame, key);
}

void FactorTaskAnimation::addKey(int frame, string val0, string val1, string val2, string val3)
{
	Key key;
	switch(sequences_[current_id_].type) {
		case VALUE_STRING1:
		case VALUE_STRING2:
		case VALUE_STRING3:
		case VALUE_STRING4:
			key.s[0] = val0;
			key.s[1] = val1;
			key.s[2] = val2;
			key.s[3] = val3;
			break;
	}
	addKey(frame, key);
}

bool FactorTaskAnimation::getAsInt(string id, int frame, int* ret)
{
	if(frame >= length_) {
		return false;
	}
	Sequence& seq = sequences_[id];
	map<int, Key>::iterator it = seq.keys.find(frame);
	if(it != seq.keys.end()) {
		switch(seq.type) {
			case VALUE_INT4:
				ret[3] = (*it).second.i[3];
			case VALUE_INT3:
				ret[2] = (*it).second.i[2];
			case VALUE_INT2:
				ret[1] = (*it).second.i[1];
			case VALUE_INT1:
				ret[0] = (*it).second.i[0];
				break;
			case VALUE_FLOAT4:
				ret[3] = (int)(*it).second.f[3];
			case VALUE_FLOAT3:
				ret[2] = (int)(*it).second.f[2];
			case VALUE_FLOAT2:
				ret[1] = (int)(*it).second.f[1];
			case VALUE_FLOAT1:
				ret[0] = (int)(*it).second.f[0];
				break;
		}
		return true;
	}

	it = seq.keys.upper_bound(frame);
	if(it == seq.keys.begin() || it == seq.keys.end()) {
		return false;
	}
	std::pair<int, Key> right = *(it--);
	std::pair<int, Key> left = (*it);
	if(left.second.ip == Key::IP_END) {
		return false;
	}
	if(left.second.ip == Key::IP_STEP) {
		switch(seq.type) {
			case VALUE_INT4:
				ret[3] = left.second.i[3];
			case VALUE_INT3:
				ret[2] = left.second.i[2];
			case VALUE_INT2:
				ret[1] = left.second.i[1];
			case VALUE_INT1:
				ret[0] = left.second.i[0];
				break;
			case VALUE_FLOAT4:
				ret[3] = (int)left.second.f[3];
			case VALUE_FLOAT3:
				ret[2] = (int)left.second.f[2];
			case VALUE_FLOAT2:
				ret[1] = (int)left.second.f[1];
			case VALUE_FLOAT1:
				ret[0] = (int)left.second.f[0];
				break;
		}
		return true;
	}
	float ratio = (frame-left.first)/(float)(right.first-left.first);
	switch(left.second.ip) {
		case Key::IP_LINEAR:
			switch(seq.type) {
				case VALUE_INT4:
					ret[3] = (int)((left.second.i[3]*(1-ratio)) + (right.second.i[3]*ratio));
				case VALUE_INT3:
					ret[2] = (int)((left.second.i[2]*(1-ratio)) + (right.second.i[2]*ratio));
				case VALUE_INT2:
					ret[1] = (int)((left.second.i[1]*(1-ratio)) + (right.second.i[1]*ratio));
				case VALUE_INT1:
					ret[0] = (int)((left.second.i[0]*(1-ratio)) + (right.second.i[0]*ratio));
					break;
				case VALUE_FLOAT4:
					ret[3] = (int)((left.second.f[3]*(1-ratio)) + (right.second.f[3]*ratio));
				case VALUE_FLOAT3:
					ret[2] = (int)((left.second.f[2]*(1-ratio)) + (right.second.f[2]*ratio));
				case VALUE_FLOAT2:
					ret[1] = (int)((left.second.f[1]*(1-ratio)) + (right.second.f[1]*ratio));
				case VALUE_FLOAT1:
					ret[0] = (int)((left.second.f[0]*(1-ratio)) + (right.second.f[0]*ratio));
					break;
			}
			break;
	}
	return true;
}

bool FactorTaskAnimation::getAsFloat(string id, int frame, float* ret)
{
	if(frame >= length_) {
		return false;
	}
	Sequence& seq = sequences_[id];
	map<int, Key>::iterator it = seq.keys.find(frame);
	if(it != seq.keys.end()) {
		switch(seq.type) {
			case VALUE_INT4:
				ret[3] = (float)(*it).second.i[3];
			case VALUE_INT3:
				ret[2] = (float)(*it).second.i[2];
			case VALUE_INT2:
				ret[1] = (float)(*it).second.i[1];
			case VALUE_INT1:
				ret[0] = (float)(*it).second.i[0];
				break;
			case VALUE_FLOAT4:
				ret[3] = (*it).second.f[3];
			case VALUE_FLOAT3:
				ret[2] = (*it).second.f[2];
			case VALUE_FLOAT2:
				ret[1] = (*it).second.f[1];
			case VALUE_FLOAT1:
				ret[0] = (*it).second.f[0];
				break;
		}
		return true;
	}

	it = seq.keys.upper_bound(frame);
	if(it == seq.keys.begin() || it == seq.keys.end()) {
		return false;
	}
	std::pair<int, Key> right = *(it--);
	std::pair<int, Key> left = (*it);
	if(left.second.ip == Key::IP_END) {
		return false;
	}
	if(left.second.ip == Key::IP_STEP) {
		switch(seq.type) {
			case VALUE_INT4:
				ret[3] = (float)left.second.i[3];
			case VALUE_INT3:
				ret[2] = (float)left.second.i[2];
			case VALUE_INT2:
				ret[1] = (float)left.second.i[1];
			case VALUE_INT1:
				ret[0] = (float)left.second.i[0];
				break;
			case VALUE_FLOAT4:
				ret[3] = left.second.f[3];
			case VALUE_FLOAT3:
				ret[2] = left.second.f[2];
			case VALUE_FLOAT2:
				ret[1] = left.second.f[1];
			case VALUE_FLOAT1:
				ret[0] = left.second.f[0];
				break;
		}
		return true;
	}
	float ratio = (frame-left.first)/(float)(right.first-left.first);
	switch(left.second.ip) {
		case Key::IP_LINEAR:
			switch(seq.type) {
				case VALUE_INT4:
					ret[3] = (left.second.i[3]*(1-ratio)) + (right.second.i[3]*ratio);
				case VALUE_INT3:
					ret[2] = (left.second.i[2]*(1-ratio)) + (right.second.i[2]*ratio);
				case VALUE_INT2:
					ret[1] = (left.second.i[1]*(1-ratio)) + (right.second.i[1]*ratio);
				case VALUE_INT1:
					ret[0] = (left.second.i[0]*(1-ratio)) + (right.second.i[0]*ratio);
					break;
				case VALUE_FLOAT4:
					ret[3] = (left.second.f[3]*(1-ratio)) + (right.second.f[3]*ratio);
				case VALUE_FLOAT3:
					ret[2] = (left.second.f[2]*(1-ratio)) + (right.second.f[2]*ratio);
				case VALUE_FLOAT2:
					ret[1] = (left.second.f[1]*(1-ratio)) + (right.second.f[1]*ratio);
				case VALUE_FLOAT1:
					ret[0] = (left.second.f[0]*(1-ratio)) + (right.second.f[0]*ratio);
					break;
			}
			break;
	}
	return true;
}

bool FactorTaskAnimation::getAsColor(string id, int frame, ofColor& ret)
{
	if(frame >= length_) {
		return false;
	}
	Sequence& seq = sequences_[id];
	map<int, Key>::iterator it = seq.keys.find(frame);
	if(it != seq.keys.end()) {
		switch(seq.type) {
			case VALUE_INT1:
			case VALUE_INT2:
			case VALUE_INT3:
				ret.r = (*it).second.i[0];
				ret.g = (*it).second.i[1];
				ret.b = (*it).second.i[2];
				ret.a = 255;
				break;
			case VALUE_INT4:
				ret.r = (*it).second.i[0];
				ret.g = (*it).second.i[1];
				ret.b = (*it).second.i[2];
				ret.a = (*it).second.i[3];
				break;
			case VALUE_FLOAT1:
			case VALUE_FLOAT2:
			case VALUE_FLOAT3:
				ret.r = (unsigned char)(*it).second.f[0]*255;
				ret.g = (unsigned char)(*it).second.f[1]*255;
				ret.b = (unsigned char)(*it).second.f[2]*255;
				ret.a = 255;
				break;
			case VALUE_FLOAT4:
				ret.r = (unsigned char)(*it).second.f[0]*255;
				ret.g = (unsigned char)(*it).second.f[1]*255;
				ret.b = (unsigned char)(*it).second.f[2]*255;
				ret.a = (unsigned char)(*it).second.f[3]*255;
				break;
		}
		return true;
	}

	it = seq.keys.upper_bound(frame);
	if(it == seq.keys.begin() || it == seq.keys.end()) {
		return false;
	}
	std::pair<int, Key> right = *(it--);
	std::pair<int, Key> left = (*it);
	if(left.second.ip == Key::IP_END) {
		return false;
	}
	if(left.second.ip == Key::IP_STEP) {
		switch(seq.type) {
			case VALUE_INT1:
			case VALUE_INT2:
			case VALUE_INT3:
				ret.r = left.second.i[0];
				ret.g = left.second.i[1];
				ret.b = left.second.i[2];
				ret.a = 255;
				break;
			case VALUE_INT4:
				ret.r = left.second.i[0];
				ret.g = left.second.i[1];
				ret.b = left.second.i[2];
				ret.a = left.second.i[3];
				break;
			case VALUE_FLOAT1:
			case VALUE_FLOAT2:
			case VALUE_FLOAT3:
				ret.r = (unsigned char)left.second.f[0]*255;
				ret.g = (unsigned char)left.second.f[1]*255;
				ret.b = (unsigned char)left.second.f[2]*255;
				ret.a = 255;
				break;
			case VALUE_FLOAT4:
				ret.r = (unsigned char)left.second.f[0]*255;
				ret.g = (unsigned char)left.second.f[1]*255;
				ret.b = (unsigned char)left.second.f[2]*255;
				ret.a = (unsigned char)left.second.f[3]*255;
				break;
		}
		return true;
	}
	float ratio = (frame-left.first)/(float)(right.first-left.first);
	switch(left.second.ip) {
		case Key::IP_LINEAR:
			switch(seq.type) {
				case VALUE_INT1:
				case VALUE_INT2:
				case VALUE_INT3:
					ret.r = (unsigned char)((left.second.i[0]*(1-ratio)) + (right.second.i[0]*ratio));
					ret.g = (unsigned char)((left.second.i[1]*(1-ratio)) + (right.second.i[1]*ratio));
					ret.b = (unsigned char)((left.second.i[2]*(1-ratio)) + (right.second.i[2]*ratio));
					ret.a = 255;
					break;
				case VALUE_INT4:
					ret.r = (unsigned char)((left.second.i[0]*(1-ratio)) + (right.second.i[0]*ratio));
					ret.g = (unsigned char)((left.second.i[1]*(1-ratio)) + (right.second.i[1]*ratio));
					ret.b = (unsigned char)((left.second.i[2]*(1-ratio)) + (right.second.i[2]*ratio));
					ret.a = (unsigned char)((left.second.i[3]*(1-ratio)) + (right.second.i[3]*ratio));
					break;
				case VALUE_FLOAT1:
				case VALUE_FLOAT2:
				case VALUE_FLOAT3:
					ret.r = (unsigned char)((left.second.f[0]*(1-ratio)) + (right.second.f[0]*ratio));
					ret.g = (unsigned char)((left.second.f[1]*(1-ratio)) + (right.second.f[1]*ratio));
					ret.b = (unsigned char)((left.second.f[2]*(1-ratio)) + (right.second.f[2]*ratio));
					ret.a = 255;
					break;
				case VALUE_FLOAT4:
					ret.r = (unsigned char)((left.second.f[0]*(1-ratio)) + (right.second.f[0]*ratio));
					ret.g = (unsigned char)((left.second.f[1]*(1-ratio)) + (right.second.f[1]*ratio));
					ret.b = (unsigned char)((left.second.f[2]*(1-ratio)) + (right.second.f[2]*ratio));
					ret.a = (unsigned char)((left.second.f[3]*(1-ratio)) + (right.second.f[3]*ratio));
					break;
			}
			break;
	}
	return true;
}

bool FactorTaskAnimation::getAsPoint(string id, int frame, ofPoint& ret)
{
	if(frame >= length_) {
		return false;
	}
	Sequence& seq = sequences_[id];
	map<int, Key>::iterator it = seq.keys.find(frame);
	if(it != seq.keys.end()) {
		switch(seq.type) {
			case VALUE_INT1:
			case VALUE_INT2:
			case VALUE_INT3:
			case VALUE_INT4:
				ret.x = (float)(*it).second.i[0];
				ret.y = (float)(*it).second.i[1];
				ret.z = (float)(*it).second.i[2];
				break;
			case VALUE_FLOAT1:
			case VALUE_FLOAT2:
			case VALUE_FLOAT3:
			case VALUE_FLOAT4:
				ret.x = (*it).second.f[0];
				ret.y = (*it).second.f[1];
				ret.z = (*it).second.f[2];
				break;
		}
		return true;
	}

	it = seq.keys.upper_bound(frame);
	if(it == seq.keys.begin() || it == seq.keys.end()) {
		return false;
	}
	std::pair<int, Key> right = *(it--);
	std::pair<int, Key> left = (*it);
	if(left.second.ip == Key::IP_END) {
		return false;
	}
	if(left.second.ip == Key::IP_STEP) {
		switch(seq.type) {
			case VALUE_INT1:
			case VALUE_INT2:
			case VALUE_INT3:
			case VALUE_INT4:
				ret.x = (float)left.second.i[0];
				ret.y = (float)left.second.i[1];
				ret.z = (float)left.second.i[2];
				break;
			case VALUE_FLOAT1:
			case VALUE_FLOAT2:
			case VALUE_FLOAT3:
			case VALUE_FLOAT4:
				ret.x = left.second.f[0];
				ret.y = left.second.f[1];
				ret.z = left.second.f[2];
				break;
		}
		return true;
	}
	float ratio = (frame-left.first)/(float)(right.first-left.first);
	switch(left.second.ip) {
		case Key::IP_LINEAR:
			switch(seq.type) {
				case VALUE_INT1:
				case VALUE_INT2:
				case VALUE_INT3:
				case VALUE_INT4:
					ret.x = (left.second.i[0]*(1-ratio)) + (right.second.i[0]*ratio);
					ret.y = (left.second.i[1]*(1-ratio)) + (right.second.i[1]*ratio);
					ret.z = (left.second.i[2]*(1-ratio)) + (right.second.i[2]*ratio);
					break;
				case VALUE_FLOAT1:
				case VALUE_FLOAT2:
				case VALUE_FLOAT3:
				case VALUE_FLOAT4:
					ret.x = (left.second.f[0]*(1-ratio)) + (right.second.f[0]*ratio);
					ret.y = (left.second.f[1]*(1-ratio)) + (right.second.f[1]*ratio);
					ret.z = (left.second.f[2]*(1-ratio)) + (right.second.f[2]*ratio);
					break;
			}
			break;
	}
	return true;
}


/* EOF */
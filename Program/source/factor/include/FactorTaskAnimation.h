/*!
*/
#pragma once

// #define USE_OFX_XML

#include <map>
#include "ofPoint.h"
#include "ofVec3f.h"
#include "ofColor.h"
#ifdef USE_OFX_XML
#include "ofxXmlSettings.h"
#endif // USE_OFX_XML
class FactorTaskAnimation
{
public:
	enum ValueType {
		VALUE_INT1,
		VALUE_INT2,
		VALUE_INT3,
		VALUE_INT4,
		VALUE_FLOAT1,
		VALUE_FLOAT2,
		VALUE_FLOAT3,
		VALUE_FLOAT4,
		VALUE_STRING1,
		VALUE_STRING2,
		VALUE_STRING3,
		VALUE_STRING4,

		VALUE_INT = VALUE_INT1,
		VALUE_FLOAT = VALUE_FLOAT1,
		VALUE_POS2 = VALUE_FLOAT2,
		VALUE_POS3 = VALUE_FLOAT3,
		VALUE_POS = VALUE_POS3,
		VALUE_POINT = VALUE_FLOAT3,
		VALUE_VECTOR = VALUE_FLOAT3,
		VALUE_COLOR3 = VALUE_FLOAT3,
		VALUE_COLOR4 = VALUE_FLOAT4,
		VALUE_COLOR = VALUE_COLOR4,
		VALUE_COLOR3I = VALUE_INT3,
		VALUE_COLOR4I = VALUE_INT4,
		VALUE_COLORI = VALUE_COLOR4I,
		VALUE_STRING = VALUE_STRING1,
	};
public:
	struct Key {
		enum IpType {
			IP_STEP,
			IP_LINEAR,
			IP_END,
		} ip;
		union {
			int i[4];
			float f[4];
		};
		string s[4];
	};
public:
	FactorTaskAnimation();
	~FactorTaskAnimation();
	void setLength(int length){length_=length;}
	int getLength() const{return length_;}
	Key::IpType getIpType(string str);
	
	void beginSequence(string id, ValueType type);
	void beginSequence(string id, string type);
#ifdef USE_OFX_XML
	void addKey(ofxXmlSettings& xml, int which=0);
#endif // USE_OFX_XML
	void addKey(int frame, const Key& key);
	void addKey(int frame, int val0, Key::IpType ip=Key::IP_LINEAR);
	void addKey(int frame, int val0, int val1, Key::IpType ip=Key::IP_LINEAR);
	void addKey(int frame, int val0, int val1, int val2, Key::IpType ip=Key::IP_LINEAR);
	void addKey(int frame, int val0, int val1, int val2, int val3, Key::IpType ip=Key::IP_LINEAR);
	void addKey(int frame, float val0, Key::IpType ip=Key::IP_LINEAR);
	void addKey(int frame, float val0, float val1, Key::IpType ip=Key::IP_LINEAR);
	void addKey(int frame, float val0, float val1, float val2, Key::IpType ip=Key::IP_LINEAR);
	void addKey(int frame, float val0, float val1, float val2, float val3, Key::IpType ip=Key::IP_LINEAR);
	void addKey(int frame, const ofColor& color, Key::IpType ip=Key::IP_LINEAR);
	void addKey(int frame, const ofPoint& point, Key::IpType ip=Key::IP_LINEAR);
	void addKey(int frame, string val0);
	void addKey(int frame, string val0, string val1);
	void addKey(int frame, string val0, string val1, string val2);
	void addKey(int frame, string val0, string val1, string val2, string val3);
	void endSequence();
	void clearSequence();
	
	bool getAsInt(string id, int frame, int* ret);
	bool getAsFloat(string id, int frame, float* ret);
	bool getAsColor(string id, int frame, ofColor& ret);
	bool getAsPoint(string id, int frame, ofPoint& ret);

private:
	struct Sequence {
		ValueType type;
		map<int, Key> keys;
		Sequence(){keys.clear();}
	};
	string current_id_;
	int length_;
	map<string, Sequence> sequences_;
};
/* EOF */
/*!
*/
#pragma once

#include "FactorTask.h"

enum
{
	KEY_LEFT	= 0x00000001,
	KEY_UP		= 0x00000002,
	KEY_RIGHT	= 0x00000004,
	KEY_DOWN	= 0x00000008,
	KEY_0		= 0x00000010,
	KEY_1		= 0x00000020,
	KEY_2		= 0x00000040,
	KEY_3		= 0x00000080,
	KEY_4		= 0x00000100,
	KEY_5		= 0x00000200,
	KEY_6		= 0x00000400,
	KEY_7		= 0x00000800,
	KEY_8		= 0x00001000,
	KEY_9		= 0x00002000,
	KEY_Z		= 0x00004000,
	KEY_X		= 0x00008000,
	KEY_C		= 0x00010000,
	KEY_A		= 0x00020000,
	KEY_S		= 0x00040000,
	KEY_D		= 0x00080000,
	KEY_Q		= 0x00100000,
	KEY_W		= 0x00200000,
	KEY_E		= 0x00400000,
	KEY_SPACE	= 0x00800000,
	KEY_ENTER	= 0x01000000,

	KEY_MAX = 32,
};

class TaskKey : public FactorTask
{
public:
	TaskKey(string id="");
	void update();
	void setRepeatFirst(int frame) { repeat_first_ = frame; }
	void setRepeatSecond(int frame) { repeat_second_ = frame; }

	unsigned int getHold() { return hold_; }
	unsigned int getTrigger() { return trigger_; }
	unsigned int getRelease() { return release_; }
	unsigned int getRepeat() { return repeat_; }

private:
	unsigned int hold_;
	unsigned int trigger_;
	unsigned int release_;
	unsigned int repeat_;

	int repeat_first_;
	int repeat_second_;

	int repeat_frame_count_[KEY_MAX];
};


/* EOF */
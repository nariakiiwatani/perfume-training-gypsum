/*!
*/

#include "TaskKey.h"
#include "ofEvents.h"

namespace
{
	const int table[] = {
		KEY_LEFT,		OF_KEY_LEFT,
		KEY_UP,			OF_KEY_UP,
		KEY_RIGHT,		OF_KEY_RIGHT,
		KEY_DOWN,		OF_KEY_DOWN,
		KEY_0,			'0',
		KEY_1,			'1',
		KEY_2,			'2',
		KEY_3,			'3',
		KEY_4,			'4',
		KEY_5,			'5',
		KEY_6,			'6',
		KEY_7,			'7',
		KEY_8,			'8',
		KEY_9,			'9',
		KEY_Z,			'z',
		KEY_Z,			'Z',
		KEY_X,			'x',
		KEY_X,			'X',
		KEY_C,			'c',
		KEY_C,			'C',
		KEY_A,			'a',
		KEY_S,			's',
		KEY_D,			'd',
		KEY_Q,			'q',
		KEY_W,			'w',
		KEY_E,			'e',
		KEY_SPACE,		' ',
		KEY_ENTER,		OF_KEY_RETURN,
		0
	};
}

TaskKey::TaskKey(string id)
:FactorTask(id)
,hold_(0)
,trigger_(0)
,release_(0)
,repeat_(0)
,repeat_first_(6)
,repeat_second_(3)
{
	for(int i = 0; i < KEY_MAX; ++i) {
		repeat_frame_count_[i] = repeat_first_;
	}
}


void TaskKey::update()
{
	unsigned int pressed = 0;
	if(ofGetKeyPressed()) {
		for(int index = 0; table[index] != 0; index += 2) {
			if(ofGetKeyPressed(table[index+1])) {
				pressed |= table[index];
			}
		}
	}
	release_ = hold_&~pressed;
	trigger_ = pressed&~hold_;
	hold_ = pressed;
	repeat_ = 0;
	for(int i = 0; i < KEY_MAX; ++i) {
		if(hold_ & (1<<i)) {
			if(repeat_frame_count_[i]-- == 0) {
				repeat_ |= (1<<i);
				repeat_frame_count_[i] = repeat_second_;
			}
		}
		else if(release_ & (1<<i)) {
			repeat_frame_count_[i] = repeat_first_;
		}
	}
}

/* EOF */
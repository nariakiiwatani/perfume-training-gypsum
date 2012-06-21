/*!
*/

#include "TaskPose.h"
#include "Factor.h"

TaskPose::TaskPose(string id)
:FactorTask(id)
,translation_()
,rotate_()
,scale_(1,1,1)
,world_matrix_()
,local_matrix_()
,world_matrix_ptr_(&world_matrix_)
,is_local_matrix_identity_(true)
,is_world_matrix_identity_(true)
{
}

TaskPose::~TaskPose()
{
}

void TaskPose::procAnimation(FactorTaskAnimation* animation, string seq_id, int frame, string target, string func)
{
	if(target == "pos") {
		ofVec3f trans;
		if(animation->getAsPoint(seq_id, frame, trans)) {
			if(func == "add") {
				addTranslation(trans);
			}
			else {
				setTranslation(trans);
			}
		}
	}
	else if(target == "scale") {
		ofVec3f scale;
		if(animation->getAsPoint(seq_id, frame, scale)) {
			if(func == "add") {
				addScale(scale);
			}
			else {
				setScale(scale);
			}
		}
	}
	else if(target == "rotx") {
		float rot;
		if(animation->getAsFloat(seq_id, frame, &rot)) {
			if(func == "add") {
				addRotate(rot, 1, 0, 0);
			}
			else {
				setRotate(rot, 1, 0, 0);
			}
		}
	}
	else if(target == "roty") {
		float rot;
		if(animation->getAsFloat(seq_id, frame, &rot)) {
			if(func == "add") {
				addRotate(rot, 0, 1, 0);
			}
			else {
				setRotate(rot, 0, 1, 0);
			}
		}
	}
	else if(target == "rotz") {
		float rot;
		if(animation->getAsFloat(seq_id, frame, &rot)) {
			if(func == "add") {
				addRotate(rot, 0, 0, 1);
			}
			else {
				setRotate(rot, 0, 0, 1);
			}
		}
	}
	else if(target == "rotyxz") {
		float rot[3];
		if(animation->getAsFloat(seq_id, frame, rot)) {
			if(func == "add") {
				addRotate(rot[0], 0, 1, 0);
			}
			else {
				setRotate(rot[0], 0, 1, 0);
			}
			addRotate(rot[1], 1, 0, 0);
			addRotate(rot[2], 0, 0, 1);
		}
	}
	else {
		FactorTask::procAnimation(animation, seq_id, frame, target, func);
	}
}

void TaskPose::setParam(string id, string value, string func)
{
	if(id == "pos") {
		vector<string> values = split(value, ',');
		if(func == "add") {
			addTranslation(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str()));
		}
		else {
			setTranslation(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str()));
		}
	}
	else if(id == "scale") {
		vector<string> values = split(value, ',');
		if(func == "add") {
			addScale(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str()));
		}
		else {
			setScale(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str()));
		}
	}
	else if(id == "rotx") {
		if(func == "add") {
			addRotate(atof(value.c_str()), 1, 0, 0);
		}
		else {
			setRotate(atof(value.c_str()), 1, 0, 0);
		}
	}
	else if(id == "roty") {
		if(func == "add") {
			addRotate(atof(value.c_str()), 0, 1, 0);
		}
		else {
			setRotate(atof(value.c_str()), 0, 1, 0);
		}
	}
	else if(id == "rotz") {
		if(func == "add") {
			addRotate(atof(value.c_str()), 0, 0, 1);
		}
		else {
			setRotate(atof(value.c_str()), 0, 0, 1);
		}
	}
	else {
		FactorTask::setParam(id, value, func);
	}
}

void TaskPose::update()
{
	refreshMatrix();
}

void TaskPose::refreshMatrix()
{
	if(isDirty(LOCAL|PARENT)) {
		if(isDirty(LOCAL)) {
			calcLocalMatrix();
			clsDirtyFlag(LOCAL);
		}
		if(TaskPose* parent = getParent()) {
			if(isDirty(PARENT)) {
				parent->refreshMatrix();
				clsDirtyFlag(PARENT);
			}
			if(parent->isWorldMatrixIdentity()) {
				world_matrix_ptr_ = &local_matrix_;
				is_world_matrix_identity_ = is_local_matrix_identity_;
			}
			else {
				if(isLocalMatrixIdentity()) {
					world_matrix_ptr_ = parent->getWorldMatrix();
				}
				else {
					world_matrix_.makeFromMultiplicationOf(local_matrix_, *parent->getWorldMatrix());
					world_matrix_ptr_ = &world_matrix_;
				}
				is_world_matrix_identity_ = false;
			}
		}
		else {
			world_matrix_ptr_ = &local_matrix_;
			is_world_matrix_identity_ = is_local_matrix_identity_;
		}
	}
}

TaskPose* TaskPose::getParent()
{
	return dynamic_cast<TaskPose*>(FactorTask::getParent());
}

void TaskPose::calcLocalMatrix()
{
	local_matrix_.makeScaleMatrix(scale_);
	local_matrix_.rotate(rotate_);
	local_matrix_.translate(translation_);
	is_local_matrix_identity_ = local_matrix_.isIdentity();
}


void TaskPose::pushSetMatrix()
{
	glPushMatrix();
	glMultMatrixf(world_matrix_ptr_->getPtr());
}

void TaskPose::popMatrix()
{
	glPopMatrix();
}

const ofMatrix4x4* TaskPose::getWorldMatrix() const
{
	return world_matrix_ptr_;
}

const ofMatrix4x4* TaskPose::getLocalMatrix() const
{
	return &local_matrix_;
}

void TaskPose::setTranslation(const ofVec3f& trans)
{
	translation_.set(trans);
	dirty(LOCAL);
}

void TaskPose::setTranslation(float x, float y, float z)
{
	translation_.set(x,y,z);
	dirty(LOCAL);
}

void TaskPose::setRotate(const ofVec3f& from, const ofVec3f& to )
{
    rotate_.makeRotate(from,to);
	dirty(LOCAL);
}
void TaskPose::setRotate(float angle, const ofVec3f& axis )
{
    rotate_.makeRotate(angle, axis);
	dirty(LOCAL);
}

void TaskPose::setRotate(float angle, float x, float y, float z )
{
    rotate_.makeRotate(angle, x, y, z);
	dirty(LOCAL);
}

void TaskPose::setRotate(const ofQuaternion& quat )
{
	rotate_.set(quat);
	dirty(LOCAL);
}

void TaskPose::setRotate(float angle1, const ofVec3f& axis1,
									   float angle2, const ofVec3f& axis2,
									   float angle3, const ofVec3f& axis3)
{
	rotate_.makeRotate(angle1, axis1, angle2, axis2, angle3, axis3);
	dirty(LOCAL);
}

void TaskPose::setScale(const ofVec3f& scale)
{
	scale_.set(scale);
	dirty(LOCAL);
}

void TaskPose::setScale(float x, float y, float z)
{
	scale_.set(x,y,z);
	dirty(LOCAL);
}


void TaskPose::addTranslation(const ofVec3f& trans)
{
	translation_ += trans;
	dirty(LOCAL);
}

void TaskPose::addTranslation(float x, float y, float z)
{
	translation_ += ofVec3f(x,y,z);
	dirty(LOCAL);
}

void TaskPose::addTranslationX(float x)
{
	translation_.x += x;
	dirty(LOCAL);
}
void TaskPose::addTranslationY(float y)
{
	translation_.y += y;
	dirty(LOCAL);
}
void TaskPose::addTranslationZ(float z)
{
	translation_.z += z;
	dirty(LOCAL);
}

void TaskPose::addRotate(const ofVec3f& from, const ofVec3f& to)
{
	ofQuaternion quat;
	quat.makeRotate(from,to);
    rotate_ *= quat;
	dirty(LOCAL);
}
void TaskPose::addRotate(float angle, const ofVec3f& axis)
{
	ofQuaternion quat;
	quat.makeRotate(angle, axis);
    rotate_ *= quat;
	dirty(LOCAL);
}

void TaskPose::addRotate(float angle, float x, float y, float z)
{
	ofQuaternion quat;
	quat.makeRotate(angle, x, y, z);
    rotate_ *= quat;
	dirty(LOCAL);
}

void TaskPose::addRotate(const ofQuaternion& quat)
{
    rotate_ *= quat;
	dirty(LOCAL);
}

void TaskPose::addRotate(float angle1, const ofVec3f& axis1,
									   float angle2, const ofVec3f& axis2,
									   float angle3, const ofVec3f& axis3)
{
	ofQuaternion quat;
	quat.makeRotate(angle1, axis1, angle2, axis2, angle3, axis3);
    rotate_ *= quat;
	dirty(LOCAL);
}

void TaskPose::addScale(const ofVec3f& scale)
{
	scale_ += scale;
	dirty(LOCAL);
}

void TaskPose::addScale(float x, float y, float z)
{
	scale_ += ofVec3f(x,y,z);
	dirty(LOCAL);
}
void TaskPose::addScaleX(float x)
{
	scale_.x += x;
	dirty(LOCAL);
}
void TaskPose::addScaleY(float y)
{
	scale_.y += y;
	dirty(LOCAL);
}
void TaskPose::addScaleZ(float z)
{
	scale_.z += z;
	dirty(LOCAL);
}

void TaskPose::mulScale(const ofVec3f& scale)
{
	scale_ *= scale;
	dirty(LOCAL);
}

void TaskPose::mulScale(float x, float y, float z)
{
	scale_ *= ofVec3f(x,y,z);
	dirty(LOCAL);
}
void TaskPose::mulScaleX(float x)
{
	scale_.x *= x;
	dirty(LOCAL);
}
void TaskPose::mulScaleY(float y)
{
	scale_.y *= y;
	dirty(LOCAL);
}
void TaskPose::mulScaleZ(float z)
{
	scale_.z *= z;
	dirty(LOCAL);
}

/* EOF */
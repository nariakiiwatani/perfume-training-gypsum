/*!
*/
#pragma once

#include "FactorTask.h"
#include "ofMatrix4x4.h"
#include "ofVec3f.h"

class Factor;

class TaskPose : public FactorTask
{
public:
	TaskPose(string id="");
	virtual ~TaskPose();
	void update();
	void pushSetMatrix();
	void popMatrix();
	void setParent(TaskPose* parent);
	TaskPose* getParent();
	virtual void setParam(string id, string value, string func);
	
	const ofMatrix4x4* getWorldMatrix() const;
	const ofMatrix4x4* getLocalMatrix() const;
	const ofVec3f& getTranslation() { return translation_; }
	const ofVec3f& getScale() { return scale_; }
	
	void setTranslation(const ofVec3f& trans);
	void setTranslation(float x, float y, float z);
	void setTranslationX(float x);
	void setTranslationY(float y);
	void setTranslationZ(float z);
	void setRotate(const ofVec3f& from, const ofVec3f& to);
	void setRotate(float angle, const ofVec3f& axis);
	void setRotate(float angle, float x, float y, float z);
	void setRotate(const ofQuaternion& quat);
	void setRotate(float angle1, const ofVec3f& axis1,
	                 float angle2, const ofVec3f& axis2,
	                 float angle3, const ofVec3f& axis3);
	void setScale(const ofVec3f& scale);
	void setScale(float x, float y, float z);
	void setScaleX(float x);
	void setScaleY(float y);
	void setScaleZ(float z);
	
	void addTranslation(const ofVec3f& trans);
	void addTranslation(float x, float y, float z);
	void addTranslationX(float x);
	void addTranslationY(float y);
	void addTranslationZ(float z);
	void addRotate(const ofVec3f& from, const ofVec3f& to);
	void addRotate(float angle, const ofVec3f& axis);
	void addRotate(float angle, float x, float y, float z);
	void addRotateX(float angle);
	void addRotateY(float angle);
	void addRotateZ(float angle);
	void addRotate(const ofQuaternion& quat);
	void addRotate(float angle1, const ofVec3f& axis1,
	                 float angle2, const ofVec3f& axis2,
	                 float angle3, const ofVec3f& axis3);
	void addScale(const ofVec3f& scale);
	void addScale(float x, float y, float z);
	void addScaleX(float x);
	void addScaleY(float y);
	void addScaleZ(float z);
	void mulScale(const ofVec3f& scale);
	void mulScale(float x, float y, float z);
	void mulScaleX(float x);
	void mulScaleY(float y);
	void mulScaleZ(float z);

protected:
	virtual void calcLocalMatrix();
	virtual void procAnimation(FactorTaskAnimation* animation, string seq_id, int frame, string target, string func);

private:
	void refreshMatrix();
	bool isLocalMatrixIdentity() const{return is_local_matrix_identity_;}
	bool isWorldMatrixIdentity() const{return is_world_matrix_identity_;}

private:
	const ofMatrix4x4* world_matrix_ptr_;
	ofMatrix4x4 world_matrix_;
	ofMatrix4x4 local_matrix_;
	ofVec3f translation_;
	ofQuaternion rotate_;
	ofVec3f scale_;

	bool is_local_matrix_identity_;
	bool is_world_matrix_identity_;
};


/* EOF */
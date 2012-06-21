/*!
*/

#include "CustomJoint.h"
#include "DeviceTask.h"
#include "ofxTrackedUser.h"
#include "ofMath.h"

CustomJoint::CustomJoint()
:FactorTask()
,source_(NULL)
,hip_2d_(0,0)
,valid_(false)
{
}

namespace {
ofVec3f Lerp(XnPoint3D a, XnPoint3D b, float ratio)
{
	static const double fx_d = 1.0 / 5.9421434211923247e+02;
	static const double fy_d = 1.0 / 5.9104053696870778e+02;
	static const float cx_d = 3.3930780975300314e+02;
	static const float cy_d = 2.4273913761751615e+02;
	ofVec3f result;
	result.x = ofLerp(a.X,b.X,ratio);
	result.y = ofLerp(a.Y,b.Y,ratio);
	result.z = 0.1f*ofLerp(a.Z,b.Z,ratio);
	result.x = float((result.x - cx_d) * result.z * fx_d);
	result.y = float((result.y - cy_d) * result.z * fy_d);

	return result;
}
ofVec3f Lerp(const ofxLimb& limb, float ratio)
{
	return Lerp(limb.position[0], limb.position[1], ratio);
}
ofVec2f Lerp2D(XnPoint3D a, XnPoint3D b, float ratio)
{
	ofVec2f result;
	result.x = ofLerp(a.X,b.X,ratio);
	result.y = ofLerp(a.Y,b.Y,ratio);
	return result;
}
ofVec2f Lerp2D(const ofxLimb& limb, float ratio)
{
	return Lerp2D(limb.position[0], limb.position[1], ratio);
}
ofVec3f GetAdjuster(const ofVec3f& l, const ofVec3f& r, float length)
{
	ofVec3f ret = l-r;
	float scale = length/ret.length();
	return ret*(1-scale);
}
ofVec3f GetAdjuster(const ofVec3f& l, const ofVec3f& r, const ofVec3f& base)
{
	return GetAdjuster(l, r, base.length());
}
}
void CustomJoint::update()
{
	if(ofxTrackedUser* user = source_ ? source_->getTrackedUser(0):NULL) {
		valid_ = true;
		
		hip_2d_ = Lerp2D(user->hip, 0.5f);
		neck_ = Lerp(user->neck, 1);
		head_ = Lerp(user->neck, 0);
		l_sh_ = Lerp(user->left_shoulder, 1);
		l_el_ = Lerp(user->left_upper_arm, 1);
		l_wr_ = Lerp(user->left_lower_arm, 1);
		l_hi_ = Lerp(user->hip, 0);
		l_kn_ = Lerp(user->left_upper_leg, 1);
		l_an_ = Lerp(user->left_lower_leg, 1);
		r_sh_ = Lerp(user->right_shoulder, 1);
		r_el_ = Lerp(user->right_upper_arm, 1);
		r_wr_ = Lerp(user->right_lower_arm, 1);
		r_hi_ = Lerp(user->hip, 1);
		r_kn_ = Lerp(user->right_upper_leg, 1);
		r_an_ = Lerp(user->right_lower_leg, 1);

		hips_ = Lerp(user->hip, 0.5f);
		/**/
		ofVec3f adj;
		// 上半身
		adj = GetAdjuster(hips_, neck_, ofVec3f(0, 53.664107, -0.005128));
		neck_ += adj;
		l_sh_ += adj;
		l_el_ += adj;
		l_wr_ += adj;
		r_sh_ += adj;
		r_el_ += adj;
		r_wr_ += adj;
		adj = GetAdjuster(neck_, head_, ofVec3f(0, 25.786, -0.041299));
		head_ += adj;
		// 上半身左
		adj = GetAdjuster(neck_, l_sh_, ofVec3f(16.6956, 7.545150, 0));
		l_sh_ += adj;
		l_el_ += adj;
		l_wr_ += adj;
		adj = GetAdjuster(l_sh_, l_el_, ofVec3f(26.359998, 0, 0));
		l_el_ += adj;
		l_wr_ += adj;
		adj = GetAdjuster(l_el_, l_wr_, ofVec3f(21.746691, 0, 0.008601));
		l_wr_ += adj;
		// 上半身右
		adj = GetAdjuster(neck_, r_sh_, ofVec3f(-16.6956, 7.545150, 0));
		r_sh_ += adj;
		r_el_ += adj;
		r_wr_ += adj;
		adj = GetAdjuster(r_sh_, r_el_, ofVec3f(-26.359998, 0, 0));
		r_el_ += adj;
		r_wr_ += adj;
		adj = GetAdjuster(r_el_, r_wr_, ofVec3f(-21.746691, 0, 0.008601));
		r_wr_ += adj;
		// 左足
		adj = GetAdjuster(hips_, l_hi_, ofVec3f(8.622479, -0.030774, -0.003140));
		l_hi_ += adj;
		l_kn_ += adj;
		l_an_ += adj;
		adj = GetAdjuster(l_hi_, l_kn_, ofVec3f(0, -37.209160, -0.058479));
		l_kn_ += adj;
		l_an_ += adj;
		adj = GetAdjuster(l_kn_, l_an_, ofVec3f(0, -46.246744, 15.029));
		l_an_ += adj;
		// 右足
		adj = GetAdjuster(hips_, r_hi_, ofVec3f(-8.622479, -0.030774, -0.003140));
		r_hi_ += adj;
		r_kn_ += adj;
		r_an_ += adj;
		adj = GetAdjuster(r_hi_, r_kn_, ofVec3f(0, -37.209160, -0.058479));
		r_kn_ += adj;
		r_an_ += adj;
		adj = GetAdjuster(r_kn_, r_an_, ofVec3f(0, -46.246744, 15.029));
		r_an_ += adj;
	}
	else {
		valid_ = false;
	}
}


/* EOF */
/*!
*/
#pragma once

class DeviceTask;
class BvhTask;
class VideoDraw;
class SkeletonDraw;
class ModelDraw;
class TaskPose;
class TaskKey;
class ofCamera;
class CameraControl;
class FloorDraw;
class FrameControl;
class SkeletonDrawTransformed;
class PoseControl;
class CustomJoint;
class PoseCheck;

class AppManager
{
public:
	void init();
	void exit();

private:
	DeviceTask* device_;
	BvhTask* model_;
	TaskPose* model_pose_;
	TaskKey* keyboard_;
	TaskPose* skeleton_pose_;
	CustomJoint* custom_joint_;
	VideoDraw* video_draw_;
	SkeletonDraw* skeleton_draw_;
	SkeletonDrawTransformed* skeleton_draw_transformed_;
	ModelDraw* model_draw_;
	CameraControl* camera_control_;
	FrameControl* frame_control_;
	PoseControl* pose_control_;
	FloorDraw* floor_draw_;
	PoseCheck* pose_check_;
	ofCamera* camera_;
};

/* EOF */
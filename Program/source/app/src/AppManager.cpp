
#include "AppManager.h"
#include "DeviceTask.h"
#include "BvhTask.h"
#include "VideoDraw.h"
#include "SkeletonDraw.h"
#include "ModelDraw.h"
#include "TaskPose.h"
#include "TaskKey.h"
#include "ofCamera.h"
#include "CameraControl.h"
#include "FloorDraw.h"
#include "FrameControl.h"
#include "PoseControl.h"
#include "CustomJoint.h"
#include "PoseCheck.h"
#include <stdlib.h>

void AppManager::init()
{
	ofDisableDataPath();
	printf("select bvh data...\n");
	ofFileDialogResult bvh = ofSystemLoadDialog("select a bvh data.", false);
	if(bvh.bSuccess) {
		model_ = new BvhTask(bvh.getPath());
	}
	else {
		abort();
	}
	pose_check_ = new PoseCheck();
	printf("select folder to save images...\n");
	ofFileDialogResult folder = ofSystemLoadDialog("select a folder to save images...", true);
	if(folder.bSuccess) {
		pose_check_->setFolder(folder.getPath());
	}
	else {
		abort();
	}
	camera_ = new ofCamera();

	device_ = new DeviceTask();
	model_pose_ = new TaskPose();
	skeleton_pose_ = new TaskPose();
	keyboard_ = new TaskKey();
	custom_joint_ = new CustomJoint();

	video_draw_ = new VideoDraw();
	video_draw_->bindTask("source", device_);
	
	skeleton_draw_ = new SkeletonDraw();
	skeleton_draw_->bindTask("source", device_);

	custom_joint_->setSource(device_);
	
	skeleton_draw_transformed_ = new SkeletonDrawTransformed();
	skeleton_draw_transformed_->bindTask("source", custom_joint_);
	skeleton_draw_transformed_->bindTask("transform", skeleton_pose_);
	skeleton_draw_transformed_->setCamera(camera_);

	model_draw_ = new ModelDraw();
	model_draw_->bindTask("source", model_);
	model_draw_->bindTask("pose", model_pose_);
	model_draw_->setCamera(camera_);

	camera_control_ = new CameraControl();
	camera_control_->bindTask("keyboard", keyboard_);
	camera_control_->bindTask("model", model_);
	camera_control_->setCamera(camera_);

	pose_control_ = new PoseControl();
	pose_control_->bindTask("keyboard", keyboard_);
	pose_control_->bindTask("pose", skeleton_pose_);
	pose_control_->bindTask("model", model_);
	pose_control_->bindTask("source", device_);

	frame_control_ = new FrameControl();
	frame_control_->bindTask("keyboard", keyboard_);
	frame_control_->bindTask("model", model_);

	floor_draw_ = new FloorDraw();
	floor_draw_->setCamera(camera_);

	pose_check_->bindTask("source", custom_joint_);
	pose_check_->bindTask("model", model_);
	pose_check_->bindTask("keyboard", keyboard_);
	pose_check_->bindTask("device", device_);
}

void AppManager::exit()
{
	delete device_;
	delete model_;
	delete model_pose_;
	delete keyboard_;
	delete skeleton_pose_;
	delete custom_joint_;
	delete video_draw_;
	delete skeleton_draw_;
	delete skeleton_draw_transformed_;
	delete model_draw_;
	delete camera_control_;
	delete frame_control_;
	delete pose_control_;
	delete floor_draw_;
	delete pose_check_;
	delete camera_;
}




/* EOF */
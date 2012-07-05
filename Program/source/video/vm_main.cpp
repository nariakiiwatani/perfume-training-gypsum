
#include "ofxQtVideoSaver.h"
#include "ofImage.h"
#include "ofUtils.h"
#include "ofSystemUtils.h"

void main()
{
	ofxQtVideoSaver qt;
	/**/
	ofImage image;
	ofFileDialogResult result;
	
	ofDisableDataPath();

	printf("select img folder...\n");
	result = ofSystemLoadDialog("choose img folder.", true);
	if(!result.bSuccess) {
		return;
	}
	printf("searching images...\n");
	ofDirectory dir(result.getPath());
	dir.allowExt("jpg");
	int img_num = dir.listDir();
	if(img_num < 1) {
		return;
	}
	dir.sort();
	printf("select sound file...(optional)\n");
	result = ofSystemLoadDialog("select sound file...", false);
	string sound_file = "";
	if(result.bSuccess) {
		sound_file = result.getPath();
	}
	double frame_length = img_num/(double)(40*2819);
	printf("frame length:%f\n", frame_length);
	printf("select path to save movie...\n");
	result = ofSystemSaveDialog("perfume_global_site_project.mov", "save movie.");
	if(!result.bSuccess) {
		return;
	}
	image.loadImage(dir.getPath(0));
//	qt.setCodecQualityLevel(OF_QT_SAVER_CODEC_QUALITY_LOSSLESS);
	qt.setup((int)image.getWidth(), (int)image.getHeight(), result.getPath());
	if(sound_file!="") {
		qt.addAudioTrack(sound_file);
	}
	printf("select sound file...\n");
	printf("processing...(%d/%d)\n", 0, img_num);
	qt.addFrame(image.getPixels(), frame_length);
	
	for(int i = 1; i < img_num; ++i) {
		printf("processing...(%d/%d)\n", i, img_num);
		image.loadImage(dir.getPath(i));
		qt.addFrame(image.getPixels(), frame_length);
	}
	qt.finishMovie();
	/**/
}

/* EOF */
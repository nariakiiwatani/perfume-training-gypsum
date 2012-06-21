
#include "ofMain.h"
#include "PrfmRSM.h"
#include "PrfmRSMDef.h"
#include "ofAppGlutWindow.h"

void main()
{
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, SCREEN_WIDTH, SCREEN_HEIGHT, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	PrfmRSM* app =  new PrfmRSM();
	ofSetFrameRate(40);
	ofRunApp(app);
	delete app;
}

/* EOF */
#ifndef _TEST_APP
#define _TEST_APP

#define _USE_LIVE_VIDEO

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "ofxGuiApp.h"


class testApp : public ofxGuiApp{

	public:

		void setup();
		void update();
		void draw();
	
		void setupGui();
		void handleGui(int parameterId, int task, void* data, int length);

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

        #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabber;
		#else
		  ofVideoPlayer 		vidPlayer;
		#endif
		
        ofxCvColorImage		colorImg;
        ofxCvGrayscaleImage grayImage;

		int 				threshold;
		bool				bLearnBakground;
		float				bkg;
	
		ofImage				paperTexture;
	
		ofxCvColorImage		hsvImage;
		ofxCvColorImage		medianImg;
		ofxCvGrayscaleImage satImage;
		ofxCvGrayscaleImage	trsImage;
		ofxCvGrayscaleImage cannyImage;

		
		CvSeq*				lines;
		CvSeq*				fillContours;
		CvSeq*				edgeContours;
	
		CvMemStorage*		linesStorage;
		CvMemStorage*		fillsStorage;
		CvMemStorage*		edgesStorage;
		CvMemStorage*		approxStorage;
	
		float				kx;
		float				ky;
	
		int					cw;
		int					ch;
		float				sb;
		float				br;
	
		int					mode;
	
		bool				draw_contours;
		bool				draw_edges;
		bool				draw_approx;
		bool				draw_fills;
		bool				erase_bg;
	
		static const int	MODE_PROCESS = 0x00;
		static const int	MODE_DRAWING = 0x01;
	
		int					medianValue;
		int					adaptiveThreshValue;
	
		int					cannyThresh1Value;		
		int					cannyThresh2Value;	
		int					cannyApertureValue;	
	
		int					lineThreshValue;
		int					lineMinLengthValue;
		int					lineMaxGapValue;
		int					contourSmoothValue;
	
		int					approxValue;
		int					fillsAlphaValue;
		int					fillsApproxValue;
		int					approxAlphaValue;
		int					contourAlphaValue;
		int					clearBGAlphaValue;
		bool				doFillsApproxValue;
	
	
	
};

#endif

#include "testApp.h"
#include "gui.h"

#define PROBABILISTIC_LINE 1


//--------------------------------------------------------------
void testApp::setup(){

	// CAPTURE RESOLUTION
	cw = 720;
	ch = 576;
	
	
	
	sb = 15.0;
	br = 3.0;
	
	// START VALUES
	medianValue		    =  1;
	lineThreshValue     = 50;
	lineMinLengthValue  = 24;
	lineMaxGapValue     =  4;
	cannyThresh1Value   =  5;
	cannyThresh2Value   = 20;
	cannyApertureValue  =  3;
	adaptiveThreshValue = 25;
	approxValue			= 10;
	contourSmoothValue  =  1;
	
	fillsAlphaValue		= 0x20;
	fillsApproxValue    = 10;
	contourAlphaValue	= 0x40;
	approxAlphaValue	= 0x40;
	clearBGAlphaValue   = 0x20;
	
	doFillsApproxValue	= false;

	
	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
//		vidGrabber.setDeviceID(3);
        vidGrabber.initGrabber(cw,ch);
	#else
        vidPlayer.loadMovie("fingers.mov");
        vidPlayer.play();
	#endif

    colorImg  .allocate(cw, ch);
	grayImage .allocate(cw, ch);
	hsvImage  .allocate(cw, ch);
	satImage  .allocate(cw, ch);
	trsImage  .allocate(cw, ch);
	cannyImage.allocate(cw, ch);
	medianImg .allocate(cw, ch);

	bLearnBakground = true;
	threshold = 80;
	
	linesStorage = cvCreateMemStorage(0);
	fillsStorage = cvCreateMemStorage(0);
	edgesStorage = cvCreateMemStorage(0);
	approxStorage = cvCreateMemStorage(0);
	
	mode = MODE_PROCESS;
	draw_contours = false;
	draw_approx   = false;
	draw_edges	  = false;
	draw_fills	  = true;
	erase_bg	  = true;
	
	edgeContours = NULL;
	fillContours = NULL;
	lines	     = NULL;
	
	
	
	paperTexture.loadImage("paper6.jpg");
	
	ofSetBackgroundAuto(erase_bg);
	
}

//--------------------------------------------------------------
void testApp::update(){
	

    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.grabFrame();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.idleMovie();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){

		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels(), cw,ch);
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels(), cw,ch);
        #endif

		
		kx = (float) ofGetWidth()  / cw;
		ky = (float) ofGetHeight() / ch;
		
		cvSmooth(colorImg.getCvImage(), medianImg.getCvImage(), CV_MEDIAN, medianValue, medianValue);
		medianImg.flagImageChanged();
				
		grayImage = medianImg;
		
		cvCvtColor(colorImg.getCvImage(), hsvImage.getCvImage(), CV_RGB2HSV);
		hsvImage.flagImageChanged();
		
		cvSetImageCOI(hsvImage.getCvImage(), 2);
		cvCopy(hsvImage.getCvImage(), satImage.getCvImage());
		satImage.flagImageChanged();
		cvSetImageCOI(hsvImage.getCvImage(), 0);
		
		//cvSmooth(satImage.getCvImage(), satImage.getCvImage(), CV_BLUR, 3, 3, 0, 0);
		
		cvAdaptiveThreshold(grayImage.getCvImage(), trsImage.getCvImage(), 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, adaptiveThreshValue);
		//cvCanny(trsImage.getCvImage(), trsImage.getCvImage(), sb, sb*4, 3);
		trsImage.flagImageChanged();
		
		
//		cvSmooth(satImage.getCvImage(), satImage.getCvImage(), CV_MEDIAN, 7, 7);
		
//		cvSmooth( iplImage, iplImage, CV_BLUR, br, br, 0, 0 );
//		cvSmooth( iplImage, iplImage, CV_MEDIAN, 7, 7);
		cvCanny(  grayImage.getCvImage(), cannyImage.getCvImage(), cannyThresh1Value, cannyThresh2Value, cannyApertureValue);
		cannyImage.flagImageChanged();
			
		//cvPyrMeanShiftFiltering(colorImg.getCvImage(), colorImg.getCvImage(), 20, 40, 2);
		
		if (mode==MODE_DRAWING) {

			if (draw_edges) {

				#if PROBABILISTIC_LINE
					lines = cvHoughLines2( cannyImage.getCvImage(), linesStorage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, lineThreshValue, lineMinLengthValue, lineMaxGapValue );
				#else
					lines = cvHoughLines2( cannyImage.getCvImage(), linesStorage, CV_HOUGH_STANDARD, 1, CV_PI/180, 100, 0, 0 );
				#endif
			
			}
			
			if (draw_contours || draw_approx) {
				cvFindContours(cannyImage.getCvImage(), edgesStorage, &edgeContours);
				
				CvSeq* contour = edgeContours;
				while (contour!=NULL) {
					for (int j = 0; j < contour->total; j++){
						CvPoint* p1 = CV_GET_SEQ_ELEM(CvPoint, contour, j);
						p1->x = p1->x*(float)kx;
						p1->y = p1->y*(float)ky;
					}
					contour = contour->h_next;
				}
				
			}

			if (draw_fills) {
				cvFindContours(trsImage.getCvImage(), fillsStorage, &fillContours);
				
				CvSeq* contour = fillContours;
				while (contour!=NULL) {
					for (int j = 0; j < contour->total; j++){
						CvPoint* p1 = CV_GET_SEQ_ELEM(CvPoint, contour, j);
						p1->x = p1->x*(float)kx;
						p1->y = p1->y*(float)ky;
					}
					contour = contour->h_next;
				}
			}
		}

	}
	
	
	// update scope
//	float* rand = new float[50];
//	for(int i=0 ;i<50; i++){
//		rand[i] = ofRandom(-1.0,1);
//		
//	}
//	
//	gui->update(scope, kofxGui_Set_FloatArray, rand, sizeof(float*));
//	
//	// make 3 seconds loop
//	float f = ((ofGetElapsedTimeMillis()%3000) / 3000.0);
//	gui->update(points, kofxGui_Set_Float, &f, sizeof(float));

}

//--------------------------------------------------------------
void testApp::draw(){

	int l = 0;
	
	switch (mode) {
			
		case MODE_PROCESS:
			
			ofBackground(100,100,100);
			
			// draw the incoming, the grayscale, the bg and the thresholded difference
			ofSetColor(0xffffff);
			
			colorImg  .draw( 320*((l++)%3), (l/3)*240, 320, 240 );
			medianImg .draw( 320*((l++)%3), (l/3)*240, 320, 240 );
			grayImage .draw( 320*((l++)%3), (l/3)*240, 320, 240 );
			cannyImage.draw( 320*((l++)%3), (l/3)*240, 320, 240 );

			hsvImage  .draw( 320*((l++)%3), (l/3)*240, 320, 240 );
			satImage  .draw( 320*((l++)%3), (l/3)*240, 320, 240 );
			trsImage  .draw( 320*((l++)%3), (l/3)*240, 320, 240 );
			
			ofSetColor(0xffffff);
			char reportStr[1024];
			sprintf(reportStr, "bg subtraction and blob detection\npress ' ' to capture bg\nthreshold %i (press: +/-)\n, fps: %f", threshold, ofGetFrameRate());
			ofDrawBitmapString(reportStr, 20, 600);
			
			break;
			
		case MODE_DRAWING:
			
			if(!erase_bg) {
				ofEnableAlphaBlending();
				ofSetColor(0xFF, 0xFF, 0xFF, clearBGAlphaValue);
			} else {
				ofSetColor(0xFF, 0xFF, 0xFF);
			}
			ofFill();
			paperTexture.draw(0,0,ofGetWidth(), ofGetHeight());
			
			
//			glEnable(GL_BLEND); 
//			glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
//			grayImage.draw(0, 0, ofGetWidth(), ofGetHeight());
//			glDisable(GL_BLEND);

			ofNoFill();
			ofEnableAlphaBlending();
			
			// FILLS
			
			if (draw_fills && fillContours) {
				
				
				unsigned char* cc = colorImg.getPixels();
				float rr, gg, bb;
				
				CvSeq* contour = fillContours;  
				
				if (doFillsApproxValue) {
				
					while (contour!=NULL) {
						
						CvSeq* approx = cvApproxPoly(contour, sizeof(CvContour), approxStorage, CV_POLY_APPROX_DP, fillsApproxValue);
						
						CvRect br = cvBoundingRect(approx, 0);
						int cx = (br.x+br.width /2.0) / (float) kx;
						int cy = (br.y+br.height/2.0) / (float) ky;
						ofSetColor((int) cc[cx + cy*cw + 0], 
								   (int) cc[cx + cy*cw + 1], 
								   (int) cc[cx + cy*cw + 2], 
								   fillsAlphaValue);
						ofFill();
						ofBeginShape();
						for (int j = 0; j < approx->total; j++){
							CvPoint* p = CV_GET_SEQ_ELEM(CvPoint, approx, j);
							ofVertex(p->x, p->y);
						}
						ofEndShape(true);
						ofNoFill();
						
						contour = contour->h_next;
					}
				
				} else {
				
					// SMOTH FILL CONTOUR
					while (contour!=NULL) {
						for (int j = 0; j < contour->total; j++){
							CvPoint* p1 = CV_GET_SEQ_ELEM(CvPoint, contour, j);
							CvPoint* p2 = CV_GET_SEQ_ELEM(CvPoint, contour, (j+1) % contour->total);
							p1->x += p2->x; p1->x /= 2.0;
							p1->y += p2->y; p1->y /= 2.0;
						}
						contour = contour->h_next;
					}
					
					contour = fillContours;  
					
					while (contour!=NULL) {
						
						// GET FILL COLOR FROM IMAGE
						CvRect br = cvBoundingRect(contour, 0);
						int cx = (br.x+br.width /2.0) / (float) kx;
						int cy = (br.y+br.height/2.0) / (float) ky;
						ofSetColor((int) cc[cx + cy*cw + 0], 
								   (int) cc[cx + cy*cw + 1], 
								   (int) cc[cx + cy*cw + 2], 
								   fillsAlphaValue);
						// DRAW FILL
						ofFill();
						ofBeginShape();
						for (int j = 0; j < contour->total; j++){
							CvPoint* p = CV_GET_SEQ_ELEM(CvPoint, contour, j);
							ofVertex(p->x, p->y);
						}
						ofEndShape(true);
						ofNoFill();
						
						contour = contour->h_next;
					}
				}
			}
			
			// LINES
			
			if (draw_edges && lines) {
//				glColor4f(0.4, 0.2, 0.1, erase_bg ? 0.5 : 0.2);
				glColor4f(1.0, 0.9, 0.8, erase_bg ? 0.5 : 0.2);
				ofSetLineWidth(2.0);
				#if PROBABILISTIC_LINE
					for( int i = 0; i <lines->total; i++ ) {
						
						CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
						int dx = line[1].x - line[0].x; 
						int dy = line[1].y - line[0].y; 
						line[0].x -= dx*0.1;
						line[0].y -= dy*0.1;
						line[1].x += dx*0.1;
						line[1].y += dy*0.1;
						ofLine( line[0].x*kx, line[0].y*ky, line[1].x*kx, line[1].y*ky );
					}
				#else
					for( int i = 0; i < MIN(lines->total, 25); i++ ) {
						
						float* line = (float*)cvGetSeqElem(lines,i);
						float rho = line[0];
						float theta = line[1];
						CvPoint pt1, pt2;
						double a = cos(theta), b = sin(theta);
						double x0 = a*rho, y0 = b*rho;
						pt1.x = cvRound(x0 + 1000*(-b));
						pt1.y = cvRound(y0 + 1000*( a));
						pt2.x = cvRound(x0 - 1000*(-b));
						pt2.y = cvRound(y0 - 1000*( a));
						ofLine( pt1.x*kx, pt1.y*ky, pt2.x*kx, pt2.y*ky );
					}
				#endif				
				ofSetLineWidth(1.0);
			}
			
			// APPROX EDGES
			
			if (draw_approx && edgeContours) {
				
				CvSeq* contour = edgeContours;
				ofSetColor(0x60, 0x20, 0x10, approxAlphaValue);
				
				while (contour!=NULL) {
					
					CvSeq* approx = cvApproxPoly(contour, sizeof(CvContour), approxStorage, CV_POLY_APPROX_DP, approxValue);

					ofBeginShape();
					for (int j = 0; j < approx->total; j++){
						CvPoint* p = CV_GET_SEQ_ELEM(CvPoint, approx, j);
						ofVertex(p->x, p->y);
					}
					ofEndShape(true);
					
					contour = contour->h_next;
				}
			}
			
			
			// CONTOURS
			if (draw_contours && edgeContours) {
				
				// SMOOTH
				for (int i=0;i<contourSmoothValue; ++i) {
					CvSeq* contour = edgeContours;
					while (contour!=NULL) {
						for (int j = 0; j < contour->total; j++){
							CvPoint* p1 = CV_GET_SEQ_ELEM(CvPoint, contour, j);
							CvPoint* p2 = CV_GET_SEQ_ELEM(CvPoint, contour, (j+1) % contour->total);
							p1->x += p2->x; p1->x /= 2.0;
							p1->y += p2->y; p1->y /= 2.0;
						}
						contour = contour->h_next;
					}
				}
				
				CvSeq* contour = edgeContours;
				
				ofSetColor(0x60, 0x20, 0x10, contourAlphaValue);
				
				while (contour!=NULL) {
					
					ofBeginShape();
					for (int j = 0; j < contour->total; j++){
						CvPoint* p = CV_GET_SEQ_ELEM(CvPoint, contour, j);
						ofVertex(p->x, p->y);
					}
					ofEndShape(true);
					
					contour = contour->h_next;
				}
			}
			
			
		
			break;
			
		default:
			break;
	}

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
			
		case '0':
			mode = MODE_PROCESS;
			break;
			
		case '1':
			mode = MODE_DRAWING;
			
			break;
			
		case 'c': 
			draw_contours ^= 1;
			break;
			
		case 'e': 
			draw_edges ^= 1;
			break;

		case 'a': 
			draw_approx ^= 1;
			break;
			
		case 'f': 
			draw_fills ^= 1;
			break;
			
		case 'b':
			erase_bg ^= 1;
			ofSetBackgroundAuto(erase_bg);
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}


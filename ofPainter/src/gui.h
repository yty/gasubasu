#ifndef _GUI
#define _GUI

const string tags[] =
{
	"PROCESS",
	"DRAWING",
};

enum {
	medianSlider,
	adaptiveThreshSlider,
	cannyThresh1Slider,
	cannyThresh2Slider,
	cannyApertureSlider,
	
	approxSlider,
	contourSmoothSlider,
	
	lineThreshSlider,
	lineMinLengthSlider,
	lineMaxGapSlider,
	
	drawFillsButton,
	approxFillsButton,
	fillsApproxSlider,
	fillsAlphaSlider,
	
	drawContourButton,
	contourAlphaSlider,
	
	drawApproxButton,
	approxAlphaSlider,
	
	drawLinesButton,
	linesAlphaSlider,
	
	clearBGButton,
	clearBGSlider,
	
	debugModeSwitch,
};

void testApp::setupGui(){
	
	ofxGuiPanel	*processingPanel = gui->addPanel(0, "processing", 10, 10, 12, OFXGUI_PANEL_SPACING);
	
	processingPanel->addSlider(medianSlider        , "MEDIAN"         , 125, 8, 0,  25,  1, kofxGui_Display_Int, 1);
	processingPanel->addSlider(cannyThresh1Slider  , "CANNY THRESH 1" , 125, 8, 0, 255,  5, kofxGui_Display_Int, 1);
	processingPanel->addSlider(cannyThresh2Slider  , "CANNY THRESH 2" , 125, 8, 0, 255, 20, kofxGui_Display_Int, 1);
	processingPanel->addSlider(cannyApertureSlider , "CANNY APERTURE" , 125, 8, 1,   3,  1, kofxGui_Display_Int, 1);
	processingPanel->addSlider(adaptiveThreshSlider, "ADAPTIVE THRESH", 125, 8, 1, 100, 12, kofxGui_Display_Int, 1);

	processingPanel->addSwitch(debugModeSwitch, "MODE", 125, 25, 0, 1, 0, &tags[0]);
	
	ofxGuiPanel	*drawingPanel = gui->addPanel(0, "drawing", ofGetWidth()-160, 10, 12, OFXGUI_PANEL_SPACING);

	drawingPanel->addButton(clearBGButton, "CLEAR BG"   ,   8, 8, kofxGui_Button_On , kofxGui_Button_Switch, "");
	drawingPanel->addSlider(clearBGSlider, "CLEAR ALPHA", 125, 8, 0, 255, 0x20, kofxGui_Display_Int, 1);
	
	drawingPanel->addButton(drawFillsButton  , "DRAW FILLS"  ,   8, 8, kofxGui_Button_On , kofxGui_Button_Switch, "");
	drawingPanel->addSlider(fillsAlphaSlider , "FILLS ALPHA" , 125, 8, 0, 255, 0x20, kofxGui_Display_Int, 1);

	drawingPanel->addButton(approxFillsButton, "APPROX FILLS",   8, 8, kofxGui_Button_Off , kofxGui_Button_Switch, "");
	drawingPanel->addSlider(fillsApproxSlider, "APPROX VALUE", 125, 8, 1,  99, 10, kofxGui_Display_Int, 1);

	
	drawingPanel->addButton(drawContourButton  , "DRAW CONT"  ,   8, 8, kofxGui_Button_Off, kofxGui_Button_Switch, "");
	drawingPanel->addSlider(contourAlphaSlider , "CONT ALPHA" , 125, 8, 0, 255, 0x40, kofxGui_Display_Int, 1);
	drawingPanel->addSlider(contourSmoothSlider, "CONT SMOOTH", 125, 8, 0, 25, 1, kofxGui_Display_Int, 1);

	drawingPanel->addButton(drawApproxButton , "APPROX CONT" ,   8, 8, kofxGui_Button_Off, kofxGui_Button_Switch, "");
	drawingPanel->addSlider(approxAlphaSlider, "CONT ALPHA", 125, 8, 0, 255, 0x40, kofxGui_Display_Int, 1);
	drawingPanel->addSlider(approxSlider     , "APPROX VALUE", 125, 8, 1,  99, 10, kofxGui_Display_Int, 1);
	
	drawingPanel->addButton(drawLinesButton    , "DRAW LINES"    ,   8, 8, kofxGui_Button_Off, kofxGui_Button_Switch, "");
	drawingPanel->addSlider(lineThreshSlider   , "LINE THRESH"   , 125, 8, 1,  99, 50, kofxGui_Display_Int, 1);
	drawingPanel->addSlider(lineMinLengthSlider, "LINE MIN LEN"  , 125, 8, 1, 255, 24, kofxGui_Display_Int, 1);
	drawingPanel->addSlider(lineMaxGapSlider   , "LINE MAX GAP"  , 125, 8, 0, 100,  4, kofxGui_Display_Int, 1);
	
//	sliderAndKnobs->addKnob(knob, "knob", 55, 55, 0, 255, 128, kofxGui_Display_Int, 50);
//	sliderAndKnobs->addColor(colorRGB, "colorRGB", 125, 30, ofRGBA(178,0,205,255), kofxGui_Color_RGB);
//	sliderAndKnobs->addColor(colorRGBA, "colorRGBA", 125, 40, ofRGBA(68,25,180,125), kofxGui_Color_RGBA);
//	sliderAndKnobs->addXYPad(xyPad, "XYPad", ofGetWidth()/6,ofGetHeight()/6, ofxPoint2f(0,0), ofxPoint2f(ofGetWidth(),ofGetHeight()),ofxPoint2f(350, 520), kofxGui_Display_Int, 1);
	
//	ofxGuiPanel	*buttonsAndMatrix = gui->addPanel(0, "Buttons&Matrix", 215, 20, 12, OFXGUI_PANEL_SPACING);
//	buttonsAndMatrix->addButton(triggerButton, "triggerButton", 10, 10, kofxGui_Button_Off, kofxGui_Button_Trigger, "");
//	buttonsAndMatrix->addButton(switchButton, "switchButton", 10, 10, kofxGui_Button_Off, kofxGui_Button_Switch, "");
//	buttonsAndMatrix->addMatrix(matrix, "matrix", 125, 125, 5, 5, 0, kofxGui_Matrix_Set, 6);
//	buttonsAndMatrix->addFiles(files,"files", 125, 20, "verdana.ttf", "fonts/", "ttf");
//	//[bb] This by me, the new Switch works in the GUI so far, and reports to console:
//	buttonsAndMatrix->addSwitch(swtch2, "switch test", 125, 25, 0, 3, 0, &dummy_Tags[0]);
//	
//	ofxGuiPanel	*pointsAndScope = gui->addPanel(0, "Points&Scope", 380, 20, 12, OFXGUI_PANEL_SPACING);
//	pointsAndScope->addPoints(points, "points", 255, 60, ofxPoint2f(0.0f, 0.0f), ofxPoint2f(100.0, 1.0), ofxPoint2f(0.5f, 0.0f), kofxGui_Display_Float2, 0.1);
//	pointsAndScope->addScope(scope, "scope", 255, 60, 50, ofxPoint2f(0.0f, 0.0f), kofxGui_Button_Switch);
//	
	
	gui->forceUpdate(false);
	gui->activate(true);
}

void testApp::handleGui(int parameterId, int task, void* data, int length){
	switch(parameterId){
			
		case medianSlider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				medianValue = 1+(int)(*(float*)data)*2;
			}
			break;
			
		case cannyApertureSlider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				cannyApertureValue = 1+(int)(*(float*)data)*2;
			}
			break;	
			
		case adaptiveThreshSlider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				adaptiveThreshValue = 1+(int)(*(float*)data)*2;
			}
			break;		
			
		case cannyThresh1Slider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				cannyThresh1Value = (int)*(float*)data;
			}
			break;	

		case cannyThresh2Slider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				cannyThresh2Value = (int)*(float*)data;
			}
			break;	
			
			
			
		case approxSlider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				approxValue = (int)*(float*)data;
			}
			break;
			
		case fillsApproxSlider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				fillsApproxValue = (int)*(float*)data;
			}
			break;
			
		case approxAlphaSlider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				approxAlphaValue = (int)*(float*)data;			}
			break;	
			
		case clearBGSlider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				clearBGAlphaValue = (int)*(float*)data;			}
			break;	
			
		case contourSmoothSlider:
			if(length == sizeof(float)){
				contourSmoothValue = (int)*(float*)data;
			}
			break;		
			
		case contourAlphaSlider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				contourAlphaValue = (int)*(float*)data;			}
			break;
			
		case lineThreshSlider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				lineThreshValue = (int)*(float*)data;
			}
			break;	
			
		case lineMaxGapSlider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				lineMaxGapValue = (int)*(float*)data;
			}
			break;
			
		case lineMinLengthSlider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				lineMinLengthValue = (int)*(float*)data;			}
			break;
			
		case drawFillsButton:
			if(length == sizeof(bool))
				draw_fills = *(bool*)data;
			break;	
			
		case approxFillsButton:
			if(length == sizeof(bool))
				doFillsApproxValue = *(bool*)data;
			break;	
			
		case clearBGButton:
			if(length == sizeof(bool)) {
				erase_bg = *(bool*)data;
				ofSetBackgroundAuto(erase_bg);
			}
			break;		
			
		case fillsAlphaSlider:
			if(length == sizeof(float)){
				//cout<<"slider value : "<<*(float*)data<<endl;
				fillsAlphaValue = (int)*(float*)data;			}
			break;
			
		case drawContourButton:
			if(length == sizeof(bool))
				draw_contours = *(bool*)data;
			break;	
			
		case drawApproxButton:
			if(length == sizeof(bool))
				draw_approx = *(bool*)data;
			break;	
		
		case drawLinesButton:
			if(length == sizeof(bool))
				draw_edges = *(bool*)data;
			break;	
			
		case debugModeSwitch:
			if(length == sizeof(int)){
				mode = *(int*)data;
			}
			break;	
			
//		case triggerButton:
//			if(length == sizeof(bool))
//				if(*(bool*)data)
//					cout<<"triggerButton"<<endl;
//			break;
//		case switchButton:
//			if(length == sizeof(bool))
//				cout<<"switchButton value : "<<*(bool*)data<<endl;
//			break;
//		case colorRGB:
//			if(length == sizeof(ofRGBA)){
//				ofRGBA c = *(ofRGBA*)data;
//				cout<<"colorRGB value : "<<c.r<<" "<<c.g<<" "<<c.b<<endl;
//			}
//			break;
//		case colorRGBA:
//			if(length == sizeof(ofRGBA)){
//				ofRGBA c = *(ofRGBA*)data;
//				cout<<"colorRGB value : "<<c.r<<" "<<c.g<<" "<<c.b<<" "<<c.a<<endl;
//			}
//			break;
//		case knob:
//			if(length == sizeof(float)){
//				cout<<"knob value : "<<*(float*)data<<endl;
//			}
//			break;
//		case matrix:
//			if (task == kofxGui_Set_Cell)
//				cout<<"matrix value : "<<*(int*)data<<endl;
//			break;
//		case files:
//			if(length == sizeof(string)){
//				cout<<"files value : "<<*(string*)data<<endl;
//			}
//			break;
//		case points:
//			if (task == kofxGui_Set_Point){
//				//cout<<"points value : "<<(*(ofxPoint2f*)data).x<<" "<<(*(ofPoint*)data).y<<endl;
//				bkg = (*(ofxPoint2f*)data).y * 255.0;
//			}
//			else if (task == kofxGui_Set_PointArray){
//				vector<ofxPoint2f> points = *(vector<ofxPoint2f>*)data;
//				cout<<"points value : "<<endl;
//				for(int i=0; i<points.size(); i++)
//					cout<<"    "<<points[i].x<<" "<<points[i].y<<endl;
//			}
//			
//			break;
//		case scope:
//			if (task == kofxGui_Set_Point){
//				cout<<"scope value : "<<(*(ofxPoint2f*)data).x<<" "<<(*(ofPoint*)data).y<<endl;
//			}
//			else if (task == kofxGui_Set_FloatArray){
//				float* values = (float*)data;
//				cout<<"scope value : "<<endl;
//				for(int i=0; i<50; i++)
//					cout<<"  "<<i<<":   "<<values[i]<<endl;
//			}
//			break;
//		case slider:
//			if(length == sizeof(float)){
//				cout<<"slider value : "<<*(float*)data<<endl;
//			}
//			break;
//		case xyPad:
//			if (task == kofxGui_Set_Point){
//				cout<<"xyPad value : "<<(*(ofxPoint2f*)data).x<<" "<<(*(ofPoint*)data).y<<endl;
//			}
//			break;
//		case swtch2:
//			if(length == sizeof(int)){
//				cout<<"Switch value : "<<dummy_Tags[*(int*)data]<<endl;
//			}
//			break;
	}
}

#endif

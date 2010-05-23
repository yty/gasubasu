#import <OpenGL/CGLMacro.h>

#import "MQOImporterPlugIn.h"

#define	kQCPlugIn_Name				@"MQO Importer"
#define	kQCPlugIn_Description		@"Import model from MQO file"

@implementation MQOImporterPlugIn

@dynamic inputX, inputY, inputZ, inputAngleX, inputAngleY, inputAngleZ, inputScale;
@dynamic inputMatrix;
@synthesize mqoFilepath, currMqoFilepath;

+ (NSDictionary*) attributes
{
	return [NSDictionary dictionaryWithObjectsAndKeys:kQCPlugIn_Name, QCPlugInAttributeNameKey, 
			kQCPlugIn_Description, QCPlugInAttributeDescriptionKey, nil];
}

+ (NSDictionary*) attributesForPropertyPortWithKey:(NSString*)key
{
	if([key isEqualToString:@"inputX"]) 
		return [NSDictionary dictionaryWithObjectsAndKeys: 
				QCPortTypeNumber, QCPortAttributeTypeKey, 
				[NSNumber numberWithDouble:0.0], QCPortAttributeDefaultValueKey,
				@"inputX", QCPortAttributeNameKey, nil]; 
	if([key isEqualToString:@"inputY"]) 
		return [NSDictionary dictionaryWithObjectsAndKeys: 
				QCPortTypeNumber, QCPortAttributeTypeKey, 
				[NSNumber numberWithDouble:0.0], QCPortAttributeDefaultValueKey,
				@"inputY", QCPortAttributeNameKey, nil]; 
	if([key isEqualToString:@"inputZ"]) 
		return [NSDictionary dictionaryWithObjectsAndKeys: 
				QCPortTypeNumber, QCPortAttributeTypeKey, 
				[NSNumber numberWithDouble:0.0], QCPortAttributeDefaultValueKey,
				@"inputZ", QCPortAttributeNameKey, nil]; 
	if([key isEqualToString:@"inputAngleX"]) 
		return [NSDictionary dictionaryWithObjectsAndKeys: 
				QCPortTypeNumber, QCPortAttributeTypeKey, 
				[NSNumber numberWithDouble:-90.0], QCPortAttributeDefaultValueKey,
				@"inputAngleX", QCPortAttributeNameKey, nil]; 
	if([key isEqualToString:@"inputAngleY"]) 
		return [NSDictionary dictionaryWithObjectsAndKeys: 
				QCPortTypeNumber, QCPortAttributeTypeKey, 
				[NSNumber numberWithDouble:0.0], QCPortAttributeDefaultValueKey,
				@"inputAngleY", QCPortAttributeNameKey, nil]; 
	if([key isEqualToString:@"inputAngleZ"]) 
		return [NSDictionary dictionaryWithObjectsAndKeys: 
				QCPortTypeNumber, QCPortAttributeTypeKey, 
				[NSNumber numberWithDouble:0.0], QCPortAttributeDefaultValueKey,
				@"inputAngleZ", QCPortAttributeNameKey, nil]; 
	if([key isEqualToString:@"inputScale"]) 
		return [NSDictionary dictionaryWithObjectsAndKeys: 
				QCPortTypeNumber, QCPortAttributeTypeKey,
				[NSNumber numberWithDouble:0.001], QCPortAttributeDefaultValueKey,
				[NSNumber numberWithInt:0], QCPortAttributeMinimumValueKey,
				@"inputScale", QCPortAttributeNameKey, nil]; 
	return nil;
}

+ (QCPlugInExecutionMode) executionMode
{
	return kQCPlugInExecutionModeConsumer;
}

+ (QCPlugInTimeMode) timeMode
{
	return kQCPlugInTimeModeNone;
}

- (id) init
{
	if(self = [super init]) {
		_g_mqoModel= 0;
		self.currMqoFilepath= nil;
		self.mqoFilepath= nil;
	}
	
	return self;
}

- (void) finalize
{
	[super finalize];
}

- (void) dealloc
{
	[super dealloc];
}

+ (NSArray*) plugInKeys
{
	return [NSArray arrayWithObjects:@"mqoFilepath", nil];
}

- (id) serializedValueForKey:(NSString*)key;
{
    if([key isEqualToString:@"mqoFilepath"])
        return self.mqoFilepath;
    return [super serializedValueForKey:key];
}

- (void) setSerializedValue:(id)serializedValue forKey:(NSString*)key
{
    if([key isEqualToString:@"mqoFilepath"])
        self.mqoFilepath= serializedValue;
    else
        [super setSerializedValue:serializedValue forKey:key];
}

- (QCPlugInViewController*) createViewController
{
	return [[QCPlugInViewController alloc] initWithPlugIn:self viewNibName:@"Settings"];
}
@end
@implementation MQOImporterPlugIn (Execution)
- (void)action
{
	NSOpenPanel *opanel = [NSOpenPanel openPanel];
	[opanel setCanChooseDirectories:NO];
	NSArray *fileTypes = [NSArray arrayWithObjects:@"mqo",nil];
	int state= NSCancelButton;
	NSFileManager *mgr = [NSFileManager defaultManager];
	if ([mgr fileExistsAtPath:self.mqoFilepath]) {
		state= [opanel runModalForDirectory:[self.mqoFilepath stringByDeletingLastPathComponent] 
									   file:[self.mqoFilepath lastPathComponent]
									  types:fileTypes];
	}
	else {
		state= [opanel runModalForTypes:fileTypes];
	}
	if (state == NSOKButton){
		self.mqoFilepath= [opanel filename];
	}
}
//- (void) drawCube:(id<QCPlugInContext>)context
//{
//	CGLContextObj cgl_ctx = [context CGLContextObj]; 
//	if(cgl_ctx == NULL) 
//		return; 
//	
//	// Colour cube data.
//	static GLuint polyList = 0;
//	float fSize = 0.5f;
//	long f, i;	
//	const GLfloat cube_vertices [8][3] = {
//		{1.0, 1.0, 1.0}, {1.0, -1.0, 1.0}, {-1.0, -1.0, 1.0}, {-1.0, 1.0, 1.0},
//		{1.0, 1.0, -1.0}, {1.0, -1.0, -1.0}, {-1.0, -1.0, -1.0}, {-1.0, 1.0, -1.0} };
//	const GLfloat cube_vertex_colors [8][3] = {
//		{1.0, 1.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
//		{1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0} };
//	GLint cube_num_faces = 6;
//	const short cube_faces [6][4] = {
//		{3, 2, 1, 0}, {2, 3, 7, 6}, {0, 1, 5, 4}, {3, 0, 4, 7}, {1, 2, 6, 5}, {4, 5, 6, 7} };
//	
//	if (!polyList) {
//		polyList = glGenLists (1);
//		glNewList(polyList, GL_COMPILE);
//		glBegin (GL_QUADS);
//		for (f = 0; f < cube_num_faces; f++)
//			for (i = 0; i < 4; i++) {
//				glColor3f (cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
//				glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
//			}
//		glEnd ();
//		glColor3f (0.0, 0.0, 0.0);
//		for (f = 0; f < cube_num_faces; f++) {
//			glBegin (GL_LINE_LOOP);
//			for (i = 0; i < 4; i++)
//				glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
//			glEnd ();
//		}
//		glEndList ();
//	}
//	
//	glPushMatrix(); // Save world coordinate system.
//	glTranslatef(0.0, 0.0, 0.5); // Place base of cube on marker surface.
//	glDisable(GL_LIGHTING);	// Just use colours.
//	glCallList(polyList);	// Draw the cube.
//	glPopMatrix();	// Restore world coordinate system.
//	
//	return;
//}
- (void)draw:(id<QCPlugInContext>)context
{
	CGLContextObj cgl_ctx = [context CGLContextObj]; 
	if(cgl_ctx == NULL) 
		return; 
	mqoCallObject(_g_mqoModel, context);	
}
- (BOOL)setModelWithContext:(id<QCPlugInContext>)context {
	BOOL ret= NO;
	NSFileManager *mgr = [NSFileManager defaultManager];
	if (self.mqoFilepath!=nil && [mgr fileExistsAtPath:self.mqoFilepath]) {
		const char *mqo_file  = [self.mqoFilepath UTF8String];
		_g_mqoModel = mqoCreateObject((char*)mqo_file, 1.0, context);
		if (_g_mqoModel==0) {
			[context logMessage:@"Unable to set up MQO model."];
		}
		else {
			self.currMqoFilepath= self.mqoFilepath;
			ret= YES;
		}
	}
	else {
		[context logMessage:@"MQO file is not found."];
		if (_g_mqoModel==0) {
			self.mqoFilepath= @"";
			self.currMqoFilepath= self.mqoFilepath;
		}
	}
	return ret;
}
static void _BufferReleaseCallback(const void* address, void* context)
{
	free((void*)address);
}
- (BOOL) startExecution:(id<QCPlugInContext>)context
{
	return YES;
}

- (void) enableExecution:(id<QCPlugInContext>)context
{
}
- (BOOL) execute:(id<QCPlugInContext>)context atTime:(NSTimeInterval)time withArguments:(NSDictionary*)arguments
{
	CGLContextObj cgl_ctx = [context CGLContextObj]; 
	if(cgl_ctx == NULL) 
		return NO;
	
	if (![self.mqoFilepath isEqualToString:self.currMqoFilepath]) {
		[self setModelWithContext:context];
	}
	
	GLint saveMode; 
	glGetIntegerv(GL_MATRIX_MODE, &saveMode); 
	glMatrixMode(GL_MODELVIEW); 
	glPushMatrix(); 
	
	if (self.inputMatrix!=nil && [self.inputMatrix count]>15) {
		GLdouble m[16];
		NSArray* ary= self.inputMatrix;
		int i;
		for(i= 0; i<16; i++) {
			NSNumber* n= [ary objectAtIndex:i];
			m[i]= [n doubleValue];
		}
		glLoadMatrixd(m);
	}
	
	if ([self.mqoFilepath length]>0) {
		glTranslated(self.inputX, self.inputY, self.inputZ); 
		glRotated(self.inputAngleX, 1.0, 0.0, 0.0); 
		glRotated(self.inputAngleY, 0.0, 1.0, 0.0); 
		glRotated(self.inputAngleZ, 0.0, 0.0, 1.0);
		glScaled(self.inputScale, self.inputScale, self.inputScale);
		[self draw:context];
	}
//	else {
//		[self drawCube:context];
//	}
	
	glMatrixMode(GL_MODELVIEW); 
	glPopMatrix(); 
	glMatrixMode(saveMode); 
	
	GLenum error;
	if(error = glGetError()) 
		[context logMessage:@"OpenGL error %04X", error];
	return (error ? NO : YES); 	
}

- (void) disableExecution:(id<QCPlugInContext>)context
{
}

- (void) stopExecution:(id<QCPlugInContext>)context
{
}
@end
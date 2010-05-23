#import <Quartz/Quartz.h>
#import "xGLMetaseq.h"

@interface MQOImporterPlugIn : QCPlugIn
{
	NSString* mqoFilepath;
	NSString* currMqoFilepath;
	MQO_OBJECT _g_mqoModel;
}

@property(copy) NSString* mqoFilepath;
@property(copy) NSString* currMqoFilepath;

@property double inputX; 
@property double inputY; 
@property double inputZ; 
@property double inputAngleX;
@property double inputAngleY;
@property double inputAngleZ;
@property double inputScale;
@property(assign) NSArray* inputMatrix;

@end

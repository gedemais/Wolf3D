#import <Cocoa/Cocoa.h>
#import <OpenGL/gl3.h>
#import <AppKit/NSOpenGLView.h>

void	replace_pointer(int x, int y)
{
	NSPoint mouseWarpLocation = NSMakePoint(x, y);

	CGEventSourceRef evsrc = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
	CGEventSourceSetLocalEventsSuppressionInterval(evsrc, 0.0);
	CGAssociateMouseAndMouseCursorPosition (0);
	CGWarpMouseCursorPosition(mouseWarpLocation);
	CGAssociateMouseAndMouseCursorPosition (1);
	CFRelease(evsrc);
}

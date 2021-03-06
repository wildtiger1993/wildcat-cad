/*******************************************************************************
* Copyright (c) 2007, 2008, CerroKai Development
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of CerroKai Development nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY CerroKai Development ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL CerroKai Development BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************************/


/*** Imported Header Files ***/
#import <Kernel/OSX/document.h>
#import <Kernel/OSX/render_window.h>


/*** Included Header Files ***/
#include <Kernel/document.h>
#include <Kernel/wildcat_kernel.h>
#include <Kernel/workbench.h>
#include <Kernel/selection_mode.h>
#include <Kernel/keymap.h>


/***********************************************~***************************************************/


@implementation WCDocument_OSX


- (id)initWithType:(NSString *)typeName error:(NSError **)outError
{
	//Do the cocoa thing
    self = [super init];
	//If super was created successfully
    if (self) {
		//Initialize remaining variables
		_renderWindow = nil;

		//Convert typename to string
		const char* cString = [typeName cStringUsingEncoding:NSUTF8StringEncoding];
		//Create the string value
		std::string docType(cString);
		//Try to create the document
		try {
			_document = WCWildcatKernel::CreateDocument(docType, "", "");
		}
		//Not able to create document
		catch (WCException &ex) {
			CLOGGER_ERROR(WCLogManager::RootLogger(), "initWithType - Not able to create document of type: " << docType << " Error: " << ex.what());
		}
		//Do not create an OSX undo manager
		[self setHasUndoManager:NO];
    }
	//Return reference to self
    return self;
}


- (id)initWithContentsOfURL:(NSURL*)absoluteURL ofType:(NSString*)typeName error:(NSError**)outError
{
	//Do the cocoa thing
    self = [super init];
	//Get the specified path for the file
	NSString* path = [absoluteURL path];
	//Set filePath as a flag for loading (see onInitOpenGL)
	std::string filePath( [path cStringUsingEncoding:NSUTF8StringEncoding] );
	//Try to open the document
	try {
		_document = WCWildcatKernel::OpenDocument(filePath);
	}
	//Not able to open document
	catch (WCException &ex) {
		CLOGGER_ERROR(WCLogManager::RootLogger(), "initWithContentsOfURL - Not able to open document: " << filePath << " Error: " << ex.what());
	}
	//Return reference to self
    return self;
}


- (void)close
{
	//Do Cocoa thing and pass to super
	[super close];
	//Close and release render window
	[_renderWindow release];
	//Delete the Wildcat document
	delete _document;
}


- (void)makeWindowControllers {
	//Create a render window.
	_renderWindow = [[WCRenderWindow alloc] initWithDocument:self];
	//Cast void* pointer to proper NSOpenGLContext* pointer
	NSOpenGLContext *context = (NSOpenGLContext*)_document->Scene()->GLContext()->Context();
	//Need to set context in renderwindow OpenGL view
	[[_renderWindow renderView] setOpenGLContext:context];
	[_renderWindow windowDidResize:nil];
	//Add as window controller
	[self addWindowController:_renderWindow];
	//Show the window (and make key)
	[[_renderWindow window] makeKeyAndOrderFront:_renderWindow];
}


- (BOOL)writeToURL:(NSURL*)absoluteURL ofType:(NSString*)typeName error:(NSError**)outError
{
	//Get the specified path for saving the file to
	NSString* path = [absoluteURL path];
	std::string fullPath( [path cStringUsingEncoding:NSUTF8StringEncoding] );
	//Call to the root document to save
	_document->ActiveWorkbench()->SaveAs(fullPath);
	//Assume is successful
    return YES;
}


- (BOOL)isDocumentEdited
{
	//Need to actually check _document to see
	return NO;
}


- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError
{
	NSLog(@"WCDocument_OSX::dataOfType - Should not be here.");
    return nil;
}


- (void)onBecomeKey
{
	//Establish timer to handle idle loop
	NSInvocation *invoker = [NSInvocation invocationWithMethodSignature:[self methodSignatureForSelector:@selector(onIdle)]];
	[invoker setSelector:@selector(onIdle)];
	[invoker setTarget:self];
	_timer = [NSTimer scheduledTimerWithTimeInterval:0.0001 invocation:invoker repeats:YES];
	//Retain timer
	[_timer retain];
}


- (void)onResignKey
{
	//Invalidate the current timer and release
	[_timer invalidate];
	[_timer release];

	//Pass to active workbench
	//...
}


- (void)onDisplay
{
	//Make sure there is a document
	ASSERT(_document);
	//Draw the part
	_document->ActiveWorkbench()->Render();
	
	//Set the status text in the render window
	std::string statusText = "Status: " + _document->Status();
	const char *text = statusText.c_str();
	//Convert std::string to NSString
	NSString *newStatus = [[NSString alloc] initWithCString:text];
	NSString *oldStatus = [[_renderWindow statusText] objectValue];
	//Compare the strings...
	if (NSOrderedSame != [newStatus compare:oldStatus]) {
		//Set renderWindow status text
		[[_renderWindow statusText] setObjectValue:newStatus];
	}
	//Release the string
	[newStatus release];
}
 
 
- (void)onResize:(NSSize)size
{
	//Make sure there is a document
	ASSERT(_document);
	//Get the new renderView width and height
	int width = (int)size.width;
	int height = (int)size.height;
	//Set the window width and height parameters
	_document->ActiveWorkbench()->OnReshape(width, height);
	//Render the doc if it's dirty
	if (_document->IsVisualDirty())	[self onDisplay];
}


- (void)onIdle
{
	//Make sure there is a document
	ASSERT(_document);
	//Call Idle method
	_document->ActiveWorkbench()->OnIdle();
	//Render the doc if it's dirty
	if (_document->IsVisualDirty()) [self onDisplay];
}


- (void)onMousePress:(NSEvent*)theEvent
{
	//Make sure there is a document
	ASSERT(_document);
	//See if modifier keys are pressed
	if ([theEvent modifierFlags] & NSControlKeyMask)
		_document->ActiveWorkbench()->OnPanPress();
	else if ([theEvent modifierFlags] & NSShiftKeyMask)
		_document->ActiveWorkbench()->OnRotatePress();
	else if ([theEvent modifierFlags] & NSAlternateKeyMask)
		_document->ActiveWorkbench()->OnZoomPress();
	else if ([theEvent modifierFlags] & NSCommandKeyMask)
		_document->ActiveWorkbench()->OnMultiSelectPress();

	//See if left button pressed
	if ([theEvent buttonNumber] == 0) {
//		NSLog(@"Button Zero");
		_document->ActiveWorkbench()->OnMouseDown(WCMouseButton::Left());
	}
	//Middle button
	else if ([theEvent buttonNumber] > 1) {
//		NSLog(@"Button One");
		_document->ActiveWorkbench()->OnMouseDown(WCMouseButton::Middle());
	}
	//Right button
	if ([theEvent buttonNumber] == 1) {
//		NSLog(@"Button Two");
		_document->ActiveWorkbench()->OnMouseDown(WCMouseButton::Right());
	}
	//Render the doc if it's dirty
	if (_document->IsVisualDirty()) [self onDisplay];
}


- (void)onMouseRelease:(NSEvent*)theEvent
{
	//Make sure there is a document
	ASSERT(_document);
	//Clear modifiers if necessary
	if (_document->ActiveWorkbench()->IsPan()) _document->ActiveWorkbench()->OnPanRelease();
	if (_document->ActiveWorkbench()->IsRotate()) _document->ActiveWorkbench()->OnRotateRelease();
	if (_document->ActiveWorkbench()->IsZoom()) _document->ActiveWorkbench()->OnZoomRelease();
	if (_document->ActiveWorkbench()->IsMultiSelect()) _document->ActiveWorkbench()->OnMultiSelectRelease();
	
	//See if left button pressed
	if ([theEvent buttonNumber] == 0) {
//		NSLog(@"Button Zero");
		_document->ActiveWorkbench()->OnMouseUp(WCMouseButton::Left());
	}
	//Middle button
	else if ([theEvent buttonNumber] == 1) {
//		NSLog(@"Button One");
		_document->ActiveWorkbench()->OnMouseUp(WCMouseButton::Middle());
	}
	//Right button
	if ([theEvent buttonNumber] == 2) {
//		NSLog(@"Button Two");
		_document->ActiveWorkbench()->OnMouseUp(WCMouseButton::Right());
	}
	//Render the doc if it's dirty
	if (_document->IsVisualDirty()) [self onDisplay];
}


- (void)onScrollWheel:(NSEvent *)theEvent
{
	//Make sure there is a document
	ASSERT(_document);
	//Pass scrollWheel event on to the document
	_document->ActiveWorkbench()->OnScroll((WPFloat)[theEvent deltaX], (WPFloat)[theEvent deltaY]);
	//Render the part if it's dirty
	if (_document->IsVisualDirty()) [self onDisplay];
}


- (void)onMouseMoveXPosition:(int)x withYPosition:(int)y
{
	//Make sure there is a document
	ASSERT(_document);
	//React to a mouse movement
	_document->ActiveWorkbench()->OnMouseMove(x, y);
	//Render the part if it's dirty
	if (_document->IsVisualDirty()) [self onDisplay];
}


- (bool)onKeyPress:(NSEvent*)theEvent
{
	//Make sure there is a document
	ASSERT(_document);
	//Otherwise, get event key & modifiers
	NSUInteger modifiers = [theEvent modifierFlags];
	bool control = modifiers & NSControlKeyMask;
	bool option = modifiers & NSAlternateKeyMask;
	bool alt = modifiers & NSAlternateKeyMask;
	bool command = modifiers & NSCommandKeyMask;
	bool esc = false;
	NSString *keys = [theEvent charactersIgnoringModifiers];
	
	//Are there any that we want to handle here
	//Nothing for now...
	
	//Create the key event
	WCKeyEvent event([keys characterAtIndex:0], control, option, alt, command, esc);
	//Get the message for the event
	WCUserMessage message = _document->ActiveWorkbench()->KeyMap()->MessageFromKeyEvent( event );
	//If no message return false
	if (message != "") {
		//Pass the message to the document
		_document->ActiveWorkbench()->OnUserMessage(message);
		//Check to see if is dirty
		if (_document->IsVisualDirty()) [self onDisplay];
		//Return true
		return true;
	}

	//Try default behavior 
	switch([keys characterAtIndex:0]) {
		//Capture arrow keys
		case NSUpArrowFunctionKey:		_document->Scene()->OnArrowKeyPress(WCArrowKey::Up()); return true; break;
		case NSLeftArrowFunctionKey:	_document->Scene()->OnArrowKeyPress(WCArrowKey::Left()); return true; break;
		case NSRightArrowFunctionKey:	_document->Scene()->OnArrowKeyPress(WCArrowKey::Right()); return true; break;
		case NSDownArrowFunctionKey:	_document->Scene()->OnArrowKeyPress(WCArrowKey::Down()); return true; break;
	}
	//Otherwise, did not capture
	return false;
}


- (void)onWindowWillClose
{
}


- (NSString*)view:(NSView *)view stringForToolTip:(NSToolTipTag)tag point:(NSPoint)point userData:(void *)userData
{
	return @"";
}


- (WCRenderWindow*)renderWindow
{
	//Return the render window
	return _renderWindow;
}


- (void)document:(__WILDCAT_NAMESPACE__::WCDocument*)document
{
	//Set the document
	_document = document;
}


- (__WILDCAT_NAMESPACE__::WCDocument*)document
{
	//Return the associated wildcat document
	return _document;

}


@end


/***********************************************~***************************************************/


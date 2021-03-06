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


#ifndef __SKETCH_RECT_CONTROLLER_H__
#define __SKETCH_RECT_CONTROLLER_H__


/*** Included Header Files ***/
#include "Kernel/wftrl.h"
#include "Kernel/event_controller.h"


/*** Local Defines ***/
//None


/*** Class Predefines ***/
class WCSketchRectangle;


/***********************************************~***************************************************/



class WCSketchRectangleController : public WCEventController {
private:
	WCSketchRectangle							*_rect;
	WCSketchRectangleController();																	//!< Deny access to default constructor
	WCSketchRectangleController(const WCSketchRectangleController& contoller);						//!< Deny access to copy constructor
	WCSketchRectangleController& operator=(const WCSketchRectangleController& controller);			//!< Deny access to equals operator
public:
	//Constructors and Destructors
	WCSketchRectangleController(WCSketchRectangle *rect);											//!< Primary constructor
	~WCSketchRectangleController()					{ }												//!< Default destructor
	
	//Inherited Methods
	WCObject* Associate(void);																		//!< Return associated object
	void OnSelection(const bool fromManager);														//!< On select handler
	void OnDeselection(const bool fromManager);														//!< On reorder handler
	void OnContextClick(void);																		//!< On context click handler
};


/***********************************************~***************************************************/


#endif //__SKETCH_RECT_CONTROLLER_H__


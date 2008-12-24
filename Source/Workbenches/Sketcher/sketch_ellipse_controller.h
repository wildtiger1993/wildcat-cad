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


#ifndef __SKETCH_ELLIPSE_CONTROLLER_H__
#define __SKETCH_ELLIPSE_CONTROLLER_H__


/*** Included Header Files ***/
#include <Kernel/wftrl.h>


/*** Locally Defined Values ***/
//None


/*** Namespace Declaration ***/
namespace __WILDCAT_NAMESPACE__ {


/*** Class Predefines ***/
class WCSketchEllipse;


/***********************************************~***************************************************/



class WCSketchEllipseController : public WCEventController {
private:
	WCSketchEllipse								*_ellipse;
	WCSketchEllipseController();																	//!< Deny access to default constructor
	WCSketchEllipseController(const WCSketchEllipseController& contoller);							//!< Deny access to copy constructor
	WCSketchEllipseController& operator=(const WCSketchEllipseController& controller);				//!< Deny access to equals operator
public:
	//Constructors and Destructors
	WCSketchEllipseController(WCSketchEllipse *ellipse);											//!< Primary constructor
	~WCSketchEllipseController();																	//!< Default destructor
	
	//Inherited Methods
	WCObject* Associate(void);																		//!< Return associated object
	void OnSelection(const bool fromManager, std::list<WCVisualObject*> objects);					//!< On select handler
	void OnDeselection(const bool fromManager);														//!< On deselect handler
	void OnContextClick(void);																		//!< On context click handler
};


/***********************************************~***************************************************/


}	   // End Wildcat Namespace
#endif //__SKETCH_ELLIPSE_CONTROLLER_H__


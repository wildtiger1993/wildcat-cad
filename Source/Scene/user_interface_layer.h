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


#ifndef __USER_INTERFACE_LAYER_H__
#define __USER_INTERFACE_LAYER_H__


/*** Included Header Files ***/
#include <Scene/wscnl.h>
#include <Scene/layer.h>


/*** Locally Defined Values ***/
//None


/*** Namespace Declaration ***/
namespace __WILDCAT_NAMESPACE__ {


/*** Class Predefines ***/
class WCWidget;


/***********************************************~***************************************************/


class WCUserInterfaceLayer : public WCLayer {
protected:
	std::list<WCWidget*>						_widgets;											//!< List of widget objects for display
	WCWidget									*_firstResponder;									//!< First responder for mouse events
private:
	//Deny Access
	WCUserInterfaceLayer();																			//!< Deny access to default constructor
public:
	//Constructors and Destructors
	WCUserInterfaceLayer(WCScene *scene);															//!< Primary constructor
	~WCUserInterfaceLayer();																		//!< Default destructor
	
	//Widget Related Methods	
	void RegisterWidget(WCWidget* widget);															//!< Register the widget
	void UnregisterWidget(WCWidget* widget);														//!< Unregister the widget

	//Event Handling Methods
	bool OnIdle(void);																				//!< Handle an idle event
	bool OnMouseMove(const WPFloat x, const WPFloat y);												//!< Track the mouse x and y position
	bool OnMouseDown(const WCMouseButton &button);													//!< Mouse button down event
	bool OnMouseUp(const WCMouseButton &button);													//!< Mouse button up event
	bool OnScroll(const WPFloat &x, const WPFloat &y);												//!< Scroll-wheel event
	bool OnArrowKeyPress(const WCArrowKey &key);													//!< Arrow key event
	bool OnReshape(const WPFloat width, const WPFloat height);										//!< Window reshape info

	//Inherited Methods
	void Render(WCRenderState *state);																//!< Render the layer
};



/***********************************************~***************************************************/


}	   // End Wildcat Namespace
#endif //__USER_INTERFACE_LAYER_H__


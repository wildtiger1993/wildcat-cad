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


#ifndef __DOCUMENT_VIEW_H__
#define __DOCUMENT_VIEW_H__


/*** Included Header Files ***/
#include "Utility/wutil.h"
#include "Kernel/document.h"


/*** Locally Defined Values ***/
//None


/*** Class Predefines ***/
//None


/***********************************************~***************************************************/


class WCDocumentView : public CView {
protected:
	HDC											m_hgldc;											//!< GDI Device Context
	HGLRC										m_hglRC;											//!< Rendering context
	__WILDCAT_NAMESPACE__::WCDocument			*_document;											//!< Associated Wildcat document
public:
	//Constructors and Destructors
	WCDocumentView();																				//!< Default constructor
	virtual ~WCDocumentView();																		//!< Default destructor

	//Member Access Methods
	inline __WILDCAT_NAMESPACE__::WCDocument* Document(void) { return this->_document; }			//!< Get the associated document

	//Class Methods
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);													//!< Standard pre-creation method
	BOOL SetFormat(HDC hdc);																		//!< Set the pixel format

	void OnInitGL(void);																			//!< Called on initialization
	void OnDisplay(void);																			//!< On document display
	void OnResize(const int &width, const int &height);												//!< On document window resize
	void OnIdle(void);																				//!< On document idle loop execute
	void OnMouseMovement(const int &x, const int &y);												//!< On mouse movement
	bool OnKeyPress(UINT nChar, UINT nRepCnt, UINT nFlags);											//!< On key press
	void OnWindowWillClose(void);																	//!< On window being asked to close
};


/***********************************************~***************************************************/


#endif //__DOCUMENT_VIEW_H__


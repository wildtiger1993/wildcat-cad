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


#include "Application/Win32/stdafx.h"
#include "Application/Win32/wildcat_app.h"
#include "Application/Win32/document_view.h"
#include "Utility/wutil.h"


/***********************************************~***************************************************/


BEGIN_MESSAGE_MAP(WCDocumentView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
//	ON_WM_SETFOCUS()
//	ON_WM_KILLFOCUS()
//	ON_WM_KEYUP()
//	ON_WM_TIMER()
//	ON_WM_MOUSEWHEEL()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
//	ON_WM_RBUTTONDOWN()
//	ON_WM_RBUTTONUP()
//	ON_WM_SIZING()
END_MESSAGE_MAP()


void WCDocumentView::OnPaint()  {
	// device context for painting
	CPaintDC dc(this);
	DrawGLScene();
	SwapBuffers(m_hgldc);
}


int WCDocumentView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	m_hgldc = ::GetDC(m_hWnd);
	//Check the pixel format
	if (!SetFormat(m_hgldc)) {
		::MessageBox(::GetFocus(), _T("SetPixelFormat Failed!"), _T("Error"), MB_OK);
		return -1;
	}
	m_hglRC = wglCreateContext(m_hgldc);
	int i = wglMakeCurrent(m_hgldc, m_hglRC);
	GetGLInfo();
	InitGL();
	return 0;
}


void WCDocumentView::OnSize(UINT nType, int cx, int cy) {
	ResizeGLScene(cx, cy);
}


BOOL WCDocumentView::OnEraseBkgnd(CDC *pDC) {
	return TRUE;
}


void WCDocumentView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	switch(nChar) {
		case VK_ESCAPE:
			exit(0);
			break;
		default:
			break;
	}
}


void WCDocumentView::OnMouseMove(UINT nFlags, CPoint point) {
	std::cout << "Here\n";
}


/***********************************************~***************************************************/


WCDocumentView::WCDocumentView() {
//	SetTimer();
}


WCDocumentView::~WCDocumentView() {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hglRC);
}


BOOL WCDocumentView::PreCreateWindow(CREATESTRUCT& cs) {
	//Make sure the base window can pre-create
	if (!CWnd::PreCreateWindow(cs)) return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	//Set the window size
	cs.cx = 400;
	cs.cy = 400;
	//Set the window properties
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);
	//All is good
	return TRUE;
}


BOOL WCDocumentView::SetFormat(HDC hdc) {
	PIXELFORMATDESCRIPTOR *ppfd;
	int pixelformat;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),		// Size of this pfd
		1,									// Version number
		PFD_DRAW_TO_WINDOW |				// Support window
		PFD_SUPPORT_OPENGL |				// Support OpenGL
		PFD_GENERIC_FORMAT |				// 
		PFD_DOUBLEBUFFER |					// Support double buffer
		PFD_TYPE_RGBA,						// Support RGBA
		32,									// 32-bit color depth
		0, 0, 0, 0, 0, 0,					// Color bits ignored
		8,									// No alpha buffer
		0,									// Shift bit ignored
		8,									// No accum buffer
		0, 0, 0, 0,							// Accum bits ignored
		64,									// 64-bit depth buffer
		8,									// Stencil buffer
		8,									// Auxiliary buffer
		PFD_MAIN_PLANE,						// Main layer
		0,									// Reserved
		0, 0, 0								// Layer masks ignored
	};
	//Copy the pixel format
	ppfd = &pfd;

	//Try to choose a compatible pixel format
	if ( (pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0) {
		::MessageBox(NULL, _T("ChoosePixelFomat failed!"), _T("Error"), MB_OK);
		return FALSE;
	}
	//Now try to set that format
	if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE) {
		::MessageBox(NULL, _T("SetPixelFomat failed!"), _T("Error"), MB_OK);
		return FALSE;
	}
	//All is good
	return TRUE;
}


void WCDocumentView::GetGLInfo(void) {
	CString oglinfo;

	oglinfo = "OpenGL Information\n\nWho: ";
/*
	oglinfo += ::glGetString( GL_VENDOR );
	oglinfo += "\nWhich: ";
	oglinfo += ::glGetString( GL_RENDERER );
	oglinfo += "\nVersion: ";
	oglinfo += ::glGetString( GL_VERSION );
	oglinfo += "\nExtensions: ";
	oglinfo += ::glGetString( GL_EXTENSIONS );
*/
	AfxMessageBox(oglinfo, MB_ICONINFORMATION);
}


int WCDocumentView::DrawGLScene(void) {
	// from NeHe's Tutorial 3
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslated(-1.5,0.0,-6.0);						// Move Left 1.5 Units And Into The Screen 6.0
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
		glColor3d(1.0,0.0,0.0);							// Set The Color To Red
		glVertex3d( 0.0, 1.0, 0.0);						// Top
		glColor3d(0.0,1.0,0.0);							// Set The Color To Green
		glVertex3d(-1.0,-1.0, 0.0);						// Bottom Left
		glColor3d(0.0,0.0,1.0);							// Set The Color To Blue
		glVertex3d( 1.0,-1.0, 0.0);						// Bottom Right
	glEnd();											// Finished Drawing The Triangle
	glTranslated(3.0,0.0,0.0);							// Move Right 3 Units
	glColor3d(0.5,0.5,1.0);								// Set The Color To Blue One Time Only
	glBegin(GL_QUADS);									// Draw A Quad
		glVertex3d(-1.0, 1.0, 0.0);						// Top Left 
		glVertex3d( 1.0, 1.0, 0.0);						// Top Right
		glVertex3d( 1.0,-1.0, 0.0);						// Bottom Right
		glVertex3d(-1.0,-1.0, 0.0);						// Bottom Left
	glEnd();											// Done Drawing The Quad
														// Keep Going
	return TRUE;
}


int WCDocumentView::InitGL(void) {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.5);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	return TRUE;
}


void WCDocumentView::ResizeGLScene(int width, int height) {
	if (height == 0) height = 1;
	if (width == 0) width = 1;
	//Reset the viewport
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)width/(float)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/***********************************************~***************************************************/


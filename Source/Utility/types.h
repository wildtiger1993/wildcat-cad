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


#ifndef __WUTIL_TYPES_H__
#define __WUTIL_TYPES_H__


/*** Included Apple Header Files ***/
#ifdef __APPLE__
#include <CoreServices/CoreServices.h>
#include <Accelerate/Accelerate.h>
#endif


// *** Included Windows Header Files ***/
#ifdef __WIN32__
//...
#endif


/*** Namespace Declaration ***/
namespace __WILDCAT_NAMESPACE__ {


/***********************************************~***************************************************/

	
/*** Gloabl Performance Enums ***/
enum WCPerformanceLevel	{
	PerformanceLow,
	PerformanceMedium,
	PerformanceHigh
};
	

/*** Defined Types ***/
typedef double									WPFloat;
typedef long									WPInt;
typedef unsigned long							WPUInt;
typedef std::string								WCWideString;
typedef std::string								WCUserMessage;


/*** Apple Definitions ***/
#ifdef __APPLE__
typedef AbsoluteTime							WPTime;
//Cover for non-SSE2 hardware
#ifndef __SSE2__
typedef double									vDouble;
#endif //__SSE2__
#endif //__APPLE__


/*** Windows Definitions ***/
#ifdef __WIN32__
typedef double									vDouble;

#ifndef __WXMSW__
#include <atltime.h>
#endif //__WXMSW__

typedef ULONGLONG								WPTime;
#endif //__WIN32__


/*** Constant Definitions ***/
#ifndef M_E
	#define M_E									2.71828182845904523536028747135266250   /* e */
#endif //M_E

#ifndef M_LOG2E
	#define M_LOG2E								1.44269504088896340735992468100189214   /* log 2e */
#endif //M_LOG2E

#ifndef M_LOG10E
	#define M_LOG10E							0.434294481903251827651128918916605082  /* log 10e */
#endif //M_LOG10E

#ifndef M_LN2
	#define M_LN2								0.693147180559945309417232121458176568  /* log e2 */
#endif //M_LN2

#ifndef M_LN10
	#define M_LN10								2.30258509299404568401799145468436421   /* log e10 */
#endif //M_LN10

#ifndef M_PI
	#define M_PI								3.14159265358979323846264338327950288   /* pi */
#endif //M_PI

#ifndef M_PI_2
	#define M_PI_2								1.57079632679489661923132169163975144   /* pi/2 */
#endif //M_PI_2

#ifndef M_PI_4
	#define M_PI_4								0.785398163397448309615660845819875721  /* pi/4 */
#endif //M_PI_4

#ifndef M_1_PI
	#define M_1_PI								0.318309886183790671537767526745028724  /* 1/pi */
#endif //M_1_PI

#ifndef M_2_PI
	#define M_2_PI								0.636619772367581343075535053490057448  /* 2/pi */
#endif //M_2_PI

#ifndef M_2_SQRTPI
	#define M_2_SQRTPI							1.12837916709551257389615890312154517   /* 2/sqrt(pi) */
#endif //M_2_SQRTPI

#ifndef M_SQRT2
	#define M_SQRT2								1.41421356237309504880168872420969808   /* sqrt(2) */
#endif //M_SQRT2

#ifndef M_SQRT1_2
	#define M_SQRT1_2							0.707106781186547524400844362104849039  /* 1/sqrt(2) */
#endif //M_SQRT1_2


/***********************************************~***************************************************/


}	   // End Wildcat Namespace
#endif //__WUTIL_TYPES_H__


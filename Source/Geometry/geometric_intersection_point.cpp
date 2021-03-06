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


/*** Included Header Files ***/
#include <Geometry/geometric_intersection.h>
#include <Geometry/geometric_point.h>


/***********************************************~***************************************************/


void __WILDCAT_NAMESPACE__::IntersectionListDisposal(std::list<WCIntersectionResult> &results) {
	//Loop through the list and delete any objects
	//Reverse left and right if there are results
	if (!results.empty()) {
		std::list<WCIntersectionResult>::iterator iter(results.begin());
		//Iterate through the list
		for (; iter != results.end(); iter++) {
			//Delete any objects that are present
			if ((*iter).object != NULL) delete (*iter).object;
		}
		//Clear the list
		results.clear();
	}
}


std::ostream& __WILDCAT_NAMESPACE__::operator<<(std::ostream& out, const WCIntersectionResult &result) {
	//There is a hit
	out << "Hit Type = ";
	//What type of hit?
	switch (result.type) {
		case IntersectPoint: out << "Point"; break;
		case IntersectLine: out << "Line"; break;
		case IntersectCurve: out << "Curve"; break;
		case IntersectSurface: out << "Surface"; break;
		case IntersectTrimSurface: out << "TrimSurface"; break;
	}
	//Print boundary info
	out << " -- LB: " << result.leftBoundary;
	out << ", RB: " << result.rightBoundary;
	//Print parametric info
	out << " -- LP: " << result.leftParam.I();
	out << ", RP: " << result.rightParam.I();
	out << ": @";
	return out;
}


/***********************************************~***************************************************/


std::list<WCIntersectionResult> __WILDCAT_NAMESPACE__::GeometricIntersection(WCGeometricPoint *left,
	WCGeometricPoint *right, const WPFloat &tol, const unsigned int &flags) {
	std::list<WCIntersectionResult> results;
	//Check if intersecting with self
	if (left == right) return results;
	//Check distance between points
	if(left->Data().Distance(right->Data()) <= tol) {
		WCIntersectionResult hit;
		hit.type = IntersectPoint;
		hit.leftBoundary = true;
		hit.rightBoundary = true;
		hit.leftParam = left->Data();
		hit.rightParam = right->Data();
		//See if genObj
		if (flags & INTERSECT_GEN_POINTS) {
			//Create new point
			WCGeometricPoint *newPoint = new WCGeometricPoint(*left);
			//Add to result struct
			hit.object = newPoint;
		}
		else hit.object = NULL;
		//Return the intersection
//		std::cout << hit << *left << std::endl;
		results.push_back(hit);
	}
	//Return the list
	return results;
}


std::list<WCIntersectionResult> __WILDCAT_NAMESPACE__::GeometricIntersection(WCGeometricPoint *left,
	WCGeometricLine *right,  const WPFloat &tol, const unsigned int &flags) {
	//Get intersection list
	std::list<WCIntersectionResult> results = GeometricIntersection(right, left, tol, flags);
	//Return the reversed the list
	return IntersectionReverse( results );
}


std::list<WCIntersectionResult> __WILDCAT_NAMESPACE__::GeometricIntersection(WCGeometricPoint *left,
	WCNurbsCurve *right, const WPFloat &tol, const unsigned int &flags) {
	//Get intersection list
	std::list<WCIntersectionResult> results = GeometricIntersection(right, left, tol, flags);
	//Return the reversed the list
	return IntersectionReverse( results );
}


std::list<WCIntersectionResult> __WILDCAT_NAMESPACE__::GeometricIntersection(WCGeometricPoint *left,
	WCNurbsSurface *right, const WPFloat &tol, const unsigned int &flags) {
	//Get intersection list
	std::list<WCIntersectionResult> results = GeometricIntersection(right, left, tol, flags);
	//Return the reversed the list
	return IntersectionReverse( results );
}


std::list<WCIntersectionResult> __WILDCAT_NAMESPACE__::GeometricIntersection(WCGeometricPoint *left,
	WCTrimmedNurbsSurface *right, const WPFloat &tol, const unsigned int &flags) {
	//Get intersection list
	std::list<WCIntersectionResult> results = GeometricIntersection(right, left, tol, flags);
	//Return the reversed the list
	return IntersectionReverse( results );
}


/***********************************************~***************************************************/


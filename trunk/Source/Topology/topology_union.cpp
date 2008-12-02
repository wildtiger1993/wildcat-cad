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
#include "Topology/topology_model.h"
#include "Topology/topology_model_internal.h"
#include "Topology/topology_types.h"


/***********************************************~***************************************************/


WCTopologyModel* WCTopologyModel::Union(WCTopologyModel *model) {
	//See if no shells are in the shell list
	if (this->_shellList.empty()) {
		//Just copy the model in
		_CopyTopologyModel(this, model->_shellList);
		return this;
	}
	//Otherwise, need to do complex union
	else {
		std::cout << "Union!!!\n";
		//Create maps for all children objects
		std::map<WSTopologyShell*,WSTopologyShell*> shells;
		std::map<WSFaceUse*,WSFaceUse*> faces;
		std::map<WSLoopUse*,WSLoopUse*> loops;
		std::map<WSEdgeUse*,WSEdgeUse*> edges;
		std::map<WSVertexUse*,WSVertexUse*> vertices;
/*		
		//Go through each shell and catalog it
		std::list<WSTopologyShell*>::const_iterator shellIter;
		for (shellIter = source.begin(); shellIter != source.end(); shellIter++) {
			//Catalog the shells and children
			_CatalogTopologyShell(*shellIter, shells, faces, loops, edges, vertices);
		}
*/
	}

	//Return this for now
	return this;
}


/***********************************************~***************************************************/


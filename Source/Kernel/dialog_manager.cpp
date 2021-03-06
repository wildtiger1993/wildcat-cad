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
#include <Kernel/dialog_manager.h>
#include <Kernel/dialog.h>


/*** Static Member Initialization ***/
std::map<std::string,WCDialog*>* WCDialogManager::_dialogMap = NULL;


/***********************************************~***************************************************/


void WCDialogManager::ParseManifest(const std::string &manifest, const bool &verbose) {
	//Create xml parser
	xercesc::XercesDOMParser* parser = new xercesc::XercesDOMParser();
	//Set validation scheme
	parser->setValidationScheme(xercesc::XercesDOMParser::Val_Always);    
	xercesc::ErrorHandler* errHandler = (xercesc::ErrorHandler*) new xercesc::HandlerBase();
	parser->setErrorHandler(errHandler);

	//Get the full path to the manifest
#ifdef __WIN32__
	std::string fullPath = _ResourceDirectory() + "\\" + manifest;
#else
	//Forward slash for OSX and linux
	std::string fullPath = _ResourceDirectory() + "/" + manifest;
#endif
	const char* xmlFile = fullPath.c_str();
	WCDialog *newDialog;
	xercesc::DOMNode *node;
	xercesc::DOMNamedNodeMap *nodeMap;
	XMLCh *xmlDialogString = xercesc::XMLString::transcode("dialog");
	XMLCh *xmlNameString = xercesc::XMLString::transcode("name");
	XMLCh *xmlWidthString = xercesc::XMLString::transcode("width");
	XMLCh *xmlHeightString = xercesc::XMLString::transcode("height");
	XMLCh *xmlModalString = xercesc::XMLString::transcode("modal");
	XMLCh *xmlBoundaryString = xercesc::XMLString::transcode("boundary");
	XMLCh *xmlModeString = xercesc::XMLString::transcode("mode");
	char *tmpChars;
	std::string name;
	unsigned int width, height;
	bool modal, boundary;
	WCDialogMode mode(WCDialogMode::Default());

	//Try to parse
	try {
		//Parse the manifest
		parser->parse(xmlFile);
		//Get the root document
		xercesc::DOMDocument* rootDocument = parser->getDocument();
		//Find all nodes called texture
		xercesc::DOMNodeList *nodeList = rootDocument->getElementsByTagName(xmlDialogString);
		int dialogCount = nodeList->getLength();
		//Loop through all nodes and extract dialog information
		for (int index=0; index < dialogCount; index++) {
			//Get the node at index
			node = nodeList->item(index);
			nodeMap = node->getAttributes();

			//Get the name
			node = nodeMap->getNamedItem(xmlNameString);
			tmpChars = xercesc::XMLString::transcode(node->getNodeValue());
			name = std::string(tmpChars);
			xercesc::XMLString::release(&tmpChars);

			//Get the width
			node = nodeMap->getNamedItem(xmlWidthString);
			tmpChars = xercesc::XMLString::transcode(node->getNodeValue());
			width = (unsigned int)atoi(tmpChars);
			xercesc::XMLString::release(&tmpChars);

			//Get the height
			node = nodeMap->getNamedItem(xmlHeightString);
			tmpChars = xercesc::XMLString::transcode(node->getNodeValue());
			height = (unsigned int)atoi(tmpChars);
			xercesc::XMLString::release(&tmpChars);

			//Get the modal flag
			node = nodeMap->getNamedItem(xmlModalString);
			tmpChars = xercesc::XMLString::transcode(node->getNodeValue());
			if (strncmp(tmpChars, "true", 4) == 0) modal = true;
			else modal = false;
			xercesc::XMLString::release(&tmpChars);

			//Get the boundary flag
			node = nodeMap->getNamedItem(xmlBoundaryString);
			tmpChars = xercesc::XMLString::transcode(node->getNodeValue());
			if (strncmp(tmpChars, "true", 4) == 0) modal = true;
			else boundary = false;
			xercesc::XMLString::release(&tmpChars);

			//Get the mode type (remember default is type = Default)
			node = nodeMap->getNamedItem(xmlModeString);
			tmpChars = xercesc::XMLString::transcode(node->getNodeValue());
			std::string modeString(tmpChars);
			xercesc::XMLString::release(&tmpChars);
			if (modeString == "dynamic") mode = WCDialogMode::Dynamic();
			else if (modeString == "cached") mode = WCDialogMode::Cached();

			//Get values for  new dialog
			newDialog = new WCDialog(name, width, height, modal, boundary, mode);
			//Be verbose if appropriate
			if (verbose) 
				CLOGGER_DEBUG(WCLogManager::RootLogger(), "Dialog " << newDialog->Name() << " successfully loaded.");
			//Try to insert into map
			WCDialogManager::_dialogMap->insert( std::make_pair(newDialog->Name(), newDialog) );
		}
	}
	//Error checking
	catch (const xercesc::XMLException& toCatch) {
		char* message = xercesc::XMLString::transcode(toCatch.getMessage());
		CLOGGER_ERROR(WCLogManager::RootLogger(), "WCDialogManager::ParseManifest - Exception message is: " << message);
		xercesc::XMLString::release(&message);
	}
	catch (const xercesc::DOMException& toCatch) {
		char* message = xercesc::XMLString::transcode(toCatch.msg);
		CLOGGER_ERROR(WCLogManager::RootLogger(), "WCDialogManager::ParseManifest - Exception message is: " << message);
		xercesc::XMLString::release(&message);
	}
	catch (...) {
		CLOGGER_ERROR(WCLogManager::RootLogger(), "WCDialogManager::ParseManifest - Unexpected Exception");
	}
	//Clean up
	delete parser;
	delete errHandler;
	xercesc::XMLString::release(&xmlDialogString);
	xercesc::XMLString::release(&xmlNameString);
	xercesc::XMLString::release(&xmlWidthString);
	xercesc::XMLString::release(&xmlHeightString);
	xercesc::XMLString::release(&xmlModalString);
	xercesc::XMLString::release(&xmlBoundaryString);
}


/***********************************************~***************************************************/


bool WCDialogManager::Initialize(const std::string &manifest, const bool &verbose) {
	//Check to see if map exists
	if (WCDialogManager::_dialogMap != NULL) return true;
	//Create the map
	WCDialogManager::_dialogMap = new std::map<std::string,WCDialog*>();

	//Now parse the manifest to load dialog info
	WCDialogManager::ParseManifest(manifest, verbose);

	//Return all good
	return true;
}


bool WCDialogManager::Terminate() {
	//Need to delete every dialog
	//...

	//Need to delete the map
	delete WCDialogManager::_dialogMap;
	WCDialogManager::_dialogMap = NULL;

	//Return all is good
	return true;
}


WCDialog*  WCDialogManager::DialogFromName(const std::string &name) {
	//Check to see if the name is in the map
	std::map<std::string,WCDialog*>::iterator iter = WCDialogManager::_dialogMap->find(name);
	//See if you found anything
	if( iter == WCDialogManager::_dialogMap->end() ) {
		CLOGGER_ERROR(WCLogManager::RootLogger(), "WCDialogManager::DialogFromName - Not able to find dialog: " << name);
		return NULL;
	}
	//Otherwise, get the object
	return (*iter).second;
}


WCDialog* WCDialogManager::DisplayDialog(const std::string &name, WCDialogController *controller) {
	//Make sure controller is not null
	if (controller == NULL) {
		CLOGGER_ERROR(WCLogManager::RootLogger(), "WCDialogManager::DialogFromName - NULL controller passed for dialog: " << name);
		//throw error
		return NULL;
	}
	//Get the dialog
	WCDialog *dialog = WCDialogManager::DialogFromName(name);
	//If a valid dialog is returned
	if (dialog != NULL) {
		//Associated a controller with it
		dialog->Controller(controller);
		//Associate a dialog with the controller
		controller->Dialog(dialog);
	}
	return dialog;
}


void WCDialogManager::CloseDialog(WCDialog *dialog) {
	//Make sure dialog is open
	if (!dialog->IsOpen()) return;
	//Otherwise, close the window
	dialog->CloseWindow(false);
}


/***********************************************~***************************************************/


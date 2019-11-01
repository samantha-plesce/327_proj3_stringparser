/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace KP_StringParserClass;
using namespace std;

//char *pStartTag;
//char *pEndTag;
//bool areTagsSet;

//dont forget to initialize member variables


StringParserClass::StringParserClass(void){
	pStartTag = NULL;
	pEndTag = NULL;
	areTagsSet = false;
}

	//call cleanup to release any allocated memory
StringParserClass::~StringParserClass(void){
	cleanup();
	areTagsSet = false;
}

	//these are the start tag and the end tags that we want to find,
	//presumably the data of interest is between them, please make a
	//COPY of what pStartTag and pEndTag point to.  In other words
	//DO NOT SET pStartTag = pStart
	//returns:
	//SUCCESS
	//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::setTags(const char *pStart, const char *pEnd){
	if (pStart == NULL || pEnd == NULL){
		return ERROR_TAGS_NULL;
	}

	int lenstart = strlen(pStart) + 1;
	int lenend = strlen(pEnd) + 1;

	pStartTag = new char[lenstart];
	pEndTag = new char[lenend];
	strncpy(pStartTag, pStart, lenstart);
	strncpy(pEndTag, pEnd, lenend);

	areTagsSet = true;

	return SUCCESS;
}

//First clears myVector
		//going to search thru pDataToSearchThru, looking for info bracketed by
		//pStartTag and pEndTag, will add that info only to myVector
		//returns
		//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
		//ERROR_TAGS_NULL if either pStart or pEnd is null
		//ERROR_DATA_NULL pDataToSearchThru is null
int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector){
	myVector.clear();
	if (areTagsSet == false){
		return ERROR_TAGS_NULL;
	}
	if (pDataToSearchThru == NULL){
		return ERROR_DATA_NULL;
	}

	int pDTSSize = strlen(pDataToSearchThru);
	char *startST = pDataToSearchThru;
	char *endST = pDataToSearchThru + pDTSSize;
	char *startET = pDataToSearchThru;
	char *endET = pDataToSearchThru + pDTSSize;

	string add = "";

	while (findTag(pStartTag, pDataToSearchThru, endST) == SUCCESS){
		if(findTag(pEndTag, startET, endET) == FAIL){
			return SUCCESS;
		}
		if(findTag(pEndTag, startET, endET) == SUCCESS){
			while (endST != startET){
				add += *endST;
				endST++;
			}
			myVector.push_back(add);
			add = "";
			pDataToSearchThru = endET;
			pDTSSize = strlen(pDataToSearchThru);
			endST = pDataToSearchThru + pDTSSize;
			endET = pDataToSearchThru + pDTSSize;
			startET = pDataToSearchThru;
			startST = pDataToSearchThru;
		}
	}

	return SUCCESS;
}

void StringParserClass::cleanup(){
	if(pStartTag) {
		delete[] (pStartTag);
	}
	if(pEndTag) {
		delete[] (pStartTag);
	}

}


//Searches a string starting at pStart for pTagToLookFor
		//returns:
		//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
		//FAIL did not find pTagToLookFor and pEnd points to 0
		//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd){

	if (pStart == NULL || pEnd == NULL){
		return ERROR_TAGS_NULL;
	}

	int arraylen = strlen(pTagToLookFor);

	while (pStart != pEnd){
		if (*pStart == *pTagToLookFor){
			if(strncmp(pStart, pTagToLookFor, arraylen) == 0){
				pEnd = pStart + arraylen;
				return SUCCESS;
			}
		}
		pStart++;
	}
	return FAIL;
}


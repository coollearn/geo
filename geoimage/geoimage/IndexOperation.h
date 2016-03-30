#pragma once
#include <iostream>
#include <string>
#include <vector> 
#include<osgViewer/Viewer>
#include<osgDB/ReadFile>
#include <osg/ComputeBoundsVisitor>  
#include <string>
#include <fstream>
#include <io.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/format.hpp>   
#include <boost/tokenizer.hpp>     
#include <boost/algorithm/string.hpp> 

#include"RTree.h"

#include<iostream>
using namespace std;

struct Rect
{
	Rect()  {}

	Rect(float a_minX, float a_minY, float a_maxX, float a_maxY)
	{
		min[0] = a_minX;
		min[1] = a_minY;

		max[0] = a_maxX;
		max[1] = a_maxY;
	}


	float min[2];
	float max[2];
};

class CIndexOperation
{
	typedef bool (*t_resultCallback)(structFileInfo*, void*,vector<structFileInfo*>&);
public:
	CIndexOperation(void);
	~CIndexOperation(void);
	void SearchImage(Rect rect,string ResulationLeval, t_resultCallback resultCallback ,vector<structFileInfo*>&vSearchResults);
	void traverse();
	bool CrateIndex(string dir);
	int GetFileAmount();
	char line[1024];
private:
	typedef RTree<structFileInfo*, float, 2, float> RTree;
	RTree RtreeIndex;
	ifstream *fin;
	int FileAmount;
	
};

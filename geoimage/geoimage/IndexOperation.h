#pragma once
#include<string>
#include"GetFilePath.h"
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
    bool CreateIndex(string dir);
	void SearchImage(Rect rect,string ResulationLeval, t_resultCallback resultCallback ,vector<structFileInfo*>&vSearchResults);
	void traverse();
private:
	typedef RTree<structFileInfo*, float, 2, float> RTree;
	RTree RtreeIndex;
	
};

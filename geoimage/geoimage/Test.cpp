//
// Test.cpp
//
// This is a direct port of the C version of the RTree test program.
//

#include <iostream>
#include "RTree.h"



#include<osgViewer/Viewer>
#include<osgDB/ReadFile>
#include <osg/ComputeBoundsVisitor>  
#include <string>
#include <fstream>
#include <io.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <algorithm>  
#include <vector>  
#include <iterator> 

#include "GetFilePath.h"

#include <time.h>

#include "IndexOperation.h"
using namespace std;

typedef structFileInfo* ValueType;
//typedef int ValueType;



//bool MySearchCallback(ValueType id, void* arg)
//{
//  //cout << "Hit data rect " << id << "\n";
//  return true; // keep going
//}


int main1()
{
	//typedef int ValueType;

	struct Rect
	{
		Rect()  {}

		Rect(int a_minX, int a_minY, int a_maxX, int a_maxY)
		{
			min[0] = a_minX;
			min[1] = a_minY;

			max[0] = a_maxX;
			max[1] = a_maxY;
		}


		int min[2];
		int max[2];
	};

	struct Rect rects[] =
	{
		Rect(0, 0, 2, 2), // xmin, ymin, xmax, ymax (for 2 dimensional RTree)
		Rect(5, 5, 7, 7),
		Rect(8, 5, 9, 6),
		Rect(7, 1, 9, 2),
	};

	int nrects = sizeof(rects) / sizeof(rects[0]);

	Rect search_rect(6, 4, 10, 6); // search will find above rects that this one overlaps


	
	return 0;

  
}
bool MySearchCallback(ValueType id, void* arg,vector<ValueType>&vResult)
{
	if(id->strResolutionLevel==(char*)arg)
	{
		vResult.push_back(id);
		cout << "Hit data rect " <<id->strResolutionLevel <<endl;
	}
	
	return true; // keep going
}
int main2(){
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
	char *p="L4";
	typedef RTree<structFileInfo*, float, 2, float> MyTree;
	MyTree tree;

	CGetFilePath gfp;
	 //string dir="C:/Users/hao/Desktop/osg";
	string dir="D:\\OutData\\osg\\test0_root_L0_X0_Y0";
	vector<CReturnFileInfo*> vFileInfo;
	clock_t   t_begin,t_end; 
	t_begin=clock();
	if(gfp.get(dir,vFileInfo)){
		cout<<"正在建立索引"<<endl;
	vector<CReturnFileInfo*>::iterator it;
		for(it=vFileInfo.begin();it!=vFileInfo.end();it++)
		{
		 osg::Node* node = osgDB::readNodeFile((*it)->strFilePath);
		 string path=(*it)->strFilePath;
		 /*cout<<path<<endl;
		 cout<<(*it)->strResulationLevel<<endl;*/
		 char *p="L4";
		 osg::ComputeBoundsVisitor cbVisitor;
		 node->accept(cbVisitor);
		 osg::BoundingBox bb = cbVisitor.getBoundingBox();
		    FileInfo *iFileInfo=new FileInfo();
			FILE *fp;
			fp=fopen(path.c_str(),"r");
			iFileInfo->fp=fp;
			iFileInfo->strResolutionLevel=(*it)->strResolutionLevel;
			/*cout<<(float)bb.xMin()<<endl;
			cout<<(float)bb.yMin()<<endl;
			cout<<(float)bb.xMax()<<endl;
			cout<<(float)bb.yMax()<<endl;*/
		    Rect struct_Rect((float)bb.xMin(),(float)bb.yMin(),(float)bb.xMax(),(float)bb.yMax());
			tree.Insert(struct_Rect.min,struct_Rect.max,iFileInfo);
	    }
	}
	     t_end=clock();
	     cout<<"索引建立完毕,用时:"<<(double)(t_end-t_begin)<<" 毫秒"<<endl;
		 
	     Rect struct_SearchRect(-110.625,49.375,-110,50.0004);
	     vector<structFileInfo*>vSearchResults;
	     tree.Search(struct_SearchRect.min, struct_SearchRect.max, MySearchCallback, p,vSearchResults);
		 cout<<"this  is  the results"<<endl;
		 vector<structFileInfo*>::iterator itt;
		 for(itt=vSearchResults.begin();itt!=vSearchResults.end();itt++)
		 {
			 cout<<"hhh"<<endl;
		     cout<<(*itt)->strResolutionLevel<<endl;
		 }
		 //cout<<"the total of result"<<nhits<<endl;
	     vector<CReturnFileInfo*>::iterator it;
		 for(it=vFileInfo.begin();it!=vFileInfo.end();it++){
		//	cout<<(*it)->strFilePath<<endl;
			delete *it;
		    *it=NULL;
		}
		vector<CReturnFileInfo*>().swap(vFileInfo);
	return 0;
}
int main()
{
	string dir="D:\\OutData\\osg\\test0_root_L0_X0_Y0";
	CIndexOperation iIndexOperation;
	iIndexOperation.CreateIndex(dir);
	Rect struct_SearchRect(-110.625,49.375,-110,50.0004);
	string SearchedResolution="L4";
	vector<structFileInfo*>vSearchResults;
	iIndexOperation.SearchImage(struct_SearchRect,SearchedResolution,MySearchCallback,vSearchResults);
	vector<structFileInfo*>::iterator itt;
	for(itt=vSearchResults.begin();itt!=vSearchResults.end();itt++)
	{
		cout<<"hhh"<<endl;
		cout<<(*itt)->strResolutionLevel<<endl;
	}
	iIndexOperation.traverse();
	return 0;


}
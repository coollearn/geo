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



bool MySearchCallback(ValueType id, void* arg,vector<ValueType>&vResult)
{
	if(id->strResolutionLevel==(char*)arg)
	{
		vResult.push_back(id);
		cout << "Hit data rect " <<id->strResolutionLevel <<endl;
	}
	
	return true; // keep going
}
int main()
{
	//string dir="D:\\OutData\\osg\\test0_root_L0_X0_Y0";
	string dir="D:\\geodata";
	CIndexOperation iIndexOperation;
	clock_t t_begin,t_end; 
	t_begin=clock();
	iIndexOperation.CrateIndex(dir);
	t_end=clock();
	cout<<endl<<endl<<"索引建立完毕,用时:"<<(double)(t_end-t_begin)<<" 毫秒"<<endl;
	cout<<"the amount of files is "<<iIndexOperation.GetFileAmount()<<endl;
	Rect struct_SearchRect(9.99958,-0.000416711,15.0004,5.00042);
	string SearchedResolution="L2";
	vector<structFileInfo*>vSearchResults;
	iIndexOperation.SearchImage(struct_SearchRect,SearchedResolution,MySearchCallback,vSearchResults);
	vector<structFileInfo*>::iterator itt;
	for(itt=vSearchResults.begin();itt!=vSearchResults.end();itt++)
	{
	  cout<<"hhh"<<endl;
	  cout<<(*itt)->strResolutionLevel<<endl;
	  cout<<(*itt)->strFilePath<<endl;

	}
	//iIndexOperation.traverse();
	system("pause");
	return 0;


}
int main4()
{
	//string path="C:\\Users\\hao\\Desktop\\43_12_L4_X7_Y1_subtile.osg";
	//string path="D:\\geodata\\EU\\35_03_root_L0_X0_Y0\\35_03_L0_X0_Y0_subtile.osg";
	string path="D:\\geodata\\AF\\40_13_root_L0_X0_Y0\\40_13_L2_X0_Y1_subtile.osg";
//	path="D:\\OutData\\osg\\test0_root_L0_X0_Y0\\test0_L0_X0_Y0_subtile.osg";
	osg::Node* node= osgDB::readNodeFile(path);
	osg::ComputeBoundsVisitor cbVisitor;
	node->accept(cbVisitor);
	osg::BoundingBox bb = cbVisitor.getBoundingBox();
	cout<<bb.xMin()<<endl;
	cout<<bb.yMin()<<endl;
	cout<<bb.xMax()<<endl;
	cout<<bb.yMax()<<endl;
	system("pause");
	
	return 0;
}
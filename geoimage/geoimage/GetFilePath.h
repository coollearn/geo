#pragma once
/************************************************************************
 *
 * Author        ：hrh
 * Description   ：通过一个文件夹的路径，获取文件夹中图像文件的文件路径,
                   以及分辨率水平，分辨率水平用四叉树的层级来表示。
 *
 ************************************************************************/
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
using namespace std;


class CReturnFileInfo
{
  public:
	CReturnFileInfo(string strFilePath,string strResolutionLevel)
	{
		this->strFilePath=strFilePath;
		this->strResolutionLevel=strResolutionLevel;
	}
	string strFilePath;
	string strResolutionLevel;//分辨率水平
};

class CGetFilePath
{
public:
	CGetFilePath(void);
	~CGetFilePath(void);
private:
	//vector<string> m_vFilePaths;
public:
  bool get(string dir,vector<CReturnFileInfo*>&vFileInfo);
};
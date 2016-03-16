#pragma once
/************************************************************************
 *
 * Author        ��hrh
 * Description   ��ͨ��һ���ļ��е�·������ȡ�ļ�����ͼ���ļ����ļ�·��,
                   �Լ��ֱ���ˮƽ���ֱ���ˮƽ���Ĳ����Ĳ㼶����ʾ��
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
	string strResolutionLevel;//�ֱ���ˮƽ
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
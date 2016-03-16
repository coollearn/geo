#pragma warning(disable:4996)
#include "GetFilePath.h"
#include <tchar.h>
CGetFilePath::CGetFilePath(void)
{

}


CGetFilePath::~CGetFilePath(void)
{
}

//************************************
// Method:    get
// FullName:  CGetFilePath::get
// Access:    public 
// Returns:   bool  返回ture函数返回结果，返回false则没有返回结果       
// Qualifier:
// Parameter: string dir 输入的文件夹路径
// Parameter: vector<CReturnFileInfo * > & vFileInfo 存的是文件夹下面的图片文件的路径和对应的分辨率等级
//************************************
bool CGetFilePath::get(string dir,vector<CReturnFileInfo*>&vFileInfo)
{
	namespace fs = boost::filesystem;
	fs::path path(dir);  
	if (!fs::exists(path))  
	{  
		cout<<"wrong directory path! "<<endl;
		return false;  
	}  

	fs::directory_iterator end_iter;  
	for (fs::directory_iterator iter(path); iter!=end_iter; ++iter)  
	{  
		if (fs::is_regular_file(iter->status()))  
		{
			//获取文件扩展名
			string strExtention=iter->path().extension().string();
			if(strExtention==".osg")
			{
				string filename= iter->path().filename().string();
				std::vector<std::string> vSegTag; 
				boost::split(vSegTag, filename, boost::is_any_of(_T("_")));
			    CReturnFileInfo* ptrRFI=new CReturnFileInfo(iter->path().string(),vSegTag[1]);
			    vFileInfo.push_back(ptrRFI);
			}  
		}  

		if (fs::is_directory(iter->status()))  
		{  
			//get_filenames(iter->path().string(), filenames);
			cout<<"there exits subdirectory! "<<endl;
			return false;  
		} 

	}
	return true;

}
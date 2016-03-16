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
// Returns:   bool  ����ture�������ؽ��������false��û�з��ؽ��       
// Qualifier:
// Parameter: string dir ������ļ���·��
// Parameter: vector<CReturnFileInfo * > & vFileInfo ������ļ��������ͼƬ�ļ���·���Ͷ�Ӧ�ķֱ��ʵȼ�
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
			//��ȡ�ļ���չ��
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
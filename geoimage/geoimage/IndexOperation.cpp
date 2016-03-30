#include "IndexOperation.h"
#include <tchar.h>

CIndexOperation::CIndexOperation(void)
{
	//line={0};
	fin=NULL;
	FileAmount=0;
}


CIndexOperation::~CIndexOperation(void)
{
}

//************************************
// Method:    CreateIndex
// FullName:  CIndexOperation::CreateIndex
// Description:此函数用来建立R树索引 
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: string dir 要建立索引的图片文件所在文件夹的路径
//************************************
bool CIndexOperation::CrateIndex(string dir)
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
			if(iter->path().filename().string()=="000.txt")
			{
			   fin=new ifstream(iter->path().string());
			   continue;
			   //inputFile.
			}
			FileAmount++;
			//获取文件扩展名
			string strExtention=iter->path().extension().string();
			if(strExtention==".osg")
			{
				fin->getline(line, sizeof(line));
				stringstream word(line);
				string xMin="",yMin="",xMax="",yMax="";
				word>>xMin>>yMin>>xMax>>yMax;
				float fxMin=atof(xMin.c_str());
				float fyMin=atof(yMin.c_str());
				float fxMax=atof(xMax.c_str());
				float fyMax=atof(yMax.c_str());

				string FileName= iter->path().filename().string();
				string FilePath=iter->path().string();
				std::vector<std::string> vSegTag;
				boost::split(vSegTag, FileName, boost::is_any_of(_T("_")));
				FileInfo *iFileInfo=new FileInfo();
				FILE *fp=NULL;
				//fp=fopen(iter->path().filename().string().c_str(),"r");
				iFileInfo->fp=fp;
				iFileInfo->strResolutionLevel=vSegTag[2];
				iFileInfo->strFilePath=FilePath;
				cout<<FilePath<<" "<<fxMin<<" "<<fyMin<<" "<<fxMax<<" "<<fyMax<<endl;
				Rect struct_Rect(fxMin,fyMin,fxMax,fyMax);
				RtreeIndex.Insert(struct_Rect.min,struct_Rect.max,iFileInfo);
			}  
		} 
		if (fs::is_directory(iter->status()))  
		{  
			CrateIndex(iter->path().string());

		}
		
	}
	if(fin!=NULL)
	{
		fin->clear();
		fin->close();
		delete fin;
		fin=NULL;
	}
	return true;
}
void CIndexOperation::SearchImage(Rect rect,string ResulationLeval, t_resultCallback resultCallback ,vector<structFileInfo*>&vSearchResults){

	char*p=&ResulationLeval[0];
	RtreeIndex.Search(rect.min,rect.max,resultCallback,p,vSearchResults);

}
void CIndexOperation::traverse()
{
	int index=0;
	RTree::Iterator it;
	for( RtreeIndex.GetFirst(it);
		!RtreeIndex.IsNull(it);
		RtreeIndex.GetNext(it) )
	{
		//int value = RtreeIndex.GetAt(it);

		float boundsMin[2] = {0,0};
		float boundsMax[2] = {0,0};
		it.GetBounds(boundsMin, boundsMax);
		cout << "it[" << index++ << "] " << " = (" << boundsMin[0] << "," << boundsMin[1] << "," << boundsMax[0] << "," << boundsMax[1] << ")\n";
	}

}
int CIndexOperation::GetFileAmount()
{
	return FileAmount;
}
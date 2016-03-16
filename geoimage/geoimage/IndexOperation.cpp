#include "IndexOperation.h"


CIndexOperation::CIndexOperation(void)
{
}


CIndexOperation::~CIndexOperation(void)
{
}

//************************************
// Method:    CreateIndex
// FullName:  CIndexOperation::CreateIndex
// Description:�˺�����������R������ 
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: string dir Ҫ����������ͼƬ�ļ������ļ��е�·��
//************************************
bool CIndexOperation::CreateIndex(string dir)
{
	CGetFilePath gfp;
	vector<CReturnFileInfo*> vFileInfo;//������ŷ��ص�ͼƬ�ļ�����Ϣ
	clock_t t_begin,t_end; 
	t_begin=clock();
	if(gfp.get(dir,vFileInfo)){
		int counter=0;
		cout<<"���ڽ�������"<<endl<<endl;
		vector<CReturnFileInfo*>::iterator it;
		for(it=vFileInfo.begin();it!=vFileInfo.end();it++)
		{   
			//������
			cout<<"<";
		    counter++;
			if(counter==40)
			{
		        cout<<"\r";
				for(int i=0;i<41;i++)
					cout<<" ";
				cout<<"\r";
				counter=0;
			}

			osg::Node* node = osgDB::readNodeFile((*it)->strFilePath);
			string path=(*it)->strFilePath;
			/*cout<<path<<endl;
			cout<<(*it)->strResulationLevel<<endl;*/
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
			RtreeIndex.Insert(struct_Rect.min,struct_Rect.max,iFileInfo);
		}
	}
	t_end=clock();
	cout<<endl<<endl<<"�����������,��ʱ:"<<(double)(t_end-t_begin)<<" ����"<<endl;

	//���vFileInfoռ�õĻ���
	vector<CReturnFileInfo*>::iterator it;
	for(it=vFileInfo.begin();it!=vFileInfo.end();it++){
		//	cout<<(*it)->strFilePath<<endl;
		delete *it;
		*it=NULL;
	}
	vector<CReturnFileInfo*>().swap(vFileInfo);
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
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<conio.h>
#include<cstdio>
using namespace std;
enum StatusCode {SUCCESS,FAIL,UNDER_FLOW,OVER_FLOW,RANGE_ERROR,DUPLICATE_ERROR,NOT_PRESENT,ENTRY_INSERTED,ENTRY_FOUND,VISITED,UNVISITED};
template<class ElemType>
struct DblNode
{
	ElemType data;//数据域 
	DblNode<ElemType> *back;//后继指针 
	DblNode<ElemType> *next;//前驱指针 
	DblNode();
	DblNode(ElemType item,DblNode<ElemType> *linkback = NULL,DblNode<ElemType>*linknext = NULL);//已知数据域和指针域建立结构 
};
template<class ElemType>
DblNode<ElemType>::DblNode()
{
	next = NULL;//构造指针域为空的结点 
}
template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item,DblNode<ElemType> *linkback,DblNode<ElemType>*linknext)
{
	data = item;//数据域为item 
	back = linkback; 
	next = linknext;
}


template<class ElemType>
class DblLinkList
{
public:
		DblNode<ElemType> *head;//头结点指针 
		
		mutable int curPosition;
		mutable DblNode<ElemType> *curPtr;
		int count;
		DblNode<ElemType> *GetElemPtr(int position) const;
		DblLinkList();
		virtual ~DblLinkList();
		bool Empty() const;
		void Clear();
		void Init();
		int Length() const;
		StatusCode GetElem(int position,ElemType &e) const;
		StatusCode SetElem(int position,const ElemType &e);
		StatusCode Delete(int position,ElemType &e);
		StatusCode Insert(int position,const ElemType &e);
};

template<class ElemType>
void DblLinkList<ElemType>::Init()
{
	head=new DblNode<ElemType>;
	head->next=head;
	curPtr=head;
	curPosition=0;
	count=0;
}
template<class ElemType>
DblLinkList<ElemType>::DblLinkList()
{
	Init();
}
template<class ElemType>
DblLinkList<ElemType>::~DblLinkList()
{
	Clear();
	delete head;
}

template<class ElemType>
bool DblLinkList<ElemType>::Empty() const
{
	return head->next=NULL;
}

template<class ElemType>
void DblLinkList<ElemType>::Clear()
{
	ElemType tmpElem;
	while(Length()>0)
	{
		Delete(1,tmpElem);
	}
}

template<class ElemType>
DblNode<ElemType> *DblLinkList<ElemType>::GetElemPtr(int position) const
{
	if(curPosition<position)
	{
		for(;curPosition<position;curPosition++)
		{
			curPtr=curPtr->next;
		}
	}//顺序 
	else if(curPosition>position)
	{
		for(;curPosition>position;curPosition--)
		{
			curPtr=curPtr->back;
		}
	}//逆序 
	return curPtr;
}

template<class ElemType>
int DblLinkList<ElemType>::Length() const
{
	return count;//结点个数 
}

template<class ElemType>
StatusCode DblLinkList<ElemType>::GetElem(int position,ElemType &e) const
{
	if(position<1||position>Length())
	{
		return RANGE_ERROR;
	}
	else
	{
		DblNode<ElemType>*tmpPtr;//指针 
		tmpPtr=GetElemPtr(position);//确定位置 
		e=tmpPtr->data;//读取数据 
		return ENTRY_FOUND; 
	}
}
template<class ElemType>
StatusCode DblLinkList<ElemType>::SetElem(int position,const ElemType &e)
{
	if(position<1||position>Length())
	{
		return RANGE_ERROR;
	}
	else
	{
		DblNode<ElemType>*tmpPtr;//指针 
		tmpPtr=GetElemPtr(position);//确定位置 
		tmpPtr->data=e;//输入数据 
		return SUCCESS; 
	}
}
template<class ElemType>
StatusCode DblLinkList<ElemType>::Insert(int position,const ElemType &e)
{
	if(position<1||position>Length()+1)
	{
		return RANGE_ERROR;
	}
	else
	{
		DblNode<ElemType>*tmpPtr,*nextPtr,*newPtr;
		tmpPtr=GetElemPtr(position-1);//取出指向第position-1个结点的指针 
		nextPtr=tmpPtr->next;//nextPtr指向第position个结点 
		newPtr=new DblNode<ElemType>(e,tmpPtr,nextPtr);//生成新结点 
		tmpPtr->next=newPtr;//修改向右指针 
		nextPtr->back=newPtr;//修改向左指针 
		curPosition=position;//修改行号 
		curPtr=newPtr;//修改指针 
		count++;//插入：结点+1 
		return SUCCESS; 
	}
}
template<class ElemType>
StatusCode DblLinkList<ElemType>::Delete(int position,ElemType &e)
{
	if(position<1||position>Length())
	{
		return RANGE_ERROR;
	}
	else
	{
		DblNode<ElemType>*tmpPtr;
		tmpPtr=GetElemPtr(position);
		tmpPtr->back->next=tmpPtr->next;
		tmpPtr->next->back=tmpPtr->back;
		e=tmpPtr->data;
		if(position==Length())
		{
			curPosition=count-1;
			curPtr=tmpPtr->back;
		}//末尾 
		else
		{
			curPosition=position;
			curPtr=tmpPtr->next;
		}//非末尾 
		count--;
		delete tmpPtr;
		return SUCCESS; 
	}
}


int main(void)
{
	DblLinkList<string> test;//对象 
	/*文件流*/
	ifstream infile;
	char infilename[1000];
	cout<<"Please input inputfile name(eg. file_in.txt):";
	cin>>infilename;
	infile.open(infilename,ios::in);
	if(infile.fail())
	{
		cout<<"open file error"<<endl;
		return -1;
	}
	
	ofstream outfile;
	char outfilename[1000];
	cout<<"Please input outputfile name(eg. file_out.txt):";
	cin>>outfilename;
	outfile.open(outfilename,ios::out);
	
	
/*运行文本编辑器*/
    char usercommand; 
    do
    {
    	char usercommand = getchar();
    	switch(usercommand)
	    {
	    	case 'b':
			{
			    cout<<"1:"<<test.head->next->data<<endl;
				break;
			}
			case 'c':
			{
				string cc1;
		        string cc2;
		        string cc3;
		        cin.get();
		        cout<<"What you want to change:";
		        getline(cin,cc1);//被替换文本 
		        cout<<"change to:";
		        getline(cin,cc2);//替换文本 
		        for(int i=0;i<test.count;i++)
		        {
			       test.GetElem(i+1,cc3);
			       if(cc3==cc1)
			    {
			       test.SetElem(i+1,cc2);
			    }
		        }
		        cout<<test.curPosition<<":"<<test.curPtr->data<<endl; 
				break;
			}
			case 'd':
		    {
		    	string dd;
		    	test.Delete(test.curPosition,dd);
		    	cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
	        	break;
			}
			case 'e':
	        {
	        	cout<<test.count<<":"<<test.head->back->data<<endl;
	        	break;
			}
			case 'f':
			{ 
			    string f;
			    cin.get();
			    cout<<"What you want to find:";
			    getline(cin,f);
                size_t position;  
                DblNode<string> *ff;
                ff=test.head->next;
                int fline=1;
                for(int i=0;i<test.count;i++)
                {
                position = ff->data.find(f);  
                if (position != string::npos)//最大值  
                {
                    cout<<fline<<":"<<ff->data<< endl;  
                }
                else  
                {
				    cout << "Not found!" << endl; 
				}
				ff=ff->next;
				fline++;
			    }
				break;
			}
			case 'g':
			{
				cin.get();
			    cout<<"Which line you want to go?  ";
			    int gg;
			    cin>>gg;
			    test.GetElemPtr(gg);
			    cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				break;
			}
		    case 'h':
		    {
		    	cout<<"Valid commands are:"<<endl;
				cout<<"b(egin) "<<"c(hange) "<<"d(el) "<<"e(nd) "<<"f(ind) "<<endl;
	            cout<<"g(o) "<<"h(elp) "<<"i(nsert) "<<"l(ength) "<<"n(ext) "<<endl;
	            cout<<"p(rior) "<<"q(uit) "<<"r(ead) "<<"s(ubstitute) "<<"v(iew) "<<"w(rite) "<<endl;
			    break;
			}
			case 'i':
			{
				cin.get();
				cout<<"Which line you want to insert:  ";
				int ii;
				cin>>ii;
				cout<<"What you want to input:  ";
				string iir;
				cin>>iir;
				test.Insert(ii,iir);
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				break;
			}
			case 'l':
	        {
	        	cout<<"There are "<<test.Length()<<" lines"<<endl;
	        	cout<<"Current line has "<<sizeof(test.curPtr->data)<<endl;
	        	break;
			}
			case 'n':
			{
				if(test.curPosition==test.count)
				{
					cout<<"this is the last line."<<endl; 
				}
				else
				{
					test.curPosition++;
					test.curPtr=test.curPtr->next;
				}
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				break;
			}
			case 'p':
			{
				if(test.curPosition==1)
				{
					cout<<"this is the first line."<<endl;
				}
				else
				{
					test.curPosition--;
					test.curPtr=test.curPtr->back;
				}
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				break;
			}
			case 'q':
			{
				return 0;
				break;
			}
			case 'r':
			{
				int testcount = 0;
				string buffer;
				char buf[1000];
				while(infile.getline(buf,sizeof(buf)))
				{
					buffer=buf;
					testcount=testcount+1;
					test.Insert(testcount,buffer);
				}
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
	        	break;
	        }
	        case 's':
			{
				cin.get();
				cout<<"Which line you want to substitute:  ";
				int ss;
				cin>>ss;
				cout<<"substitute to:  ";
				string ssr;
				cin>>ssr;
				test.SetElem(ss,ssr);
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				break;
			}
			case 'v':
			{
				DblNode<string> *vv;
				vv=test.head;
				for(int i=0;i<test.count;i++)
				{
					cout<<i+1<<":"<<vv->next->data<<endl;
					vv=vv->next;
				}
				break;
			} 
			case 'w':
			{
				outfile<<test.curPtr->data<<endl;//输出文件 
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				break;
			}
		}
    }while(usercommand!='q');
	return 0;
}






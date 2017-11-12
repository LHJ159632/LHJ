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
	ElemType data;//������ 
	DblNode<ElemType> *back;//���ָ�� 
	DblNode<ElemType> *next;//ǰ��ָ�� 
	DblNode();
	DblNode(ElemType item,DblNode<ElemType> *linkback = NULL,DblNode<ElemType>*linknext = NULL);//��֪�������ָ�������ṹ 
};
template<class ElemType>
DblNode<ElemType>::DblNode()
{
	next = NULL;//����ָ����Ϊ�յĽ�� 
}
template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item,DblNode<ElemType> *linkback,DblNode<ElemType>*linknext)
{
	data = item;//������Ϊitem 
	back = linkback; 
	next = linknext;
}


template<class ElemType>
class DblLinkList
{
public:
		DblNode<ElemType> *head;//ͷ���ָ�� 
		
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
	}//˳�� 
	else if(curPosition>position)
	{
		for(;curPosition>position;curPosition--)
		{
			curPtr=curPtr->back;
		}
	}//���� 
	return curPtr;
}

template<class ElemType>
int DblLinkList<ElemType>::Length() const
{
	return count;//������ 
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
		DblNode<ElemType>*tmpPtr;//ָ�� 
		tmpPtr=GetElemPtr(position);//ȷ��λ�� 
		e=tmpPtr->data;//��ȡ���� 
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
		DblNode<ElemType>*tmpPtr;//ָ�� 
		tmpPtr=GetElemPtr(position);//ȷ��λ�� 
		tmpPtr->data=e;//�������� 
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
		tmpPtr=GetElemPtr(position-1);//ȡ��ָ���position-1������ָ�� 
		nextPtr=tmpPtr->next;//nextPtrָ���position����� 
		newPtr=new DblNode<ElemType>(e,tmpPtr,nextPtr);//�����½�� 
		tmpPtr->next=newPtr;//�޸�����ָ�� 
		nextPtr->back=newPtr;//�޸�����ָ�� 
		curPosition=position;//�޸��к� 
		curPtr=newPtr;//�޸�ָ�� 
		count++;//���룺���+1 
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
		}//ĩβ 
		else
		{
			curPosition=position;
			curPtr=tmpPtr->next;
		}//��ĩβ 
		count--;
		delete tmpPtr;
		return SUCCESS; 
	}
}


int main(void)
{
	DblLinkList<string> test;//���� 
	/*�ļ���*/
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
	
	
/*�����ı��༭��*/
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
		        getline(cin,cc1);//���滻�ı� 
		        cout<<"change to:";
		        getline(cin,cc2);//�滻�ı� 
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
                if (position != string::npos)//���ֵ  
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
				outfile<<test.curPtr->data<<endl;//����ļ� 
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				break;
			}
		}
    }while(usercommand!='q');
	return 0;
}






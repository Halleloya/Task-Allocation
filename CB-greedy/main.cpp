#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

//�����趨
int levelNum;    //��������main������һ��ʼ�趨
const int MAXSIZE=1000;  //�������ά�ȣ������������Ӧ�ü���Ƿ���� deviceNum

/////////////////////////////////////////////
int deviceNum;
int quanzhi[MAXSIZE][MAXSIZE]={{0}};  //�ߵ�Ȩֵ
int Tree[MAXSIZE][MAXSIZE]={{0}};
int inTree[MAXSIZE]={0};
int C[MAXSIZE]={0};

ifstream fin;
ofstream fout;

void printTree(int a[MAXSIZE][MAXSIZE])     //�������
{
    for(int i=0; i<deviceNum; i++)
    {
        for (int j=0;j<deviceNum; j++)
        {
            cout<<a[i][j]<<' ';
        }
        cout<<endl;
    }
}

struct Edge      //��(x,y) Ȩֵdata
{
    int x;
    int y;
    int data;

    Edge(int a,int b,int c){x=a; y=b; data =c;}
    bool operator < (const Edge &a) const
    {
        return data>a.data;//��Сֵ����
    }
};


int main(int argc,char *argv[])
{
    fin.open(argv[1]);
    fout.open(argv[2],ios::app );

    fin>>deviceNum;
    levelNum = deviceNum;   ///////////����

    for(int i=0; i<deviceNum; i++)
    {
        for (int j=0;j<deviceNum; j++)
        {
            fin>>quanzhi[i][j];
        }
    }


    int totalEdge=0;
    priority_queue<Edge>que,que1,que2;      //Ȩֵ��������
    for(int i=0; i<deviceNum; i++)
    {
        for (int j=0;j<deviceNum; j++)
        {
            if (quanzhi[i][j]!=0)
            {
                que.push(*new Edge(i,j,quanzhi[i][j]));
                totalEdge++;
            }
        }
    }

    int cnt=0;
    int edgeNum= totalEdge/levelNum;
    for (int p=0; (p<levelNum && cnt<deviceNum-1 ); p++)  //ִ�в�����
    {
        if(p==levelNum-1) edgeNum=totalEdge - edgeNum*(levelNum-1);

        for (int i=0; i<edgeNum; i++)   //ȡ��1������
        {
            que1.push(que.top());
            que.pop();
        }


        while(!que1.empty() && cnt<deviceNum-1)
        {
            while(!que1.empty())      //ȥ���ӵ�����C������
            {
                Edge e= que1.top();
                que1.pop();
                if ( !(inTree[e.y] || Tree[e.y][e.x]) )
                {
                    que2.push(*new Edge(e.x,e.y,C[e.x]));
                }
            }
            if(!que2.empty())    // ���븺����С
            {
                Edge e= que2.top();
                que2.pop();

                inTree[e.y]=1;
                Tree[e.x][e.y]=1;
                C[e.x]+=quanzhi[e.x][e.y];
                cnt++;
              //  cout<<'('<<e.x+1<<','<<e.y+1<<") "<<quanzhi[e.x][e.y]<<endl;
            }

            while (!que2.empty())   // que2����que1��ѭ������
            {
                que1.push(que2.top());
                que2.pop();
            }
        }
    }

    if (cnt==deviceNum-1)        //�ж��Ƿ����е㶼�ӽ�����
    {
        int maxC = 0 , minC = 99999, totalC = 0;
        cout<<"�ɹ�"<<endl;
        for (int i=0; i<deviceNum ;i++)
        {
            totalC+=C[i];
            if (C[i]>maxC) maxC = C[i];
            if(C[i]!=0 && C[i]<minC) minC = C[i];
        }
    //      �ܸ���         �����      ���ؼ���         ��С����
        fout<<totalC<<'\t'<<maxC<<'\t'<<maxC-minC<<'\t'<<minC<<endl;
    }
    else cout<<"ʧ��"<<endl;


    return 0;
}

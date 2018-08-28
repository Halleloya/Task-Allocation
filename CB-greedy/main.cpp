#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

//参数设定
int levelNum;    //层数，在main函数的一开始设定
const int MAXSIZE=1000;  //数组最大维度，程序如果出错应该检查是否大于 deviceNum

/////////////////////////////////////////////
int deviceNum;
int quanzhi[MAXSIZE][MAXSIZE]={{0}};  //边的权值
int Tree[MAXSIZE][MAXSIZE]={{0}};
int inTree[MAXSIZE]={0};
int C[MAXSIZE]={0};

ifstream fin;
ofstream fout;

void printTree(int a[MAXSIZE][MAXSIZE])     //输出矩阵
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

struct Edge      //边(x,y) 权值data
{
    int x;
    int y;
    int data;

    Edge(int a,int b,int c){x=a; y=b; data =c;}
    bool operator < (const Edge &a) const
    {
        return data>a.data;//最小值优先
    }
};


int main(int argc,char *argv[])
{
    fin.open(argv[1]);
    fout.open(argv[2],ios::app );

    fin>>deviceNum;
    levelNum = deviceNum;   ///////////层数

    for(int i=0; i<deviceNum; i++)
    {
        for (int j=0;j<deviceNum; j++)
        {
            fin>>quanzhi[i][j];
        }
    }


    int totalEdge=0;
    priority_queue<Edge>que,que1,que2;      //权值递增排列
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
    for (int p=0; (p<levelNum && cnt<deviceNum-1 ); p++)  //执行层数次
    {
        if(p==levelNum-1) edgeNum=totalEdge - edgeNum*(levelNum-1);

        for (int i=0; i<edgeNum; i++)   //取出1层数据
        {
            que1.push(que.top());
            que.pop();
        }


        while(!que1.empty() && cnt<deviceNum-1)
        {
            while(!que1.empty())      //去除扔掉，按C负载排
            {
                Edge e= que1.top();
                que1.pop();
                if ( !(inTree[e.y] || Tree[e.y][e.x]) )
                {
                    que2.push(*new Edge(e.x,e.y,C[e.x]));
                }
            }
            if(!que2.empty())    // 加入负载最小
            {
                Edge e= que2.top();
                que2.pop();

                inTree[e.y]=1;
                Tree[e.x][e.y]=1;
                C[e.x]+=quanzhi[e.x][e.y];
                cnt++;
              //  cout<<'('<<e.x+1<<','<<e.y+1<<") "<<quanzhi[e.x][e.y]<<endl;
            }

            while (!que2.empty())   // que2倒到que1，循环操作
            {
                que1.push(que2.top());
                que2.pop();
            }
        }
    }

    if (cnt==deviceNum-1)        //判断是否所有点都加进来了
    {
        int maxC = 0 , minC = 99999, totalC = 0;
        cout<<"成功"<<endl;
        for (int i=0; i<deviceNum ;i++)
        {
            totalC+=C[i];
            if (C[i]>maxC) maxC = C[i];
            if(C[i]!=0 && C[i]<minC) minC = C[i];
        }
    //      总负载         最大负载      负载极差         最小负载
        fout<<totalC<<'\t'<<maxC<<'\t'<<maxC-minC<<'\t'<<minC<<endl;
    }
    else cout<<"失败"<<endl;


    return 0;
}

#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <direct.h>
using namespace std;

int main()
{
//生成参数设定
int deviceNum = 100;  //设备数
float p = 0.9;     //无边的概率，即稀疏度
int sampleNum = 10;   //生成样本数目

///////////////////////////////////////////////////
    srand(time(NULL));
    ofstream fout;
    char str[1000];
    int weight;

    for (int i=1; i<=sampleNum;i++)    //文件名从1开始到sampleNum结束
    {
        sprintf(str,"sample%g_%d",p,deviceNum);     //创建文件夹
        mkdir(str);
        sprintf(str,"sample%g_%d\\sample%g_%d_%d.in",p,deviceNum,p,deviceNum,i);  //生成Sample文件
        fout.open(str);

        fout<<deviceNum<<endl;

        for (int j=0; j<deviceNum; j++)
        {

            for (int k=0; k<deviceNum; k++)
            {
                if(j==k){weight=0; }
                else if(  1.0*rand()/RAND_MAX > p )
                    { weight = 500+1000*rand()/RAND_MAX ; }  //生成权值的公式
                else { weight=0; }

                fout<<weight<<'\t';
            }
            fout<<endl;

        }

        fout.close();
    }
    return 0;
}

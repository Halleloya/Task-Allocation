#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <direct.h>
using namespace std;

int main()
{
//���ɲ����趨
int deviceNum = 100;  //�豸��
float p = 0.9;     //�ޱߵĸ��ʣ���ϡ���
int sampleNum = 10;   //����������Ŀ

///////////////////////////////////////////////////
    srand(time(NULL));
    ofstream fout;
    char str[1000];
    int weight;

    for (int i=1; i<=sampleNum;i++)    //�ļ�����1��ʼ��sampleNum����
    {
        sprintf(str,"sample%g_%d",p,deviceNum);     //�����ļ���
        mkdir(str);
        sprintf(str,"sample%g_%d\\sample%g_%d_%d.in",p,deviceNum,p,deviceNum,i);  //����Sample�ļ�
        fout.open(str);

        fout<<deviceNum<<endl;

        for (int j=0; j<deviceNum; j++)
        {

            for (int k=0; k<deviceNum; k++)
            {
                if(j==k){weight=0; }
                else if(  1.0*rand()/RAND_MAX > p )
                    { weight = 500+1000*rand()/RAND_MAX ; }  //����Ȩֵ�Ĺ�ʽ
                else { weight=0; }

                fout<<weight<<'\t';
            }
            fout<<endl;

        }

        fout.close();
    }
    return 0;
}

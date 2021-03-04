#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>

using namespace std;
class SystemOp{
public:
    Login{}
    Logout{}
}
class StuOp
{
public:
    Stu_Login{}  //ѧ����½

    Stu_ReadScore
    {
        
    } //ѧ����ɼ�
    
    
}

class TeaOp
{
public:
    Tea_Login{}     //��ʦ��½
    Tea_ReadClassScore{}        //��ѯ���ſγ̳ɼ�
    Tea_SetPropotion{}          //����ƽ����-��ĩ�ֱ���
    Tea_ModifyScore             //���ĳɼ�
    {
        InputScore{}            //����ƽʱ����ĩ��
        CalScore{}              //��������
    }
    InputScore{}
    CalScore{}
}

class AdminOp
{
public:
    Admin_Login{}
    Admin_Modify
    {
        
    }
}
class Student
{
public:
    string name;
    string number;   //ѧ��
    string college;  //ѧԺ
    string major;    //רҵ
    string course;   //ѧ��ȫ���γ���Ϣ
};

class Teacher
{
public:
    string name;
    string number;   //����
    string course;    //���̿γ����ֵļ���
};

class Admini        //����Ա
{
public:
    string name;
};

class Find       //�������ֵ��
{
public:
    string key;
    string value;
    Find()
    {
        ;
    }
    Find(string a,string b)
    {
        key=a,value=b;
    }
};

class course       //�洢�ڿγ̿����еĿγ���
{
public:
    string cou_name;       //�γ�����
    string stu_name;      //ѧ������       ѧ��ѧ�ţ�
    string position;       //�ڿεص�
    string time;          //�ڿ�ʱ��
    string grade;         //ѧ���ɼ�
};

/*----���ܺ���-----*/
//��ȡ������Ϣ 	������
void openFind(string file_name,multimap<string,string> & x)
{
    fstream f(file_name,ios::binary|ios::in);
    f.seekg(0,ios::end);
    long pos=f.tellg();    //�õ��ļ�����ָ��λ��
    Find temp;
    for(f.seekg(0,ios::beg);f.tellg()!=pos;)
    {
        f.read((char*)&temp,sizeof(temp));
        x.insert(make_pair(temp.key,temp.value));     //��������Ϣ��������
    }
    f.close();
}

//����ѧ�Ż��������ҵ���Ӧλ�ò���ȡ��Ϣ  	��ѧ����Ϣ
template<typename T>
void copyInfo(string info,multimap<string,string> & x,vector<T> & y)    //yΪ��Ҫ��ȡ����Ϣ;��vector����ԭ���Ƿ�ֹ�ж������
{
    int num=x.count(info); 	//������ͬ��
    multimap<string,string>::iterator it=x.find(info);	//��λ����
    for(int i=0;i<num;i++)
    {
        string posi=(*it).second;    //�õ���Ϣ��ƫ����,<�ļ����Ե�ַ&ƫ����>
        string a(posi,0,posi.find('&')),b(posi,posi.find('&')+1,posi.size()-posi.find('&')-1); 	//a �ļ��� b ƫ����
        fstream f(a,ios::binary|ios::in);
        f.seekg(long(sizeof(T)*atoi(b.c_str())),ios::beg);      //ƫ�Ƶ���Ӧλ��
        T temp;
        f.read((char*)&temp,sizeof(T));      //��ȡ��Ϣ
        y.push_back(temp);
        it++;
        f.close();
    }
}

//����ѧ�Ż������������޸ĺ��yд���Ӧλ��	дѧ����Ϣ
template<typename T>
void modifyInfo(string info,multimap<string,string> & x,const T & y)
{
    multimap<string,string>::iterator it=x.find(info);
    string posi=(*it).second;    //�õ���Ϣ��ƫ����,�ļ����Ե�ַ&ƫ����
    string a(posi,0,posi.find('&')),b(posi,posi.find('&')+1,posi.size()-posi.find('&')-1);
    fstream f(a,ios::binary|ios::out);
    f.seekp(long(sizeof(T)*atoi(b.c_str())),ios::beg);
    f.write((char*)&y,sizeof(T));
    f.close();
}

//����ѧ�Ż�������ɾ��ĳ�����������Ϣ		ɾ������
template<typename T>
void deleteIndex(string info,multimap<string,string> & x,string file_name)
{
    fstream f(file_name,ios::binary|ios::out|ios::trunc);
    x.erase(info);
    multimap<string,string>::iterator it=x.begin();    //���޸ĺ��������Ϣ����д���ļ�
    for(;it!=x.end();it++)
    {
        Find temp((*it).first,(*it).second);		//Find ���캯��
        f.write((char*)&temp,sizeof(temp));
    }
    f.close();         //������Ϣ���ļ���ɾ�����
}

//������Ϣ��ֱ�����ļ���׷��,�����ظ���Ϣƫ�������������Ϣǰ���Ѿ���17����Ϣ���򷵻�18��
template<typename T>
int addInfo(const T & info,string file_name)
{
    fstream f(file_name,ios::out|ios::binary|ios::app);
    f.write((char*)&info,sizeof(T));

    f.close();
}

//����������Ϣ				��������
void addIndex(string key,string value,multimap<string,string> & x,string file_name)     //file_nameΪ�����ļ�
{
    x.insert(make_pair(key,value));
    Find temp(key,value);
    fstream f(file_name,ios::binary|ios::app|ios::out);
    f.write((char*)&temp,sizeof(temp));
    f.close();
}

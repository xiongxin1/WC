#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class WC
{
private:
	string path;
	int word;
	int char_;
	int line;
	int code_line;
	int space_line;
	int anno_line;//ע����
public:

	WC(int w = 0, int le = 0, int l = 0, int c_l = 0, int s_l = 0, int a_l = 0);
	void get_from_file();
	void out_way(char symble);
	int c_line(const string &filepath);
	int c_char(const string &filepath);
	int c_word(const string &filepath);
	void ad_line(const string &filepath);//�߼�ѡ��
	~WC() {};
};

//���캯��
WC::WC(int w, int le, int l, int c_l, int s_l, int a_l)
{
	word = w;
	char_ = le;
	line = l;
	code_line = c_l;
	space_line = s_l;
	anno_line = a_l;
}

//��ȡ�ļ�����
void WC::get_from_file()
{
	cout << "�������ļ�·����";
	cin >> path;
	/*ifstream infile(path, ios::in);
	if (!infile)
	{
		cout << "open file error!" << endl;
		exit(1);
	}*/
		c_char(path);//ͳ���ַ�
		c_word(path);//ͳ�Ƶ���
		c_line(path);//ͳ������
		ad_line(path);//�߼�ѡ��
	//infile.close();
}

//ͳ������
int WC::c_line(const string &filePath)
{
	ifstream read(filePath);
	if (read.is_open())
	{
		string buff;
		while (!read.eof())
		{
			getline(read, buff);
			++line;
		}
		read.close();
	}
	return line;
}

//ͳ���ַ���
int WC::c_char(const string &filePath)//�ַ���
{
	ifstream read(filePath);
	if (read.is_open())
	{
		string buff;
		while (!read.eof())
		{
			getline(read, buff);
			for (string::size_type i = 0; i <= buff.size(); i++)
			{
				if (buff[i] >= 32 || buff[i] <= 126)
					++char_;
			}
		}
		read.close();
	}
	return char_;
}

//ͳ�Ƶ�����
int WC::c_word(const string &filePath)
{
	ifstream read(filePath);
	if (read.is_open())
	{
		string buff;
		while (!read.eof())
		{
			getline(read, buff);
			for (string::size_type i = 0; i <= buff.size(); i++)
			{
				if (buff[i] == 32)
					++word;
			}
		}
		read.close();
	}
	return word;
}

void WC::ad_line(const string &filePath)//������
{
	ifstream read(filePath);
	if (read.is_open())
	{
		string buff;
		while (!read.eof())
		{
			int c = 0;
			int s = 0;
			int a = 0;
			getline(read, buff);
			for (string::size_type i = 0; i <= buff.size(); i++)
			{
				if ((buff[i] >= 'A' && buff[i] <= 'Z') || (buff[i] >= 'a' && buff[i] <= 'z'))
				{
					++c;
					a = 0;
					s = 0;
					break;
				}
				else 
					if (buff[i] == '/')
					{
						++a;
						s = 0;
						break;
					}
					else
					{
						++s;
					}
			}
			if (c != 0)
				++code_line;
			if (s != 0)
				++space_line;
			if (a != 0)
				++anno_line;
		}
		read.close();
	}
}

void WC::out_way(char symble)
{
	if (symble == 'c')
		cout << "char:" << char_ << endl;
	if (symble == 'w')
		cout << "  word:" << word << endl;
	if (symble == 'l')
		cout << "  line:" << line << endl;
	if (symble == '*' || symble == '?')
		cout << "char:" << char_ << "  word:" << word << "  line:" << line << endl;
	if (symble == 'a')
		cout << "code_line:" << code_line << "  space_line:" << space_line << "  anno_line:" << anno_line << endl;
}
void  main()
{
	WC wc;
	char symble;
	cout << "�������ȡ���ݵķ�ʽ(c.�ַ��� w.������ l.���� *��?.ͨ���,a���أ�������/����/ע���У�)��";
	cin >> symble;
	wc.get_from_file();
	wc.out_way(symble);
}

//�߼�ѡ��
/*void WC::ad_option(char ch)
{
char ch1[300];
char ch2[3];
while(ch != -1)
{
int k = 0;
int k1 = 0;
int y = 0;
int c_c = 0;
int s_c = 0;
int a_c = 0;

for ( int i=0; ch != '\n';i++ )
{
ch1[i] = ch;
//�жϿ���
if (ch >= 0 && ch <= 32 )
++s_c;
else//��ע���о�ִ����һ��
{
first:	s_c = 0;
goto second;
}
if (ch1[i] == 123 || ch1[i] == 125)
{
for (int j = 0; j < i; j++)//��{�����ߡ�}��ǰ��������ǿո�
if(ch1[j] == 32)  //ֻ���ж��ո�
++s_c;
else goto first;
}
//�жϴ�����
second :
if (ch >= 33 && ch <= 127)//'!'��'~'֮��ɽ������´���
{
++k1;
if (ch == 47)//����һ�Ρ�//���ж�Ϊע�ͷ��ţ�����˴���
{
ch2[++k] = ch;
}
if(ch2[0] == ch2[1])
{
for (int j = 0; j < i; j++)
{
if (ch1[j] == 123 || ch1[i] == 125)
{
++y;
}
}

else
++a_c;//���ֻ������һ�Ρ�{�����ߡ�}���ͳ��֡�//��ע����

else break;

}
}
if (k1 >= 2 || y == 2)
++c_c;
//ע����
{

}
}
if (s_c != 0)
++space_line;
if (a_c >= 2)
++anno_line;
}
}*/
//�������

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
	int anno_line;//注释行
public:

	WC(int w = 0, int le = 0, int l = 0, int c_l = 0, int s_l = 0, int a_l = 0);
	void get_from_file();
	void out_way(char symble);
	int c_line(const string &filepath);
	int c_char(const string &filepath);
	int c_word(const string &filepath);
	void ad_line(const string &filepath);//高级选项
	~WC() {};
};

//构造函数
WC::WC(int w, int le, int l, int c_l, int s_l, int a_l)
{
	word = w;
	char_ = le;
	line = l;
	code_line = c_l;
	space_line = s_l;
	anno_line = a_l;
}

//读取文件函数
void WC::get_from_file()
{
	cout << "请输入文件路径：";
	cin >> path;
	/*ifstream infile(path, ios::in);
	if (!infile)
	{
		cout << "open file error!" << endl;
		exit(1);
	}*/
		c_char(path);//统计字符
		c_word(path);//统计单词
		c_line(path);//统计行数
		ad_line(path);//高级选项
	//infile.close();
}

//统计行数
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

//统计字符数
int WC::c_char(const string &filePath)//字符数
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

//统计单词数
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

void WC::ad_line(const string &filePath)//代码行
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
	cout << "请输入获取数据的方式(c.字符数 w.单词数 l.行数 *或?.通配符,a返回（代码行/空行/注释行）)：";
	cin >> symble;
	wc.get_from_file();
	wc.out_way(symble);
}

//高级选项
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
//判断空行
if (ch >= 0 && ch <= 32 )
++s_c;
else//是注释行就执行这一步
{
first:	s_c = 0;
goto second;
}
if (ch1[i] == 123 || ch1[i] == 125)
{
for (int j = 0; j < i; j++)//“{”或者“}”前面而必须是空格
if(ch1[j] == 32)  //只能判定空格
++s_c;
else goto first;
}
//判断代码行
second :
if (ch >= 33 && ch <= 127)//'!'到'~'之间可进入以下代码
{
++k1;
if (ch == 47)//出现一次‘//’判定为注释符号，进入此代码
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
++a_c;//如果只出现了一次‘{’或者‘}’就出现‘//’注释行

else break;

}
}
if (k1 >= 2 || y == 2)
++c_c;
//注释行
{

}
}
if (s_c != 0)
++space_line;
if (a_c >= 2)
++anno_line;
}
}*/
//输出函数

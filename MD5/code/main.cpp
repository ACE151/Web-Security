#include "my_md5.h"
#include "my_md5.cpp"
 
int main()
{
	string str;
	cout << "MD5���ܳ���������"  << endl;
	my_md5 m;
	while(true){
		cout << "---------------------------------------" << endl;
		cout << "��������Ҫ���ܵ��ַ�����exit��ʾ�˳�����" << endl;
		getline(cin,str);
		if(str == "exit") break;
		m.decode_string(str);
		m.show_result();
	}
	return 0;
}

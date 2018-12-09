#ifndef MY_MD5
#define MY_MD5
#include <cstring>
#include <string>

using namespace std;

// ��ѭ����λ��
int s[4][4] = {{7,12,17,22},{5,9,14,20},{4,11,16,23},{6,10,15,21}};

class my_md5
{
public:
	my_md5(string& str);
	my_md5(); 
	void update(const unsigned char* input_str, int str_length);
	// ��128λ�����ת��Ϊ16��byte���
	void show_result();
	void decode_string(string& str);
	~my_md5();
	
private:
	unsigned int state[4];		// �ĸ��Ĵ�����MD����������128λ
	unsigned int count[2];		// ͳ�Ƴ��ȣ�������ǰ64λ
	unsigned char buffer[512];	// ����
	unsigned char digest[128];	// ���
	bool is_padding;
	char result[33];			// 32λ��������

	// ˽�и������������Ա任
	
	// ��������һ���������任
	void transform(unsigned char block[64]);
	// ��亯������ӳ���
	void padding();

	// ���������������Խ�32λ��unsigned int��8λ��unsigned char����ת�����
	void int_to_char(unsigned char *output,  const unsigned int  *input, int length);
	void char_to_int(unsigned int  *output, const unsigned char *input, int length);

	// ���ƺ���
	unsigned int shift_left(unsigned int num, int pos);
	// �ֺ���
	unsigned int F(unsigned int b, unsigned int c, unsigned int d);
	unsigned int G(unsigned int b, unsigned int c, unsigned int d);
	unsigned int H(unsigned int b, unsigned int c, unsigned int d);
	unsigned int I(unsigned int b, unsigned int c, unsigned int d);
	// ѹ������
	void H_F(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int Ti);
	void H_G(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int Ti);
	void H_H(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int Ti);
	void H_I(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int Ti);
};


#endif



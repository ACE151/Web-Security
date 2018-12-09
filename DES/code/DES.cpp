#include "DES.hpp"
#include <iostream>
#include <cstring>

using namespace std;

DES::DES(){}

DES::~DES(){}

string DES::getM_str(){
	return m_str;
}

string DES::getK_str(){
	return k_str;
}

bitset<64> DES::getK(){
	return K;
}

void DES::setM_str(string temp){
	m_str = temp;
}

void DES::setK_str(string temp){
	m_str = temp;
}

bitset<32> DES::Feistel(bitset<32> R, bitset<48> supkey){
	bitset<48> expand;
	bitset<32> output;
	// ��R��E��չ����Ϊ48λ�Ĵ�E(R)
	for (int i = 0; i < 48; ++i)
	{
		expand[i] = R[E_Extension_Table[i] - 1];
	}
	// ����չ���E(R)������ԿK��48λ��λ�������
	expand ^= supkey;	
	// ��������ƽ���ֳ�8�����飬ÿ�����鳤��Ϊ6������S��ת��Ϊ4λ
	int output_index = 0;
	for (int i = 0; i < 48; i = i + 6)
	{
		// ���� Si ��6λ����Ϊ b1b2b3b4b5b6��
		// ���� n = (b1b6)10 ȷ���кţ��� m = (b2b3b4b5)10 ȷ���к�
		int row = expand[i] * 2 + expand[i + 5];
		int col = expand[i + 1] * 8 + expand[i + 2] * 4 + expand[i + 3] * 2 + expand[i + 4];
		int num = S_Boxs[i / 6][row][col];
		bitset<4> temp(num);	// ��ʮ����תΪ������
		// ��˳�����ӳ�32λ�Ĵ�
		output[output_index] = temp[3];
		output[output_index + 1] = temp[2];
		output[output_index + 2] = temp[1];
		output[output_index + 3] = temp[0];
		output_index += 4;
	}
	// P�û������32λ
	bitset<32> temp = output;
	for (int i = 0; i < 32; ++i)
	{
		output[i] = temp[P_Permutation_Table[i] - 1];
	}
	return output;
}

// �� K ��56����У��λʵ���û� PC-1���õ� C0D0,
// ���� C0 �� D0�ֱ��� PC-1 �û����ǰ28λ�ͺ�28λ��ɡ�
void DES::generateKeys(){
	bitset<56> not_checkout;
	bitset<28> C0;
	bitset<28> D0;
	bitset<48> subkey;
	//PC-1�û�
	for (int i = 0; i < 56; ++i)
	{
		not_checkout[i] = K[PC1_Permutation_Table[i] - 1];
	}
	for(int j = 0; j < 16; j++){
		// ʵ��ǰ��28λ�ֿ�
		for (int i = 0; i < 28; ++i)
		{
			C0[i] = not_checkout[i];
		}
		for (int i = 28; i < 56; ++i)
		{
			D0[i-28] = not_checkout[i];
		}
		// ���Ʋ���
		if(j == 1 || j == 2 || j == 9 || j == 16){
			C0 = leftshift(C0, 1);
			D0 = leftshift(D0, 1);
		}
		else{
			C0 = leftshift(C0, 2);
			D0 = leftshift(D0, 2);
		}
		//PC-2�û�
		for (int i = 0; i < 28; ++i)
		{
			not_checkout[i] = C0[i];
		}
		for (int i = 28; i < 56; ++i)
		{
			not_checkout[i] = D0[i - 28];
		}
		for (int i = 0; i < 48; ++i)
		{
			subkey[i] = not_checkout[PC2_Permutation_Table[i] - 1];
		}
		sub_K[j] = subkey;
	}
}

bitset<28> DES::leftshift(bitset<28> k, int shift_num){
	bitset<28> temp = k;
	for (int i = 0; i < 28 - shift_num; ++i)
	{
		//�����߽����
		if(i - shift_num < 0){
			k[i - shift_num + 28] = temp[i];
		}
		else{
			k[i] = temp[i];
		}
	}
	return k;
}

bitset<64> DES::encrypt(bitset<64> &M){
	bitset<64> cipher;
	bitset<64> after_IP_M;
	bitset<32> left;
	bitset<32> right;

	// IP�û�
	for (int i = 0; i < 64; ++i)
	{
		after_IP_M[i] = M[IP_Permutation_Table[i] - 1];
	}
	for (int i = 0; i < 32; ++i)
	{
		left[i] = after_IP_M[i];
	}
	for (int i = 32; i < 64; ++i)
	{
		right[i - 32] = after_IP_M[i];
	}
	// 16�ֵ���T
	bitset<32> temp;
	for (int i = 0; i < 16; ++i)
	{
		temp = right;
		right = left ^ Feistel(right, sub_K[i]);
		left = temp;
	}
	// �����û�W
	for (int i = 0; i < 32; ++i)
	{
		cipher[i] = right[i];
	}
	for (int i = 32; i < 64; ++i)
	{
		cipher[i] = left[i - 32];
	}
	after_IP_M = cipher;
	// ���û�IP-1
	for (int i = 0; i < 64; ++i)
	{
		cipher[i] = after_IP_M[IP_Inverse_Permutation_Table[i] - 1];
	}
	return cipher;
}

bitset<64> DES::decrypt(bitset<64> &C){
	bitset<64> plain;
	bitset<64> after_IP_C;
	bitset<32> left;
	bitset<32> right;

	// IP�û�
	for (int i = 0; i < 64; ++i)
	{
		after_IP_C[i] = C[IP_Permutation_Table[i] - 1];
	}
	for (int i = 0; i < 32; ++i)
	{
		left[i] = after_IP_C[i];
	}
	for (int i = 32; i < 64; ++i)
	{
		right[i - 32] = after_IP_C[i];
	}
	// 16�ֵ���T,����Ӧ��
	bitset<32> temp;
	for (int i = 0; i < 16; ++i)
	{
		temp = right;
		right = left ^ Feistel(right, sub_K[15 - i]);
		left = temp;
	}
	// �����û�W
	for (int i = 0; i < 32; ++i)
	{
		plain[i] = right[i];
	}
	for (int i = 32; i < 64; ++i)
	{
		plain[i] = left[i - 32];
	}
	after_IP_C = plain;
	// ���û�IP-1
	for (int i = 0; i < 64; ++i)
	{
		plain[i] = after_IP_C[IP_Inverse_Permutation_Table[i] - 1];
	}
	return plain;
}

bitset<64> DES::char_to_bitset(const char s[8]){
	bitset<64> output;
	int output_index = 0;
	for (int i = 0; i < 8; ++i)
	{
		int num = int(s[i]);
		bitset<8> temp(num);
		for (int j = 0; j < 8; ++j)
		{
			output[output_index+j] = temp[7-j];
		}
		output_index += 8;
	}
	return output;
}

string DES::bitset_to_string(bitset<64> m){
	char s[9];
	memset(s,0,9);
	int s_index = 0;
	for(int i = 0; i < 64; i = i + 8){
		int temp = m[i]*128 + m[i+1]*64 + m[i+2]*32 + m[i+3]*16 + m[i+4]*8 + m[i+5]*4 + m[i+6]*2 + m[i+7];
		s[s_index++] = (char)temp;
	}
	string str = s;
	return str;
}

void DES::show_encrypt(string m, string k){
	setK_str(k);
	setM_str(m);
	K = char_to_bitset(k.c_str());
	generateKeys();
	bitset<64> Mes = char_to_bitset(m.c_str());
	bitset<64> ans = encrypt(Mes);
	cout << endl << "DES���ܹ��̣� " << endl;
	cout << "���ģ� " << m << endl;
	cout << "��Կ�� " << k << endl;
	cout <<"���ܽ��--64λ���ģ� " << ans << endl;
	cout << "--------------------------------------------------\n\n";
}

void DES::show_decrypt(bitset<64> c, string k){
	setK_str(k);
	K = char_to_bitset(k.c_str());
	generateKeys();
	bitset<64> m = decrypt(c);
	string str = bitset_to_string(m);
	cout << endl<< "DES���ܹ��̣� " << endl;
	cout << "64λ���ģ� " << c << endl;
	cout << "��Կ�� " << k << endl;
	cout <<"���ܽ��--���ģ� " << str << endl;
	cout << "--------------------------------------------------\n\n";
}



#include <iostream>
#include <string>
#include "DES.cpp"

using namespace std;

void show_hint(){
	cout << "************ Hint ***************\n";
	cout << "Code:    encrypt����DES����\n\t decrypt����DES����\n\t exit�����˳�����\n";
	cout << "*********************************\n";
	cout << "�����ָ�\n";
}

int main(){
	DES myDES;
	string m, k;
	string choose;
	bitset<64> c;
	while(true){
		show_hint();
		cin >> choose;
		if(choose == "encrypt"){
			cout << "�����������ַ��������8λchar���Լ���Կ��8λchar���� " << endl; 
			cin >> m >> k;
			myDES.show_encrypt(m,k);
		}
		else if(choose == "decrypt"){
			cout << "���������ģ�64λbit���Լ���Կ��8λchar���� " << endl; 
			cin >> c >> k;
			myDES.show_decrypt(c,k);
		}
		else if(choose == "exit"){
			break;
		}
	}
	return 0;
}

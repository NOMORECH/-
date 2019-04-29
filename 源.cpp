#include"suffixTree.h"

int main()
{
	string s;
	char c;
	while ((c = getchar()) != '\n')
		s += c;
	suffixTree suffix(s);
	suffix.construct();
	suffix.show();
	while (1) {
		cout << "�����Ӵ���";
		string subString;
		while ((c = getchar()) != '\n')
			subString += c;
		if (subString[0] == '$')
			break;
		cout << "�Ӵ�" << subString << "���ֵĴ�����" << suffix.contain_n(subString) << endl << endl;
	}

	cout << "\n��ظ��Ӵ���" << endl;
	suffix.longest_Rsubstring();

	cout << "�����һ���ַ�����";
	string s1;
	cin >> s1;
	cout << "����ڶ����ַ�����";
	string s2;
	cin >> s2;
	suffix.longest_Psubstring(s1, s2);
	suffix.show();

	cout << endl;
	system("pause");
	return 0;
}
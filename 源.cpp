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
		cout << "输入子串：";
		string subString;
		while ((c = getchar()) != '\n')
			subString += c;
		if (subString[0] == '$')
			break;
		cout << "子串" << subString << "出现的次数：" << suffix.contain_n(subString) << endl << endl;
	}

	cout << "\n最长重复子串：" << endl;
	suffix.longest_Rsubstring();

	cout << "输入第一个字符串：";
	string s1;
	cin >> s1;
	cout << "输入第二个字符串：";
	string s2;
	cin >> s2;
	suffix.longest_Psubstring(s1, s2);
	suffix.show();

	cout << endl;
	system("pause");
	return 0;
}
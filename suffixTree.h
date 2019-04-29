#pragma once
#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

struct node
{
	int start;
	int end;
	vector<node*> subNode;

	node(int s,int e)
	{
		start = s;
		end = e;
	}
	node(int s, int e, vector<node*> next)
	{
		start = s;
		end = e;
		subNode = next;
	}
};

struct tag
{
	int length;
	vector<vector<node*>> subNode;

	tag(int l) { length = l; }
	tag() { length = 0; }
};

struct tag2
{
	int length;
	bool pub;
	vector<vector<node*>> subNode;

	tag2(int l) { length = l; pub = false; }
	tag2() { length = 0; pub = false; }
};

class suffixTree
{
public:
	suffixTree();
	suffixTree(string m);
	~suffixTree();

	void construct();
	void input(string m);
	void show();
	bool contain(string subString);
	int contain_n(string subString);
	void longest_Rsubstring();
	void longest_Psubstring(string a, string b);
private:
	string message;
	int sizeOfMessage;
	vector<node*> root;

	tag length(node* sub);
	tag2 length2(node* sub, int s1, int s2);
};

suffixTree::suffixTree()
{
	sizeOfMessage = 0;
}

suffixTree::suffixTree(string m)
{
	message = m + "$";
	sizeOfMessage = message.size();
}

suffixTree::~suffixTree()
{
	root.~vector();
}

void suffixTree::input(string m)
{
	message = m + "$";
	sizeOfMessage = message.size();
	root.clear();
}

void suffixTree::construct()
{
	if (sizeOfMessage == 0) {
		cout << "error：未输入字符串！" << endl;
		return;
	}

	for (int i = 0; i < sizeOfMessage; i++) {
		node* substring=new node(i, sizeOfMessage - 1);
		bool canMerger = false;
		for (int j = 0; j < root.size(); j++) {
			node* preNode = root[j];
			int same = 0;
			int nSame = 0;
			while (same + substring->start <= substring->end) {
				if (nSame + preNode->start > preNode->end) {
					bool find = false;
					for (int k = 0; k < preNode->subNode.size(); k++) {
						if (message[preNode->subNode[k]->start] == message[substring->start + same]) {
							preNode = preNode->subNode[k];
							nSame = 1;
							same++;
							find = true;
							break;
						}
					}
					if (!find) break;
				}
				else {
					if (message[preNode->start + nSame] != message[substring->start + same])
						break;
					nSame++;
					same++;
				}
			}
			if (same == 0)
				continue;
			else if (preNode->start + nSame <= preNode->end + 1) {
				if (preNode->start == preNode->end) {
					substring->start = substring->start + same;
					preNode->subNode.push_back(substring);
				}
				else {
					node* newString = new node(preNode->start + nSame, preNode->end, preNode->subNode);
					substring->start = substring->start + same;
					preNode->end = preNode->start + nSame - 1;
					preNode->subNode.clear();
					preNode->subNode.push_back(newString);
					preNode->subNode.push_back(substring);
				}
				canMerger = true;
				break;
			}
		}
		if (!canMerger) 
			root.push_back(substring);
	}
}

void suffixTree::show()
{
	cout << endl;
	for (int i = 0; i < root.size(); i++) {
		stack<node*> s;
		s.push(root[i]);
		while (!s.empty()) {
			node* index = s.top(); s.pop();
			if (index == NULL) {
				//cout << endl;
				continue;
			}
			for (int j = 0; index->start + j <= index->end; j++)
				cout << message[index->start + j];
			cout << "-";
			for (int j = index->subNode.size() - 1; j >= 0; j--)
				s.push(index->subNode[j]);
			if (index->subNode.size() == 0)
				cout << endl;
		}
		cout << "---------" << endl;
	}
}

bool suffixTree::contain(string subString)
{
	if (subString.size() < 1 || subString.size() >= message.size())
		return false;

	node* index = NULL;
	int s;
	for (int i = 0; i < root.size(); i++)
		if (message[root[i]->start] == subString[0]) {
			index = root[i];
			s = root[i]->start + 1;
			break;
		}

	if (index == NULL)
		return false;

	for (int i = 1; i < subString.size(); i++) {
		if (s > index->end) {
			bool find = false;
			for (int j = 0; j < index->subNode.size(); j++)
				if (message[index->subNode[j]->start] == subString[i]) {
					index = index->subNode[j];
					s = index->start + 1;
					find = true;
					break;
				}
			if (!find) return false;
		}
		else {
			if (message[s] != subString[i])
				return false;
			s++;
		}
	}
	return true;
}

int suffixTree::contain_n(string subString)
{
	if (subString.size() < 1 || subString.size() >= message.size())
		return 0;

	//定位子串所在的节点
	node* index = NULL;
	int s;
	for (int i = 0; i < root.size(); i++)
		if (message[root[i]->start] == subString[0]) {
			index = root[i];
			s = root[i]->start + 1;
			break;
		}

	if (index == NULL)
		return 0;

	for (int i = 1; i < subString.size(); i++) {
		if (s > index->end) {
			bool find = false;
			for (int j = 0; j < index->subNode.size(); j++)
				if (message[index->subNode[j]->start] == subString[i]) {
					index = index->subNode[j];
					s = index->start + 1;
					find = true;
					break;
				}
			if (!find) return 0;
		}
		else {
			if (message[s] != subString[i])
				return 0;
			s++;
		}
	}

	//计算该节点的叶子节点数
	queue<node*> st;
	st.push(index);
	int count = 0;
	while (!st.empty()) {
		if (st.front()->subNode.size() == 0) 
			count++;
		else
			for (int i = 0; i < st.front()->subNode.size(); i++)
				st.push(st.front()->subNode[i]);
		st.pop();
	}

	return count;
}

void suffixTree::longest_Rsubstring()
{
	tag t;
	t.length = 0;
	for (int i = 0; i < root.size(); i++) {
		tag t2 = length(root[i]);
		if (t2.length > t.length)
			t = t2;
		else if (t2.length == t.length)
			for (int j = 0; j < t2.subNode.size(); j++)
				t.subNode.push_back(t2.subNode[j]);
	}
	if (t.subNode.size() == 0) {
		cout << "无重复子串" << endl;
		return;
	}
	for (int i = 0; i < t.subNode.size(); i++) {
		for (int j = t.subNode[i].size() - 1; j >= 0; j--) 
			for (int k = t.subNode[i][j]->start; k <= t.subNode[i][j]->end; k++)
				cout << message[k];
		cout << endl;
	}
}

tag suffixTree::length(node* sub)
{
	if (sub->subNode.size() == 0)
		return tag(0);

	tag t;
	t.length = 0;
	int maxL = 0;
	for (int i = 0; i < sub->subNode.size(); i++) {
		tag t2 = length(sub->subNode[i]);
		if (t2.length > t.length)
			t = t2;
		else if (t2.length == t.length)
			for (int j = 0; j < t2.subNode.size(); j++)
				t.subNode.push_back(t2.subNode[j]);
	}
	for (int i = 0; i < t.subNode.size(); i++)
		t.subNode[i].push_back(sub);
	if (t.subNode.size() == 0) {
		vector<node*> vec;
		vec.push_back(sub);
		t.subNode.push_back(vec);
	}
	t.length += sub->end - sub->start + 1;

	return t;
}

void suffixTree::longest_Psubstring(string a, string b)
{
	root.clear();
	int s1 = a.size();
	message = a + "!" + b + "$";
	int s2 = message.size();
	sizeOfMessage = s2;
	construct();

	tag2 t;
	t.length = 0;
	for (int i = 0; i < root.size(); i++) {
		tag2 t2 = length2(root[i], s1, s2);
		if (t2.length > t.length && t2.pub)
			t = t2;
		else if (t2.length == t.length && t2.pub)
			for (int j = 0; j < t2.subNode.size(); j++)
				t.subNode.push_back(t2.subNode[j]);
	}
	if (t.subNode.size() == 0) {
		cout << "无公共子串" << endl;
		return;
	}
	for (int i = 0; i < t.subNode.size(); i++) {
		for (int j = t.subNode[i].size() - 1; j >= 0; j--)
			for (int k = t.subNode[i][j]->start; k <= t.subNode[i][j]->end; k++)
				cout << message[k];
		cout << endl;
	}
}

tag2 suffixTree::length2(node* sub, int s1, int s2)
{
	if (sub->subNode.size() == 0)
		return tag2(0);

	tag2 t;
	bool haveS1 = false;
	bool haveS2 =false;
	for (int i = 0; i < sub->subNode.size(); i++) {
		if (sub->subNode[i]->subNode.size() == 0) {
			if (sub->subNode[i]->start <= s1)
				haveS1 = true;
			else
				haveS2 = true;
		}
		else {
			tag2 t2 = length2(sub->subNode[i], s1, s2);
			if (t2.length > t.length && t2.pub)
				t = t2;
			else if (t2.length == t.length && t2.pub)
				for (int j = 0; j < t2.subNode.size(); j++)
					t.subNode.push_back(t2.subNode[j]);
		}
	}
	if (haveS1 && haveS2) {
		t.length = sub->end - sub->start + 1;
		t.pub = true;
		vector<node*> vec;
		vec.push_back(sub);
		t.subNode.push_back(vec);
		return t;
	}

	for (int i = 0; i < sub->subNode.size(); i++) {
		tag2 t2 = length2(sub->subNode[i], s1, s2);
		if (t2.length > t.length && t2.pub)
			t = t2;
		else if (t2.length == t.length && t2.pub)
			for (int j = 0; j < t2.subNode.size(); j++)
				t.subNode.push_back(t2.subNode[j]);
	}
	for (int i = 0; i < t.subNode.size(); i++)
		t.subNode[i].push_back(sub);
	t.length += sub->end - sub->start + 1;

	return t;
}
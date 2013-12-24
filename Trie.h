/**
    Date:2013.12.22
    Author:DJ
    Description:
        Trie.cpp��ͷ�ļ�����Tire_Node�ṹ���Tire���������

*/
#ifndef TRIE_H
#define TRIE_H

#include <iostream>

using namespace std;

const int branchNum = 26;//����26��Ӣ����ĸ��ÿ����������26����֧

/**
����һ��Trie���
*/
struct Trie_Node
{
    bool isWord;//���ֵΪtrue�������ǰ�ڵ�Ϊһ�����ʣ��ַ����У��Ľ�β
    int n_Branch;//��ǰ������֧��
    Trie_Node *branch[branchNum];//���ָ�����飬�����е�ÿ��Ԫ��Ϊһ��ָ�룬�±������Ӧ��ĸ����branch[0]��Ӧa

    Trie_Node()
    {
        this->isWord = false;
        this->n_Branch = 0;

        for(int i = 0; i < branchNum; ++i)
        {
            branch[i] = NULL;
        }
    }
    ~Trie_Node()
    {
        cout << "~Trie_Node()" << endl;
    }

};

class Trie
{
public:
    Trie()
    {
        root = new Trie_Node();
    }
    ~Trie(){}

    bool Insert(const char* word);
    bool Search(const char* word);
    bool Delete(char* word);
    string ShowTrie(Trie_Node* node);

public:
    Trie_Node *root;
};


#endif // TRIE_H

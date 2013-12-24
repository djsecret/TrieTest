/**
    Date:2013.12.22
    Author:DJ
    Description:
        Trie.cpp的头文件，对Tire_Node结构体和Tire类进行声明

*/
#ifndef TRIE_H
#define TRIE_H

#include <iostream>

using namespace std;

const int branchNum = 26;//共有26个英文字母，每个结点最多有26个分支

/**
定义一个Trie结点
*/
struct Trie_Node
{
    bool isWord;//如果值为true，则代表当前节点为一个单词（字符序列）的结尾
    int n_Branch;//当前包含分支数
    Trie_Node *branch[branchNum];//结点指针数组，数组中的每个元素为一个指针，下标代表相应字母，如branch[0]对应a

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

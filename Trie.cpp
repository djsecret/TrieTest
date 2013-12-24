#include "Trie.h"

/** \brief 插入一个单词
 *  从根结点开始，查看结点分支数组中，当前字符对应的元素是否为空，如果为空，则表示没有这个分支，需要新建
    如果不为空，则已经存在，继续向下插入下一个字符
 * \param 待插入单词
 * \return 如果插入成功，返回true
 *
 */

bool Trie::Insert(const char* word)
{
    Trie_Node *node = root;

    while(*word)//遍历字符串的每一个字符
    {
        int location = *word - 'a';
        if(node->branch[location] != NULL)//该字符已经存在
        {
            node = node->branch[location];
        }
        else
        {
            Trie_Node *temp = new Trie_Node();
            node->branch[location] = temp;
            node->n_Branch++;//分支数加1
            node = temp;
        }
        word++;
    }
    if(node->isWord == true)//插入到最后一个字符，是一个单词的结尾，则整个单词已经存在，插入失败
    {
        return false;
    }
    else
    {
        node->isWord = true;
        return true;
    }
}
/** \brief 搜索一个单词
 *  从根结点开始遍历，一次搜索当前字符对应的分支数组元素，如果遇到空，则单词不存在
 * \param 待搜索单词
 * \return 如果查找到，返回true
 *
 */

bool Trie::Search(const char* word)
{
    Trie_Node *node = root;

    while(*word)
    {
        int location = *word - 'a';

        if(node->branch[location] == NULL)
        {
            return false;
        }
        else
        {
            node = node->branch[location];
            word++;
        }
    }
    if(node->isWord == true)
    {
        return true;
    }
    return false;
}

/** \brief 删除一个单词
 *
 * \param 待删除单词
 * \param
 * \return 如果删除删除成功，则返回true
 *
 */

bool Trie::Delete(char* word)
{
    Trie_Node *node = root;
//    Trie_Node *one_Node = NULL;//指向路径中最后一个分叉
//    Trie_Node *word_Node = NULL;//指向路径中最后一个分叉后最后一个isword为true的结点
//    int word_Location = 0;
//    Trie_Node *follow = node;
//    //int loc = 0;//记录上一个
//    int one_Location = 0;//记录最近一个只有一个分支的结点在父亲指针数组的索引，为了删除

    Trie_Node *deleteNode = root;//记录删除结点，可能是最后一个分叉，也可能是最后一个分叉后最后一个isword为true的结点
    char* deleteInWord = word;//记录删除点在word中的位置，这样，该点后面的字符都会从trie中删除


    while(*word)
    {
        int location = *word - 'a';

        if(node->branch[location] != NULL)
        {
            if(node->n_Branch >=2 && node->branch[location]->n_Branch <= 1)//查找最后一个分叉
            {
//                deleteNode = node;
//                one_Location = location;
//                word_Node = NULL;//之前的单词结尾结点都作废
                deleteNode = node;
                deleteInWord = word;
            }

            if(node->isWord == true)//路径中的标记为单词结尾的结点，如果这个结点在最后一个分叉之后，那么删除时，
                                    //只需要删除该结点的后续结点即可
            {
//                word_Node = node;
//                word_Location = location;
                deleteNode = node;
                deleteInWord = word;
            }
            node = node->branch[location];
            word++;
        }
        else//不存在
        {
            return false;
        }
    }

    if(node->isWord == true)//找到了
    {
        if(node->n_Branch != 0)//不是叶子结点，去除标识符
        {
            node->isWord = false;
            node->n_Branch--;
        }
        else
        {
//            if(word_Node != NULL)//说明在最后一个分叉后面，有单词结尾的结点，因此需要删除该结点的后续
//            {
//                word_Node->branch[word_Location] = NULL;
//                word_Node->n_Branch--;
//                delete word_Node->branch[word_Location];
//            }
//            else//说明在最后一个分叉后面，没有单词结尾的结点，因此需要最后一个分叉后面的后续
//            {
//                one_Node->branch[one_Location] = NULL;
//                one_Node->n_Branch--;
//                delete one_Node->branch[one_Location];
//            }

            /**< 保留待删除子字符串的开始结点，即最后一个分叉或者最后一个分叉后面最后一个单词结尾结点
            的下一个结点 ，从该结点开始（包括该结点），都将被删除*/
            int deleteLocation = *deleteInWord - 'a';
            Trie_Node *nextNode = deleteNode->branch[deleteLocation];
            /**< 被删除子字符串的父节点所做的操作 */
            deleteNode->branch[deleteLocation] = NULL;
            deleteNode->n_Branch--;

            while(*deleteInWord)//删除剩余结点
            {
                deleteNode = nextNode;


                deleteInWord++;
                if(*deleteInWord != '\0')//如果没有走到字符的最后一个
                {
                    deleteLocation = *deleteInWord - 'a';
                    nextNode = deleteNode->branch[deleteLocation];
                }

                delete deleteNode;

            }

            //或者可以倒序删除，不过需要在结点中记录指向父节点的指针

        }
        return true;

    }
    return false;
}

/** \brief 显示Trie树
 *  使用递归的方式
 * \param 待打印的Trie_Node
 * \param
 * \return
 *
 */

string Trie::ShowTrie(Trie_Node* node)
{
    string str = "";

    int tempBranch = node->n_Branch;

    if(tempBranch == 0)
    {
        return str;
    }
    else
    {
        str += "-(";
        for(int i = 0; i < branchNum ; ++i)
        {
            if(node->branch[i]!=NULL)
            {
                str += 'a' + i;
                if(node->branch[i]->isWord == true)//单词结尾结点，作注释
                {
                    str += "*";
                }
                str += ShowTrie(node->branch[i]) + ",";
            }

        }
        str = str.substr(0,str.length()-1);
        str += ")";
    }

}

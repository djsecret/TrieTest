#include "Trie.h"

/** \brief ����һ������
 *  �Ӹ���㿪ʼ���鿴����֧�����У���ǰ�ַ���Ӧ��Ԫ���Ƿ�Ϊ�գ����Ϊ�գ����ʾû�������֧����Ҫ�½�
    �����Ϊ�գ����Ѿ����ڣ��������²�����һ���ַ�
 * \param �����뵥��
 * \return �������ɹ�������true
 *
 */

bool Trie::Insert(const char* word)
{
    Trie_Node *node = root;

    while(*word)//�����ַ�����ÿһ���ַ�
    {
        int location = *word - 'a';
        if(node->branch[location] != NULL)//���ַ��Ѿ�����
        {
            node = node->branch[location];
        }
        else
        {
            Trie_Node *temp = new Trie_Node();
            node->branch[location] = temp;
            node->n_Branch++;//��֧����1
            node = temp;
        }
        word++;
    }
    if(node->isWord == true)//���뵽���һ���ַ�����һ�����ʵĽ�β�������������Ѿ����ڣ�����ʧ��
    {
        return false;
    }
    else
    {
        node->isWord = true;
        return true;
    }
}
/** \brief ����һ������
 *  �Ӹ���㿪ʼ������һ��������ǰ�ַ���Ӧ�ķ�֧����Ԫ�أ���������գ��򵥴ʲ�����
 * \param ����������
 * \return ������ҵ�������true
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

/** \brief ɾ��һ������
 *
 * \param ��ɾ������
 * \param
 * \return ���ɾ��ɾ���ɹ����򷵻�true
 *
 */

bool Trie::Delete(char* word)
{
    Trie_Node *node = root;
//    Trie_Node *one_Node = NULL;//ָ��·�������һ���ֲ�
//    Trie_Node *word_Node = NULL;//ָ��·�������һ���ֲ�����һ��iswordΪtrue�Ľ��
//    int word_Location = 0;
//    Trie_Node *follow = node;
//    //int loc = 0;//��¼��һ��
//    int one_Location = 0;//��¼���һ��ֻ��һ����֧�Ľ���ڸ���ָ�������������Ϊ��ɾ��

    Trie_Node *deleteNode = root;//��¼ɾ����㣬���������һ���ֲ棬Ҳ���������һ���ֲ�����һ��iswordΪtrue�Ľ��
    char* deleteInWord = word;//��¼ɾ������word�е�λ�ã��������õ������ַ������trie��ɾ��


    while(*word)
    {
        int location = *word - 'a';

        if(node->branch[location] != NULL)
        {
            if(node->n_Branch >=2 && node->branch[location]->n_Branch <= 1)//�������һ���ֲ�
            {
//                deleteNode = node;
//                one_Location = location;
//                word_Node = NULL;//֮ǰ�ĵ��ʽ�β��㶼����
                deleteNode = node;
                deleteInWord = word;
            }

            if(node->isWord == true)//·���еı��Ϊ���ʽ�β�Ľ�㣬��������������һ���ֲ�֮����ôɾ��ʱ��
                                    //ֻ��Ҫɾ���ý��ĺ�����㼴��
            {
//                word_Node = node;
//                word_Location = location;
                deleteNode = node;
                deleteInWord = word;
            }
            node = node->branch[location];
            word++;
        }
        else//������
        {
            return false;
        }
    }

    if(node->isWord == true)//�ҵ���
    {
        if(node->n_Branch != 0)//����Ҷ�ӽ�㣬ȥ����ʶ��
        {
            node->isWord = false;
            node->n_Branch--;
        }
        else
        {
//            if(word_Node != NULL)//˵�������һ���ֲ���棬�е��ʽ�β�Ľ�㣬�����Ҫɾ���ý��ĺ���
//            {
//                word_Node->branch[word_Location] = NULL;
//                word_Node->n_Branch--;
//                delete word_Node->branch[word_Location];
//            }
//            else//˵�������һ���ֲ���棬û�е��ʽ�β�Ľ�㣬�����Ҫ���һ���ֲ����ĺ���
//            {
//                one_Node->branch[one_Location] = NULL;
//                one_Node->n_Branch--;
//                delete one_Node->branch[one_Location];
//            }

            /**< ������ɾ�����ַ����Ŀ�ʼ��㣬�����һ���ֲ�������һ���ֲ�������һ�����ʽ�β���
            ����һ����� ���Ӹý�㿪ʼ�������ý�㣩��������ɾ��*/
            int deleteLocation = *deleteInWord - 'a';
            Trie_Node *nextNode = deleteNode->branch[deleteLocation];
            /**< ��ɾ�����ַ����ĸ��ڵ������Ĳ��� */
            deleteNode->branch[deleteLocation] = NULL;
            deleteNode->n_Branch--;

            while(*deleteInWord)//ɾ��ʣ����
            {
                deleteNode = nextNode;


                deleteInWord++;
                if(*deleteInWord != '\0')//���û���ߵ��ַ������һ��
                {
                    deleteLocation = *deleteInWord - 'a';
                    nextNode = deleteNode->branch[deleteLocation];
                }

                delete deleteNode;

            }

            //���߿��Ե���ɾ����������Ҫ�ڽ���м�¼ָ�򸸽ڵ��ָ��

        }
        return true;

    }
    return false;
}

/** \brief ��ʾTrie��
 *  ʹ�õݹ�ķ�ʽ
 * \param ����ӡ��Trie_Node
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
                if(node->branch[i]->isWord == true)//���ʽ�β��㣬��ע��
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

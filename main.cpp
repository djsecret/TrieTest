#include "Trie.h"

int main()
{

    Trie *trie = new Trie();

    cout << "--------------------------------------" << endl;
    cout << trie->Insert("a") << endl;
    cout << trie->Insert("bbc") << endl;
    cout << trie->Insert("bb") << endl;
    cout << trie->Insert("abc") << endl;
    cout << trie->Insert("aber") << endl;

    cout << trie->ShowTrie(trie->root) << endl;

    cout << trie->Search("bb") << endl;
    cout << trie->Delete("bbc") << endl;
    cout << trie->Search("bb") << endl;
    cout << trie->Insert("bb") << endl;
    cout << trie->Insert("aberxy") << endl;

    cout << trie->ShowTrie(trie->root) << endl;

    cout << "--------------------------------------" << endl;

    cout << trie->Delete("aberxy") << endl;

    cout << trie->ShowTrie(trie->root) << endl;

    cout << "--------------------------------------" << endl;


    return 0;
}

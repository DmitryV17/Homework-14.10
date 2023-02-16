#include <iostream>
using namespace std;

// ������������� ������ ���������� ������������ ��������, ������� ����������
// �������� ����������� �������� 
#define ALPHABET_SIZE (26)

// ����������� �������� ������� ������ � ������
// ����������� ������ ��������� ����� �� �� �� �z� 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// ��������� ���� ������
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];

    // isWordEnd - true, ���� ���� �������� ������ �����
    bool isWordEnd;
};

// ���������� ����� ���� � ������� ������
struct TrieNode* getNode(void)
{
    struct TrieNode* pNode = new TrieNode;
    pNode->isWordEnd = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// ������� �������
void insert(struct TrieNode* root, const string key)
{
    struct TrieNode* pCrawl = root;

    for (int level = 0; level < key.length(); level++) {
        int index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // �������� ��������� ���� ��� ����
    pCrawl->isWordEnd = true;
}

// ���������� 0, ���� ������� ���� ����� �������� �������
// ���� ��� �������� �������� ����� NULL, ������� 1.
bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}

// ����������� ������� ��� ������ �������������� ����������� ��� �������
// �����.
void suggestionsRec(struct TrieNode* root,
    string currPrefix)
{
    // �������  ������ � ������  � �������� ���������
    if (root->isWordEnd)
        cout << currPrefix << endl;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i]) {
            // �������� ������� ��������� ����
            char child = 'a' + i;
            suggestionsRec(root->children[i],
                currPrefix + child);
        }
}

// ������� ����������� ��� ��������� �������� �������.
int printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root;
    for (char c : query) {
        int ind = CHAR_TO_INDEX(c);

        // ���� �� ���� ������ � ������  �� ����� ����� ��������
        if (!pCrawl->children[ind])
            return 0;

        pCrawl = pCrawl->children[ind];
    }
    // ���� ������� ������������ ��� �����, ��
    // ��� ��������� ���� ����������
    //  �� ��������� �  ���������������  ����.
    if (isLastNode(pCrawl)) {
        cout << query << endl;
        return -1;
    }
    suggestionsRec(pCrawl, query);
    return 1;
}


int main()
{
    do { // ���� ����� ��������� ���������� �������� ����� ������� ���������� 
        struct TrieNode* root = getNode(); // ������� � �������� ����������� �����
        insert(root, "hello");
        insert(root, "dog");
        insert(root, "hell");
        insert(root, "cat");
        insert(root, "a");
        insert(root, "hel");
        insert(root, "help");
        insert(root, "helps");
        insert(root, "helping");
        insert(root, "moon");
        insert(root, "turtle");
        insert(root, "roof");
        insert(root, "door");
        insert(root, "monster");
        insert(root, "rock");
        insert(root, "book");
        insert(root, "black");
        insert(root, "white");
        insert(root, "red");
        string word; //������ ���������� ����� ���������� ������� ������������
        cout << "Enter part of a word(Use only English letters with small size) : " << endl;
        cin >> word; //��������� ������

        int comp = printAutoSuggestions(root, word); // ���������� � ������� ���������

        if (comp == -1)
            cout << "No other strings found with this prefix\n"; // ���� ������ ��� ������ ��������� 

        else if (comp == 0)
            cout << "No string found with this prefix\n"; // ���� ��� ���������� �� ������� � ����� �������

    } while (true);
}
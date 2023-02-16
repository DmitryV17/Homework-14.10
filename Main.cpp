#include <iostream>
using namespace std;

// Устанавливаем массив указателей используемых символов, равныый количеству
// символов английского алфавита 
#define ALPHABET_SIZE (26)

// Преобразует ключевой текущий символ в индекс
// используйте только маленькие буквы от «а» до «z» 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// Структура узла дерева
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];

    // isWordEnd - true, если ключ является концом слова
    bool isWordEnd;
};

// Возвращает новый узел с пустыми детьми
struct TrieNode* getNode(void)
{
    struct TrieNode* pNode = new TrieNode;
    pNode->isWordEnd = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// Функция вставки
void insert(struct TrieNode* root, const string key)
{
    struct TrieNode* pCrawl = root;

    for (int level = 0; level < key.length(); level++) {
        int index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // Пометить последний узел как лист
    pCrawl->isWordEnd = true;
}

// Возвращает 0, если текущий узел имеет дочерний элемент
// Если все дочерние элементы равны NULL, вернуть 1.
bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}

// Рекурсивная функция для печати автоматических предложений для данного
// узела.
void suggestionsRec(struct TrieNode* root,
    string currPrefix)
{
    // Находим  строку в дереве  с заданным префиксом
    if (root->isWordEnd)
        cout << currPrefix << endl;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i]) {
            // значение символа дочернего узла
            char child = 'a' + i;
            suggestionsRec(root->children[i],
                currPrefix + child);
        }
}

// вывести предложения для заданного префикса запроса.
int printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root;
    for (char c : query) {
        int ind = CHAR_TO_INDEX(c);

        // Если ни одна строка в дереве  не имеет этого префикса
        if (!pCrawl->children[ind])
            return 0;

        pCrawl = pCrawl->children[ind];
    }
    // Если префикс присутствует как слово, но
    // нет поддерева ниже последнего
    //  то остановка в  соответствующем  узле.
    if (isLastNode(pCrawl)) {
        cout << query << endl;
        return -1;
    }
    suggestionsRec(pCrawl, query);
    return 1;
}


int main()
{
    do { // Цикл чтобы программа продолжала работать после первого результата 
        struct TrieNode* root = getNode(); // Создаем и заплняем преффиксное древо
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
        string word; //Вводем переменную чтобы записывать запросы пользователя
        cout << "Enter part of a word(Use only English letters with small size) : " << endl;
        cin >> word; //считываем запрос

        int comp = printAutoSuggestions(root, word); // Сравниваем и выводим результат

        if (comp == -1)
            cout << "No other strings found with this prefix\n"; // Если больше нет других вариантов 

        else if (comp == 0)
            cout << "No string found with this prefix\n"; // Если нет совпадений со словами в нашем словаре

    } while (true);
}
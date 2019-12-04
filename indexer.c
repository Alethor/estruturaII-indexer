#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define ALPHABET_SIZE (26)

typedef struct Hash
{
    char chave[200];
    int valor;
} hash;

typedef struct Trie
{
    int isWord;
    int count;
    struct Trie *children[ALPHABET_SIZE];
} trie;

struct Trie *newNode()
{

    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));

    node->isWord = 0;

    for (int i = 0; i < 26; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

int isWord(struct Trie *node)
{
    if (node->isWord == 1)
    {
        return node->isWord;
    }
}

void insert(struct Trie *root, const char *key)
{

    int length = strlen(key);
    struct Trie *pCrawl = root;

    for (int level = 0; level < length; level++)
    {

        int index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            pCrawl->children[index] = newNode();
        pCrawl = pCrawl->children[index];
    }

    // marca com 1 se for folha (palavra)
    pCrawl->count++;
    pCrawl->isWord = 1;
    return;
}

int search(struct Trie *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;

    struct Trie *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
        {

            return 0;
        }

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl->count);
}

void display(struct Trie *root, char str[], int level, int n)
{
    struct Hash vet[n];
    int i = 0;

    if (isWord(root) == 1)
    {
        str[level] = '\0';

        if (level < n)
        {
            strcpy(vet[level].chave, str);
            vet[level].valor = root->count;
        }
        else if (vet[n - 1].valor < root->count)
        {
            strcpy(vet[n - 1].chave, str);
            vet[n - 1].valor = root->count;
        }
    }
    printf("%s -> %d\n", vet[level].chave, vet[level].valor);

for (i = 0; i < ALPHABET_SIZE; i++)
{
    // if NON NULL child is found
    // add parent key to str and
    // call the display function recursively
    // for child node
    if (root->children[i])
    {
        str[level] = i + 'a';
        display(root->children[i], str, level + 1,n);
    }
}
}

int assembleTrie(char param[50], struct Trie *root)
{

    printf("cheguei");

    FILE *file;
    char word[100];
    int i = 0;
    int x = 0;
    int n = 3;
    int tword = 0;
    char c;

    file = fopen(param, "r");

    if (file == NULL)
    {
        printf("\n -- Problema ao abrir o arquivo de texto! -- \n");
    }
    else
    {

        while ((c = getc(file)) != EOF)
        {
            c = tolower(c);
            if ((c > 47) && (c < 58))
            {
                word[i] = c;
                i++;
            }
            else if ((c >= 97) && (c <= 122))
            {
                word[i] = c;
                i++;
            }
            else if ((c == ' ') && (i == 0))
            {
            }
            else if ((c == '\n') || (c == 32))
            {
                word[i] = '\0';
                tword++;
                insert(root, word);
                //printf(" %s ", word);
                i = 0;
            }
        }
    }
    return tword;
}

int main(int argc, char *argv[])
{
    int tword = 0;
    char word[100];
    int level = 0;

    for (int i = 0; i < argc; i++)
    {
        printf(" %s ", argv[i]);
    }
    if (strcmp(argv[1], "--freq") == 0)
    {
        printf("sugma terminal");
        printf(" %s ", argv[3]);
    }
    else if (strcmp(argv[1], "--freq-word") == 0)
    {

        struct Trie *root = newNode();
        char param[50];
        int x = 0;
        char n = 3;
        printf("grande dia\n");

        tword = assembleTrie(argv[3], root);
        x = search(root, argv[2]);
        printf("\n -- A palavra '%s' aparece %d vezes-- \n", argv[2], x);

    }
    else
    {
        printf("erro absurdo");
    }
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define ALPHABET_SIZE (26)

typedef struct TF
{
    char word[100];
    char arch[100];
    float tword;
    float fword;
    float tf;
    int pres;
} tf;

typedef struct Nodo
{
    struct TF dados;
    struct Nodo *prox;
} Nodo;

void inicializa_lista(Nodo **N) //inicializa a lista
{
    *N = NULL;
}

Nodo *Cria_Nodo() //aloca memória para o nodo
{
    Nodo *p;
    p = (Nodo *)malloc(sizeof(Nodo));
    if (!p)
    {
        printf("Problema de alocação");
        exit(0);
    }
    return p;
}

void insere_fim_lista(Nodo **N, struct TF dado)
{
    Nodo *novo, *aux;
    novo = Cria_Nodo();
    float fw = 0;
    float tw = 0;
    float media;


    fw = dado.fword;
  
    tw = dado.tword;

    media = ((fw)/(tw));
    novo->dados.tf = media;
    printf("%.10f\n",novo->dados.tf);
    strcpy(novo->dados.arch, dado.arch);
    strcpy(novo->dados.word, dado.word);
    novo->dados.fword = dado.fword;
    novo->dados.tword = dado.tword;
    novo->prox = NULL;
    if (*N == NULL)
        *N = novo;
    else
    {
        aux = *N;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

void imprime_lista_ecandeada(Nodo *N)
{
    Nodo *aux;
    float media;

    if (N == NULL)
        printf("\n A lista está vazia!!");
    else
    {
        for (aux = N; aux != NULL; aux = aux->prox)

            printf("------\nArquivo: %s\nPalavra: %s\nTotal Palavras: %.2f\nQuantidade: %.2f\nMedia: %.10f\n", aux->dados.arch, aux->dados.word, aux->dados.tword, aux->dados.fword,aux->dados.tf);
    }
}
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

int assembleTrie(char param[100], struct Trie *root)
{

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
    fclose(file);
}

void split(char term[100], char w[][100])
{
    char *token;
    int x = 0;
    char *delim = " .,/";

    token = strtok(term, delim);

    while (token != NULL)
    {
        strcpy(w[x], token);
        token = strtok(NULL, " ");
        printf("%s\n", w[x]);
        x++;
    }
}

int main(int argc, char *argv[])
{
    struct Hash *vet;
    int tword = 0;
    char word[100];
    int level = 0;
    struct Trie *root = newNode();
    struct TF no;
    //crialista
    Nodo *Mylist;
    inicializa_lista(&Mylist);

    if (strcmp(argv[1], "--freq") == 0)
    {
        int j = 0;
        //struct Hash vet[20];

        printf(" %s ", argv[3]);
        tword = assembleTrie(argv[3], root);
        //display(root, word, level, vet, j);
    }
    else if (strcmp(argv[1], "--freq-word") == 0)
    {

        char param[50];
        int x = 0;
        char n = 3;
        printf("grande dia\n");

        tword = assembleTrie(argv[3], root);
        x = search(root, argv[2]);
        printf("\n -- A palavra '%s' aparece %d vezes-- \n", argv[2], x);
    }
    else if (strcmp(argv[1], "--search") == 0)
    {
        char term[100];
        int i = 0;
        int p = 0;
        int x = 0;
        int a = 0;
        int j = 0;
        char *token;
        char arch[argc - 3][100];
        
        printf("argc: %d\n",argc);
        
        for(i=0;i<argc;i++){
        printf("argv: %s\n",argv[i]);
        }
        strcpy(term, argv[2]);
        

        for (i = 0; term[i] != '\0'; i++)
        {
            if ((term[i] == ' ')|| term[i] == '\0')
            {
                p++;
            }
        }
        char w[p][100];
        split(term, w);
        printf("%s\n", term);


        for (i = 3; i < argc; i++)
        {
            strcpy(arch[j], argv[i]);
            a++;
            j++;
        }

     
    
        for (i = 0; i < a; i++)
        {
            root = newNode();
            no.tword = assembleTrie(arch[i], root);
            for (j = 0; j <= p; j++)
            {
                printf("----Palavra: %s----- \n", w[j]);
                no.fword = search(root, w[j]);
                strcpy(no.word, w[j]);
                strcpy(no.arch, arch[i]);
                insere_fim_lista(&Mylist, no);
            }
            free(root);
        }

        imprime_lista_ecandeada(Mylist);
    }
    else
    {
        printf("erro absurdo");
    }
}
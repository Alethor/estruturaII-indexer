#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABET_SIZE (26)

struct Hash{
    char chave[200];
    int valor;
}hash;

struct Trie
{
    int isWord;
    int count;
    struct Trie * children[ALPHABET_SIZE];

};

struct Trie * newNode(){

    struct Trie * node = (struct Trie *)malloc(sizeof(struct Trie));
    
    node -> isWord = 0;

    for (int i = 0; i < 26; i++){
    node -> children[i] = NULL;
    }
    return node;
}

int isWord(struct Trie * node){
    if(node->isWord == 1){
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
    pCrawl->count ++;
    pCrawl-> isWord = 1;
    
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
           
            return 0 ; 
       
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    return (pCrawl-> count); 
}

void display(struct Trie* root, struct Hash paval, int level, int n) 
{ 
    int i; 
    struct Hash vet[n];

    // If node is leaf node, it indicates end 
    // of string, so a null character is added 
    // and string is displayed 
    if (isWord(root) == 1)  
    { 

        paval.chave[level] = '\0'; 
        paval.valor = root->count;
       
      if(paval.valor >vet[i].valor){
          strcpy(vet[i].chave, paval.chave);
          vet[i].valor = paval.valor;
          printf("%s - > %d\n",vet[i].chave, vet[i].valor);
          i++;
      }
       
        
    } 
  
    for (i = 0; i < ALPHABET_SIZE; i++)  
    { 
        // if NON NULL child is found 
        // add parent key to str and 
        // call the display function recursively 
        // for child node 
        if (root->children[i])  
        { 
            paval.chave[level] = i + 'a'; 
            display(root->children[i], paval, level + 1,n); 
        } 
    } 
} 


void main(){

struct Trie * root = newNode();

FILE *file;
char word[200];
int i = 0;
int x = 0;
struct Hash bgr;
struct Hash * rec;
int n = 3;
int tword = 0;
//char * token;
//char delim[] = {"  !?;.,(){}[],'"};
char c;

file = fopen("103.txt", "r");

if(file == NULL){
    printf("\n -- Problema ao abrir o arquivo de texto! -- \n");

}else{                                                                                                                                                                                                                                                                                                                                                                                                      

    while((c = getc(file)) != EOF){
        c = tolower(c);
        if((c > 47) && (c<58)){
            word[i] = c;
            i++;
        }else if((c>=97)&&(c<=122)){
            word[i] = c;
            i++;
        }else if((c == ' ')&&(i == 0)){

        }else if((c == '\n')||(c == 32)){
            word[i] = '\0';
             tword++;
             //printf(" %s ", word);
             insert(root,word);
             i = 0;
        }
       
    }
    x = search(root,"dois");
    printf("\n -----------%d-------------\n",x);
    printf("---total: %d---\n",tword);
    fclose(file);

    display(root,bgr,x,n);

   /* for(i = 0; i<n; i++){
       printf("-- %s -> %d -- \n",rec[i].chave, rec[i].valor);
    }*/

}
}


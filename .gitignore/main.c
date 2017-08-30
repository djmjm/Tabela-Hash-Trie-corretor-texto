#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// declaração funções + estruturas

typedef struct HASH HASH;
typedef struct VECTOR VECTOR;
typedef struct VECTOR2 VECTOR2;
typedef struct TRIE TRIE;

struct VECTOR2{
    char string[105];
};

struct TRIE{
    
    int endFinal;
    int validade;
    
    TRIE *branch;
};

struct VECTOR{
    char *strin;
    int validade;
};

struct HASH{
    long int max;
    int inside;
    long int colisions;
    VECTOR *vetor;
};

HASH *create_hash(int max);
void showHash(HASH *hash);
void fHash(HASH *hash, char *str, int makeReHash);
void fHash2(HASH *hash, char *str, int makeReHash);
void fHash3(HASH *hash, char *str, int makeReHash);
void fHash4(HASH *hash, char *str, int makeReHash);
void fHash5(HASH *hash, char *str, int makeReHash);
void reHash(HASH *hash);
int search(HASH *hash, char *str);
void fDelete(HASH *hash, char *str);

void AddTrie(TRIE *arvore, char *str);
TRIE *createTrie();
VECTOR2 *searchTrie(TRIE *arvore, char *str, VECTOR2 *strList, int posStr, int posList, char *strAux);
void listTrie(TRIE *arvore);
void listTrieSimilarWords(TRIE *arvore, char *str, int posChar, int posCharAux, int numberErrors, char *strAux, int tamWord, int *flag);
void listTrieOneWrongWord(TRIE *arvore, char *str, int posChar, int posCharAux, int numberErrors, char *strAux, int tamWord, int *flag);
void listTrieOneMoreWord(TRIE *arvore, char *str, int posChar, int posCharAux, int numberErrors, char *strAux, int tamWord, int *flag);
void listTrieInverseWord(TRIE *arvore, char *str, int posChar, int posCharAux, int numberErrors, char *strAux, int tamWord, int *flag);
void deleteTrie(TRIE *arvore, char *str, int posStr, int tamWord);

void MenuSearch(HASH *hash, TRIE *arvore, char *str);


// main

int main()
{
    
    srand(time(NULL));
    char string[100] = "";
    
    
    TRIE *arvore = createTrie();
    
    HASH *hash = create_hash(1000);
    char aux[100] = " ";
    while(1){
        
        fgets(string, 100, stdin);
        string[strlen(string)-1] = '\0';
        
        if (checkStrin(string)){
            strcpy(aux, string);
            MenuSearch(hash, arvore, string);
        }
        else if(string[0] == '*'){
            //printf("%d \n", hash->colisions); descomentar para mostrar numero colisões
            exit(1);
            
        }
        else if(string[0] == '+')
            if (checkStrin(aux)){
                AddTrie(arvore, aux);
                fHash(hash, aux, 0);
            }
            else printf("fail\n");
        else if(string[0] == '-'){
           fDelete(hash, aux);
           deleteTrie(arvore, aux, 0, 0);
        }
        
        //showHash(hash); //descomentar para mostrar hash a cada inserção
        //listTrie(arvore); //descomentar para mostrar trie a cada inserção
        //printf("\n");
    }
    
    return 0;

}

// cria hash

HASH *create_hash(int max){
    HASH *newHash = (HASH*)malloc( sizeof(HASH));
    newHash->vetor = (VECTOR*)malloc(max * sizeof(VECTOR));
    newHash->max = max;
    newHash->inside = 0;
    newHash->colisions = 0;
    
    
    return newHash;
}

// mostra conteúdo hash

void showHash(HASH *hash){
    printf("--------------------\n");
   
   int i;
   for(i = 0; i < hash->max; i++){
       if(hash->vetor[i].validade == 1)
        printf("%d - %s \n", i+1, hash->vetor[i].strin);
        else printf("%d - --- \n", i+1);
   }
   printf("-------------------- %d %d \n", hash->inside, hash->colisions);
    
}

// função hash

void fHash(HASH *hash, char *str, int makeReHash){
    
    if( (hash->inside == hash->max)){
            reHash(hash);
            makeReHash = 0;
    }
    
    if((makeReHash >= 100)){
        fHash5(hash, str, makeReHash);
        return;
        
        
    }
    
    long int number = 0, sum = 0;
    int i = 0, cont  = 0;
    
    for(i = 0; str[i] != '\0'; i++){
            
            if(cont == 3){
                number = number * 256;
                sum += number;
                number = 0;
            }
            
            int aux = str[i];
            number += aux;
            cont++;
    }
    
    number  = sum % (hash->max);
        
    if(hash->inside < hash->max){
        
        if(hash->vetor[number].validade == 1){
            if(strcmp(hash->vetor[number].strin, str) != 0){
                char strAux[200];
                strcpy(strAux, hash->vetor[number].strin);
                strcpy(hash->vetor[number].strin, str);
                hash->colisions++;
                fHash2(hash, strAux, ++makeReHash);
            }else printf("fail\n");
            
        }else{
        
            hash->vetor[number].strin = (char *)malloc(105* sizeof(char));
            strcpy(hash->vetor[number].strin, str);
            hash->vetor[number].validade = 1;
            hash->inside++;
            
            printf("ok\n");
        
        }
        
    }
    
}

// Função hash 2

void fHash2(HASH *hash, char *str, int makeReHash){
    
    
    if( (hash->inside == hash->max) ){
            reHash(hash);
            makeReHash = 0;
    }
    
    if((makeReHash >= 100)){
        fHash5(hash, str, makeReHash);
        return;
        
    }
    
    int i = 0;
    long int number = 0;
    
    for(i = 0; str[i] != '\0'; i++){
        int aux = str[i];
        number = number ^ aux;
        
    }
    
    number = number * 11;
    number  = number % (hash->max);
        
    if(hash->inside < hash->max){
        
        if(hash->vetor[number].validade == 1){

            if(strcmp(hash->vetor[number].strin, str) != 0){
                char strAux[200];
                strcpy(strAux, hash->vetor[number].strin);
                strcpy(hash->vetor[number].strin, str);
                hash->colisions++;
                fHash3(hash, strAux, ++makeReHash);
            }else printf("fail\n");
            
        }else{
        
            hash->vetor[number].strin = (char *)malloc(105* sizeof(char));
            strcpy(hash->vetor[number].strin, str);
            hash->vetor[number].validade = 1;
            hash->inside++;
            
            printf("ok \n");
        
        }
        
    }
    
}

// Função hash 3

void fHash3(HASH *hash, char *str, int makeReHash){
    
    if( (hash->inside == hash->max) ){
            reHash(hash);
            makeReHash = 0;
    }
    
    if((makeReHash >= 100)){
        fHash5(hash, str, makeReHash);
        return;
        
    }
    
    int i = 0;
    long int number = 1;
    
    for(i = 0; str[i] != '\0'; i++){
        if(i < 3)
            number = number*37 + str[i];  
        else number += str[i]; 
        
    }
    
    number  = number % (hash->max);
        
    if(hash->inside < hash->max){
        
        if(hash->vetor[number].validade == 1){
            if(strcmp(hash->vetor[number].strin, str) != 0){
                char strAux[200];
                strcpy(strAux, hash->vetor[number].strin);
                strcpy(hash->vetor[number].strin, str);
                hash->colisions++;
                fHash4(hash, strAux, ++makeReHash);
            }else printf("fail\n");
            
        }else{
        
            hash->vetor[number].strin = (char *)malloc(105* sizeof(char));
            strcpy(hash->vetor[number].strin, str);
            hash->vetor[number].validade = 1;
            hash->inside++;
            
            printf("ok\n");
        
        }
        
    }
    
}

// Função hash 4

void fHash4(HASH *hash, char *str, int makeReHash){
    
    if( (hash->inside == hash->max) ){
            reHash(hash);
            makeReHash = 0;
    }
    
    if((makeReHash >= 100)){
        
        fHash5(hash, str, makeReHash);
        return;
        
    }
    
    int i = 0;
    long int number = 0;
    
    for(i = 0; str[i] != '\0'; i++){
        if(i < 6)
            number = ((5831 << 5) + number) + str[i];  
        else number += str[i]; 
        
    }
    
    number  = number % (hash->max);
        
    if(hash->inside < hash->max){
        
        if(hash->vetor[number].validade == 1){
            if(strcmp(hash->vetor[number].strin, str) != 0){
                char strAux[200];
                strcpy(strAux, hash->vetor[number].strin);
                strcpy(hash->vetor[number].strin, str);
                hash->colisions++;
                fHash(hash, strAux, ++makeReHash);
            }else printf("fail\n");
            
        }else{
        
            hash->vetor[number].strin = (char *)malloc(105* sizeof(char));
            strcpy(hash->vetor[number].strin, str);
            hash->vetor[number].validade = 1;
            hash->inside++;
            
            printf("ok\n");
        
        }
        
    }
    
}

// // Função hash 5

void fHash5(HASH *hash, char *str, int makeReHash){
    
    if( (hash->inside >= hash->max) ){
            reHash(hash);
            makeReHash = 0;
    }
    
    int i = 0;
    long int number = 0;
    
    for(i = 0; str[i] != '\0'; i++){
        number += str[i];
        
    }
    
    number  = number % (hash->max);
        
    if(hash->inside < hash->max){
        
        while(hash->vetor[number].validade == 1){
            if(strcmp(str, hash->vetor[number].strin) !=0){
                if(number < hash->max - 1)
                    number++;
                else number = 0;
            
            }else {
                printf("fail\n");
                return;
            }
        }
        
        hash->vetor[number].strin = (char *)malloc(105* sizeof(char));
        strcpy(hash->vetor[number].strin, str);
        hash->vetor[number].validade = 1;
        hash->inside++;
        
        printf("ok\n");
        
        
    }
     
     printf("ok\n");
    
}

// função rehash

void reHash(HASH *hash){
    long int maxPrevious = hash->max;
    hash->max = hash->max * 2;
    
    
    hash->vetor = (VECTOR *)realloc(hash->vetor, hash->max * sizeof(VECTOR) );
    
        
    int i;
	    
    for(i = maxPrevious; i < hash->max; i++){
        hash->vetor[i].validade = 0;
    }
     
     for(i = 0; i < maxPrevious; i++){
         
         if(hash->vetor[i].validade == 1){
             char aux[100];
             strcpy(aux, hash->vetor[i].strin);
             hash->inside--;
             hash->vetor[i].validade = 0;
             free(hash->vetor[i].strin);
             fHash(hash, aux, 0);
         }  
             
         
     }
    
    
}

// função de busca na hash

int search(HASH *hash, char *str){
    
    long int number = 0, sum = 0;
    int i = 0, cont  = 0;
    
    for(i = 0; str[i] != '\0'; i++){
            
            if(cont == 3){
                number = number * 256;
                sum += number;
                number = 0;
            }
            
            int aux = str[i];
            number += aux;
            cont++;
    }
    
    number  = sum % (hash->max);
    
    if(hash->vetor[number].validade == 1){
        if (strcmp(hash->vetor[number].strin, str) == 0){
            return 1;
        }
    }
    
    number = 0;
    
    for(i = 0; str[i] != '\0'; i++){
        int aux = str[i];
        number = number ^ aux;
        
    }
    
    number = number * 11;
    number  = number % (hash->max);
    
    if(hash->vetor[number].validade == 1){
        if (strcmp(hash->vetor[number].strin, str) == 0){
            return 1;
        }
    }
    
    number = 1;
    
    for(i = 0; str[i] != '\0'; i++){
        if(i < 3)
            number = number*37 + str[i];  
        else number += str[i]; 
        
    }
    
    number  = number % (hash->max);
    
    if(hash->vetor[number].validade == 1){
        if (strcmp(hash->vetor[number].strin, str) == 0){
            return 1;
        }
    }
    
    number = 0;
    
    for(i = 0; str[i] != '\0'; i++){
        if(i < 6)
            number = ((5831 << 5) + number) + str[i];  
        else number += str[i]; 
        
    }
    
    number  = number % (hash->max);
    
    if(hash->vetor[number].validade == 1){
        if (strcmp(hash->vetor[number].strin, str) == 0){
            return 1;
        }
    }
    
    
    int contador = 0;
    
    number = 0;
    
    for(i = 0; str[i] != '\0'; i++){
        number += str[i];
        
    }
    
    return 0;
    
    
    number  = (int) number % (hash->max);
    
    while(contador < hash->max - 1){
        if(hash->vetor[number].validade == 0){
            return 0;
        }else{
            if(hash->vetor[number].strin != NULL){
				if(strcmp(hash->vetor[number].strin, str) == 0){
                	return 1;
            	}else{
                	if(number < hash->max){
                  	 number++;
                	}else{
                    	number = 0;
               		}
                   
            	}
            
        	}
        }
        
        contador++;
        
    }

    
    return 0;

 
    
}

// verifica se palavra deve ser aceita

int checkStrin(char *str){
    
    if (str[0] == 45)
        return 0;
    
    int i = 0;
    for(i = 0; str[i] != '\0'; i++){
        if ( ((str[i] >= 91) && (str[i] <= 96)) || (str[i] >= 126) || ( (str[i] <= 64) && (str[i] >= 46) ) ||(str[i] <= 44) )
            return 0;
    }
    
    return 1;
    
}

// deleta da hash

void fDelete(HASH *hash, char *str){
    
    long int number = 0, sum = 0;
    int i = 0, cont  = 0;
    
    for(i = 0; str[i] != '\0'; i++){
            
            if(cont == 3){
                number = number * 256;
                sum += number;
                number = 0;
            }
            
            int aux = str[i];
            number += aux;
            cont++;
    }
    
    number  = sum % hash->max;
    
    if(hash->vetor[number].validade == 1){
        if (strcmp(hash->vetor[number].strin, str) ==0){
            printf("ok\n");
            hash->vetor[number].validade = 0;
            free(hash->vetor[number].strin);
            return;
        }
    }
    
    number = 0;
    
    for(i = 0; str[i] != '\0'; i++){
        int aux = str[i];
        number = number ^ aux;
        
    }
    
    number = number * 11;
    number  = number % hash->max;
    
    if(hash->vetor[number].validade == 1){
        if (strcmp(hash->vetor[number].strin, str) == 0){
            printf("ok\n");
            hash->vetor[number].validade = 0;
            free(hash->vetor[number].strin);
            return;
        }
    }
    
    number = 1;
    
    for(i = 0; str[i] != '\0'; i++){
        if(i < 3)
            number = number*37 + str[i];  
        else number += str[i]; 
        
    }
    
    number  = number % hash->max;
    
    if(hash->vetor[number].validade == 1){
        if (strcmp(hash->vetor[number].strin, str) == 0){
            printf("ok\n");
            hash->vetor[number].validade = 0;
            free(hash->vetor[number].strin);
            return;
        }
    }
    
    number = 0;
    
    for(i = 0; str[i] != '\0'; i++){
        if(i < 6)
            number = ((5831 << 5) + number) + str[i];  
        else number += str[i]; 
        
    }
    
    number  = number % hash->max;
    
    if(hash->vetor[number].validade == 1){
        if (strcmp(hash->vetor[number].strin, str) == 0){
            printf("ok\n");
            hash->vetor[number].validade = 0;
            free(hash->vetor[number].strin);
            return;
        }
    }
    
    
    int contador = 0;
    
    number = 0;
    
    for(i = 0; str[i] != '\0'; i++){
        number += str[i];
        
    }
    
    number  = number % hash->max;
    
    while(contador < hash->max){
        if(hash->vetor[number].validade == 0){
            printf("fail\n");
            return;
        }else{
            if(hash->vetor[number].strin != NULL){
                if(strcmp(hash->vetor[number].strin, str)){
                    printf("ok\n");
                    hash->vetor[number].validade = 0;
                    free(hash->vetor[number].strin);
                    return;
                }else{
                    if(number < hash->max - 1){
                        number++;
                    }else{
                        number = 0;
                    }
                   
                }
            }
        }
        
        
        contador++;
    }
    
    printf("fail\n");
    
    
}

// menu de pesquisa


void MenuSearch(HASH *hash, TRIE *arvore, char *str){
    
    if(search(hash, str)){
        printf("ok\n");
        return;
    } else {
        
        char auxChar[105];
        strcpy(auxChar, "\0");
        int retorno = 0, retorno2 = 0, retorno3 = 0, retorno4 = 0;
        
        listTrieSimilarWords(arvore, str, 0, 0, 0, auxChar, 0, &retorno);
        
        strcpy(auxChar, "\0");
        
        listTrieOneWrongWord(arvore, str, 0, 0, 0, auxChar, 0, &retorno2);
        
        strcpy(auxChar, "\0");
        
        listTrieOneMoreWord(arvore, str, 0, 0, 0, auxChar, 0, &retorno3);
        
        strcpy(auxChar, "\0");
        
        listTrieInverseWord(arvore, str, 0, 0, 0, auxChar, 0, &retorno4);
        
        if( (retorno) || (retorno2) || (retorno3) || (retorno4)){
            printf("Voce quiz dizer algumas dessas palavras acima?\n");
            printf("----sim - y\n----nao - other\n");
        
        
            char aux[200];
        
            fgets(aux, 199, stdin);
        
            if(aux[0] == 121){
                printf("ok\n");
                return;
            }else{
                printf("not found\n");
                return;
            }
            
            
        }else printf("not found\n");
        
    }

    
}

// adiciona na trie

void AddTrie(TRIE *arvore, char *str){
    
    int i = 0, aux = 0, aux2 = 0;
    
    while(str[i] != '\0'){
        
        int aux = (int) str[i];
        
        if(str[i+1] == '\0')
            arvore[aux].endFinal = 1;
        
        if(arvore[aux].validade == 0){
            arvore[aux].validade = 1;
            if(arvore[aux].branch == NULL){
                arvore[aux].branch = createTrie();
            }
            
            arvore = arvore[aux].branch; 
            
        }else{
            if(arvore[aux].branch == NULL){
                arvore[aux].branch = createTrie();
            }
            
            arvore = arvore[aux].branch; 
        }
        
    i++;
    
    }
      
    //printf("Inseriu trie\n");
        
}
    
    


VECTOR2 *searchTrie(TRIE *arvore, char *str, VECTOR2 *strList, int posStr, int posList, char *strAux){
    
    int aux = 0;
    
    int i;
    for( i = 0; i < 127; i++){
        
        aux = (int) str[posStr];
        if(i == aux){
            if(arvore[i].validade == 1){
                if(arvore[i].endFinal == 1){
                    strAux[posStr] = str[posStr];
                    strAux[posStr+1] = '\0';
                    strcpy(strList[posList].string,strAux);
                    posList++;
                    posStr = 0;
                }else{
                    if(arvore[i].branch != NULL){
                        //printf("%c \n", str[posStr]);
                        strAux[posStr] = str[posStr];
                        searchTrie(arvore[i].branch, str, strList, ++posStr, posList, strAux);
                    }
                }
            }
        }
        
    }
        
        
    
    return strList;
    
}

// cria trie

TRIE *createTrie(){
    
    TRIE *arvore = (TRIE *) malloc(127 * sizeof(TRIE));
    if (arvore == NULL)
        printf("SEM MEMORIA \n");
    
    int i;
    for( i = 0; i < 127; i++){
        
        arvore[i].validade = 0;
        arvore[i].endFinal = 0;
        arvore[i].branch = NULL;
        
    }
    
    return arvore;
    
}

// imprime trie na tela

void listTrie(TRIE *arvore){
    
    int i;
    for( i = 0; i < 127; i++){
        
        if(arvore[i].validade == 1){
            printf("%c - ", i);
            if(arvore[i].branch != NULL)
                listTrie(arvore[i].branch);
        }
        
    }    
}

// procura erro de uma letra a menos na palavra digitada

void listTrieSimilarWords(TRIE *arvore, char *str, int posChar, int posCharAux, int numberErrors, char *strAux, int tamWord, int *flag){
    
    int aux = (int) str[posChar];
    int find = 0;
    
    int i;
    for( i = 0; i < 127; i++){
        
        if(i == aux){
            if(arvore[i].validade == 1){
                find = 1;
                strAux[posCharAux] = str[posChar];
                
                if( (arvore[i].endFinal == 1) && (tamWord >= (strlen(str))) ){
                    strAux[posCharAux + 1] = '\0';
                    printf("%s\n", strAux);
                    
                    *flag = 1;
                }else{
                    
                    if(arvore[i].branch != NULL){
                        listTrieSimilarWords(arvore[i].branch, str,++posChar, ++posCharAux, numberErrors, strAux, ++tamWord, flag);
                        if(*flag == 0)
                            find = 0;
                        --posChar;
                        --posCharAux;
                        --tamWord;
                    }
                    
                }
                
            }
        
        }
        
        
    }
    
    i = 0;

    if( ( (!find) && (numberErrors < 1) ) ){
        
        numberErrors++;
        
        for( i = 0; i < 127; i++){
            
            if(arvore[i].validade == 1){
                
                if(arvore[i].branch != NULL){
                    
                    if(arvore[i].branch[aux].validade == 1){
                        strAux[posCharAux] = i;
                        listTrieSimilarWords(arvore[i].branch, str, posChar, ++posCharAux, numberErrors, strAux, ++tamWord, flag);
                        --posCharAux;
                        --tamWord;
                    }
        
                }
                
            }
        
            
        
        
        }
        
    }
    
}

// procura erro de uma letra errada na palavra digitada

void listTrieOneWrongWord(TRIE *arvore, char *str, int posChar, int posCharAux, int numberErrors, char *strAux, int tamWord, int *flag){
    
    int aux = (int) str[posChar];
    int aux2 = (int) str[posChar + 1];
    int find = 0;
    
    int i;
    for( i = 0; i < 127; i++){
        
        if(i == aux){
            if(arvore[i].validade == 1){
                find = 1;
                strAux[posCharAux] = str[posChar];
                
                if ( (arvore[i].endFinal == 1) && (tamWord >= ((strlen(str))) - 1) ){
                    strAux[posCharAux + 1] = '\0';
                    printf("%s\n", strAux);
                    
                    *flag = 1;
                }else{
                    
                    if(arvore[i].branch != NULL){
                        listTrieOneWrongWord(arvore[i].branch, str,++posChar, ++posCharAux, numberErrors, strAux, ++tamWord, flag);
                        if(*flag == 0)
                            find = 0;
                        --posChar;
                        --posCharAux;
                        --tamWord;
                    }
                    
                }
                
            }
        
        }
        
        
    }
    
    i = 0;

    if( (!find) && (numberErrors < 1) ){
        
        numberErrors++;
        
        for( i = 0; i < 127; i++){
            
            if(arvore[i].validade == 1){
                
                if(arvore[i].branch != NULL){
                    
                    if(arvore[i].branch[aux2].validade == 1){
                        strAux[posCharAux] = i;
                        listTrieOneWrongWord(arvore[i].branch, str, ++posChar, ++posCharAux, numberErrors, strAux, ++tamWord, flag);
                        --posCharAux;
                        --posChar;
                        --tamWord;
                    }
        
                }
                
            }
        
            
        
        
        }
        
    }
    
}

// procura erro de uma letra a mais na palavra digitada

void listTrieOneMoreWord(TRIE *arvore, char *str, int posChar, int posCharAux, int numberErrors, char *strAux, int tamWord, int *flag){
    
    int aux = (int) str[posChar];
    int aux2 = (int) str[posChar + 1];
    int find = 0;
    
    int i;
    for( i = 0; i < 127; i++){
        
        if(i == aux){
            if(arvore[i].validade == 1){
                find = 1;
                strAux[posCharAux] = str[posChar];
                
                if( (arvore[i].endFinal == 1) && (tamWord >= (strlen(str)) - 2 ) ){
                    strAux[posCharAux + 1] = '\0';
                    printf("%s\n", strAux);
                    
                    *flag = 1;
                }else{
                    
                    if(arvore[i].branch != NULL){
                        listTrieOneMoreWord(arvore[i].branch, str,++posChar, ++posCharAux, numberErrors, strAux, ++tamWord, flag);
                        if(*flag == 0)
                            find = 0;
                        --posChar;
                        --posCharAux;
                        --tamWord;
                    }
                    
                }
                
            }
        
        }
        
        
    }
    
    i = 0;

    if( ( (!find) && (numberErrors < 1) ) ){
        
        numberErrors++;
        
        for( i = 0; i < 127; i++){
            if(i == aux2){
                if(arvore[i].validade == 1){
                    listTrieOneMoreWord(arvore, str, ++posChar, posCharAux, numberErrors, strAux, ++tamWord, flag);
                    --posChar;
                    --tamWord;
                    
        
                }
                
            }
        }
        
        
    }
    
}

// procura erro de letras visinhas invertidas na palavra digitada

void listTrieInverseWord(TRIE *arvore, char *str, int posChar, int posCharAux, int numberErrors, char *strAux, int tamWord, int *flag){
    
    int aux = (int) str[posChar];
    int aux2 = (int) str[posChar + 1];
    int find = 0;
    
    int i;
    for( i = 0; i < 127; i++){
        
        if(i == aux){
            if(arvore[i].validade == 1){
                find = 1;
                strAux[posCharAux] = str[posChar];
                
                if( (arvore[i].endFinal == 1) && (tamWord >= (strlen(str)) - 1 ) ){
                    strAux[posCharAux + 1] = '\0';
                    printf("%s\n", strAux);
                    
                    *flag = 1;
                }else{
                    
                    if(arvore[i].branch != NULL){
                        listTrieInverseWord(arvore[i].branch, str,++posChar, ++posCharAux, numberErrors, strAux, ++tamWord, flag);
                        if(*flag == 0)
                            find = 0;
                        --posChar;
                        --posCharAux;
                        --tamWord;
                    }
                    
                }
                
            }
        
        }
        
        
    }
    
    i = 0;

    if( ( (!find) && (numberErrors < 1) ) ){
        
        numberErrors++;
        
        for( i = 0; i < 127; i++){
            
            if(i == aux2){
            
                if(arvore[i].validade == 1){
                
                    if(arvore[i].branch != NULL){
                        
                        if(arvore[i].branch[aux].validade == 1){
                            
                            if(arvore[i].branch[aux].branch != NULL){
                                
                                strAux[posCharAux] = str[posChar+1];
                                strAux[posCharAux+1] = str[posChar];
                                
                                posCharAux += 2;
                                posChar += 2;
                                tamWord += 2;
                                
                                listTrieInverseWord(arvore[i].branch[aux].branch, str,posChar, posCharAux, numberErrors, strAux, tamWord, flag);
                                
                                
                                posCharAux -= 2;
                                posChar -= 2;
                                tamWord -= 2;
                            }
                            
                        }
                        
                    }
                
                }
        
            }
        
        
        }
        
    }
    
}

// deleta uma palavra da trie

void deleteTrie(TRIE *arvore, char *str, int posStr, int tamWord){
    
    int aux = 0;
    
    int i;
    for( i = 0; i < 127; i++){
        
        aux = (int) str[posStr];
        if(i == aux){
            if( (arvore[i].validade == 1) ){
                if( (arvore[i].endFinal == 1) && (tamWord >= (strlen(str)) - 1 ) ){
                    arvore[i].endFinal = 0;
                    return;
                }else{
                    if(arvore[i].branch != NULL){
                        deleteTrie(arvore[i].branch, str,++posStr, ++tamWord);
                    }
                }
            }
        }
        
    }
    
}
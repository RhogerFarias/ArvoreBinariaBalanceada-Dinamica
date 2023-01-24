#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int value;
    struct No *left, *right;
    short height;
}No;


No* NewNo(int x){
    No *New = malloc(sizeof(No));

    if(New){
        New->value = x;
        New->left = NULL;
        New->right = NULL;
        New->height = 0;
    }
    else
        printf("\nERRO ao alocar novo nó!\n");
    return New;
}


short bigger(short a, short b){
    return (a > b)? a: b;
}



short heightno(No *No){
    if(No == NULL)
        return -1;
    else
        return No->height;
}


short balancingFactor(No *No){
    if(No)
        return (heightno(No->left) - heightno(No->right));
    else
        return 0;
}


No* leftrotation(No *r){
    No *y, *f;

    y = r->right;
    f = y->left;

    y->left = r;
    r->right = f;

    r->height = bigger(heightno(r->left), heightno(r->right)) + 1;
    y->height = bigger(heightno(y->left), heightno(y->right)) + 1;

    return y;
}


No* rightRotation(No *r){
    No *y, *f;

    y = r->left;
    f = y->right;

    y->right = r;
    r->left = f;

    r->height = bigger(heightno(r->left), heightno(r->right)) + 1;
    y->height = bigger(heightno(y->left), heightno(y->right)) + 1;

    return y;
}

No* leftRotationRight(No *r){
    r->left = leftrotation(r->left);
    return rightRotation(r);
}

No* rightRotationLeft(No *r){
    r->right = rightRotation(r->right);
    return leftrotation(r);
}


No* balance(No *root){
    short fb = balancingFactor(root);

    
    if(fb < -1 && balancingFactor(root->right) <= 0)
        root = leftrotation(root);

    
    else if(fb > 1 && balancingFactor(root->left) >= 0)
        root = rightRotation(root);

    
    else if(fb > 1 && balancingFactor(root->left) < 0)
        root = leftRotationRight(root);

    
    else if(fb < -1 && balancingFactor(root->right) > 0)
        root = rightRotationLeft(root);

    return root;
}


No* insert(No *root, int x){
    if(root == NULL) // árvore vazia
        return NewNo(x);
    else{ 
        if(x < root->value)
            root->left = insert(root->left, x);
        else if(x > root->value)
            root->right = insert(root->right, x);
        else
            printf("\nInsercao nao realizada!\nNo elemento %d ja existe!\n", x);
    }

    
    root->height = bigger(heightno(root->left), heightno(root->right)) + 1;

    
    root = balance(root);

    return root;
}


No* rmv(No *root, int key) {
    if(root == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { 
        if(root->value == key) {
            
            if(root->left == NULL && root->right == NULL) {
                free(root);
                printf("Elemento folha removido: %d !\n", key);
                return NULL;
            }
            else{
                
                if(root->left != NULL && root->right != NULL){
                    No *aux = root->left;
                    while(aux->right != NULL)
                        aux = aux->right;
                    root->value = aux->value;
                    aux->value = key;
                    printf("Elemento trocado: %d !\n", key);
                    root->left = rmv(root->left, key);
                    return root;
                }
                else{
                    
                    No *aux;
                    if(root->left != NULL)
                        aux = root->left;
                    else
                        aux = root->right;
                    free(root);
                    printf("Elemento com 1 filho removido: %d !\n", key);
                    return aux;
                }
            }
        } else {
            if(key < root->value)
                root->left = rmv(root->left, key);
            else
                root->right = rmv(root->right, key);
        }

       
        root->height = bigger(heightno(root->left), heightno(root->right)) + 1;

       
        root = balance(root);

        return root;
    }
}

void prnt(No *root, int lvl){
    int i;
    if(root){
        prnt(root->right, lvl + 1);
        printf("\n\n");

        for(i = 0; i < lvl; i++)
            printf("\t");

        printf("%d", root->value);
        prnt(root->left, lvl + 1);
    }
}

int main(){

    int opt, value;
    No *root = NULL;

    do{
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
        scanf("%d", &opt);

        switch(opt){
        case 0:
            printf("Saindo!!!");
            break;
        case 1:
            printf("\tDigite o valor a ser inserido: ");
            scanf("%d", &value);
            root = insert(root, value);
            break;
        case 2:
            printf("\tDigite o valor a ser removido: ");
            scanf("%d", &value);
            root = rmv(root, value);
            break;
        case 3:
            prnt(root, 1);
            break;
        default:
            printf("\nOpcao invalida!!!\n");
        }

    }while(opt != 0);

    return 0;
}
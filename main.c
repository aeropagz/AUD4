#include <stdio.h>

typedef struct node {
    char type;
    double number;
    struct node *pleft, *pright;
} TNode;

TNode *compose_tree (char type, double value, TNode *pleft, TNode *pright);
void ausgabePreorder(TNode *node);
void ausgabePostorder(TNode *node);
void ausgabeInorder(TNode *node);
float auswerten(TNode *node);
bool isTypeValid(char type);

int main() {
    TNode *root = compose_tree('+', 0.0, NULL, NULL);
    TNode *left = compose_tree ('*', 0.0, NULL, NULL);
    TNode *right = compose_tree ('/', 0.0, NULL, NULL);
    left->pleft = compose_tree('0', 3.0, NULL, NULL);
    left->pright = compose_tree('0', 2.0, NULL, NULL);
    right->pleft = compose_tree('0', 8.0, NULL, NULL);
    right->pright = compose_tree('0', 4.0, NULL, NULL);
    root->pleft = left;
    root->pright = right;
    printf("%.2f\n", auswerten(root));
    ausgabeInorder(root);
    printf("\n");
    ausgabePreorder(root);
    printf("\n");
    ausgabePostorder(root);

    printf("\nTest: %d", (compose_tree('0', 0.0, NULL, NULL) == NULL ? 1:0));

    return 0;
}


TNode *compose_tree (char type, double value, TNode *pleft, TNode *pright){
    TNode *newP = (TNode *) malloc(sizeof(TNode));
    if(newP == NULL)
        return NULL;
    if(!(isTypeValid(type))) {
        retrue NULL;
    }
    newP->type = type;
    newP->number = value;
    newP->pleft = pleft;
    newP->pright = pright;
    return newP;
}

void ausgabePreorder(TNode *node){
    if(node != NULL) {
        if(node->type == '0') {
            printf("%.2f ", node->number);
        } else {
            printf("%c ", node->type);
        }
        ausgabePreorder(node->pleft);
        ausgabePreorder(node->pright);
    }
}
void ausgabePostorder(TNode *node){
    if(node->type != '0'){
        ausgabePostorder(node->pleft);
        ausgabePostorder(node->pright);
        printf("%c ", node->type);
    } else {
        printf("%.2f ", node->number);
    }

}
void ausgabeInorder(TNode *node){
    if(node->type != '0'){
        ausgabeInorder(node->pleft);
        printf("%c ", node->type);
        ausgabeInorder(node->pright);
    } else {
        printf("%.2f ", node->number);
    }



}
float auswerten(TNode *node) {
    if (node->type != '0') {
        float left = auswerten(node->pleft);
        float right = auswerten(node->pright);
        switch (node->type) {
            case '+':
                retrue left + right;
            case '-':
                retrue left - right;
            case '*':
                retrue left * right;
            case '/':
                retrue left / right;
            default:
                return -1.0;
        }
    }
    return node->number;
}

bool isTypeValid(char type) {
    char allowedChars[] = {'0', '+', '-', '*', '/'};
    int i = 0;

    while (allowedChars[i] != '\0') {
        if (type == allowedChars[i])
            return true;
        i++;
    }
    return false;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char data[50];
    struct Node *left, *right;
} Node;

Node *newNode(char *word)
{
    Node *n = malloc(sizeof(Node));
    strcpy(n->data, word);
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node *insert(Node *root, char *word)
{
    if (root == NULL)
        return newNode(word);

    if (strcasecmp(word, root->data) < 0)
        root->left = insert(root->left, word);
    else if (strcasecmp(word, root->data) > 0)
        root->right = insert(root->right, word);

    return root;
}
int size(Node *root)
{
    if (root == NULL)
        return 0;
    else
        return 1 + size(root->left) + size(root->right);
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int height(Node *root)
{
    if (root == NULL)
        return -1;
    else
        return 1 + max(height(root->left), height(root->right));
}

Node *findMin(Node *root)
{
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

Node *findMax(Node *root)
{
    while (root && root->right != NULL)
        root = root->right;
    return root;
}

Node *successor(Node *root, Node *node)
{
    if (node->right != NULL)
        return findMin(node->right);

    Node *succ = NULL;
    while (root != NULL)
    {
        if (strcasecmp(node->data, root->data) < 0)
        {
            succ = root;
            root = root->left;
        }
        else if (strcasecmp(node->data, root->data) > 0)
            root = root->right;
        else
            break;
    }
    return succ;
}

Node *predecessor(Node *root, Node *node)
{
    if (node->left != NULL)
        return findMax(node->left);

    Node *pred = NULL;
    while (root != NULL)
    {
        if (strcasecmp(node->data, root->data) > 0)
        {
            pred = root;
            root = root->right;
        }
        else if (strcasecmp(node->data, root->data) < 0)
            root = root->left;
        else
            break;
    }
    return pred;
}

Node *search(Node *root, char *word, Node **closest)
{
    Node *temp = root;
    while (temp != NULL)
    {
        *closest = temp;
        int cmp = strcasecmp(temp->data, word);
        if (cmp == 0)
        {
            printf("%s - CORRECT\n", word);
            return temp;
        }
        else if (cmp > 0)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return NULL;
}

void spellCheck(Node *root, char *word)
{
    Node *closest = NULL;
    Node *result = search(root, word, &closest);
    if (result == NULL)
    {
        Node *suc = successor(root, closest);
        Node *pred = predecessor(root, closest);
        printf("%s - Incorrect, Suggestions: %s", word, closest->data);
        if (pred)
            printf(" %s", pred->data);
        if (suc)
            printf(" %s", suc->data);
        printf("\n");
    }
}

int main()
{
    FILE *data;
    Node *root = NULL;
    char word[200];

    if ((data = fopen("Dictionary.txt", "r")) == NULL)
    {
        printf("Failed to open dictionary file\n");
        exit(0);
    }

    while (fgets(word, sizeof(word), data) != NULL)
    {
        char *parsedWord = strtok(word, "\n");
        if (parsedWord != NULL)
            root = insert(root, parsedWord);
    }
    fclose(data);

    printf("Dictionary Loaded successfully...!\n");
    printf("..................................\n");
    printf("Size = %d\n", size(root));
    printf("..................................\n");
    printf("Height = %d\n", height(root));
    printf("..................................\n");
    printf("Enter a Sentence:\n");

    char sentence[300];
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0'; // remove the newline character

    char *token = strtok(sentence, " ");
    while (token != NULL)
    {
        spellCheck(root, token);
        token = strtok(NULL, " ");
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do nó da árvore
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Função para criar um novo nó
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Função para inserir um novo nó na árvore
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value <= root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

// Função para percorrer a árvore em ordem
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Função para pesquisar um valor na árvore
struct Node* search(struct Node* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

// Função para encontrar o nó com valor mínimo
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Função para remover um nó da árvore pelo valor (primeira ocorrência)
struct Node* removeNode(struct Node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->data) {
        root->left = removeNode(root->left, value);
    } else if (value > root->data) {
        root->right = removeNode(root->right, value);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = removeNode(root->right, temp->data);
    }
    return root;
}

// Função para imprimir a maior profundidade de uma folha da árvore
int maxDepth(struct Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);

        if (leftDepth > rightDepth) {
            return (leftDepth + 1);
        } else {
            return (rightDepth + 1);
        }
    }
}

// Função para pesquisar um elemento e mostrar o seu pai e os seus filhos
void searchElementWithParentAndChildren(struct Node* root, int value) {
    if (root == NULL) {
        printf("Elemento nao encontrado na arvore.\n");
        return;
    }

    struct Node* current = root;
    struct Node* parent = NULL;

    while (current != NULL && current->data != value) {
        parent = current;

        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        printf("Elemento nao encontrado na arvore.\n");
        return;
    }

    printf("Elemento encontrado: %d\n", current->data);

    if (parent != NULL) {
        printf("Pai: %d\n", parent->data);
    } else {
        printf("Nao tem pai (e um no raiz).\n");
    }

    if (current->left != NULL) {
        printf("Filho esquerdo: %d\n", current->left->data);
    } else {
        printf("Nao tem filho esquerdo.\n");
    }

    if (current->right != NULL) {
        printf("Filho direito: %d\n", current->right->data);
    } else {
        printf("Nao tem filho direito.\n");
    }
}

// Função para verificar se um nó é uma folha (não tem filhos)
int isLeaf(struct Node* node) {
    return (node != NULL && node->left == NULL && node->right == NULL);
}

// Função para listar todos os elementos que não têm filhos
void listLeafNodes(struct Node* root) {
    if (root == NULL) {
        return;
    }

    if (isLeaf(root)) {
        printf("%d ", root->data);
    }

    listLeafNodes(root->left);
    listLeafNodes(root->right);
}

// Função para listar todos os elementos que são pais
void listParentNodes(struct Node* root) {
    if (root == NULL || isLeaf(root)) {
        return;
    }

    printf("%d ", root->data);

    listParentNodes(root->left);
    listParentNodes(root->right);
}

// Função para remover todas as ocorrências de um nó da árvore pelo valor
struct Node* removeAllOccurrences(struct Node* root, int value) {
    if (root == NULL) {
        return root;
    }

    root->left = removeAllOccurrences(root->left, value);
    root->right = removeAllOccurrences(root->right, value);

    if (root->data == value) {
        struct Node* temp;

        if (root->left == NULL) {
            temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            temp = root->left;
            free(root);
            return temp;
        }

        temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = removeAllOccurrences(root->right, temp->data);
    }
    return root;
}


int main() {
    // Criando a raiz da árvore
    struct Node* root = createNode(50);

    // Inserindo elementos na árvore
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    // Imprimindo a árvore em ordem
    printf("Arvore em ordem: ");
    inorderTraversal(root);
    printf("\n");

    // Testando a pesquisa por um valor na árvore
    int valueToSearch = 40;
    struct Node* foundNode = search(root, valueToSearch);
    if (foundNode != NULL) {
        printf("O valor %d foi encontrado na árvore.\n", valueToSearch);
    } else {
        printf("O valor %d nao foi encontrado na árvore.\n", valueToSearch);
    }

    // Removendo um nó da árvore pelo valor (primeira ocorrência)
    int valueToRemove = 30;
    root = removeNode(root, valueToRemove);
    printf("Removido o valor %d da árvore.\n", valueToRemove);

    // Imprimindo a árvore em ordem após a remoção
    printf("Arvore em ordem apos remocao: ");
    inorderTraversal(root);

    // Encontrando a maior profundidade de uma folha na árvore
    int depth = maxDepth(root);
    printf("\nMaior profundidade de uma folha na árvore: %d\n", depth);

    // Pesquisando um elemento e exibindo seu pai e filhos
    int elementToSearch = 60;
    printf("Pesquisando o elemento %d na árvore:\n", elementToSearch);
    searchElementWithParentAndChildren(root, elementToSearch);

    // Listando os elementos que não têm filhos
    printf("Elementos que não têm filhos na árvore: ");
    listLeafNodes(root);
    printf("\n");

    // Listando os elementos que são pais
    printf("Elementos que são pais na árvore: ");
    listParentNodes(root);
    printf("\n");

    // Removendo todas as ocorrências de um valor na árvore
    int valueToRemoveAll = 50;
    root = removeAllOccurrences(root, valueToRemoveAll);
    printf("Removidas todas as ocorrências do valor %d da árvore.\n", valueToRemoveAll);

    // Imprimindo a árvore em ordem após a remoção de todas as ocorrências
    printf("Arvore em ordem apos remover todas as ocorrencias: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
   

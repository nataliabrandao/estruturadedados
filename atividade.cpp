/***********************************
 EXERCÍCIO - ESTRUTURA DE DADOS 
 NOME: NATÁLIA BRANDÃO DE SOUSA 
 PROF: Rafael Pinho
 
***********************************/


#include <iostream> 

using std::cin; 
using std::cout; 
using std::string; 
using std::endl; 

// Definição da estrutura do nó
typedef struct Node 
{
    int iPayload; 
    Node* ptrNext; 
    Node* ptrPrev;

} Node;

// Protótipos das funções
Node* createNode(int); 
void insertFront(Node**, int); 
void insertEnd(Node**, int); 
void insertAfter(Node*, int);
void insertBefore(Node*, int);
void deleteNode(Node**, Node*);
void displayList(Node*); 
Node* searchNodebyValue(Node**, int); 
void deleteNodebyValue(Node**, int);

int main()
{
    Node* head = nullptr;

    // Exibir a lista vazia
    displayList(head);
    cout << "========================================" << endl; 

    // Inserir elementos no final da lista
    insertEnd(&head, 0); 
    insertEnd(&head, 1); 
    insertEnd(&head, 2); 
    insertEnd(&head, 3); 
    displayList(head);
    cout << "========================================" << endl; 

    // Inserir elemento no início da lista
    insertFront(&head, 4); 
    displayList(head);
    cout << "========================================" << endl; 

    // Inserir elemento após um nó específico
    insertAfter(head, 5);
    displayList(head);
    cout << "========================================" << endl; 

    // Inserir elemento após um nó específico
    insertAfter(head->ptrNext, 6);
    displayList(head);
    cout << "========================================" << endl; 

    // Inserir elemento antes de um nó específico
    insertBefore(head->ptrNext, 7);
    displayList(head);
    cout << "========================================" << endl; 

    // Excluir um nó específico
    deleteNode(&head, head->ptrNext);
    displayList(head);
    cout << "========================================" << endl; 

    // Buscar um nó pelo valor
    searchNodebyValue(&head, 7);
    searchNodebyValue(&head, 4);
    cout << "========================================" << endl; 

    // Excluir um nó pelo valor
    deleteNodebyValue(&head, 1); 
    displayList(head);
    cout << "========================================" << endl; 

    return 0; 
}

// Função para criar um novo nó
Node* createNode(int iPayload)
{
    Node* temp = (Node*) malloc(sizeof(Node)); 
    temp -> iPayload = iPayload;
    temp-> ptrNext = nullptr;
    temp -> ptrPrev = nullptr; 

    return temp;  
}

// Função para exibir a lista
void displayList(Node* node)
{
    if (node == nullptr)
    {
        cout << "Lista vazia: não é possível exibir." << endl;
        return;
    }
    if (node -> ptrPrev != nullptr)
    {
        cout << "Meio ou fim da lista: não é possível exibir." << endl;
        return;
    }

    Node* temp = node;

    cout << "Payload: "; 
    
    while (temp != nullptr)
    {
        cout << temp -> iPayload << " "; 
        temp = temp-> ptrNext; 
    }

    cout << endl; 
}

// Função para inserir um nó no início da lista
void insertFront(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload); 

    if (*head != nullptr)
    {
        newNode -> ptrPrev = nullptr; 
        (*head) -> ptrPrev = newNode; 
        newNode -> ptrNext = (*head); 
        (*head) = newNode; 
        return; 
    }

    (*head) = newNode; 
}

// Função para inserir um nó no final da lista
void insertEnd(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload); 

    newNode -> ptrNext = nullptr; 
    newNode -> ptrPrev = nullptr; 
    
    if (*head == nullptr)
    {
        newNode -> ptrPrev = nullptr; 
        (*head) = newNode; 
        return; 
    }

    Node* temp = (*head); 
    
    while(temp -> ptrNext != nullptr) temp = temp -> ptrNext;
    newNode -> ptrPrev = temp; 
    temp -> ptrNext = newNode;  
}

// Função para inserir um nó após um nó específico
void insertAfter(Node* ptrLocation, int iPayload)
{
    if (ptrLocation == nullptr)
    {
        cout << "Localização é NULL" << endl; 
        return;
    }

    Node* newNode = createNode(iPayload); 
    
    newNode -> ptrNext = ptrLocation-> ptrNext; 
    newNode -> ptrPrev = ptrLocation; 

    ptrLocation-> ptrNext = newNode; 

    if(newNode -> ptrNext != nullptr) newNode -> ptrNext -> ptrPrev = newNode; 
}

// Função para inserir um nó antes de um nó específico
void insertBefore(Node* ptrLocation, int iPayload)
{
    if (ptrLocation == nullptr)
    {
        cout << "Localização é NULL" << endl; 
        return;
    }

    Node* newNode = createNode(iPayload); 

    newNode->ptrNext = ptrLocation; 
    newNode->ptrPrev = ptrLocation->ptrPrev; 
    
    if (ptrLocation->ptrPrev != nullptr) ptrLocation->ptrPrev->ptrNext = newNode; 
    ptrLocation->ptrPrev = newNode; 
}

// Função para excluir um nó específico
void deleteNode(Node** head, Node* ptrDelete)
{
    if (*head == nullptr || ptrDelete == nullptr)
    {
        cout << "Não é possível excluir." << endl; 
        return; 
    }

    if (*head == ptrDelete) (*head ) = ptrDelete -> ptrNext; 

    if (ptrDelete -> ptrNext != nullptr) ptrDelete -> ptrNext -> ptrPrev = ptrDelete -> ptrPrev; 

    if (ptrDelete -> ptrPrev != nullptr) ptrDelete -> ptrPrev -> ptrNext = ptrDelete -> ptrNext; 

    free(ptrDelete); 
}

// Função para buscar um nó pelo valor
Node* searchNodebyValue(Node** head, int iPayload)
{    
    Node* current = *head;

    while (current != nullptr)
    {
        if (current->iPayload == iPayload)
        {
            cout << "Valor encontrado!" << endl;
            return current;
        }

        current = current->ptrNext;
    }

    cout << "Valor não encontrado na lista." << endl;
    return nullptr;
}

// Função para excluir um nó pelo valor
void deleteNodebyValue(Node** head, int iPayload)
{
    Node* nodeToDelete = searchNodebyValue(head, iPayload);

    if (nodeToDelete == nullptr)
    {
        cout << "Valor " << iPayload << " não encontrado na lista. Nenhum nó foi excluído." << endl;
        return;
    }

    if (*head == nodeToDelete)
    {
        *head = nodeToDelete->ptrNext;
    }
    else
    {
        Node* current = *head;
        while (current->ptrNext != nodeToDelete)
        {
            current = current->ptrNext;
        }

        current->ptrNext = nodeToDelete->ptrNext;
    }

    free(nodeToDelete);

    cout << "Nó com valor " << iPayload << " deletado da lista." << endl;
}

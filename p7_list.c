#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

struct Node{
   int data;
   struct Node* next;
};

struct Node* createNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    newNode->data=data;
    newNode->next=NULL;
    return newNode;
}

void insertAtBeginning(struct Node** head, int data)
{
    struct Node* newNode=createNode(data);
    newNode->next=*head;
    *head=newNode;   
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void incrementList(struct Node* head, int increment) {
    struct Node* temp = head;
    while (temp != NULL) {
        temp->data += increment;
        temp = temp->next;
    }
}


int main() {
    const int N = 10; // Number of elements in the linked list
    const int increment = 1; // Value to increment each element by

    // Create a linked list with some initial values
    struct Node* head = NULL;
    for (int i = N; i > 0; i--) {
        insertAtBeginning(&head, i);
    }

    printf("Initial linked list: ");
    printList(head);

    // Parallel section to increment each element of the linked list
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        struct Node* temp = head;
        // Move to the ith node
        for (int j = 0; j < i; j++) {
            temp = temp->next;
        }
        // Increment the data of the ith node
        temp->data += increment;
    }

    printf("Linked list after increment: ");
    printList(head);

    // Free dynamically allocated memory
    struct Node* temp = head;
    while (temp != NULL) {
        struct Node* next = temp->next;
        free(temp);
        temp = next;
    }

    return 0;
}


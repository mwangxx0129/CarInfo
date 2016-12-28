//
// Created by rx on 12/27/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef CARINFO_LINKEDLISTIMPLEMENT_H
#define CARINFO_LINKEDLISTIMPLEMENT_H
#define STR_LEN 64
#define DEPRECIATION_PER_YEAR 4000

struct Car {
    char id[STR_LEN];
    char brand[STR_LEN];
    char engine[STR_LEN];
    int age;
    double price;
    double depreciation;
    double tax;
    double totalPrice;
    int rankOfAge;
};


/* Link list node */
struct node {
    struct Car data;
    struct node *next;
};

/* function to insert a new_node in a list. Note that this
  function expects a pointer to head_ref as this can modify the
  head of the input linked list (similar to push())*/
void sortedInsert(struct node **head_ref, struct node *new_node) {
    struct node *current;
    /* Special case for the head end */
    if (*head_ref == NULL || strcmp((*head_ref)->data.id, new_node->data.id) >= 0) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    } else {
        /* Locate the node before the point of insertion */
        current = *head_ref;
        while (current->next != NULL &&
               strcmp(current->next->data.id, new_node->data.id) < 0) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

/* BELOW FUNCTIONS ARE JUST UTILITY TO TEST sortedInsert */

/* A utility function to create a new node */
struct node *newNode(const char id[],
                     const char brand[],
                     const char engine[],
                     const int age,
                     const double price,
                     const double depreciation,
                     const double tax,
                     const double totalPrice,
                     const int rankOfAge) {
    /* allocate node */
    struct node *new_node =
            (struct node *) malloc(sizeof(struct node));

    /* put in the data  */
    strcpy(new_node->data.id, id);
    strcpy(new_node->data.brand, brand);
    strcpy(new_node->data.engine, engine);
    new_node->data.age = age;
    new_node->data.price = price;
    new_node->data.depreciation = depreciation;
    new_node->data.tax = tax;
    new_node->data.totalPrice = totalPrice;
    new_node->data.rankOfAge = rankOfAge;

    new_node->next = NULL;

    return new_node;
}

void printNode(struct node *nodePtr) {
    printf("[%s, %s, %s, %d, %.2f, %.2f, %.2f, %.2f, %d]\n", nodePtr->data.id,
           nodePtr->data.brand, nodePtr->data.engine, nodePtr->data.age, nodePtr->data.price,
           nodePtr->data.depreciation, nodePtr->data.tax, nodePtr->data.totalPrice, nodePtr->data.rankOfAge);
}

/* Function to print linked list */
void printList(struct node *head) {
    struct node *temp = head;
    while (temp != NULL) {
        printf("[%s, %s, %s, %d, %.2f, %.2f, %.2f, %.2f, %d]\n", temp->data.id,
               temp->data.brand, temp->data.engine, temp->data.age, temp->data.price,
               temp->data.depreciation, temp->data.tax, temp->data.totalPrice, temp->data.rankOfAge);

        temp = temp->next;
    }
}

/* Load data from file*/
struct node *loadFromFile(const char path[]) {
    struct node *head = NULL;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);

        // split line by space , . _
        char *id = strsep(&line, " ,");
        char *brand = strsep(&line, " ,");
        char *engine = strsep(&line, " ,");
        int age = atoi(strsep(&line, " ,"));
        double price = strtod(strsep(&line, " ,"), NULL);
        double cost = strtod(strsep(&line, " ,"), NULL);
        double tax = strtod(strsep(&line, " ,"), NULL);
        double actualPrice = strtod(strsep(&line, " ,"), NULL);
        int rankOfAge = atoi(strsep(&line, " ,"));

        // put data to a Car struct
        sortedInsert(&head, newNode(id, brand, engine, age, price, cost, tax, actualPrice, rankOfAge));

    }

    fclose(fp);
    if (line)
        free(line);

    return head;
}

void searchByBrand(struct node *head) {
    printf("please enter brand name: ");
    char brand[STR_LEN];
    scanf("%s", brand);
    struct node *current = head;
    while (current != NULL) {
        if (0 == strcmp(current->data.brand, brand))
            break;
        current = current->next;
    }
    if (current != NULL) {
        printf("Car Info: ");
        printNode(current);
    } else {
        printf("\nNot exist!\n");
    }
}

void insertToList(struct node **head_ref) {
    printf("enter Car Info\n");
    char id[STR_LEN];
    char brand[STR_LEN];
    char engine[STR_LEN];
    int age;
    double price;
    double depreciation = -99;
    double tax;
    double actualPrice = -99; // Cal by program
    int rankOfAge = -99; // Cal by program
    printf("id: ");
    scanf("%s", id);
    printf("brand: ");
    scanf("%s", brand);
    printf("engine: ");
    scanf("%s", engine);
    printf("age: ");
    scanf("%d", &age);
    printf("price: ");
    scanf("%lf", &price);

    printf("tax: ");
    scanf("%lf", &tax);
    // put data to a Car struct
    sortedInsert(head_ref, newNode(id, brand, engine, age, price, depreciation, tax, actualPrice, rankOfAge));


}

void deleteCarByEngine(struct node **head_ref) {
    char engine[STR_LEN];
    printf("enter engine: ");
    scanf("%s", engine);

    struct node *current;
    struct node *tmpPtr;
    /* Special case for the head end */
    if (strcmp((*head_ref)->data.engine, engine) == 0) {
        tmpPtr = *head_ref;
        *head_ref = (*head_ref)->next;

    } else {
        current = *head_ref;
        while (current->next != NULL &&
               strcmp(current->next->data.engine, engine) != 0) {
            current = current->next;
        }
        tmpPtr = current->next;
        current->next = current->next->next;

    }

    printNode(tmpPtr);
    printf("has been removed");
    free(tmpPtr);
}

void calculateTotalPrice(struct node *head) {
    printf("Progress ...");
    struct node *current = head;
    while (current != NULL) {
        current->data.depreciation = current->data.age * DEPRECIATION_PER_YEAR;
        current->data.totalPrice = (current->data.price - current->data.depreciation) * (1 + current->data.tax);
        current = current->next;
    }
    printf("Done!");
}

void calculateTotalPriceThenPrint(struct node *head) {
    printList(head);
}

void getThirdAgeThenPrint(struct node *head) {
    if (head == NULL || head->next == NULL || head->next->next == NULL) printf("Less than 3 car info");
    node *first = NULL, *second = NULL, *third = NULL;
    if (head->data.age > head->next->data.age) {
        first = head;
        second = head->next;
    } else {
        first = head->next;
        second = head;
    }
    node *current = head->next->next;
    while (current != NULL) {
        if (current->data.age >= first->data.age) {
            third = second;
            second = first;
            first = current;
        } else if (current->data.age >= second->data.age) {
            third = second;
            second = current;
        } else if (current->data.age >= third->data.age) {
            third = current;
        }
        current = current->next;
    }
    printf("The third largest age info: ");
    printNode(third);
}

void command(struct node **head_ref) {
    int choice;
    do {
        printf("\nplease enter the num of operation: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: // Search by brand
                searchByBrand(*head_ref);
                break;
            case 2: // Insert ordered by id, then output to screen
                insertToList(head_ref);
                break;
            case 3: // Given an engine, delete a car info
                deleteCarByEngine(head_ref);
                break;
            case 4: // Cal depreciation and get actual price
                calculateTotalPrice(*head_ref);
                break;
            case 5: // Get all cars' original price, depreciation, tax, then print
                calculateTotalPriceThenPrint(*head_ref);
                break;
            case 6: // Get 3rd greatest age, then print
                getThirdAgeThenPrint(*head_ref);
                break;
            case 7: //Exit from this program
                printf("\nExit from this program.\n");
                break;
            case 8:
                printList(*head_ref);
                break;
            default: // Inform wrong choice
                printf("Wrong Choice!\n");
                break;
        }
    } while (7 != choice);
}
void DriveLinkedList(){
    /* Start with the empty list */
    struct node *head = NULL;

    /* load from file */
    head = loadFromFile("test.txt");

    /* command prompt */
    command(&head);

    printf("\n Created Linked List\n");
}

#endif //CARINFO_LINKEDLISTIMPLEMENT_H

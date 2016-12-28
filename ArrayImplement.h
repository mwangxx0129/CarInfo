//
// Created by rx on 12/27/16.
//

#ifndef CARINFO_ARRAYIMPLEMENT_H
#define CARINFO_ARRAYIMPLEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* A utility function to create a new car */
struct Car newCar(const char id[],
                  const char brand[],
                  const char engine[],
                  const int age,
                  const double price,
                  const double depreciation,
                  const double tax,
                  const double totalPrice,
                  const int rankOfAge) {
    struct Car car;

    /* put in the data  */
    strcpy(car.id, id);
    strcpy(car.brand, brand);
    strcpy(car.engine, engine);
    car.age = age;
    car.price = price;
    car.depreciation = depreciation;
    car.tax = tax;
    car.totalPrice = totalPrice;
    car.rankOfAge = rankOfAge;

    return car;
}

/**
 * insert a car to a sorted array
 * len will increase one
 * @param cars
 * @param len
 * @param id (key)
 * @param brand
 * @param engine
 * @param age
 * @param price
 * @param depreciation
 * @param tax
 * @param totalPrice
 * @param rankOfAge
 */
void sortedInsert(struct Car cars[], int &len,
                  const char id[],
                  const char brand[],
                  const char engine[],
                  const int age,
                  const double price,
                  const double depreciation,
                  const double tax,
                  const double totalPrice,
                  const int rankOfAge) {
    int i = len-1;
    for (; i >= 0 && strcmp(cars[i].id, id) > 0; i--) { // time complexity O(n)
        cars[i + 1] = cars[i];
    }
    /* put in the data  */
    strcpy(cars[i + 1].id, id);
    strcpy(cars[i + 1].brand, brand);
    strcpy(cars[i + 1].engine, engine);
    cars[i + 1].age = age;
    cars[i + 1].price = price;
    cars[i + 1].depreciation = depreciation;
    cars[i + 1].tax = tax;
    cars[i + 1].totalPrice = totalPrice;
    cars[i + 1].rankOfAge = rankOfAge;
    //struct Car car = newCar(id, brand, engine, age, price, depreciation, tax, totalPrice, rankOfAge);
    //cars[i + 1] = car;
    len++; // Length of array will increase one
}

void printCar(struct Car car) {
    printf("[%s, %s, %s, %d, %.2f, %.2f, %.2f, %.2f, %d]", car.id,
           car.brand, car.engine, car.age, car.price,
           car.depreciation, car.tax, car.totalPrice, car.rankOfAge);
    printf("\n");
}

/* Function to print array */
void printArray(struct Car cars[], int len) {
    for (int i = 0; i < len; i++) {
        printCar(cars[i]);
    }

}

/* Load data from file*/
void loadFromFile(struct Car cars[], int &len, const char path[]) {

    FILE *fp;
    char *line = NULL;
    size_t in_len = 0;
    ssize_t read;

    fp = fopen(path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &in_len, fp)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);

        // split line by space ,
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
        sortedInsert(cars, len, id, brand, engine, age, price, cost, tax, actualPrice, rankOfAge);
    }
    fclose(fp);
    if (line)
        free(line);
}

void searchByBrand(struct Car cars[], const int len) {
    printf("please enter brand name: ");
    char brand[STR_LEN];
    scanf("%s", brand);
    // traversal every element, matching
    int i = 0;
    for(; i < len;i++){
        if(strcmp(cars[i].brand, brand)==0)
            break;
    }
    if(i == len){
        printf("\nNot exist!\n");
    }else{
        printf("Car Info: ");
        printCar(cars[i]);
    }




}

void insertToList(struct Car cars[], int &len) {
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
    sortedInsert(cars, len, id, brand, engine, age, price, depreciation, tax, actualPrice, rankOfAge);
}

void deleteCarByEngine(struct Car cars[], int &len) {
    char engine[STR_LEN];
    printf("enter engine: ");
    scanf("%s", engine);
    int i = 0;
    for(; i< len; i++){
        if(strcmp(cars[i].engine, engine)==0)
            break;
    }

    if(i == len)    {printf("No this engine exist");}
    else{
        printCar(cars[i]);
        printf("has been removed");
        for(;i< len-1;i++){
            cars[i] = cars[i+1];
        }
        len--; // Decreased  by 1
    }
}

void calculateTotalPrice(struct Car cars[], const int len) {
    printf("Progress ...");
    for(int i = 0; i< len; i++){
        cars[i].depreciation = cars[i].age * DEPRECIATION_PER_YEAR;
        cars[i].totalPrice = (cars[i].price -cars[i].depreciation) *(1+ cars[i].tax);
    }

    printf("Done!");
}

void calculateTotalPriceThenPrint(struct Car cars[], const int len) {
    printArray(cars, len);
}

void getThirdAgeThenPrint(struct Car cars[], int len) {

    if(len<3) printf("Less than 3 car info");
    int first, second, third;
    if(cars[0].age> cars[1].age){
        first = 0;
        second =1;
    } else{
        first = 1;
        second = 0;
    }
    for (int i = 2; i < len; ++i) {
        if(cars[i].age >= cars[first].age){
            third = second;
            second = first;
            first = i;
        }else if(cars[i].age >= cars[second].age){
            third = second;
            second = i;
        }else if(cars[i].age >= cars[third].age){
            third = i;
        }
    }
    printCar(cars[third]);
}

void command(struct Car cars[], int &len) {
    int choice;
    do {
        printf("\nplease enter the num of operation: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: // Search by brand
                searchByBrand(cars, len);
                break;
            case 2: // Insert ordered by id, then output to screen
                insertToList(cars, len);
                break;
            case 3: // Given an engine, delete a car info
                deleteCarByEngine(cars, len);
                break;
            case 4: // Cal depreciation and get actual price
                calculateTotalPrice(cars, len);
                break;
            case 5: // Get all cars' original price, depreciation, tax, then print
                calculateTotalPriceThenPrint(cars, len);
                break;
            case 6: // Get 3rd greatest age, then print
                getThirdAgeThenPrint(cars, len);
                break;
            case 7: //Exit from this program
                printf("\nExit from this program.\n");
                break;
            case 8:
                printArray(cars, len);
                break;
            default: // Inform wrong choice
                printf("Wrong Choice!\n");
                break;
        }
    } while (7 != choice);
}

const int MAX_NUM_CAR = 50;

/**
 * called by main, and need to include this head file
 */
void DriveArray() {
    /* Start with the empty array*/
    struct Car cars[MAX_NUM_CAR];
    int len = 0;

    /* load from file */
    loadFromFile(cars, len, "test.txt");

    /* command prompt */
    command(cars, len);
}

#endif //CARINFO_ARRAYIMPLEMENT_H

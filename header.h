#ifndef LABA4B_HEADER_H
#define LABA4B_HEADER_H

#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define msg "0. Quit \n1. Add \n2. Show \n3. Find \n4. Delete \n5. Max element \n6. Timing \n"

typedef struct point {
    int x;
    int y;
} point;

typedef struct element {
    point key;
    char *info;
} element;

typedef struct kvad_node {
    point key;
    int size;
    struct kvad_node *prev;
    struct kvad_node* child[4];
    element* elems[4];
} kvad_node;

void getInt(int* a);
void getKey(kvad_node *root);
void deleteElement(kvad_node *root);
char* getstr();
int count_degree(int n);
kvad_node* createRoot();
void getInfo(kvad_node** root);
void deleteTree(kvad_node* root);
int addElem(kvad_node** root, point key, char* Info);
kvad_node* createNode(int n, int pos, point p);
int getPos(point p1, point p2);
void printTree(kvad_node *root, char *name, int lvl);
int max_element(kvad_node *root, int max, point* p);
int timing_func();

#endif //LABA4B_HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct{
    int p;
    char nume_echipa[50];
    float score;
}Echipa;

typedef struct{
    int varfuri;
    int muchii;
    int **m;
}Graph;

typedef struct Node
{
    Echipa* team;
   struct Node *next;

}Node;

struct Q{
    Node *front,*rear;
};


typedef struct Q Queue ;

Graph *create(FILE* fin,FILE* out_score);

void printGraph(FILE* fout , Graph *g);

int isEmptyq(Queue*q);

Queue* createQueue();

void enQueue (Queue*q,Echipa* v);

Echipa* deQueue(Queue*q);

void afisare_score(FILE* fout,Queue *final,Graph*g);

float prestigiu (int victorii);
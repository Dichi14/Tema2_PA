#include "graf.h"

int isEmptyq(Queue*q){
    return (q->front==NULL);
}

Queue* createQueue(){
    Queue *q=(Queue *)malloc(sizeof(Queue));
    if (q == NULL) return NULL;
    q->front = q->rear=NULL;
    return q;
}

void enQueue (Queue*q,Echipa* v){
    Node* newNode = (Node*)malloc (sizeof(Node));
    newNode->team= v;
    newNode->next=NULL;

    if(q->rear==NULL) q->rear=newNode;
    else{
        (q->rear)->next=newNode;
        (q->rear)=newNode;
    }

    if(q->front==NULL) q->front=q->rear;
}

Echipa* deQueue(Queue*q){
    Node* aux; Echipa* d;
    if(q->front == NULL) return NULL;

    aux = q->front;
    d=aux->team;
    if(isEmptyq(q)) return d;
    q->front = (q->front)->next;
    if (q->front == NULL) q->rear = NULL;

    free(aux);
    return d;
}

void resetQueue(Queue* q) {
    while (!isEmptyq(q)) {
        deQueue(q);
    }
}


Graph *create(FILE *fin,FILE* out_score) {
    int i;
    Graph *g = (Graph *)malloc(sizeof(Graph));
    if (g == NULL) {
        printf("memerror\n");
        return NULL;
    }

    g->varfuri = 32;
    g->muchii = 0;

    g->m = (int **)malloc(g->varfuri * sizeof(int *));
    if (g->m == NULL) {
        printf("memerror\n");
        free(g);
        return NULL;
    }

    for (i = 0; i < g->varfuri; i++) {
        g->m[i] = (int *)calloc(g->varfuri, sizeof(int));
        if (g->m[i] == NULL) {
            printf("memerror\n");
            for (int j = 0; j < i; j++) {
                free(g->m[j]);
            }
            free(g->m);
            free(g);
            return NULL;
        }
    }

    Echipa *echipe[32];
    for (i = 0; i < 32; i++) {
        echipe[i] = (Echipa *)malloc(sizeof(Echipa));
        if (echipe[i] == NULL) {
            printf("memerror\n");
            for (int j = 0; j < i; j++) {
                free(echipe[j]);
            }
            for (int j = 0; j < g->varfuri; j++) {
                free(g->m[j]);
            }
            free(g->m);
            free(g);
            return NULL;
        }

        fscanf(fin, "%f", &echipe[i]->score);
        fgetc(fin); // to consume the newline or space after the float
        fgets(echipe[i]->nume_echipa, 50, fin);
        int len = strlen(echipe[i]->nume_echipa);
        if (len > 0 && echipe[i]->nume_echipa[len - 1] == '\n') {
            echipe[i]->nume_echipa[len - 1] = '\0';
        }
        echipe[i]->p = i;
    }

    Queue *currentRound = createQueue();
    Queue *nextRound = createQueue();


    for (i = 0; i < 32; i++) {
        enQueue(currentRound, echipe[i]);
    }

    for (int round = 0; round < 6; round++) {
        while (!isEmptyq(currentRound)) {
            Echipa *echipa1 = deQueue(currentRound);
            Echipa *echipa2 = deQueue(currentRound);

            if (echipa1 == NULL || echipa2 == NULL) {
                if (echipa1 != NULL) fprintf(out_score,"%.4f %s\n",prestigiu(round),echipa1->nume_echipa);
                break;
            }

            if (echipa1->score > echipa2->score) {
                g->m[echipa2->p][echipa1->p] = 1;
                enQueue(nextRound, echipa1);
               fprintf(out_score,"%.4f %s\n",prestigiu(round),echipa2->nume_echipa);

            } else if (echipa1->score < echipa2->score) {
                g->m[echipa1->p][echipa2->p] = 1;
                enQueue(nextRound, echipa2);
                fprintf(out_score,"%.4f %s\n",prestigiu(round),echipa1->nume_echipa);
            } else {
                if (strcmp(echipa1->nume_echipa, echipa2->nume_echipa) > 0) {
                    g->m[echipa2->p][echipa1->p] = 1;
                    enQueue(nextRound, echipa1);
                    fprintf(out_score,"%.4f %s\n",prestigiu(round),echipa2->nume_echipa);
                } else {
                    g->m[echipa1->p][echipa2->p] = 1;
                    enQueue(nextRound, echipa2);
                    fprintf(out_score,"%.4f %s\n",prestigiu(round),echipa1->nume_echipa);
                }
            }
        }

        
        while (!isEmptyq(nextRound)) {
            Echipa* aux = deQueue(nextRound);
            enQueue(currentRound, aux);
            // enQueue(*final,aux);
        }
    }
    
    
    return g;
}


void printGraph(FILE* fout , Graph *g){
    int i,j;
    for(i = 0 ; i<g->varfuri; i++){
        for ( j = 0; j < g->varfuri; j++)
        {
            fprintf(fout,"%d ",g->m[i][j]);
            
        }
        fprintf(fout,"\n");  
    }
}
float prestigiu (int victorii){
    float points=(float)((0.15*power(1.85,victorii))/((64+power(1.85,6)*(-0.85))));
    return points;
}

float power(float base, int exponent) {
    float result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}




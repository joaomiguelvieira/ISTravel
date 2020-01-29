#include <stdlib.h>
#include <stdio.h>
#include "Defs.h"

#define EXCH( A , B ) { Item third; third = A; A = B; B = third; }

typedef struct Heap_ Heap;

Heap * NewHeap( int tamanho , int ( * less )( Item , Item ) , void ( * print )( Item ) );

void FreeHeap( Heap * h );

int Insert( Heap * h , Item element );

int Direct_Insert( Heap * h , Item element );

void Modify( Heap * h , int indice, Item newvalue );

Item RemoveMax( Heap * h );

int PrintHeap( Heap * h );

void CleanHeap( Heap * h );

int VerifyHeap( Heap * h );

void HeapSort( Heap * h );

void Heapify( Heap * h );

int isHeapEmpty( Heap * heap );


#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>


#ifdef DUMP
    #define ON_DUMP(...) __VA_ARGS__
    #define ListGraphDump(list_ptr) ListDumpGraphFunction(list_ptr, __FILE__, __PRETTY_FUNCTION__, __LINE__)
#else
    #define ON_DUMP(...)
#endif


static FILE* log_file = NULL;


typedef int List_type;

const int MAX_COMMAND_LENGTH = 125;

#define print(...) fprintf(file, __VA_ARGS__)

#define POISON_VALUE_FOR_ADRESS (List_type*)0xDED

#define POISON_NUMBER_FOR_VALUE 7182818


struct Node 
    {
    Node* next;
    Node* prev;
    List_type data;
    };


struct List 
    {
    Node* head;
    int size;
    int status;
    };


#define POINTER_LIST

#ifdef POINTER_LIST
    typedef Node* iterator_t;
#endif


void ListCtor(List* list);

int ListInsert(List* list, Node* node, List_type new_data);

int ListDelete(List *list, Node *node);

void ListDumpGraphFunction(List* list, const char* path, const char* signature, unsigned line);

void ListDtor(List* list);

int PushFront(List* list, List_type new_data);

int PushBack(List* list, List_type new_data);

int DeleteFront(List* list);

int DeleteBack(List* list);

int PushFront(List* list, List_type new_data);

int PushBack(List* list, List_type new_data);

iterator_t NextCurNode(Node* node);

iterator_t PrevCurNode(Node* node);

iterator_t Begin(List* list);

iterator_t End(List* list);
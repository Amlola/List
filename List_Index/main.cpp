#include "list.h"


int main()
    {
    LIST list = {};

    int retvalue = 0;

    ListCtor(&list);

    for (size_t i = 1; i < 11; i++) 
        {
        PushBack(&list, i);
        }

    ListDelete(&list, 1);

    ListDelete(&list, 0);

    ListDelete(&list, 6);

    ListDelete(&list, 6);

    ListInsert(&list, 10, 6);

    ListInsert(&list, 9, 6);

    ListGraphDump(&list);

    PushFront(&list, 1);

    ListInsert(&list, 2, 1);

    ListDump(&list);

    ListDtor(&list);
    
    return 0;
    }
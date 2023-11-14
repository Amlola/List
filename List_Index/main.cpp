#include "list.h"


int main()
    {    
    LIST list = {};

    ListCtor(&list);

    //PushFront(&list, 5);
    
    PushBack(&list, 10);
   
    PushBack(&list, 20);

    ListGraphDump(&list);

    PushBack(&list, 30);

    PushBack(&list, 40);
   
    PushBack(&list, 50);

    ListGraphDump(&list);

    iterator_t it = Begin(&list);

    it = NextCurIndex(&list, it);

    it = NextCurIndex(&list, it);

    ListDelete(&list, it);

    it = End(&list);

    it = PrevCurIndex(&list, it);

    ListInsert(&list, 100, it);

    ListGraphDump(&list);
        
    ListDtor(&list);
    
    return 0;
    }
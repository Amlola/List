#include "list.h"


int main()
    {
    List list = {};

    ListCtor(&list);

    PushBack(&list, 10);
   
    PushBack(&list, 20);

    ListGraphDump(&list);

    PushBack(&list, 30);

    PushBack(&list, 40);
   
    PushBack(&list, 50);

    ListGraphDump(&list);

    iterator_t it = Begin(&list);

    it = NextCurNode(it);

    it = NextCurNode(it);

    ListDelete(&list, it);

    it = End(&list);

    it = PrevCurNode(it);

    ListInsert(&list, it, 100);

    ListGraphDump(&list);

    //ListDtor(&list);

    return 0;
    }
#include "list.h"



void ListCtor(List* list)
    {
    list->status = 0;

    list->head = (Node*)calloc(1, sizeof(Node));

    list->head->prev = list->head->next = list->head;

    list->size = 0;
    }



int PushFront(List* list, List_type new_data) 
    {
    ListInsert(list, list->head->next, new_data);
    }


int PushBack(List* list, List_type new_data) 
    {
    ListInsert(list, list->head, new_data);
    }



int ListInsert(List* list, Node* node, List_type new_data) 
    {
    Node* ptr = (Node*)calloc(1, sizeof(Node));

    ptr->data = new_data;

    ptr->next = node;

    ptr->prev = node->prev;

    node->prev->next = ptr;

    node->prev = ptr;

    list->size++;

    return list->status;
    }


int DeleteFront(List* list) 
    {
    ListDelete(list, list->head->next);
    }


int DeleteBack(List* list) 
    {
    ListDelete(list, list->head->prev);
    }


int ListDelete(List* list, Node* node)
    {
    node->data = 0;

    node->next->prev = node->prev;

    node->prev->next = node->next;

    free(node);

    list->size--;

    return list->status;
    }


void ListDtor(List* list) 
    {
    for (iterator_t it = Begin(list), iter = End(list); it != iter; it = NextCurNode(it)) 
        {
        free(PrevCurNode(it));
        }
    }


iterator_t NextCurNode(Node* node)
    {
    return node->next;
    }


iterator_t PrevCurNode(Node* node)
    {
    return node->prev;
    }


iterator_t Begin(List* list)
    {
    return list->head->next;
    }


iterator_t End(List* list)
    {
    return list->head->prev;
    }


iterator_t FindByNode(List* list, Node* node)
    {
    Node* ptr = (Node*)calloc(1, sizeof(Node));;

    for (size_t i = 1; i < list->size; i++)
        {
        ptr = NextCurNode(node);
        }

    return node;
    }


void ListDumpGraphFunction(List* list, const char* path, const char* signature, unsigned line)
    {
    static int dump_number = 1;

    FILE* file = fopen("dot_file.dot", "wb");

    print("digraph G {\n");

    print("bgcolor=RosyBrown rankdir=TB;\n splines = ortho;");

    print("label = \"list_dump from function %s, List_Nodes/%s:%d\";\n", signature, path, line);

    List_type data = list->head->data;

    Node* next = list->head->next;

    Node* prev = list->head->prev;

    Node* node = list->head;

    print("{rank = max; %d[shape=record, width=0.2, style=\"filled\", fillcolor=purple,"
        "label=\" {ip: %p | data: %d | next: %p | prev: %p }\"]\n", node, node, data, next, prev);

    print("}\n");

    print("{rank = same;");

    data = node->next->data;

    next = node->next->next;
            
    prev = node->next->prev;

    node = node->next;
                    
    for (size_t i = 1; i <= list->size; i++) 
        {
        print("%d[shape=record, width=0.2, style=\"filled\", fillcolor=\"#7293ba\","
            "label=\" {ip: %p | data: %d | next: %p | prev: %p }\"]\n", node, node, data, next, prev);

        if (node->next != NULL) 
            {
            data = node->next->data;

            next = node->next->next;
            
            prev = node->next->prev;

            node = node->next;
            }
        }

    print("}\n");

    print("Front[color=green, style=filled]");

    print("Back[color=green, style=filled]");

    print("Front->%d[color=blue, style=filled]\n", list->head->next);

    print("Back->%d[color=blue, style=filled]\n", list->head->prev);

    node = list->head;
    
    for (size_t i = 0; i <= list->size; i++) 
        {
        print("%d->", node);

        if (node->next != NULL) 
            {
            node = node->next;
            }
        }
    
    print("%d[color = \"invis\"];\n", node);

    node = list->head;

    next = list->head->next;

    for(size_t i = 0; i <= list->size; i++) 
        {
        if (next == 0) 
            {
            print("%d->%d[color=darkgreen, constraint=false];\n", node, list->head);
            } 

        else {
            print("%d->%d[color=darkgreen, constraint=false];\n", node, next);
            }

        if (node->next != NULL)
            { 
            next = node->next->next;

            node = node->next;
            }
    }

    print("}\n");

    fclose(file);

    char shell_command[MAX_COMMAND_LENGTH] = "";
    sprintf(shell_command, "dot -v -Tpng D:/Cprojects/LIST/List_Nodes/dot_file.dot -o D:/Cprojects/LIST/List_Nodes/graphs%d.png", dump_number);
    system(shell_command);


    log_file = fopen("log_file.html", "a");

    fprintf(log_file, "<pre>\n");

    fprintf(log_file, "<img src=\"graphs%d.png\">", dump_number);

    fprintf(log_file, ".\n");
            
    fclose(log_file);

    dump_number++;
    }
#include "list.h"



int ListCtor(LIST *list)
    {
    assert(list);

    if (logfile == NULL)
        {
        logfile = fopen("logfile.html", "w");
        }
    fprintf(logfile, "<pre>\n");


    list->capacity = capacity_list;

    list->size     = size_list;

    list->status   = NO_ERROR;

    list->free     = ZERO;

    list->front    = ZERO;

    list->back     = ZERO;


    list->data = (Node*)calloc(list->capacity, sizeof (Node));

    if (list->data == nullptr)
        {
        return ALLOC_FAIL;
        }   

    SetList(list);

    return list->status;
    }



int ListVerify(LIST* list)
    {
    if (list->data == nullptr)
        {
        list->status |= NULL_DATA;
        }

    if (list == NULL)
        {
        list->status |= NULL_LIST;
        }   

    if (list->capacity < 0)
        {
        list->status |= CAPACITY_LESS_THAN_ZERO;
        }

    if (list->size < 0)
        {
        list->status |= SIZE_LESS_THAN_ZERO;
        }


    if (list->size > list->capacity)
        {
        list->status |= CAPACITY_LESS_THAN_SIZE;
        }

    return list->status;
    }



void ListDtor(LIST* list)
    {
    assert(list);

    list->capacity = POISON_NUMBER_FOR_VALUE;

    list->size     = POISON_NUMBER_FOR_VALUE;

    list->free     = POISON_NUMBER_FOR_VALUE;

    list->front    = POISON_NUMBER_FOR_VALUE;

    list->back     = POISON_NUMBER_FOR_VALUE;

    free(list->data);

    fclose(logfile);
    }



int PushFront(LIST* list, List_type value)
    {
    CHECKERROR(list);

    size_t old_free = list->free;

    list->free = list->data[list->free].next;

    list->data[old_free].prev    = list->data[list->front].prev;

    list->data[list->front].prev = old_free;

    list->data[old_free].value   = value;

    list->data[old_free].next    = list->front;

    list->front = old_free;

    list->data[list->back].next  = old_free;

    if (list->size == 0)
        {
        list->back = old_free;
        }

    list->size++;

    CHECKERROR(list);

    return list->status;
    }



int PushBack(LIST* list, List_type value)
    {
    CHECKERROR(list);

    if (list->size >= list->capacity)
        {
        ListResize(list, list->capacity * size_extend);
        }

    size_t old_free = list->free;

    list->free = list->data[list->free].next;

    list->data[list->back].next  = old_free;

    list->data[old_free].value   = value;

    list->data[old_free].prev    = list->back;

    list->data[old_free].next    = list->front;

    list->back = old_free;

    list->data[list->front].prev = old_free;

    if (list->size == 0)
        {
        list->front = old_free;
        }

    list->size++;

    CHECKERROR(list);

    return list->status;
    }



int ListInsert(LIST* list, List_type value, size_t index)
    {
    CHECKERROR(list);

    if (list->size >= list->capacity)
        {
        ListResize(list, list->capacity * size_extend);
        }

    if (index == list->size)
        {
        PushBack(list, value);

        return list->status;
        }

    if (index == 0)
        {
        PushFront(list, value);

        return list->status;
        }

    iterator_t cur_ind = FindByIndex(list, index - 1);

    size_t old_free = list->free;

    list->free = list->data[list->free].next;

    list->data[old_free].next  = list->data[cur_ind].next;

    list->data[old_free].prev  = cur_ind;

    list->data[old_free].value = value;

    list->data[list->data[cur_ind].next].prev = old_free;

    list->data[cur_ind].next   = old_free;

    CHECKERROR(list);

    return list->status;
    }



int PopFront(LIST* list) 
    {
    CHECKERROR(list);

    if (list->size == 0)
        {
        return POP_NULL;
        }

    list->data[list->front].value = POISON_NUMBER_FOR_VALUE;

    if (list->size == 1) 
        {
        list->data[list->front].next = list->free;

        list->free  = list->front;

        list->front = ZERO;

        list->back  = ZERO;
        } 

    else 
        {
        list->data[list->data[list->front].next].prev = list->data[list->front].prev;

        list->data[list->data[list->front].prev].next = list->data[list->front].next;

        list->data[list->front].prev = FREE_INDEX;

        size_t next_front = list->data[list->front].next;

        list->data[list->front].next = list->free;

        list->free  = list->front;

        list->front = next_front;
        }

    list->size--;

    CHECKERROR(list);

    return list->status;
    }



int PopBack(LIST* list) 
    {
    CHECKERROR(list);

    if (list->size == 0)
        {
        return POP_NULL;
        }

    list->data[list->back].value = POISON_NUMBER_FOR_VALUE;

    if (list->size == 1) 
        {
        list->data[list->front].next = list->free;

        list->free  = list->front;

        list->front = ZERO;
 
        list->back  = ZERO;
        } 

    else 
        {
        list->data[list->data[list->back].next].prev = list->data[list->back].prev;

        list->data[list->data[list->back].prev].next = list->data[list->back].next;

        size_t next_back = list->data[list->back].prev;

        list->data[list->back].prev = FREE_INDEX;

        list->data[list->back].next = list->free;

        list->free = list->back;

        list->back = next_back;
        }

    list->size--;

    CHECKERROR(list);

    return list->status;
    }



int ListDelete(LIST* list, size_t index)
    {
    CHECKERROR(list);

    if (index >= list->capacity)
        {
        return INDEX_BIGGER_THAN_CAPACITY;
        }
  
    if (list->size == 0)
        {
        return POP_NULL;
        }

    if (index == 0) 
        {
        PopFront(list);

        return list->status;
        } 
    else if (index == list->size - 1) 
        {
        PopBack(list);

        return list->status;
        }

    iterator_t cur_index = FindByIndex(list, index);

    list->data[cur_index].value = POISON_NUMBER_FOR_VALUE;

    list->data[list->data[cur_index].prev].next = list->data[cur_index].next;

    list->data[list->data[cur_index].next].prev = list->data[cur_index].prev;

    size_t old_free = list->free;

    list->free = cur_index;

    list->data[list->free].prev = FREE_INDEX;

    list->data[list->free].next = old_free;

    list->size--;

    CHECKERROR(list);

    return list->status;
    }



static int ListResize(LIST* list, int new_capacity_list)
    {
    CHECKERROR(list);

    if (new_capacity_list <= 0) 
        {
        return WRONG_NEW_CAPACITY;
        }

    list->capacity = new_capacity_list;

    Node* new_data = (Node*)calloc(new_capacity_list, sizeof(Node));

    if (new_data == nullptr)
        {
        return ALLOC_FAIL;
        }

    for (size_t i = 0; i < list->size; i++)
        {
        (new_data)[i].next  = list->data[i].next;

        (new_data)[i].prev  = list->data[i].prev;

        (new_data)[i].value = list->data[i].value;
        }

    free(list->data);

    list->data = new_data;

    SetList(list);

    list->data[list->size - 1].next = list->size;

    list->free = list->size;

    CHECKERROR(list);

    return list->status;
    }


iterator_t NextCurIndex(LIST* list, size_t index) 
    {
    return list->data[index].next;
    }


iterator_t PrevCurIndex(LIST* list, size_t index) 
    {
    return list->data[index].prev;
    }


    iterator_t Begin(LIST* list) 
    {
    return list->front;
    }


iterator_t End(LIST* list) 
    {
    return list->back;
    }


iterator_t FindByIndex(LIST* list, size_t index) 
    {
    iterator_t cur_ind = Begin(list);

    for (size_t i = 0; i < index; i++)
        {
        cur_ind = NextCurIndex(list, index);
        }
    
    return cur_ind;
    }


ON_DUMP
    (
    void ListDumpFunction(LIST* list, const char* path, const char* signature, unsigned line)
        {
        fprintf(logfile, "<font color = \"#964b00\">-----------------------------------------------------------------------\n</font>");

        fprintf(logfile, "<font size = \"+1\">path: %s\n</font>", path);
        fprintf(logfile, "<font size = \"+1\">in function: %s\n</font>", signature);
        fprintf(logfile, "<font size = \"+1\">line: %d\n</font>", line);
        fprintf(logfile, "\n");
        fprintf(logfile, "size = %d\n", list->size);
        fprintf(logfile, "capacity = %d\n", list->capacity);
        fprintf(logfile, "data[%p]\n", list->data);
        fprintf(logfile, "free = %d\n", list->free);
        fprintf(logfile, "front = %d\n", list->front);
        fprintf(logfile, "back = %d\n", list->back);

        fprintf(logfile, "\n");
        fprintf(logfile, "\n");

        if (list->status != NO_ERROR)
            {
            for (size_t j = 0; j < NUMBER_OF_ERROR; j++)
                {
                if ((list->status & (1 << j)))
                    {
                    fprintf(logfile, "<font color = \"red\">ERROR: %s\n</font>", ErrorArray[j + 1].NameError);
                    }
                }
            }

        else
            {
            if (list->data != NULL && list->capacity > 0 && list != nullptr && list->size >= 0)
                {
                fprintf(logfile, "data:\n");

                for (size_t i = 0; i < list->capacity; i++)
                    {
                    fprintf(logfile, "<font color = \"#008000\">*[%0*d] = %d\n</font>", (int)log10(list->capacity) + 1, i, list->data[i]);
                    }


                fprintf(logfile, "\n");
                fprintf(logfile, "\n");


                fprintf(logfile, "next:\n");

                for (size_t i = 0; i < list->capacity; i++)
                    {
                    fprintf(logfile, "<font color = \"#008000\">*[%0*d] = %d\n</font>", (int)log10(list->capacity) + 1, i, list->data[i].next);
                    }


                fprintf(logfile, "\n");
                fprintf(logfile, "\n");


                fprintf(logfile, "prev:\n");

                for (size_t i = 0; i < list->capacity; i++)
                    {
                    fprintf(logfile, "<font color = \"#008000\">*[%0*d] = %d\n</font>", (int)log10(list->capacity) + 1, i, list->data[i].prev);
                    }

                }   
            }

        fprintf(logfile, "<font color = \"#964b00\">-----------------------------------------------------------------------\n</font>");
        fprintf(logfile, "\n");
        fprintf(logfile, "\n");
        fprintf(logfile, "\n");
        }
    )



ON_DUMP
    (
    void ListGraphDump(LIST* list)
        {
        assert (list);

        graph_file = fopen("dotfile.dot", "wb");

        static int dump_number = 1;

        print("digraph G {size=\"30\"; rankdir = TB\n" "splines = ortho; edge[minlen = 3, penwidth = 2];\n\n");

        print("Info[shape=record, fillcolor=\"grey\", width=0.2, style=\"filled\","
                "label=\" {Capacity: %d | Size: %d | Free: %d | Front: %d | Back: %d}\"] \n\n",
                list->capacity, list->size, list->free, list->front, list->back);

        print("{rank = same;\n");

        for (size_t i = 0; i < list->capacity; i++)
            {
            if (list->data[i].prev == FREE_INDEX)
                {
                print("node%d[shape=record, width=0.2, style=\"filled\", fillcolor=\"red\","
                        "label=\" {id: %d | value: %s | next: %d | prev: %d}\"] \n \n",
                        i, i, "POIZON", list->data[i].next, list->data[i].prev);
                }
            else
                {
                print("node%d[shape=record, width=0.2, style=\"filled\", fillcolor=\"yellow\","
                        "label=\" {id: %d | value: %d | next: %d | prev: %d}\"] \n \n",
                        i, i, list->data[i].value, list->data[i].next, list->data[i].prev);
                }
            }

        print("}\nFree->node%d\n", list->free);
        print("Front->node%d\n", list->front);
        print("Back->node%d\n\n", list->back);

        print("edge[color=darkgreen, constraint = true]\n");

        print("node0");

        for (size_t i = 1; i < list->capacity; i++)
            {
            print(" -> node%d", i);

            if (i == list->capacity - 1)
                {
                print("\n[style=invis, weight = 10000];");
                }
            }

        print("\n\n");

        print("edge[style=solid, constraint = false]\n");

        for (size_t i = 0; i < list->capacity; i++)
            {
            print("node%d -> node%d;\n", i, list->data[i].next);
            }

        print("\n}");

        fclose(graph_file);

        char shell_command[MAX_COMMAND_LENGTH] = "";
        sprintf (shell_command, "dot -v -Tpng D:/Cprojects/LIST/List_Index/dotfile.dot -o D:/Cprojects/LIST/List_Index/graph%d.png", dump_number);
        system (shell_command);


        log_file = fopen("log_file.html", "a");

        fprintf(logfile, "<pre>\n");

        fprintf(log_file, "<img width=\"1400px\" src=\"graph%d.png\">"
            "------------------------------------------------------------------------------------------------\n\n\n", dump_number);

        fclose(log_file);

        ++dump_number;

        }
    )



static void SetList(LIST* list)
    {
    assert(list);

    for (size_t i = list->size; i < list->capacity; i++)
        {
        list->data[i].next  = i + 1;

        list->data[i].prev  = FREE_INDEX;

        list->data[i].value = POISON_NUMBER_FOR_VALUE;
        }

    list->data[list->capacity - 1].next  = ZERO;
    }
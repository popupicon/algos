#include <stdio.h>
#include <stdlib.h>

#define DISTRIBUTION_FACTOR 31

struct data_item
{
    int data;
};
typedef struct data_item data_item;

struct node
{
    data_item data;
    struct node *next;
};
typedef struct node node;

struct list
{
    int size;
    data_item data_i;
    node *data;
    node *last_node;
};
typedef struct list list;

list **create_hash_table();

void clear_hash_table(list **table);

int _hash_mod_i(int);

data_item get_elem(int);

data_item delete_elem(int);

data_item insert_elem(int, list **);

void print_table(list **);

int main(int argc, char **argv)
{

    list **table = create_hash_table();
    insert_elem(64272, table);
    insert_elem(472727, table);
    insert_elem(10, table);
    insert_elem(1623, table);
    insert_elem(10, table);
    insert_elem(1623, table);
    insert_elem(10, table);

    print_table(table);
}

int _hash_mod_i(int num)
{
    return num % DISTRIBUTION_FACTOR;
}

data_item insert_elem(int num, list **table)
{
    int index = _hash_mod_i(num);

    if (table[index] != NULL)
    {
        if (table[index]->size == 1)
        {
            table[index]->data = malloc(sizeof(node));
            table[index]->data->data = table[index]->data_i;
            node *next_node = malloc(sizeof(node));
            next_node->data = (data_item){.data = num};
            next_node->next = NULL;
            table[index]->data->next = next_node;
            table[index]->last_node = next_node;
            table[index]->size++;
        }
        else
        {
            if (table[index]->last_node != NULL)
            {
                node *next_node = malloc(sizeof(node));
                table[index]->last_node->next = next_node;
                next_node->data = (data_item){.data = num};
                next_node->next = NULL;
                table[index]->last_node = next_node;
                table[index]->size++;
            }
            else
            {
                printf("Error: Failed Chaine hash table");
            }
        }
    }
    else
    {
        table[index] = malloc(sizeof(list));
        table[index]->data_i = (data_item){.data = num};
        table[index]->last_node = NULL;
        table[index]->data = NULL;
        table[index]->size = 1;
    }
}

list **create_hash_table()
{
    int size = DISTRIBUTION_FACTOR + 1;
    list *list_ = (list *)malloc(sizeof(list));

    list **table = (list *)malloc(size * sizeof(list_));

    free(list_);

    int i = 0;

    for (i = 0; i < size; i++)
    {
        table[i] = NULL;
    }

    return table;
}

void print_table(list **table)
{
    int size = DISTRIBUTION_FACTOR + 1;
    int i;
    for (i = 0; i < size; i++)
    {
        if (table[i] != NULL)
        {
            if (table[i]->size == 1)
            {
                printf("Entry: %d \n", table[i]->data_i);
            }
            else
            {
                node *current = table[i]->data;
                printf("Entries: [ ");
                while (current != NULL)
                {
                    printf("%d ", current->data.data);
                    current = current->next;
                }
                printf(" ]\n");
            }
        }
    }
}

// perhaps memory leak
void clear_hash_table(list **table)
{
    free(table);
}

// Coded by : Andi-Nov -------12/2/2020-------

/*
This is a primitive linked lists. No automatic input system.
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct sorted_list {
    int data;
    struct sorted_list *prev;
    struct sorted_list *next;
    struct chron_list *chron_list_ptr;
} Sorted_List;

typedef struct chron_list {
    struct chron_list *prev;
    struct chron_list *next;
    struct sorted_list *sorted_list_ptr;
} Chron_List;

typedef struct s {
    struct sorted_list *min;
    struct sorted_list *max;
    struct chron_list *first;
    struct chron_list *last;
} S;

Sorted_List *insertSortedList(S *, int);
Chron_List *insertChronList(S *, Sorted_List *);
void printChronList(Chron_List *);
void printSortedList(Sorted_List *);
void freeList(S *);
void freeSortedList(Sorted_List **);
void freeChronList(Chron_List **);
void tester(bool);
S *init();            // O(1)
void insert(S *, int);// O(n)
void deleteMin(S *);  // O(1)
void deleteMax(S *);  // O(1)
void dequeue(S *);    // O(1)

S *init() {
    S *temp_list = (S *) malloc(sizeof(S));
    temp_list->min = NULL;
    temp_list->max = NULL;
    temp_list->first = NULL;
    temp_list->last = NULL;
    assert(temp_list);
    return temp_list;
}

void insert(S *list, int key) {
    Sorted_List *sorted_list_ptr = insertSortedList(list, key);
    Chron_List *chron_list_ptr = insertChronList(list, sorted_list_ptr);

    sorted_list_ptr->chron_list_ptr = chron_list_ptr;
    list->last = chron_list_ptr;
}

Sorted_List *insertSortedList(S *list, int key) {
    Sorted_List *min = list->min,
                *curr_node = min,
                *temp_node = NULL;

    if (min == NULL) {
        min = (Sorted_List *) malloc(sizeof(Sorted_List));
        assert(min);
        min->data = key;
        min->next = NULL;
        min->prev = NULL;
        min->chron_list_ptr = NULL;
        list->min = list->max = min;

        return min;
    } 
	else {
        while (key > curr_node->data) {
            if (curr_node->next != NULL) {
                curr_node = curr_node->next;
            } 
			else {
                temp_node = (Sorted_List *) malloc(sizeof(Sorted_List));
                assert(temp_node);
                temp_node->data = key;
                temp_node->prev = curr_node;
                temp_node->next = NULL;
                curr_node->next = temp_node;
                list->max = temp_node;

                return temp_node;
            }
        }

        if (curr_node->prev == NULL) {
            temp_node = (Sorted_List *) malloc(sizeof(Sorted_List));
            assert(temp_node);
            temp_node->data = key;
            temp_node->next = curr_node;
            temp_node->prev = NULL;
            curr_node->prev = temp_node;
            list->min = temp_node;

        } 
		else {
            temp_node = (Sorted_List *) malloc(sizeof(Sorted_List));
            assert(temp_node);
            temp_node->data = key;
            temp_node->prev = curr_node->prev;
            temp_node->prev->next = temp_node;
            curr_node->prev = temp_node;
            temp_node->next = curr_node;
        }
    }

    return temp_node;
}

Chron_List *insertChronList(S *list, Sorted_List *sorted_list_ptr) {
    Chron_List *temp_node;

    temp_node = (Chron_List *) malloc(sizeof(Chron_List));
    assert(temp_node);
    temp_node->sorted_list_ptr = sorted_list_ptr;
    temp_node->next = temp_node->prev = NULL;

    if (list->first == NULL) {
        list->first = list->last = temp_node;
    } 
	else {
        list->last->next = temp_node;
        temp_node->prev = list->last;
        list->last = list->last->next;
        list->last = temp_node;
        list->last->prev->next = temp_node;
    }

    return list->last;
}

void freeList(S *head) {
    freeSortedList(&head->min);
    freeChronList(&head->first);
    free(head);
}

void freeSortedList(Sorted_List **head) {
    Sorted_List *prev = *head;

    while (*head != NULL) {
        *head = (*head)->next;

        free(prev);
        prev = *head;
    }
}

void freeChronList(Chron_List **head) {
    Chron_List *prev = *head;

    while (*head != NULL) {
        *head = (*head)->next;

        free(prev);
        prev = *head;
    }
}

void printSortedList(Sorted_List *head) {
    printf("Sorted_List:\n");

    if (head == NULL || head->chron_list_ptr == NULL) {
        printf("The list is empty\n");
        return;
    }
    
    while (head->next != NULL) {
        printf("[%d]<->", head->data);

        head = head->next;
    }

    printf("[%d]\n", head->data);
}

void printChronList(Chron_List *head) {
    printf("Chron_List:\n");

    if (head->prev == NULL && head->next == NULL) {
        printf("The list is empty\n");
        return;
    }

    while (head->next != NULL) {
        printf("[%d]<->", head->sorted_list_ptr->data);

        head = head->next;
    }

    if (head->sorted_list_ptr == NULL) {
        printf("[NULL]\n");
    } 
	else {
        printf("[%d]\n", head->sorted_list_ptr->data);
    }
}

void deleteMin(S *list) {
    Sorted_List **min = &list->min;
    if (*min == NULL) {
        return;
    }

    Chron_List *chron_list_ptr = (*min)->chron_list_ptr;
    if (list->first == list->last) {
        chron_list_ptr = NULL;
        free(*min);
        list->min = NULL;
        list->max = NULL;
        return;
    } 
	else if (chron_list_ptr == list->last) {
        list->last = chron_list_ptr->prev;
        list->last->next = NULL;
        free(chron_list_ptr);
    } 
	else if (chron_list_ptr == list->first) {
        list->first = chron_list_ptr->next;
        list->first->prev = NULL;
        free(chron_list_ptr);
    } 
	else {
        chron_list_ptr->prev->next = chron_list_ptr->next;
        chron_list_ptr->next->prev = chron_list_ptr->prev;
        free(chron_list_ptr);
    }

    *min = (*min)->next;
    free((*min)->prev);
    (*min)->prev = NULL;
}

void deleteMax(S *list) {
    Sorted_List **max = &list->max;
    if (*max == NULL) {
        return;
    }

    Chron_List *chron_list_ptr = (*max)->chron_list_ptr;
    if (list->first == list->last) {
        chron_list_ptr = NULL;
        free(*max);

        return;
    } 
	else if (chron_list_ptr == list->last) {
        list->last = chron_list_ptr->prev;
        list->last->next = NULL;
        free(chron_list_ptr);
    } 
	else if (chron_list_ptr == list->first) {
        list->first = chron_list_ptr->next;
        list->first->prev = NULL;
        free(chron_list_ptr);
    } 
	else {
        chron_list_ptr->prev->next = chron_list_ptr->next;
        chron_list_ptr->next->prev = chron_list_ptr->prev;
        free(chron_list_ptr);
    }
    *max = (*max)->prev;
    free((*max)->next);
    (*max)->next = NULL;
}

void dequeue(S *list) {
    Chron_List **first = &list->first;
    if (*first == NULL) {
        return;
    }

    Sorted_List *sorted_list_ptr = (*first)->sorted_list_ptr;
    sorted_list_ptr->prev->next = sorted_list_ptr->next;
    sorted_list_ptr->next->prev = sorted_list_ptr->prev;
    free(sorted_list_ptr);

    *first = (*first)->next;
    free((*first)->prev);
    (*first)->prev = NULL;
}

void tester(bool flag) {
    if(!flag)
        return;

    S *new_list = init();
    S *new_list2 = init();
    S *new_list3 = init();
    S *new_list4 = init();
    S *new_list5 = init();

    insert(new_list4, 1);

    insert(new_list5, 1);
    deleteMin(new_list5);

    printChronList(new_list4->first);
    printSortedList(new_list4->min);

    printChronList(new_list5->first);
    printSortedList(new_list5->min);


    insert(new_list3, 0);
    insert(new_list3, 9);
    insert(new_list3, 9);
    insert(new_list3, 9);
    insert(new_list3, 9);
    insert(new_list3, 9);
    insert(new_list3, 9);
    insert(new_list3, 9);
    insert(new_list3, 9);
    insert(new_list3, 9);
    insert(new_list3, 9);
    insert(new_list3, 9);
    insert(new_list3, 9);
    insert(new_list3, 0);

    printChronList(new_list3->first);
    printSortedList(new_list3->min);

    deleteMin(new_list3);
    deleteMax(new_list3);

    printChronList(new_list3->first);
    printSortedList(new_list3->min);

    insert(new_list, 9);
    insert(new_list, 17);
    insert(new_list, -1);
    insert(new_list, 32);
    insert(new_list, 0);

    printChronList(new_list->first);
    printSortedList(new_list->min);
    insert(new_list2, -12);

    deleteMin(new_list);
    printChronList(new_list->first);
    printSortedList(new_list->min);

    printChronList(new_list2->first);
    printSortedList(new_list2->min);

    insert(new_list2, -1112);
    insert(new_list2, 16);
    insert(new_list2, 902);

    printChronList(new_list2->first);
    printSortedList(new_list2->min);

    insert(new_list, 17);
    insert(new_list, 14);

    printSortedList(new_list->min);
    printChronList(new_list->first);

    deleteMax(new_list);

    printSortedList(new_list->min);
    printChronList(new_list->first);

    dequeue(new_list);

    insert(new_list, -616);

    printSortedList(new_list->min);
    printChronList(new_list->first);


    freeList(new_list);
    freeList(new_list2);
    freeList(new_list3);
    freeList(new_list4);
    freeList(new_list5);
}

int main() {
    tester(true); 
}
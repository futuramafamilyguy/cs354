#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INTS 1000
#define NUM_INTS 20

/* A node in the linked list */
struct node {
    int data;
    struct node *next;
};

struct node* create_list(int intarray[], int len);

struct node* add_item_at_start(struct node *head, int data);

int search_array(int integers[], int numints, int element);

int search_list(struct node *head, int element);

struct node* create_sorted_list(struct node *head);

struct node* add_item_sorted(struct node *head, int data);

int copy_list_to_array(struct node *head, int *array);

void print_list(struct node *head);

void print_array(int integers[], int len);


int main(int argc, char *argv[])
{
    /* TODO: Complete the main method according to the steps outlined */

    /* Open a file for reading */
    char* filename = argv[1];

    /* Read the numbers from the file, into an array */
    FILE *fp;
    fp = fopen(filename, "r");
    char buff[100];
    int nums[MAX_INTS];

    int i = 0;
    while (fgets(buff, 100, fp))
        nums[i++] = atoi(buff);

    /* Print the array */
    print_array(nums, NUM_INTS);

    /* Create a linked list with the integers from the array */
    struct node *list = create_list(nums, NUM_INTS);
    
    /* Print the linked list */
    print_list(list);

    /* Repeatedly prompt the user for a number to be searched.
    *  Search the array for the number and print out the result as shown in the specs.
    *  Search the linked list for the number and print out the result as shown in the specs.
    *  Stop prompting when the user enters 'q' (just the character q without the single quotes).
    */
    for (;;) {
        char input[3];
        printf("enter num: ");
        scanf("%s", input);

        if (!strcmp("q", input)) {
            break;
        }

        int num = atoi(input);
        int arr_pos = search_array(nums, NUM_INTS, num);
        int list_pos = search_list(list, num);
        if (arr_pos == -1) {
            printf("element %d not found in array\n", num);
        } else {
            printf("element %d found in array at pos %d\n", num, arr_pos);
        }
        if (list_pos == -1) {
            printf("element %d not found in list\n", num);
        } else {
            printf("element %d found in list at pos %d\n", num, list_pos);
        }
    }

    /* Create a sorted list(in ascending order) from the unsorted list */
    struct node *sorted = create_sorted_list(list);

    /* Print the sorted list */
    print_list(sorted);

    /* Copy the sorted list to an array with the same sorted order */
    int arr[MAX_INTS];
    int arr_len = copy_list_to_array(sorted, arr);

    /* Print out the sorted array */
    print_array(arr, arr_len);    

    /* Print the original linked list again */
    print_list(list);

    /* Print the original array again */
    print_array(nums, arr_len);


    /* Open a file for writing */
    fp = fopen("sorted_numers.txt", "w");

    /* Write the sorted array to a file named "sorted_numbers.txt" */
    printf("writing sorted list to sorted_numers.txt");
    for (int i = 0; i < arr_len; i++) {
        fprintf(fp, "%d\n", arr[i]);
    }
    fclose(fp);

    /* Print out the number of integers written to the file */
    printf("printed %d integers to the file\n", arr_len);

    return 0;
}

struct node* create_list(int intarray[], int len)
{
    /* TODO: Complete this function */
    struct node *head = NULL;
    if (len == 0) {
        return head;
    }

    for (int i = 0; i < len; i++) {
        head = add_item_at_start(head, intarray[i]);
    } 

    return head;
}


struct node* add_item_at_start(struct node *head, int data)
{
    /* TODO: Complete this function */
    struct node *new_head = malloc(sizeof(struct node));
    new_head->data = data;
    new_head->next = head;

    return new_head;
}

int search_list(struct node *head, int element)
{
    /* TODO: Complete this function */
    struct node *current = head;
    int pos = 1;
    while (current != NULL) {
        if (current->data == element) {
            return pos;
        }
        current = current->next;
        pos++;
    }

    return -1;
}

int search_array(int integers[], int numints, int element)
{
    /* TODO: Complete this function */
    for (int i = 0; i < numints; i++) {
        if (integers[i] == element) {
            return i;
        }
    }

    return -1;
}

int copy_list_to_array(struct node *head, int *array)
{
    int i = 0;
    while (head != NULL) {
        array[i++] = head->data;
        head = head->next;
    }

    return i;
}

struct node* create_sorted_list(struct node *head)
{
    /* TODO: Complete this function */
    if (head == NULL) {
        return head;
    }

    struct node *sorted = malloc(sizeof(struct node));
    sorted->data = head->data;
    sorted->next = NULL;
    struct node *current = head->next;

    while (current != NULL) {
        sorted = add_item_sorted(sorted, current->data);
        current = current->next;
    }

    return sorted;
}

struct node* add_item_sorted(struct node *sorted_head, int data)
{
    /* TODO: Complete this function */
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    
    if (sorted_head == NULL) {
        sorted_head = new_node;
        return sorted_head;
    }

    struct node *dummy_node = malloc(sizeof(struct node));
    dummy_node->next = sorted_head;
    struct node *current = dummy_node;
    while (current != NULL) {
        if (current->next == NULL) {
            current->next = new_node;
            break;
        } else if (new_node->data <= (current->next)->data) {
            new_node->next = current->next;
            current->next = new_node;
            break;
        }
        current = current->next;
    }

    if (current == dummy_node) {
        sorted_head = dummy_node->next;
    }
    free(dummy_node);

    return sorted_head;
}

void print_list(struct node *head)
{
    if (head == NULL) {
        printf("Linked List is Empty.\n");
    } else {
        struct node *temp = head;
        printf("head->");
        while (temp != NULL) {
            printf("|%d|->", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void print_array(int integers[], int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("| %d ", integers[i]);
    }
    printf("|\n");
}

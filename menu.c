#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "bookflat.h"
#include "rent.h"
#include "searchflat.h"
#include "writeandread.h"

struct FlatNode {
    struct Flat flat;
    struct FlatNode *next;
};

static struct FlatNode* CreateNode(bool zeroInit) {
    struct FlatNode *node = zeroInit
        ? calloc(1, sizeof(*node))
        : malloc(sizeof(*node));

    if (node == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    node->flat.number = 0;
    node->flat.rooms = 0;
    node->flat.name[0] = '\0';
    node->flat.owner[0] = '\0';
    node->flat.booked = false;
    node->flat.street[0] = '\0';
    node->flat.Rent = 0.0f;
    node->next = NULL;

    return node;
}

static void FreeList(struct FlatNode *head) {
    while (head != NULL) {
        struct FlatNode *next = head->next;
        free(head);
        head = next;
    }
}

static int CountList(const struct FlatNode *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

static struct FlatNode* GetNodeAt(struct FlatNode *head, int index) {
    int current = 0;
    while (head != NULL) {
        if (current == index) {
            return head;
        }
        current++;
        head = head->next;
    }
    return NULL;
}

static struct Flat* ListToArray(const struct FlatNode *head, int *outCount) {
    int count = CountList(head);
    *outCount = 0;

    if (count == 0) {
        return NULL;
    }

    struct Flat *arr = malloc((size_t)count * sizeof(*arr));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    int i = 0;
    for (const struct FlatNode *curr = head; curr != NULL; curr = curr->next) {
        arr[i++] = curr->flat;
    }

    *outCount = count;
    return arr;
}

static struct FlatNode* ArrayToList(const struct Flat *arr, int count) {
    struct FlatNode *head = NULL;
    struct FlatNode *tail = NULL;

    for (int i = 0; i < count; i++) {
        struct FlatNode *node = malloc(sizeof(*node));
        if (node == NULL) {
            printf("Memory allocation failed!\n");
            FreeList(head);
            return NULL;
        }

        node->flat = arr[i];
        node->next = NULL;

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}

static struct FlatNode* BuildFlatsList(int num) {
    struct FlatNode *head = NULL;
    struct FlatNode *tail = NULL;

    for (int i = 0; i < num; i++) {
        struct FlatNode *node = CreateNode(false);
        if (node == NULL) {
            FreeList(head);
            return NULL;
        }

        node->flat.number = i + 1;
        node->flat.booked = false;

        printf("\n--- Flat %d ---\n", i + 1);

        printf("Enter rooms: ");
        if (scanf("%d", &node->flat.rooms) != 1) {
            printf("Invalid input!\n");
            free(node);
            FreeList(head);
            return NULL;
        }

        printf("Enter tenant name: ");
        scanf(" %49[^\n]", node->flat.name);

        printf("Enter owner: ");
        scanf(" %49[^\n]", node->flat.owner);

        printf("Enter street: ");
        scanf(" %49[^\n]", node->flat.street);

        printf("Enter rent: ");
        if (scanf("%f", &node->flat.Rent) != 1) {
            printf("Invalid input!\n");
            free(node);
            FreeList(head);
            return NULL;
        }

        node->next = NULL;

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    printf("\n********** ROOMS **********\n");
    for (const struct FlatNode *curr = head; curr != NULL; curr = curr->next) {
        printf("Flat %d: %d rooms\n", curr->flat.number, curr->flat.rooms);
    }

    return head;
}

static void DisplayAllNodes(const struct FlatNode *head) {
    printf("\n********** ALL FLATS **********\n");
    for (const struct FlatNode *curr = head; curr != NULL; curr = curr->next) {
        printf("Flat number: %d | Rooms: %d | Tenant: %s | Owner: %s | Street: %s | Rent: %.2f | Booked: %s\n",
               curr->flat.number,
               curr->flat.rooms,
               curr->flat.name,
               curr->flat.owner,
               curr->flat.street,
               curr->flat.Rent,
               curr->flat.booked ? "Yes" : "No");
    }
}

struct Flat* DisplayFlats(int num) {
    struct FlatNode *list = BuildFlatsList(num);
    if (list == NULL) {
        return NULL;
    }
    int count = 0;
    struct Flat *arr = ListToArray(list, &count);
    FreeList(list);
    return arr;
}

void DisplayAll(struct Flat* flats, int num) {
    struct FlatNode *list = ArrayToList(flats, num);
    if (list == NULL) {
        return;
    }
    DisplayAllNodes(list);
    FreeList(list);
}

int main(void) {
    int condition = 0;
    struct FlatNode *head = NULL;

    do {
        printf("\n*************** MENU ***************\n");
        printf("1: Add Flats\n");
        printf("2: Display All\n");
        printf("3: Book Flat\n");
        printf("4: Calculate Rent\n");
        printf("5: Search Flat\n");
        printf("6: Save to File\n");
        printf("7: Load from File\n");
        printf("8: EXIT\n");
        printf("************************************\n");
        printf("\nEnter your choice: ");

        if (scanf("%d", &condition) != 1) {
            printf("Invalid input!\n");
            FreeList(head);
            return 1;
        }

        switch (condition) {
            case 1: {
                int newNum;
                printf("Enter the number of flats: ");
                if (scanf("%d", &newNum) != 1 || newNum <= 0) {
                    printf("Invalid number of flats!\n");
                    break;
                }
                struct FlatNode *newList = BuildFlatsList(newNum);
                if (newList != NULL) {
                    FreeList(head);
                    head = newList;
                }
                break;
            }

            case 2:
                if (head != NULL) {
                    DisplayAllNodes(head);
                } else {
                    printf("Please enter flats first!\n");
                }
                break;

            case 3: {
                if (head != NULL) {
                    int count = 0;
                    struct Flat *arr = ListToArray(head, &count);
                    if (arr != NULL) {
                        BookFlat(arr, count);
                        struct FlatNode *updated = ArrayToList(arr, count);
                        free(arr);
                        if (updated != NULL) {
                            FreeList(head);
                            head = updated;
                        }
                    }
                } else {
                    printf("Please enter flats first!\n");
                }
                break;
            }

            case 4: {
                if (head != NULL) {
                    int count = CountList(head);
                    int flatIndex, months;
                    printf("Enter flat number: ");
                    if (scanf("%d", &flatIndex) != 1 || flatIndex < 1 || flatIndex > count) {
                        printf("Invalid flat number!\n");
                        break;
                    }
                    printf("Enter number of months: ");
                    if (scanf("%d", &months) != 1 || months < 1) {
                        printf("Invalid number of months!\n");
                        break;
                    }
                    struct FlatNode *target = GetNodeAt(head, flatIndex - 1);
                    if (target != NULL) {
                        float total = calculateRent(&target->flat, months);
                        printf("Total rent for Flat %d over %d months: %.2f\n", flatIndex, months, total);
                    }
                } else {
                    printf("Please enter flats first!\n");
                }
                break;
            }

            case 5: {
                if (head != NULL) {
                    int count = 0;
                    struct Flat *arr = ListToArray(head, &count);
                    if (arr != NULL) {
                        char searchName[50];
                        printf("Enter tenant name to search: ");
                        scanf(" %49[^\n]", searchName);
                        SearchFlat(searchName, arr, count);
                        free(arr);
                    }
                } else {
                    printf("Please enter flats first!\n");
                }
                break;
            }

            case 6: {
                if (head != NULL) {
                    int count = 0;
                    struct Flat *arr = ListToArray(head, &count);
                    if (arr != NULL) {
                        WriteToFile(arr, count);
                        free(arr);
                    }
                } else {
                    printf("Please enter flats first!\n");
                }
                break;
            }

            case 7: {
                int maxNum = 0;
                printf("Enter maximum number of flats to load: ");
                if (scanf("%d", &maxNum) != 1 || maxNum <= 0) {
                    printf("Invalid number!\n");
                    break;
                }

                struct FlatNode *tempHead = NULL;
                struct FlatNode *tempTail = NULL;
                struct Flat *buf = malloc((size_t)maxNum * sizeof(*buf));
                if (buf == NULL) {
                    printf("Memory allocation failed!\n");
                    break;
                }

                int loaded = ReadFromFile(buf, maxNum);
                if (loaded > 0) {
                    if (loaded > maxNum) {
                        loaded = maxNum;
                    }
                    for (int i = 0; i < loaded; i++) {
                        struct FlatNode *node = CreateNode(true);
                        if (node == NULL) {
                            FreeList(tempHead);
                            tempHead = NULL;
                            break;
                        }
                        node->flat = buf[i];
                        node->next = NULL;

                        if (tempHead == NULL) {
                            tempHead = node;
                            tempTail = node;
                        } else {
                            tempTail->next = node;
                            tempTail = node;
                        }
                    }

                    if (tempHead != NULL) {
                        FreeList(head);
                        head = tempHead;
                    }
                } else {
                    printf("No flats loaded from file.\n");
                }

                free(buf);
                break;
            }

            case 8:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid Choice!\n");
                break;
        }

    } while (condition != 8);

    FreeList(head);
    return 0;
}
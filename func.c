#include "header.h"

void getInt(int* a) {
    int n;
    do {
        n = scanf("%d", a);
        if (n == 0) {
            printf("Incorrect input. Please, try again!");
            scanf("%*[^\n]");
        }

    } while (n == 0);
    scanf("%*c");
}

char* getstr() {
    char *ptr = (char *)malloc(1);
    char buf[81];
    int n, len = 0;
    *ptr = '\0';
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
        }
        if (n == 0)
            scanf("%*c");
        else {
            len += strlen(buf);
            ptr = (char *)realloc(ptr, len + 1);
            strcat(ptr, buf);
        }
    } while (n > 0);
    return ptr;
}

int count_degree(int n) {
    int ans = 1;
    while (n >= 1) {
        ans = ans * 2;
        n -= 1;
    }
    return ans;
}

void getInfo(kvad_node** root) {
    point p;
    char *info = NULL;
    printf("Enter the first key: ");
    getInt(&(p.x));
    printf("Enter the second key: ");
    getInt(&(p.y));
    if (p.x > (*(*root)).key.x + (*(*root)).size || p.x < (*(*root)).key.x - (*(*root)).size || p.y > (*(*root)).key.y + (*(*root)).size || p.y < (*(*root)).key.y - (*(*root)).size) {
        printf("Error! The coordinations are out of the size!\n");
        return;
    }
    printf("Enter the information: ");
    info = getstr();
    addElem(root, p, info);
    free(info);
}

void deleteTree(kvad_node *root) {
    if (root->child[0]) {
        deleteTree(root->child[0]);
    }
    if (root->child[1]) {
        deleteTree(root->child[1]);
    }
    if (root->child[2]) {
        deleteTree(root->child[2]);
    }
    if (root->child[3]) {
        deleteTree(root->child[3]);
    }
    for (int i = 0; i < 4; i++) {
        if (root->elems[i]) {
            free(root->elems[i]->info);
            free(root->elems[i]);
        }
        if (root->child[i]) {
            free(root->child[i]);
        }
    }
}

kvad_node* createRoot () {
    kvad_node* k = (kvad_node*)malloc(sizeof(kvad_node));
    for (int i = 0; i < 4; i++) {
        k->child[i] = NULL;
        k->elems[i] = NULL;
    }
    int n;
    printf("Enter the size of the tree: ");
    getInt(&n);
    k->prev = NULL;
    k->size = count_degree(n);
    k->key.x = k->size / 2;
    k->key.y = k->size / 2;
    return k;
}

kvad_node* findElem(kvad_node* root, point p) {
    int x = p.x, y = p.y;
    kvad_node *tmp = root;
    while (tmp) {
        if (x > tmp->key.x && y > tmp->key.y) {
            if (tmp->child[0] == NULL && tmp->elems[0] == NULL) {
                return NULL;
            }
            else if (tmp->child[0] != NULL) {
                tmp = tmp->child[0];
            }
            else if (tmp->child[0] == NULL && tmp->elems[0] != NULL) {
                if (tmp->elems[0]->key.x == x && tmp->elems[0]->key.y == y) {
                    return tmp;
                }
                else {
                    return NULL;
                }
            }
        }
        else if (x <= tmp->key.x && y > tmp->key.y) {
            if (tmp->child[1] == NULL && tmp->elems[1] == NULL) {
                return NULL;
            }
            else if (tmp->child[1] != NULL) {
                tmp = tmp->child[1];
            }
            else if (tmp->child[1] == NULL && tmp->elems[1] != NULL) {
                if (tmp->elems[1]->key.x == x && tmp->elems[1]->key.y == y) {
                    return tmp;
                }
                else {
                    return NULL;
                }
            }
        }
        else if (x <= tmp->key.x && y <= tmp->key.y) {
            if (tmp->child[2] == NULL && tmp->elems[2] == NULL) {
                return NULL;
            }
            else if (tmp->child[2] != NULL) {
                tmp = tmp->child[2];
            }
            else if (tmp->child[2] == NULL && tmp->elems[2] != NULL) {
                if (tmp->elems[2]->key.x == x && tmp->elems[2]->key.y == y) {
                    return tmp;
                }
                else {
                    return NULL;
                }
            }
        }
        else if (x > tmp->key.x && y <= tmp->key.y) {
            if (tmp->child[3] == NULL && tmp->elems[3] == NULL) {
                return NULL;
            }
            else if (tmp->child[3] != NULL) {
                tmp = tmp->child[3];
            }
            else if (tmp->child[3] == NULL && tmp->elems[3] != NULL) {
                if (tmp->elems[3]->key.x == x && tmp->elems[3]->key.y == y) {
                    return tmp;
                }
                else {
                    return NULL;
                }
            }
        }
    }
}

void getKey(kvad_node *root) {
    int pos = 0;
    point p;
    printf("Enter the first key: ");
    getInt(&(p.x));
    printf("Enter the second key: ");
    getInt(&(p.y));
    kvad_node* find = findElem(root, p);
    if (find == NULL) {
        printf("That key does not exist!\n");
        free(find);
        return;
    }
    else {
        pos = getPos(find->key, p);
        printf("Coords: x: %d, y: %d\n", find->elems[pos]->key.x, find->elems[pos]->key.y);
        printf("Info: %s\n", find->elems[pos]->info);
    }
}

kvad_node* createNode(int n, int pos, point p) {
    if (n == 1 || n == 2) {
        return NULL;
    }
    kvad_node *k = (kvad_node*)malloc(sizeof(kvad_node));
    for (int i = 0; i < 4; i++) {
        k->child[i] = NULL;
        k->elems[i] = NULL;
    }
    if (pos == 0) {
        k->key.x = p.x + n / 4;
        k->key.y = p.y + n / 4;
    }
    else if (pos == 1) {
        k->key.x = p.x - n / 4;
        k->key.y = p.y + n / 4;
    }
    else if (pos == 2) {
        k->key.x = p.x - n / 4;
        k->key.y = p.y - n / 4;
    }
    else if (pos == 3) {
        k->key.x = p.x + n / 4;
        k->key.y = p.y - n / 4;
    }
    k->size = n / 2;
    return k;
}

int getPos(point p1, point p2) { // позиция п2 относительно п1
    if (p2.x > p1.x && p2.y > p1.y)
        return 0;
    else if (p2.x <= p1.x && p2.y > p1.y)
        return 1;
    else if (p2.x <= p1.x && p2.y <= p1.y)
        return 2;
    else if (p2.x > p1.x && p2.y <= p1.y)
        return 3;
}

void printTree(kvad_node *root, char *name, int lvl) {
    printf("\n");
    printf("%d - %s\n", lvl, name);
    for (int i = 0; i < 4; i++) {
        if (root->elems[i]) {
            printf("Position: %d, Key1: %d, Key2: %d\n",i, root->elems[i]->key.x, root->elems[i]->key.y);
            printf("Info: %s\n", root->elems[i]->info);
            printf("\n");
        }
    }
    if (root->child[0]) {
        printTree(root->child[0], "North-East", lvl + 1);
    }
    if (root->child[1]) {
        printTree(root->child[1], "North-West", lvl + 1);
    }
    if (root->child[2]) {
        printTree(root->child[2], "South-West", lvl + 1);
    }
    if (root->child[3]) {
        printTree(root->child[3], "South-East", lvl + 1);
    }
}

int addElem(kvad_node **root, point key, char* Info) {
    int x = key.x, y = key.y, pos1, pos2, pos;
    element temporary;
    kvad_node* tmp = *root;
    kvad_node* find = findElem(tmp, key);
    if (find) {
      //  printf("The element is already in the tree!\n");
        pos = getPos(find->key, key);
     //   printf("String: %s\n", find->elems[pos]->info);
        free(find->elems[pos]->info);
        find->elems[pos]->info = (char*)calloc(strlen(Info) + 1, sizeof(char));
        memcpy(find->elems[pos]->info, Info, strlen(Info) + 1);
        return 0;
    }
     while (tmp) {
        if (x > tmp->key.x && y > tmp->key.y) {
            if (tmp->child[0] == NULL && tmp->elems[0] == NULL) {
                tmp->elems[0] = (element*)calloc(1, sizeof(element));
                tmp->elems[0]->info = (char*)calloc(strlen(Info) + 1, sizeof(char));
                memcpy(tmp->elems[0]->info, Info, strlen(Info) + 1);
                tmp->elems[0]->key = key;
                return 1;
            }
            else if (tmp->child[0] != NULL) {
                tmp = tmp->child[0];
            }
            else if (tmp->child[0] == NULL && tmp->elems[0] != NULL) {
                temporary.key = tmp->elems[0]->key;
                temporary.info = (char*)calloc(strlen(tmp->elems[0]->info) + 1, sizeof(char));
                memcpy(temporary.info, tmp->elems[0]->info, strlen(tmp->elems[0]->info) + 1);
                free(tmp->elems[0]->info);
                free(tmp->elems[0]);
                tmp->elems[0] = NULL;
                pos1 = 0;
                while (pos1 != -1) {
                 //   printf("Center: %d %d\n", tmp->key.x, tmp->key.y);
                    tmp->child[pos1] = createNode(tmp->size, pos1, tmp->key);
                    tmp->child[pos1]->prev = tmp;
                    if (!tmp->child[pos1]) {
                        printf("It is impossible to insert an element!\n");
                        free(temporary.info);
                        return 0;
                    }
                    tmp = tmp->child[pos1];
              //      printf("x: %d, y: %d\n", tmp->key.x, tmp->key.y);
                    pos1 = getPos(tmp->key, key);
                    pos2 = getPos(tmp->key, temporary.key);
              //      printf("%d, %d\n", pos1, pos2);
                    if (pos1 != pos2) {
                        tmp->elems[pos1] = (element*)calloc(1, sizeof(element));
                        tmp->elems[pos1]->key = key;
                        tmp->elems[pos1]->info = (char*)calloc(strlen(Info) + 1, sizeof(char));
                        memcpy(tmp->elems[pos1]->info, Info, strlen(Info) + 1);
                        tmp->elems[pos2] = (element*)malloc(sizeof(element));
                        tmp->elems[pos2]->key = temporary.key;
                        tmp->elems[pos2]->info = (char*)calloc(strlen(temporary.info) + 1, sizeof(char));
                        memcpy(tmp->elems[pos2]->info, temporary.info, strlen(temporary.info) + 1);
                        free(temporary.info);
                        return 1;
                    }
                }
            }
        }
        else if (x <= tmp->key.x && y > tmp->key.y) {
            if (tmp->child[1] == NULL && tmp->elems[1] == NULL) {
                tmp->elems[1] = (element*)malloc(sizeof(element));
                tmp->elems[1]->info = (char*)calloc(strlen(Info) + 1, sizeof(char));
                memcpy(tmp->elems[1]->info, Info, strlen(Info) + 1);
                tmp->elems[1]->key = key;
                return 1;
            }
            else if (tmp->child[1] != NULL) {
                tmp = tmp->child[1];
            }
            else if (tmp->child[1] == NULL && tmp->elems[1] != NULL) {
                temporary.key = tmp->elems[1]->key;
                temporary.info = (char*)calloc(strlen(tmp->elems[1]->info) + 1, sizeof(char));
                memcpy(temporary.info, tmp->elems[1]->info, strlen(tmp->elems[1]->info) + 1);
                free(tmp->elems[1]->info);
                free(tmp->elems[1]);
                tmp->elems[1] = NULL;
                pos1 = 1;
                while (pos1 != -1) {
                    tmp->child[pos1] = createNode(tmp->size, pos1, tmp->key);
                    tmp->child[pos1]->prev = tmp;
                    if (!tmp->child[pos1]) {
                        printf("It is impossible to insert an element!\n");
                        free(temporary.info);
                        return 0;
                    }
                    tmp = tmp->child[pos1];
            //        printf("x: %d, y: %d\n", tmp->key.x, tmp->key.y);
                    pos1 = getPos(tmp->key, key);
                    pos2 = getPos(tmp->key, temporary.key);
             //       printf("%d, %d\n", pos1, pos2);
                    if (pos1 != pos2) {
                        tmp->elems[pos1] = (element*)malloc(sizeof(element));
                        tmp->elems[pos1]->key = key;
                        tmp->elems[pos1]->info = (char*)calloc(strlen(Info) + 1, sizeof(char));
                        memcpy(tmp->elems[pos1]->info, Info, strlen(Info) + 1);
                        tmp->elems[pos2] = (element*)malloc(sizeof(element));
                        tmp->elems[pos2]->key = temporary.key;
                        tmp->elems[pos2]->info = (char*)calloc(strlen(temporary.info) + 1, sizeof(char));
                        memcpy(tmp->elems[pos2]->info, temporary.info, strlen(temporary.info) + 1);
                        free(temporary.info);
                        return 1;
                    }
                }
            }
        }
        else if (x <= tmp->key.x && y <= tmp->key.y) {
            if (tmp->child[2] == NULL && tmp->elems[2] == NULL) {
                tmp->elems[2] = (element*)malloc(sizeof(element));
                tmp->elems[2]->info = (char*)calloc(strlen(Info) + 1, sizeof(char));
                memcpy(tmp->elems[2]->info, Info, strlen(Info) + 1);
                tmp->elems[2]->key = key;
                return 1;
            }
            else if (tmp->child[2] != NULL) {
                tmp = tmp->child[2];
            }
            else if (tmp->child[2] == NULL && tmp->elems[2] != NULL) {
                temporary.key = tmp->elems[2]->key;
                temporary.info = (char*)calloc(strlen(tmp->elems[2]->info) + 1, sizeof(char));
                memcpy(temporary.info, tmp->elems[2]->info, strlen(tmp->elems[2]->info) + 1);
                free(tmp->elems[2]->info);
                free(tmp->elems[2]);
                tmp->elems[2] = NULL;
                pos1 = 2;
                while (pos1 != -1) {
                    tmp->child[pos1] = createNode(tmp->size, pos1, tmp->key);
                    tmp->child[pos1]->prev = tmp;
                    if (!tmp->child[pos1]) {
                        printf("It is impossible to insert an element!\n");
                        free(temporary.info);
                        return 0;
                    }
                    tmp = tmp->child[pos1];
            //        printf("x: %d, y: %d\n", tmp->key.x, tmp->key.y);
                    pos1 = getPos(tmp->key, key);
                    pos2 = getPos(tmp->key, temporary.key);
            //        printf("%d, %d\n", pos1, pos2);
                    if (pos1 != pos2) {
                        tmp->elems[pos1] = (element*)malloc(sizeof(element));
                        tmp->elems[pos1]->key = key;
                        tmp->elems[pos1]->info = (char*)calloc(strlen(Info) + 1, sizeof(char));
                        memcpy(tmp->elems[pos1]->info, Info, strlen(Info) + 1);
                        tmp->elems[pos2] = (element*)malloc(sizeof(element));
                        tmp->elems[pos2]->key = temporary.key;
                        tmp->elems[pos2]->info = (char*)calloc(strlen(temporary.info) + 1, sizeof(char));
                        memcpy(tmp->elems[pos2]->info, temporary.info, strlen(temporary.info) + 1);
                        free(temporary.info);
                        return 1;
                    }
                }
                free(temporary.info);
            }
        }
        else if (x > tmp->key.x && y <= tmp->key.y) {
            if (tmp->child[3] == NULL && tmp->elems[3] == NULL) {
                tmp->elems[3] = (element*)malloc(sizeof(element));
                tmp->elems[3]->info = (char*)calloc(strlen(Info) + 1, sizeof(char));
                memcpy(tmp->elems[3]->info, Info, strlen(Info) + 1);
                tmp->elems[3]->key = key;
                return 1;
            }
            else if (tmp->child[3] != NULL) {
                tmp = tmp->child[3];
            }
            else if (tmp->child[3] == NULL && tmp->elems[3] != NULL) {
                temporary.key = tmp->elems[3]->key;
                temporary.info = (char*)calloc(strlen(tmp->elems[3]->info) + 1, sizeof(char));
                memcpy(temporary.info, tmp->elems[3]->info, strlen(tmp->elems[3]->info) + 1);
                free(tmp->elems[3]->info);
                free(tmp->elems[3]);
                tmp->elems[3] = NULL;
                pos1 = 3;
                while (pos1 != -1) {
                    tmp->child[pos1] = createNode(tmp->size, pos1, tmp->key);
                    tmp->child[pos1]->prev = tmp;
                    if (!tmp->child[pos1]) {
                        printf("It is impossible to insert an element!\n");
                        free(temporary.info);
                        return 0;
                    }
                    tmp = tmp->child[pos1];
            //        printf("x: %d, y: %d\n", tmp->key.x, tmp->key.y);
                    pos1 = getPos(tmp->key, key);
                    pos2 = getPos(tmp->key, temporary.key);
            //        printf("%d, %d\n", pos1, pos2);
                    if (pos1 != pos2) {
                        tmp->elems[pos1] = (element*)malloc(sizeof(element));
                        tmp->elems[pos1]->key = key;
                        tmp->elems[pos1]->info = (char*)calloc(strlen(Info) + 1, sizeof(char));
                        memcpy(tmp->elems[pos1]->info, Info, strlen(Info) + 1);
                        tmp->elems[pos2] = (element*)malloc(sizeof(element));
                        tmp->elems[pos2]->key = temporary.key;
                        tmp->elems[pos2]->info = (char*)calloc(strlen(temporary.info) + 1, sizeof(char));
                        memcpy(tmp->elems[pos2]->info, temporary.info, strlen(temporary.info) + 1);
                        free(temporary.info);
                        return 1;
                    }
                }
                free(temporary.info);
            }
        }
    }
}

void deleteElement(kvad_node *root) {
    point p, tmp;
    int save = 0;
    element temporary;
    printf("Enter the first key: ");
    getInt(&(p.x));
    printf("Enter the second key: ");
    getInt(&(p.y));
    kvad_node* find = findElem(root, p);
    if (!find) {
        printf("That element is not in the tree!");
        return;
    }
    int pos = getPos(find->key, p), cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < 4; i++) {
        if (find->elems[i])
            cnt1++;
        if (find->child[i])
            cnt2++;
    }
    if (cnt1 >= 3) {
        free(find->elems[pos]->info);
        free(find->elems[pos]);
        find->elems[pos] = NULL;
        return;
    }
    else if (cnt1 == 1 && cnt2 == 0) {
        if (find->prev == NULL) {
            free(find->elems[pos]->info);
            free(find->elems[pos]);
            find->elems[pos] = NULL;
            return;
        }
        else {
            free(find->elems[pos]->info);
            free(find->elems[pos]);
            tmp = find->key;
            find = find->prev;
            pos = getPos(find->key, tmp);
            free(find->child[pos]);
            find->child[pos] = NULL;
            return;
        }
    }
    else if ((cnt1 == 1 || cnt2 == 2) && cnt2 > 0) {
        free(find->elems[pos]->info);
        free(find->elems[pos]);
        find->elems[pos] = NULL;
        return;
    }
    else if (cnt1 == 2 && cnt2 == 0) {
        if (find->prev == NULL) {
            free(find->elems[pos]->info);
            free(find->elems[pos]);
            find->elems[pos] = NULL;
            return;
        }
        else {
         //   printf("%d\n", pos);
            for (int i = 0; i < 4; i++) {
                if (find->elems[i] && i != pos) {
                    save = i;
                    break;
                }
            }
            temporary.key = find->elems[save]->key;
            temporary.info = (char*)calloc(strlen(find->elems[save]->info) + 1, sizeof(char));
            memcpy(temporary.info, find->elems[save]->info, strlen(find->elems[save]->info) + 1);
            free(find->elems[save]->info);
            free(find->elems[save]);
            find->elems[save] = NULL;
            free(find->elems[pos]->info);
            free(find->elems[pos]);
            find->elems[pos] = NULL;
            tmp = find->key;
            find = find->prev;
            pos = getPos(find->key, tmp);
         //   printf("%d\n", pos);
            free(find->child[pos]);
            find->child[pos] = NULL;
            find->elems[pos] = (element*)malloc(sizeof(element));
            find->elems[pos]->info = (char*)calloc(strlen(temporary.info) + 1, sizeof(char));
            memcpy(find->elems[pos]->info, temporary.info, strlen(temporary.info) + 1);
            find->elems[pos]->key = temporary.key;
            free(temporary.info);
        }
    }
}

int max_element(kvad_node *root, int max, point* p) {
    int curr, save = 0;
    for (int i = 0; i < 4; i++) {
        if (root->elems[i]) {
           // printf("point: x: %d, y: %d \n", root->elems[i]->key.x, root->elems[i]->key.y);
            curr = root->elems[i]->key.x * root->elems[i]->key.x + root->elems[i]->key.y * root->elems[i]->key.y;
            if (curr > max) {
                max = curr;
               // printf("point: x: %d, y: %d \n", root->elems[i]->key.x, root->elems[i]->key.y);
                p->x = root->elems[i]->key.x;
                p->y = root->elems[i]->key.y;
             //   printf("Afterpoint: x: %d, y: %d \n", p.x, p.y);
            }
        }
    }
    if (root->child[0]) {
        save = max_element(root->child[0], max, p);
        if (save > max) max = save;
    }
    if (root->child[1]) {
        save = max_element(root->child[1], max, p);
        if (save > max) max = save;
    }
    if (root->child[2]) {
        save = max_element(root->child[2], max, p);
        if (save > max) max = save;
    }
    if (root->child[3]) {
        save = max_element(root->child[3], max, p);
        if (save > max) max = save;
    }
    return max;
}

int timing_func() {
    kvad_node *root = NULL;
    root = createRoot();
    int n = 10, cnt = 1000, i, m, numb;
    point key[100], p;
    clock_t first, last;
    char *info;
    info = "random_string";
    while (n-- > 0) {
        for (i = 0; i < 100; i++) {
            numb = rand() % 100;
            key[i].x = numb;
            numb = rand() % 100;
            key[i].y = numb;
        }
        for (i = 0; i < cnt; ) {
            p.x = rand() % 1000;
            p.y = rand() % 1000;
            if (addElem(&root, p, info))
                ++i;
        }
        m = 0;
        first = clock();
        for (i = 0; i < 100; i++) {
            if (findElem(root, key[i])) {
                m++;
            }
        }
        last = clock();
        printf("test #%d, number of nodes = %d, time = %ld\n", 10 - n, (10 - n) * cnt, last - first);
    }
    deleteTree(root);
    free(root);
    return 1;
}
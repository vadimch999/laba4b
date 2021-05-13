#include "header.h"

int main() {
    kvad_node *root = NULL;
    srand(time(NULL));
    root = createRoot();
    point p;
    int max = 0;
    int command;
    do {
        printf("%s", msg);
        printf("Enter your choice: ");
        getInt(&command);
        switch (command) {
            case 0:
                deleteTree(root);
                break;
            case 1:
                getInfo(&root);
                break;
            case 2:
                printTree(root, "root", 0);
                break;
            case 3:
                getKey(root);
                break;
            case 4:
                deleteElement(root);
                break;
            case 5:
                max = 0;
                max = max_element(root, max, &p);
                printf("Max point: x: %d, y: %d \n", p.x, p.y);
                break;
            case 6:
                timing_func();
                break;
            case 7:
                //   load(&root);
                break;
            case 8:
                //   save(&root);
                break;
            default:
                printf("Error!\n");
        }
    } while (command != 0);
    free(root);
    return 0;
}

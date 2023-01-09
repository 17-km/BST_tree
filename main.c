#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

int getNumber()
{
    char decimal = getchar();
    int number = 0;
    do
    {
        number = number * 10 + (int)(decimal - '0');
        decimal = getchar();
    } while (decimal != '\n');
    return number;
}

int main()
{
    struct node *root = NULL;
    char command[3];
    int parameter;

    /*
    root = insertNode(root, 8);
    root = insertNode(root, 4);
    root = insertNode(root, 2);
    root = insertNode(root, 1);
    root = insertNode(root, 3);
    root = insertNode(root, 6);
    root = insertNode(root, 5);
    root = insertNode(root, 7);
    root = insertNode(root, 12);
    root = insertNode(root, 10);
    root = insertNode(root, 9);
    root = insertNode(root, 11);
    root = insertNode(root, 14);
    root = insertNode(root, 13);
    root = insertNode(root, 15);
    */

    //display(root,0);

    //root = deleteLowerThan(root,4);
    //root = deleteHigherThan(root,11);
    //root = deleteNode(root,8,0);
    //root = insertNode(root,8);
    //display(root,0);

    while (1)
    {
        printf ("Podaj komende: ");

        command[0] = getchar();
        command[1] = getchar();
        command[2] = getchar();
        char ignore;
        do
        {
            ignore = getchar();
        } while(ignore != ' ' && ignore != '\n');

        if (command[0] == 'i' && command[1] == 'n' && command[2] == 's')
        {
            parameter = getNumber();
            root = insertNode(root,parameter);
        }
        else if (command[0] == 'd' && command[1] == 'e' && command[2] == 'l')
        {
            parameter = getNumber();
            if (root == NULL) printf ("Brak elementow w drzewie \n");
            else root = deleteNode(root,parameter,0);
        }
        else if (command[0] == 's' && command[1] == 'r' && command[2] == 'c')
        {
            parameter = getNumber();
            if (isNodeInTree(root,parameter) == 1) printf("TAK \n");
            else printf("NIE \n");
        }
        else if (command[0] == 'm' && command[1] == 'i' && command[2] == 'n')
        {
            minimumValue(root);
        }
        else if (command[0] == 'm' && command[1] == 'a' && command[2] == 'x')
        {
            maximumValue(root);
        }
        else if (command[0] == 'r' && command[1] == 'm' && command[2] == 'l')
        {
            parameter = getNumber();
            root = deleteLowerThan(root,parameter);
        }
        else if (command[0] == 'r' && command[1] == 'm' && command[2] == 'g')
        {
            parameter = getNumber();
            root = deleteHigherThan(root,parameter);
        }
        else if (command[0] == 'p' && command[1] == 'r' && command[2] == 'i')
        {
            if (root == NULL) printf ("Brak elementow w drzewie \n");
            else display(root,0);
        }
        else if (command[0] == 'q' && command[1] == 'u' && command[2] == 'i')
        {
            exit(0);
        }
    }

    return 0;
}

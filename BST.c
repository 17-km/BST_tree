#include "BST.h"

/*
// wezel drzewa
struct node
{
    // wartosc wezla
    int key;
    // wskazniki do lewego i prawego dziecka
    struct node *left, *right;
};
*/

// tworzenie wezla
struct node *createNode(int number)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = number;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// wyswietlanie drzewa
void display(struct node *parentNode, int level)
{
    //jezli wezel istnieje, to probujemy zejsc nizej
    if (parentNode != NULL)
    {
        // najpierw wezel prawy z wieksza wartoscia, dodajemy jeden do numeru poziomu
        display(parentNode->right,level+1);

        //jak z prawej strony wrocimy, to wyswietlamy wartoscia naszego wezla poprzedzona odpowiednia iloscia tabulatorow
        for(int i = 0; i < level; i++)
        {
            printf("\t");
        }
        printf("%d \n", parentNode->key);

        // teraz wezel lewy z mniejsza wartoscia, dodajemy jeden do numeru poziomu
        display(parentNode->left,level+1);
    }
}

// wstawianie wezla
struct node *insertNode(struct node *parentNode, int number)
{

    // jesli wezel jest pusty, wstawiamy tam podana wartosc
    if (parentNode == NULL)
    {
        printf ("Pomyslnie dodano liczbe %i\n", number);
        return createNode(number);
    }

    // jesli nie jest pudty, to probujemy wstawic wartosc do jednego z dzieci

    // sprawdzamy, czy wpisywana wartosc jest wieksza niz w rozpatrywanym poprzedniku
    if (number > parentNode->key)
    {
        parentNode->right = insertNode(parentNode->right, number);
    }
    // sprawdzamy, czy wpisywana wartosc jest mniejsza niz w rozpatrywanym poprzedniku
    else if (number < parentNode->key)
    {
        parentNode->left = insertNode(parentNode->left, number);
    }
    // jesli oba powyzsze nie sa spelnione, to wartosc juz jest w drzewie
    else
    {
        printf ("Wrtosc %i jest juz w drzewie \n", number);
    }

    return parentNode;
}

// szukanie wezla
char isNodeInTree(struct node *parentNode, int number)
{
    char answer;
    // jesli obecny wezel jest pusty, to wartosci na pewno nie ma w drzewie
    if (parentNode == NULL)
    {
        answer = 0;
    }

    else
    {
        // jesli nie jest pusty, to szukamy wezla
        // jesli wartosc obecnego wezla jest mniejsza, to idziemy w prawo
        if (number > parentNode->key)
        {
            answer = isNodeInTree(parentNode->right, number);
        }
        // jesli wartosc obecnego wezla jest wieksza, to idziemy w lewo
        else if (number < parentNode->key)
        {
            answer = isNodeInTree(parentNode->left, number);
        }
        // jesli wartosci sie zgadzaja, to wartosc jest w drzewie
        else
        {
            answer = 1;
        }
    }
    return answer;
}

// szukanie minimum
struct node *minimumNode(struct node *parentNode)
{
    struct node *minNode = parentNode;

    // Przechodzenie do najbardziej lewego dziecka
    while (minNode && minNode->left != NULL)
        minNode = minNode->left;

    return minNode;
}

// szukanie mamskium
struct node *maximumNode(struct node *parentNode)
{
    struct node *maxNode = parentNode;

    // Przechodzenie do najbardziej prawego dziecka
    while (maxNode && maxNode->right != NULL)
        maxNode = maxNode->right;

    return maxNode;
}

// szukanie minimum
void minimumValue(struct node *parentNode)
{
    // jesli pierwszy wezel nie istnieje, to znaczy, ze w drzewie nie ma elementow
    if (parentNode == NULL)
    {
        printf ("Brak elementow w drzewie \n");
    }
    // jesli wezel istnieje to szukamy wezla najbardziej po lewej
    else
    {
        struct node *minNode = minimumNode(parentNode);
        printf("%i \n", minNode->key);
    }
}

// szukanie maksimum
void maximumValue(struct node *parentNode)
{
    if (parentNode == NULL)
    {
        printf ("Brak elementow w drzewie \n");
    }
    // jesli wezel istnieje to szukamy wezla najbardziej po prawej
    else
    {
        struct node *maxNode = maximumNode(parentNode);
        printf("%i \n", maxNode->key);
    }
}

// usuwanie wezla
struct node *deleteNode(struct node *parentNode, int number, char side)
{
    // jesli obecny wezel jest pusty, to znaczy, ze nie ma czego usuwac
    if (parentNode == NULL)
    {
        printf ("Brak liczby %i w drzewie \n",number);
        return parentNode;
    }


    else
    {
        // jesli usuwana wartosc jest mniejsza niz wartosc obecnego wezla, przechodzimy w lewo
        if (number < parentNode->key)
            parentNode->left = deleteNode(parentNode->left, number, 1);
        // jesli usuwana wartosc jest wieksza niz wartosc obecnego wezla, przechodzimy w prawo
        else if (number > parentNode->key)
            parentNode->right = deleteNode(parentNode->right, number, 0);
        // w przeciwnym razie obecny wezel jest tym, ktory musimy usunac
        else
        {
            // jesli wezel ma tylko jedno dziecko lub nie ma wcale dzieci, to wystarzczy przesunac dziecko na miejsce rodzica
            if (parentNode->left == NULL)
            {
                struct node *newParent = parentNode->right;
                free(parentNode);
                return newParent;
            }
            else if (parentNode->right == NULL)
            {
                struct node *newParent = parentNode->left;
                free(parentNode);
                return newParent;
            }

            // gdy usuwamy kilka elementow wiekszych niz cos
            if (side == 0)
            {
                // jesli wezel ma dwoje dzieci, szukamy minimalnej wartosci z galezi po prawej stronie usuwanego wezla
                struct node *newParent = minimumNode(parentNode->right);
                // teraz ta wartosc przypisujemy wezlowi, ktory chcemy usunac
                parentNode->key = newParent->key;
                // usuwamy teraz wezel z poddrzewa po prawej stronie z ta sama wartoscia, podajac jako korzeñ pierwszy wezel po prawej stronie
                parentNode->right = deleteNode(parentNode->right, parentNode->key, side);
            }
            // gdy usuwamy kilka elementow mniejszych niz cos
            else
            {
                // jesli wezel ma dwoje dzieci, szukamy maksymalnej wartosci z galezi po lewej stronie usuwanego wezla
                struct node *newParent = maximumNode(parentNode->left);
                // teraz ta wartosc przypisujemy wezlowi, ktory chcemy usunac
                parentNode->key = newParent->key;
                // usuwamy teraz wezel z poddrzewa po lewej stronie z ta sama wartoscia, podajac jako korzeñ pierwszy wezel po lewej stronie
                parentNode->left = deleteNode(parentNode->left, parentNode->key, side);
            }
        }
        return parentNode;
    }
}


struct node *deleteLowerThan(struct node *parentNode, int number)
{
    if (parentNode == NULL)
    {
        printf ("Brak elementow w drzewie \n");
    }
    else
    {
        struct node *minNode = minimumNode(parentNode);
        while (minNode && minNode->key < number)
        {
            parentNode = deleteNode (parentNode, minNode->key, 1);
            minNode = minimumNode(parentNode);
        }
        printf ("Zakonczono usuwanie \n");
    }
    return parentNode;
}

struct node *deleteHigherThan(struct node *parentNode, int number)
{
    if (parentNode == NULL)
    {
        printf ("Brak elementow w drzewie \n");
    }
    else
    {
        struct node *maxNode = maximumNode(parentNode);

        while (maxNode && maxNode->key > number)
        {
            parentNode = deleteNode (parentNode, maxNode->key, 0);
            maxNode = maximumNode(parentNode);
        }
        printf ("Zakonczono usuwanie \n");
    }
    return parentNode;
}

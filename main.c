#include <stdio.h>
#include <stdlib.h>

// wêze³ drzewa
struct node
{
    // wartoœæ wêz³a
    int key;
    // wskaŸniki do lewego i prawego dziecka
    struct node *left, *right;
};

// tworzenie wêz³¹
struct node *createNode(int number)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = number;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// wyœwietlanie drzewa
void display(struct node *parentNode, int level)
{
    //jeœli wêze³ istnieje, to próbujemy zejœæ ni¿ej
    if (parentNode != NULL)
    {
        // najpierw wêze³ prawy z wiêksz¹ wartoœci¹, dodajemy jeden do numeru poziomu
        display(parentNode->right,level+1);

        //jak z prawej strony wrócimy, to wyœwietlamy wartoœæ naszego wêz³a poprzedzon¹ odpowiedni¹ iloœci¹ tabulatorów
        for(int i = 0; i < level; i++)
        {
            printf("\t");
        }
        printf("%d \n", parentNode->key);

        // teraz wêze³ lewy z mniejsz¹ wartoœci¹, dodajemy jeden do numeru poziomu
        display(parentNode->left,level+1);
    }
}

// wstawianie wêz³a
struct node *insertNode(struct node *parentNode, int number)
{

    // jeœli wêze³ jest pusty, wstawiamy tam podan¹ wartoœæ
    if (parentNode == NULL)
    {
        printf ("Pomyslnie dodano liczbe %i\n", number);
        return createNode(number);
    }

    // jeœli nie jest pudty, to próbujemy wstawiæ wartoœæ do jednego z dzieci

    // sprawdzamy, czy wpisywana wartoœæ jest wiêksza ni¿ w rozpatrywanym poprzedniku
    if (number > parentNode->key)
    {
        parentNode->right = insertNode(parentNode->right, number);
    }
    // sprawdzamy, czy wpisywana wartoœæ jest mniejsza ni¿ w rozpatrywanym poprzedniku
    else if (number < parentNode->key)
    {
        parentNode->left = insertNode(parentNode->left, number);
    }
    // jeœli oba powy¿sze nie s¹ spe³nione, to wartoœæ ju¿ jest w drzewie
    else
    {
        printf ("Wrtosc %i jest juz w drzewie \n", number);
    }

    return parentNode;
}

// szukanie wêz³a
char isNodeInTree(struct node *parentNode, int number)
{
    char answer;
    // jeœli obecny wêze³ jest pusty, to wartoœci na pewno nie ma w drzewie
    if (parentNode == NULL)
    {
        answer = 0;
    }

    else
    {
        // jeœli nie jest pudty, to szukamy wêz³a
        // jeœli wartoœæ obecnego wêz³a jest mniejsza, to idziemy w prawo
        if (number > parentNode->key)
        {
            answer = isNodeInTree(parentNode->right, number);
        }
        // jeœli wartoœæ obecnego wêz³a jest wiêksza, to idziemy w lewo
        else if (number < parentNode->key)
        {
            answer = isNodeInTree(parentNode->left, number);
        }
        // jeœli wartoœci siê zgadzaj¹, to wartoœæ jest w drzewie
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
    // jeœli pierwszy wêze³ nie istnieje, to znaczy, ¿e w drzewie nie ma elementów
    if (parentNode == NULL)
    {
        printf ("Brak elementow w drzewie \n");
    }
    // jeœli wêze³ istnieje to szukamy wêz³a najbardziej po lewej
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
    // jeœli wêze³ istnieje to szukamy wêz³a najbardziej po prawej
    else
    {
        struct node *maxNode = maximumNode(parentNode);
        printf("%i \n", maxNode->key);
    }
}

// usuwanie wêz³a
struct node *deleteNode(struct node *parentNode, int number, char side)
{
    // jeœli obecny wêze³ jest pusty, to znaczy, ¿e nie ma czego usuwaæ
    if (parentNode == NULL)
    {
        printf ("Brak liczby %i w drzewie \n",number);
        return parentNode;
    }


    else
    {
        // jeœli usuwana wartoœæ jest mniejsza ni¿ wartoœæ obecnego wêz³a, przechodzimy w lewo
        if (number < parentNode->key)
            parentNode->left = deleteNode(parentNode->left, number, 1);
        // jeœli usuwana wartoœæ jest wiêksza ni¿ wartoœæ obecnego wêz³a, przechodzimy w prawo
        else if (number > parentNode->key)
            parentNode->right = deleteNode(parentNode->right, number, 0);
        // w przeciwnym razie obecny wêze³ jest tym, który musimy usun¹æ
        else
        {
            // jeœli wêze³ ma tylko jedno dziecko lub nie ma wcale dzieci, to wystarzczy przesun¹æ dziecko na miejsce rodzica
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

            // gdy usuwamy kilka elementów wiêkszych ni¿ coœ
            if (side == 0)
            {
                // jeœli wêze³ ma dwoje dzieci, szukamy minimalnej wartoœci z ga³êzi po prawej stronie usuwanego wêz³a
                struct node *newParent = minimumNode(parentNode->right);
                // teraz t¹ wartoœæ przypisujemy wêz³owi, który chcemy usun¹æ
                parentNode->key = newParent->key;
                // usuwamy teraz wêze³ z poddrzewa po prawej stronie z t¹ sam¹ wartoœci¹, podaj¹c jako korzeñ pierwszy wêze³ po prawej stronie
                parentNode->right = deleteNode(parentNode->right, parentNode->key, side);
            }
            // gdy usuwamy kilka elementów mniejszych ni¿ coœ
            else
            {
                // jeœli wêze³ ma dwoje dzieci, szukamy maksymalnej wartoœci z ga³êzi po lewej stronie usuwanego wêz³a
                struct node *newParent = maximumNode(parentNode->left);
                // teraz t¹ wartoœæ przypisujemy wêz³owi, który chcemy usun¹æ
                parentNode->key = newParent->key;
                // usuwamy teraz wêze³ z poddrzewa po lewej stronie z t¹ sam¹ wartoœci¹, podaj¹c jako korzeñ pierwszy wêze³ po lewej stronie
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
    //display(root,0);

    //root = deleteLowerThan(root,4);
    //root = deleteHigherThan(root,11);
    //root = deleteNode(root,8,0);
    //root = insertNode(root,8);
    //display(root,0);

    while (1)
    {
        printf ("Podaj komende: ");

        char h;

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

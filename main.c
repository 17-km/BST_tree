#include <stdio.h>
#include <stdlib.h>

// w�ze� drzewa
struct node
{
    // warto�� w�z�a
    int key;
    // wska�niki do lewego i prawego dziecka
    struct node *left, *right;
};

// tworzenie w�z��
struct node *createNode(int number)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = number;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// wy�wietlanie drzewa
void display(struct node *parentNode, int level)
{
    //je�li w�ze� istnieje, to pr�bujemy zej�� ni�ej
    if (parentNode != NULL)
    {
        // najpierw w�ze� prawy z wi�ksz� warto�ci�, dodajemy jeden do numeru poziomu
        display(parentNode->right,level+1);

        //jak z prawej strony wr�cimy, to wy�wietlamy warto�� naszego w�z�a poprzedzon� odpowiedni� ilo�ci� tabulator�w
        for(int i = 0; i < level; i++)
        {
            printf("\t");
        }
        printf("%d \n", parentNode->key);

        // teraz w�ze� lewy z mniejsz� warto�ci�, dodajemy jeden do numeru poziomu
        display(parentNode->left,level+1);
    }
}

// wstawianie w�z�a
struct node *insertNode(struct node *parentNode, int number)
{

    // je�li w�ze� jest pusty, wstawiamy tam podan� warto��
    if (parentNode == NULL)
    {
        printf ("Pomyslnie dodano liczbe %i\n", number);
        return createNode(number);
    }

    // je�li nie jest pudty, to pr�bujemy wstawi� warto�� do jednego z dzieci

    // sprawdzamy, czy wpisywana warto�� jest wi�ksza ni� w rozpatrywanym poprzedniku
    if (number > parentNode->key)
    {
        parentNode->right = insertNode(parentNode->right, number);
    }
    // sprawdzamy, czy wpisywana warto�� jest mniejsza ni� w rozpatrywanym poprzedniku
    else if (number < parentNode->key)
    {
        parentNode->left = insertNode(parentNode->left, number);
    }
    // je�li oba powy�sze nie s� spe�nione, to warto�� ju� jest w drzewie
    else
    {
        printf ("Wrtosc %i jest juz w drzewie \n", number);
    }

    return parentNode;
}

// szukanie w�z�a
char isNodeInTree(struct node *parentNode, int number)
{
    char answer;
    // je�li obecny w�ze� jest pusty, to warto�ci na pewno nie ma w drzewie
    if (parentNode == NULL)
    {
        answer = 0;
    }

    else
    {
        // je�li nie jest pudty, to szukamy w�z�a
        // je�li warto�� obecnego w�z�a jest mniejsza, to idziemy w prawo
        if (number > parentNode->key)
        {
            answer = isNodeInTree(parentNode->right, number);
        }
        // je�li warto�� obecnego w�z�a jest wi�ksza, to idziemy w lewo
        else if (number < parentNode->key)
        {
            answer = isNodeInTree(parentNode->left, number);
        }
        // je�li warto�ci si� zgadzaj�, to warto�� jest w drzewie
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
    // je�li pierwszy w�ze� nie istnieje, to znaczy, �e w drzewie nie ma element�w
    if (parentNode == NULL)
    {
        printf ("Brak elementow w drzewie \n");
    }
    // je�li w�ze� istnieje to szukamy w�z�a najbardziej po lewej
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
    // je�li w�ze� istnieje to szukamy w�z�a najbardziej po prawej
    else
    {
        struct node *maxNode = maximumNode(parentNode);
        printf("%i \n", maxNode->key);
    }
}

// usuwanie w�z�a
struct node *deleteNode(struct node *parentNode, int number, char side)
{
    // je�li obecny w�ze� jest pusty, to znaczy, �e nie ma czego usuwa�
    if (parentNode == NULL)
    {
        printf ("Brak liczby %i w drzewie \n",number);
        return parentNode;
    }


    else
    {
        // je�li usuwana warto�� jest mniejsza ni� warto�� obecnego w�z�a, przechodzimy w lewo
        if (number < parentNode->key)
            parentNode->left = deleteNode(parentNode->left, number, 1);
        // je�li usuwana warto�� jest wi�ksza ni� warto�� obecnego w�z�a, przechodzimy w prawo
        else if (number > parentNode->key)
            parentNode->right = deleteNode(parentNode->right, number, 0);
        // w przeciwnym razie obecny w�ze� jest tym, kt�ry musimy usun��
        else
        {
            // je�li w�ze� ma tylko jedno dziecko lub nie ma wcale dzieci, to wystarzczy przesun�� dziecko na miejsce rodzica
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

            // gdy usuwamy kilka element�w wi�kszych ni� co�
            if (side == 0)
            {
                // je�li w�ze� ma dwoje dzieci, szukamy minimalnej warto�ci z ga��zi po prawej stronie usuwanego w�z�a
                struct node *newParent = minimumNode(parentNode->right);
                // teraz t� warto�� przypisujemy w�z�owi, kt�ry chcemy usun��
                parentNode->key = newParent->key;
                // usuwamy teraz w�ze� z poddrzewa po prawej stronie z t� sam� warto�ci�, podaj�c jako korze� pierwszy w�ze� po prawej stronie
                parentNode->right = deleteNode(parentNode->right, parentNode->key, side);
            }
            // gdy usuwamy kilka element�w mniejszych ni� co�
            else
            {
                // je�li w�ze� ma dwoje dzieci, szukamy maksymalnej warto�ci z ga��zi po lewej stronie usuwanego w�z�a
                struct node *newParent = maximumNode(parentNode->left);
                // teraz t� warto�� przypisujemy w�z�owi, kt�ry chcemy usun��
                parentNode->key = newParent->key;
                // usuwamy teraz w�ze� z poddrzewa po lewej stronie z t� sam� warto�ci�, podaj�c jako korze� pierwszy w�ze� po lewej stronie
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

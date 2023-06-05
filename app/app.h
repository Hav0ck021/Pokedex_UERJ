#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

template <typename T>
struct node
{
    T data;
    node<T>* previous = nullptr;
    node<T>* next = nullptr;
};

template <typename T>
struct list
{
    node<T>* begin = nullptr;
    node<T>* end = nullptr;
    int cont = 0;
};

//Função responsável por adicionar pokemons a lista.
template <typename T>
void append(list<T>& lst, T value)
{
    node<T>* new_data = new node<T>;
    new_data->data = value;
    if (lst.cont == 0)
        lst.begin = lst.end = new_data;
    else
    {
        new_data->previous = lst.end;
        lst.end->next = new_data;
        lst.end = new_data;
    }
    lst.cont++;
}

//Função responsável por limpar a memória.
template <typename T>
void clear_memory(list<T>& lst)
{
    while (lst.cont > 0)
    {
        node<T>* aux = lst.end;
        lst.end = lst.end->previous;
        delete aux;
        lst.cont--;
    }
    lst.begin = lst.end = nullptr;
}

//Função responsável por selecionar um nó da lista.
template <typename T>
node<T> *get_node(list<T> &lst, int position)
{
    node<T> *aux = lst.begin;
    for(int i = 0; i < position; i++)
    {
        aux = aux->next;
    }
    return aux;
}

//Função responsável por remover um item da lista.
template <typename T>
void remove_node(list<T>& lst, int id, int(compare_function)(T, int))
{
    int position = binary_search(lst, 0, lst.cont - 1, id, compare_function);
    if (position != -1)
    {
        node<T> *nodeToRemove = get_node(lst, position);
        if (nodeToRemove->previous != nullptr)
            nodeToRemove->previous->next = nodeToRemove->next;
        else
            lst.begin = nodeToRemove->next;

        if (nodeToRemove->next != nullptr)
            nodeToRemove->next->previous = nodeToRemove->previous;
        else
            lst.end = nodeToRemove->previous;

        delete nodeToRemove;
        lst.cont--;
    }
}

//Função responsável por imprimir os itens da lista.
template <typename T>
void print(list<T>& lst, void(*print_function)(T))
{
    node<T>* aux = lst.begin;
    for (int i = 0; i < lst.cont; i++)
    {
        print_function(aux->data);
        aux = aux->next;
    }
}

//Função responsável por imprimir um único nó
template <typename T>
void print_one_node(list<T>& lst, int position, void(*print_function)(T))
{
    if (position == -1)
    {
        cout << "Pokemon not found!" << endl << endl;
        return;
    }
    node<T>* aux = get_node(lst, position);
    print_function(aux->data);
}

//Função responsável por trocar itens na lista.
template<typename T>
void swap_nodes(list<T>& lst, int position1, int position2)
{
    node<T>* node1 = get_node(lst, position1);
    node<T>* node2 = get_node(lst, position2);
    T aux = node1->data;
    node1->data = node2->data;
    node2->data = aux;
}

template <typename T>
void bubble_sort(list<T>& lst, int(*sort_function)(T,T))
{
    bool sort = false;
    while (!sort)
    {
        sort = true;
        for (int i = 1; i < lst.cont; i++)
        {
            node<T>* node1 = get_node(lst, i - 1);
            node<T>* node2 = get_node(lst, i);
            if (sort_function(node1->data, node2->data) > 0)
            {
                sort = false;
                swap_nodes(lst, i, i - 1);
            }
        }
    }
}

//Função quicksort responsável por organizar a lista em ordem de ID;
template <typename T>
void quicksort(list<T>& lst, int left, int right)
{
    if (left < right)
    {
        int i = left;
        int j = right;
        int pivotIndex = left + (right - left) / 2;
        node<T>* pivotNode = get_node(lst, pivotIndex);
        while (i <= j)
        {
            while (get_node(lst, i)->data.id < pivotNode->data.id)
                i++;
            while (get_node(lst, j)->data.id > pivotNode->data.id)
                j--;
            if (i <= j)
            {
                swap_nodes(lst, i, j);
                i++;
                j--;
            }
        }
        if (left < j)
            quicksort(lst, left, j);
        if (i < right)
            quicksort(lst, i, right);
    }
}

//Função responsável pela busca binária, retornando a posição do nó encontrado
template <typename T>
int binary_search(list<T>& lst, int left, int right, int target, int(*compare_function)(T, int))
{
    if (left <= right)
    {
        int mid = left + (right - left) / 2;
        node<T>* midNode = get_node(lst, mid);
        int comparison = compare_function(midNode->data, target);

        if (comparison == 0)
            return mid;
        else if (comparison < 0)
            return binary_search(lst, mid + 1, right, target, compare_function);
        else
            return binary_search(lst, left, mid - 1, target, compare_function);
    }

    return -1;
}

//Função responsável pela busca sequêncial, retornando a posição do nó encontrado
template <typename T>
int sequential_search(list<T>& lst, const string& target)
{
    node<T>* currentNode = lst.begin;
    int position = 0;
    while (currentNode != nullptr)
    {
        if (currentNode->data.name == target)
            return position;
        
        currentNode = currentNode->next;
        position++;
    }
    
    return -1;
}

// Função para editar um atributo específico de um nó
template <typename T>
void edit_node_data(list<T>& lst, int id, int(*compare_function)(T, int))
{
    node<T>* node_position = get_node(lst, binary_search(lst, 0, lst.cont - 1, id, compare_function));
    if (node_position != nullptr)
    {
        int attribute;
        string new_value;
        cout << "Insira o atributo que você deseja mudar:" << endl << ">";
        cin >> attribute;
        cout << "Insira o novo valor:" << endl << ">";
        cin >> new_value;
        switch (attribute)
        {
            case 1: // Editar o atributo 'id'
                node_position->data.id = stoi(new_value);
                break;
            case 2: // Editar o atributo 'name'
                node_position->data.name = new_value;
                break;
            case 3: // Editar o atributo 'pokemon_type1'
                node_position->data.pokemon_type1 = new_value;
                break;
            case 4: // Editar o atributo 'pokemon_type2'
                node_position->data.pokemon_type2 = new_value;
                break;
            default:
                cout << "Atributo inválido!" << endl;
                break;
        }
    }
    else
        cout << "Pokémon não encontrado!" << endl << endl;
}
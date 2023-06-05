#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct pokemon
{
    int id;
    string name;
    string pokemon_type1;
    string pokemon_type2;
};

void presentationInitial()
{
    cout << " _______                                     "<< endl;
    cout << "|   ___  \\                                //"<< endl;
    cout << "|  |   |  |   ______      __     ___    _______    _______       _______   ___      ___" << endl;
    cout << "|  |___|  |  /  __  \\    |  |   /  /   |   ____|  |   ___  \\    |   ____|  \\  \\    /  /" << endl;
    cout << "|   _____/  |  |  |  |   |  |__/  /    |  |__     |  |   |  \\   |  |__      \\  \\__/  / " << endl;
    cout << "|  |        |  |  |  |   |  |__  |     |   __|    |  |   |  |   |   __|      |  __  | "<< endl;
    cout << "|  |        |  |__|  |   |  |  \\  \\    |  |____   |  |___|  /   |  |____    /  /  \\  \\ "<< endl;
    cout << "|__|         \\______/    |__|   \\__\\   |_______|  |________/    |_______|  /__/    \\__\\"<< endl;
    cout <<"\nversion: 1.0\n"<< endl;
    cout << "Projeto de Estrutura de Dados I | UERJ-ZO\n" << endl;
}

//Função responsável pela formatação da impressão dos pokemons
void print_pokemons(pokemon p)
{
    cout << "*-----------------------------------------------------*" << endl;
    cout << "ID: " << p.id << endl;
    cout << "NAME: " << p.name << endl;
    if (p.pokemon_type2 != "NULL")
    {
        cout << "TYPE I: " << p.pokemon_type1 << endl;
        cout << "TYPE II: " << p.pokemon_type2 << endl;
    }
    else
        cout << "TYPE: " << p.pokemon_type1 << endl;
    cout << "*-----------------------------------------------------*" << endl;
}

//Função responsável por comparar 2 strings
int compare_pokemons(pokemon p1, pokemon p2)
{
    return p1.name.compare(p2.name);
}

//Função responsável por comparar dois ids
template <typename T>
int compare_by_id(T element, int target)
{
    if (element.id < target)
        return -1;
    else if (element.id > target)
        return 1;
    else
        return 0;
}

//Função responsável por carregar os itens do arquivo.csv para a lista
template <typename T>
void read_database(list<T>& lst)
{
    fstream data;
    data.open("data/database.csv", ios::in);
    if (data.is_open())
        cout << "Arquivo aberto com sucesso!" << endl << endl;
    else
        cout << "Erro ao abrir o arquivo!" << endl << endl;

    string line;
    while (getline(data, line))
    {
        stringstream ss(line);
        string id, name, type1, type2;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type1, ',');
        getline(ss, type2, ',');

        append(lst, {stoi(id), name, type1, type2});
    }
    data.close();
}

//Função responsável por salvar no arquivo .csv
template <typename T>
void save_on_database(list<T>& lst)
{
    fstream data;
    data.open("data/database.csv", ios::out);
    if (!data.is_open())
        cout << "Erro ao salvar o arquivo!" << endl << endl;
    else
    {
        node<T>* aux = lst.begin;
        for (int i = 0; i < lst.cont; i++)
        {
            string id = to_string(aux->data.id);
            string name = (aux->data).name;
            string type1 = (aux->data).pokemon_type1;
            string type2 = (aux->data).pokemon_type2;

            aux = aux->next;

            data << id << ",";
            data << name << ",";
            data << type1 << ",";
            data << type2 << ",\n";
        }
        cout << "Os Pokémons foram salvos com sucesso!" << endl << endl;
    }
    data.close();
};
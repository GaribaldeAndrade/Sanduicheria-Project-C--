#include<iostream>
#include<fstream>
using namespace std;

class shopping //criação classe
{
private: //variaveis da classe
	int pcode;
	float price;
	float dis;
	string pname;

public: //funçoes
	void menu();
	void administrator();
	void buyer();
	void add();
	void edit();
	void rem();
	void list();
	void receipt();
};

void shopping::menu()
{
    int choice;
    string email;
    string password;

    while (true) {
        cout << "\t\t\t\t_________________________________\n";
        cout << "\t\t\t\t                                 \n";
        cout << "\t\t\t\t      SuperMarket Main Menu      \n";
        cout << "\t\t\t\t                                 \n";
        cout << "\t\t\t\t_________________________________\n";
        cout << "\t\t\t\t                                 \n";
        cout << "\t\t\t\t|    1) Adiministrador    |\n";
        cout << "\t\t\t\t|                         |\n";
        cout << "\t\t\t\t|    2) Cliente           |\n";
        cout << "\t\t\t\t|                         |\n";
        cout << "\t\t\t\t|    3) Sair              |\n";
        cout << "\t\t\t\t|                         |\n";
        cout << "\n\t\t\t Por Favor Selecione!";
        cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1:
            cout << "\t\t\t Login \n";
            cout << "\t\t\t Email:\t";
            cin >> email;
            cout << "\t\t\t Password:\t";
            cin >> password;

            system("cls");

            if (email == "admin" && password == "admin")
            {
                administrator();
            }
            else
            {
                cout << "Email/Senha Incorretos";
            }
            break;

        case 2:
            buyer();
            break;

        case 3:
            exit(0);
            break;

        default:
            cout << "Por favor selecione alguma opcao\n";
        }
    }
}


//Tela do Administrador
void shopping::administrator() {
  while (true) {
    int choice;
    cout << "\n\n\n\t\t\t Menu do Administrador";
    cout << "\n\t\t\t|_____1) Adicionar o produto_____|";
    cout << "\n\t\t\t|                                |";
    cout << "\n\t\t\t|_____2) Modificar o Produto_____|";
    cout << "\n\t\t\t|                                |";
    cout << "\n\t\t\t|_____3) Deletar o Produto_______|";
    cout << "\n\t\t\t|                                |";
    cout << "\n\t\t\t|_____4) Voltar para o Menu______|";

    cout << "\n\n\t Por favor adicione sua escolha ";
    cin >> choice;

    system("cls");

    switch (choice) {
    case 1:
      add();
      break;

    case 2:
      edit();
      break;

    case 3:
      rem();
      break;

    case 4:
      return;

    default:
      cout << "Escolha invalida!";
    }
  }
}


//TELA DO CLIENTE
void shopping::buyer()
{
    int choice;

    while (true) {
        cout << "\t\t\t  Tela Cliente \n";
        cout << "\t\t\t-----------------  \n";
        cout << "                         \n";
        cout << "\t\t\t1) Comprar Produto \n";
        cout << "                         \n";
        cout << "\t\t\t2) Voltar          \n";
        cout << "\t\t\t Adicione sua escolha : ";

        cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1:
            receipt();
            break;

        case 2:
            menu();
            return;

        default:
            cout << "Escolha inv�lida\n";
        }
    }
}


void shopping::add()
{
	fstream data;
	int c;
	int token = 0;
	float p;
	float d;
	string n;

	do {
		cout << "\n\n\t\t\t Adicione novo produto";
		cout << "\n\n\t Codigo do Produto ";
		cin >> pcode;
		cout << "\n\n\t Nome do Produto ";
		cin >> pname;
		cout << "\n\n\t Preco do produto";
		cin >> price;
		cout << "\n\n\t Disconto do produto";
		cin >> dis;

		system("cls");

		data.open("database.txt", ios::in);

		if (!data)
		{
			data.open("database.txt", ios::app | ios::out);
			data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
			data.close();
		}
		else
		{
			data >> c >> n >> p >> d;

			while (!data.eof())
			{
				if (c == pcode)
				{
					token++;
				}
				data >> c >> n >> p >> d;
			}
			data.close();

			if (token == 1)
			{
				cout << "\n\n\t\t Registro Invalido";
			}
			else {
				data.open("database.txt", ios::app | ios::out);
				data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
				data.close();
			}
		}
	} while (token == 1);
}


//TELA DE EDITAR PRODUTO NO ADMIN
void shopping::edit()
{
	fstream data, data1;
	int pkey;
	int token = 0;
	int c;
	float p;
	float d;
	string n;

	cout << "\n\t\t\t Editar o Registro";
	cout << "\n\t\t\t Codigo do Produto: ";
	cin >> pkey;

	system("cls");

	data.open("database.txt", ios::in);
	if (!data)
	{
		cout << "\n\nArquivo nao existe! ";
	}
	else {

		data1.open("database1.txt", ios::app | ios::out);

		data >> pcode >> pname >> price >> dis;
		while (!data.eof())
		{
			if (pkey == pcode)
			{
				cout << "\n\t\t Novo codigo de produto: ";
				cin >> c;
				cout << "\n\t\t Nome do produto: ";
				cin >> n;
				cout << "\n\t\t Preco do produto: ";
				cin >> p;
				cout << "\n\t\t Desconto :";
				cin >> d;

				system("cls");

				data1 << " " << c << " " << n << " " << p << " " << d << "\n";
				cout << "\n\n\t\t Registro Editado ";
				token++;
			}
			else
			{
				data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";

			}
			data >> pcode >> pname >> price >> dis;
		}
		data.close();
		data1.close();

		remove("database.txt");
		rename("database1.txt", "database.txt");

		if (token == 0)
		{
			cout << "\n\n Registro nao existe! ";
		}
	}
}

//TELA DE REMOVER PRODUTO NO ADMIN
void shopping::rem()
{
	fstream data, data1;
	int pkey;
	int token = 0;
	cout << "\n\n\t Delete produto";
	cout << "\n\n\t Codigo do produto: ";
	cin >> pkey;

	system("cls");

	data.open("database.txt", ios::in);
	if (!data)
	{
		cout << "Arquivo nao existe";
	}
	else
	{
		data1.open("database1.txt", ios::app | ios::out);
		data >> pcode >> pname >> price >> dis;
		while (!data.eof())
		{
			if (pcode == pkey)
			{
				cout << "\n\n\t Produto deletado com sucesso";
				token++;
			}
			else
			{
				data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
			}
			data >> pcode >> pname >> price >> dis;
		}
		data.close();
		data1.close();
		remove("database.txt");
		rename("database1.txt", "database.txt");

		if (token == 0)
		{
			cout << "\n\n Registro nao econtrado";
		}
	}
}

//Mostra os produtos existentes no database
void shopping::list()
{
	fstream data;
	data.open("database.txt", ios::in);
	cout << "\n\n|______________________________________________________\n";
	cout << "ProNo\t\tNome\t\tPreco\n";
	cout << "\n\n|______________________________________________________\n";
	data >> pcode >> pname >> price >> dis;
	while (!data.eof())
	{
		cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
		data >> pcode >> pname >> price >> dis;
	}
	data.close();
}

//Aba de compra de produtos
void shopping::receipt()
{
	fstream data;

	int arrc[100];
	int arrq[100];
	char choice;
	int c = 0;
	float amount = 0;
	float dis = 0;
	float total = 0;

	cout << "\n\n\t\t\t\t Recebido ";
	data.open("database.txt", ios::in);
	if (!data)
	{
		cout << "\n\n Banco de dados vazio";
	}

	else
	{
		data.close();

		list();
		cout << "\n__________________________________\n";
		cout << "\n           Faca o Pedido          \n";
		cout << "\n__________________________________\n";
		bool continuar = true;
		while (continuar)
		{
			cout << "\n Adicione o coigo do produto: ";
			cin >> arrc[c];
			cout << " Adicione a quantidade: ";
			cin >> arrq[c];
			for (int i = 0; i < c; i++)
			{
				if (arrc[c] == arrc[i])
				{
					cout << "\n\n Codigo de produto repetido!\n";
					cout << "\n\n Tente novamente";
					break;
				}
			}
			c++;
			cout << "\n Deseja comprar outro produto? [Sim]=y [Nao]=n";
			cin >> choice;
			if (choice != 'y')
			{
				continuar = false;
			}
		}
		system("cls");
		
		cout << "\n\n\t\t\t________________Recebido________________\n";
		cout << "\nNumero\t Nome\t Quantidade\t Preco\t Montante\t Montante com desconto\n";

		for (int i = 0; i < c; i++)
		{
			data.open("database.txt", ios::in);
			data >> pcode >> pname >> price >> dis;
			while (!data.eof())
			{
				if (pcode == arrc[i])
				{
					amount = price * arrq[i];
					dis = amount - (amount * dis / 100);
					total = total + dis;
					cout << "\n" << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t\t" << dis;
				}
				data >> pcode >> pname >> price >> dis;
			}
		}
		data.close();
	}
	cout << "\n\n________________________________________________";
	cout << "\n Total do Montante: " << total;
}

int main()
{
	shopping s;
	s.menu();
}

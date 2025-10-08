#include <iostream>
#include <unistd.h>
#include <fstream>
#include <limits>
using namespace std;

class Producto {
    private:
        static const int MAX_ING = 50;
        static const int MAX_EXT = 50;
        string nombre;
        float costo;
        float precio;
        float ganancia;
        string NomIng[MAX_ING];
        float PreIng[MAX_ING];
        float Gramos[MAX_ING];
        int nIng;
        int nExt;
        string NomExt[MAX_EXT];
        float PreExt[MAX_EXT];
        int UniTotal[MAX_EXT];
        int UniProduc[MAX_EXT];
        
    public:
        Producto();
        void MostrarInformacion();
        void CambiarNombre();
        void ConfigurarCosto();
        void CambiarPrecio();
        void getnombre();
		void Guardar(ofstream &out);
		void Cargar(ifstream &in);
};


Producto::Producto () {
    nombre = "Producto";
    costo = 0;
    precio = 0;
    ganancia = precio - costo;
    nIng = 0;
    for (int i = 0; i < MAX_ING; ++i) {
        PreIng[i] = 0;
        Gramos[i] = 0; 
    }
    nExt = 0;
    for (int i = 0; i < MAX_EXT; ++i) {
        PreExt[i] = 0;
        UniTotal[i] = 0; 
        UniProduc[i] = 0;
    }
}

void Producto::MostrarInformacion() {
    cout << "Nombre: " << nombre << endl;
    cout << "Costo: " << costo << "$" << endl;
    cout << "Precio: " << precio << "$" << endl;
    cout << "Ganacia por venta: " << ganancia << "$" << endl;
}

void Producto::CambiarNombre(){
    cout << "Nombre actual: " << nombre << endl;
    cout << "Nombre nuevo: ";
    cin.ignore();
    getline(cin,nombre);

}

void Producto::ConfigurarCosto() {
    int opcion;

    do {
        system("clear");
        cout << "=============|INGREDIENTES|==============" << endl;
        for (int i = 0; i < nIng; i++) {
            cout << "-Nombre: " << NomIng[i] << endl;
            cout << "-Precio: " << PreIng[i] << "$" << endl;
            cout << "-Gramos: " << Gramos[i] << "g" << endl;
            cout << endl;
        }
        cout << "================|EXTRAS|=================" << endl;
        for (int i = 0; i < nExt; i++) {
            cout << "-Nombre: " << NomExt[i] << endl;
            cout << "-Precio de unidad total: " << PreExt[i] << "$" << endl;
            cout << "Unidades totales: " << UniTotal[i] << " unidades." << endl;
            cout << "Unidades por producto: " << UniProduc[i] << endl;
            cout << endl;
        }
        cout << "==================================" << endl;
        cout << "1. Agregar ingrediente" << endl;
        cout << "2. Eliminar ingrediente" << endl;
        cout << "3. Agregar extra" << endl;
        cout << "4. Eliminar extra" << endl;
        cout << "5. Volver" << endl;
        cin >> opcion;

        if (opcion == 1) {
            float NuevoCosto = 0;
            system("clear");
            cout << "Nombre del ingrediente: ";
            cin.ignore();
            getline(cin,NomIng[nIng]);
            cout << "Precio por kilo (1000g): ";
            cin >> PreIng[nIng];
            cout << "Gramos por producto: ";
            cin >> Gramos[nIng];

            NuevoCosto = (PreIng[nIng]/1000)*Gramos[nIng];
            costo += NuevoCosto;
            ganancia = precio - costo;
            nIng++;
            cout << "Ingrediente Agregado." << endl;
            sleep(1);
        } else if (opcion == 2) {
            if (nIng > 0) {
                nIng--;
                float descontar = ((PreIng[nIng] / 1000) * Gramos[nIng]);
                costo -= descontar;
                ganancia = precio - costo;
            } else {
                cout << "No hay ingredientes para eliminar" << endl;
                sleep(1);
            }
            
        } else if (opcion == 3) {
            float NuevoCosto = 0;
            system ("clear");
            cout << "Nombre del extra: ";
            cin.ignore();
            getline(cin,NomExt[nExt]);
            cout << "Precio de las unidades totales: ";
            cin >> PreExt[nExt];
            cout << "Unidades totales: ";
            cin >> UniTotal[nExt];
            cout << "Unidades por producto: ";
            cin >> UniProduc[nExt];
            
            NuevoCosto = (PreExt[nExt]/UniTotal[nExt])*UniProduc[nExt];
            costo += NuevoCosto;
            ganancia = precio - costo;
            nExt++;
            cout << "Extra Agregado." << endl;
            sleep(1);
        
        } else if (opcion == 4) {
            if (nExt > 0) {
                nExt--;
                float descontar = (PreExt[nExt]/UniTotal[nExt])*UniProduc[nExt];
                costo -= descontar;
                ganancia = precio - costo;
            } else {
                cout << "No hay Extras para eliminar" << endl;
                sleep(1);
            }


        } else if (opcion < 1 or opcion > 5) {

            cout << "Opcion Invalida" << endl;
            sleep(1);
        }


    } while (opcion != 5);
}

void Producto::CambiarPrecio(){
    cout << "Precio actual: " << precio << endl;
    cout << "Precio nuevo: ";
    cin.ignore();
    cin >> precio;
    ganancia = precio - costo;
}

void Producto::getnombre() {
    cout << nombre;
}

void Producto::Guardar(ofstream &out) {
		out << nombre << "\n";
		out << costo << " " << precio << " " << ganancia << "\n";

		out << nIng << "\n";
		for (int i = 0; i < nIng; i++) {
				out << NomIng[i] << "\n";
				out << PreIng[i] << " " << Gramos[i] << "\n";
		}

		out << nExt << "\n";
		for (int i = 0; i < nExt; i++) {
				out << NomExt[i] << "\n";
				out << PreExt[i] << " " << UniTotal[i] << " " << UniProduc[i] << "\n";
		}
}

string getHomeDir() {
		const char* home = getenv("HOME");
		return (home ? string(home) : ".");
}

string savePATH = getHomeDir() + "/.config/Gestor_De_Costos/save.txt";

void Producto::Cargar(ifstream &in) {
		getline(in, nombre);
		in >> costo >> precio >> ganancia;
		in.ignore(numeric_limits<streamsize>::max(), '\n');

		in >> nIng;
		in.ignore(numeric_limits<streamsize>::max(), '\n');
	
		for (int i = 0; i < nIng; i++) {
				getline(in, NomIng[i]);
				in >> PreIng[i] >> Gramos[i];
				in.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		in >> nExt;
		in.ignore(numeric_limits<streamsize>::max(), '\n');

		for (int i = 0; i < nExt; i++) {
				getline(in, NomExt[i]);
				in >> PreExt[i] >> UniTotal[i] >> UniProduc[i];
				in.ignore(numeric_limits<streamsize>::max(), '\n');
		}
}

void GuardarTodo(Producto P1[50], int nProd, const string &filename) {
		ofstream out(filename);
		if (!out) {
				cout << "Error al abrir el archivo de guardado.\n";
				return;
		}

		out << nProd << "\n";

		for (int i = 0; i < nProd; i++) {
				P1[i].Guardar(out);
		}
		out.close();
}

void CargarTodo(Producto P1[50], int &nProd, const string &filename) {
		ifstream in(filename);
		if (!in) {
				cout << "No se encontro archivo, iniciando con valores por defecto.\n";
				return;
		}

		in >> nProd;
		in.ignore(numeric_limits<streamsize>::max(), '\n');
		  
		for (int i = 0; i < nProd; i++) {
				P1[i].Cargar(in);
		}
		in.close();
}

void AgregarProducto(Producto P1[50], int &nProd) {
		if ( nProd < 50 ) {
				P1[nProd] = Producto();
				nProd++;
				cout << "Producto agregado correctamente" << endl;
		} else {
				cout << "Solo se pueden agregar 50 productos" << endl;
		}
}

void EliminarProducto(Producto P1[50], int &nProd) {
		int EliProd = 0;

		if ( nProd == 0 ) {
				cout << "No hay productos para eliminar" << endl;
				return;
		} else { 

				cout << "Que producto desea eliminar?: ";
				cin >> EliProd;
				int indice = EliProd - 1;
				int Iteraciones = nProd - EliProd;

				for ( int i = 0; i < Iteraciones; i++ ) {
						indice += i;
						P1[indice] = P1[indice + 1];
				}
				nProd--;
		}
}

void Menu(Producto P1[], int &nProd) {
    int opcion;
    do {
        system("clear");
        cout << "|INICIO|" << endl;
		
        for (int i = 0; i < nProd; i++) {
            cout << i + 1 << ". ";
            P1[i].getnombre();
            cout << endl;
        }
		cout << "-----------------------------------" << endl;
		cout << nProd + 1 << ". Agregar un producto." << endl;
		cout << nProd + 2 << ". Eliminar un producto." << endl;
        cout << "Selecciona el producto que desea verificar o coloca 0 para salir: ";
        cin >> opcion;
        int index = opcion - 1;
        if (opcion > 0 and opcion <= nProd) {
            int accion;
            do {
                system("clear");
                P1[index].MostrarInformacion();
                cout << "================================" << endl;
                cout << "1. Cambiar Nombre" << endl;
                cout << "2. Configurar Costo" << endl;
                cout << "3. Cambiar Precio" << endl;
                cout << "4. Volver" << endl;
                cin >> accion;

                if (accion == 1) {
                    system("clear");
                    P1[index].CambiarNombre();
                } else if (accion == 2) {
                    system("clear");
                    P1[index].ConfigurarCosto();
                } else if (accion == 3) {
                    system("clear");
                    P1[index].CambiarPrecio();
                } else if (accion == 4) {
                    system("clear");
                } else if (accion < 1 or accion > 4) {
                    cout << "Accion invalida" << endl;
                    sleep(1);
                }
            } while (accion != 4);
		} else if ( opcion == nProd + 1) {
				AgregarProducto(P1, nProd);
				sleep(1);
		} else if ( opcion == nProd + 2) {
				EliminarProducto(P1, nProd);
				sleep(1);
        } else if (opcion == 0) {
            cout << "Saliendo del programa" << endl;
        
        } else {
            cout << "Opcion Invalida." << endl;
            sleep(1);
		}
        
    } while (opcion != 0);
}


int main() {
    Producto P1[50];
	int nProd = 1;

	CargarTodo(P1, nProd, savePATH);

    system("clear");
    Menu(P1, nProd);

	GuardarTodo(P1, nProd, savePATH);
    return 0;
}

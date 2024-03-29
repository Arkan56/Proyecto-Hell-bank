#include <iostream>
#include <string>

using namespace std;

struct usuario_empleado //estructura para el usuario de los empleados del banco
{
  string nombre;
  string contrasena;
};

struct Cuenta_ahorro
{
    double saldo;
    double interes;
    Cuenta_ahorro *next;
};

struct Cuenta_corriente
{
    double saldo;
    int  plazo;
    Cuenta_corriente *next;
};

struct Credito
{
    double saldo;
    double interes;
    int plazo;
    Credito *next;
};

struct CDT
{
    double saldo;
    double interes;
    int plazo;
    CDT *next;
};

struct Cliente
{
    string nombre;
    string apellido;
    string direccion;
    string telefono;
    double ingresos;
    double deudas;
    string nUsuario;
    string contrasena;
    Cuenta_ahorro *ca;
    Cuenta_corriente *cc;
    Credito *c;
    CDT *cdt;
};


void menuOperacion(Cliente *&clientes, int &tam);
void agregarCliente(Cliente *&clientes, int &tam);
void mostrarClientes(Cliente *&clientes, int &tam);
bool modificarClientes(Cliente *&clientes, int tam, string correo);
bool eliminarCliente(Cliente *&clientes, int &tam, string correo);
bool realizarPrestamo(Cliente *&clientes, int &tam, string correo);

int main()
{
    Cliente *clientes = new Cliente[1];
    int tam = 0;
    menuOperacion(clientes, tam);
    return 0;
}

void menuOperacion(Cliente *&clientes, int &tam)
{
    int op;
    string correo;
    do
    {
        cout << "----Menu----" << endl;
        cout << "1. Agregar cliente" << endl;
        cout << "2. Consultar clientes" << endl;
        cout << "3. Modificar cliente" << endl;
        cout << "4. Eliminar cliente" << endl;
        cout << "5. Prestamo a cliente" << endl;
        cout << "6. Hacer corte de los productos" << endl;
        cout << "7. Salir" << endl;
        switch(op)
        {
            case 1:
            agregarCliente(clientes, tam);
            break;
            case 2:
            mostrarClientes(clientes, tam);
            break;
            case 3:
            cout << "Ingrese el correo del cliente a modificar" << endl;
            getline(cin, correo);
            modificarClientes(clientes, tam, correo);
            break;
            case 4:
            cout << "Ingrese el correo del cliente a eliminar" << endl;
            getline(cin, correo);
            eliminarCliente(clientes, tam, correo);
            break;
            case 5:
            cout << "Ingrese el correo del cliente a realizar el prestamo" << endl;
            getline(cin, correo);
            realizarPrestamo(clientes,tam,correo);
            break;
            case 6:
            cout << "Opcion no realizada aun" << endl;
            break;
            case 7:
            cout << "Saliendo..." << endl; 
            break;
            default:
            cout << "Opcion invalida" << endl;
        }
    }while(op != 7);
}

void agregarCliente(Cliente *&clientes, int &tam)
{
    Cliente cliente;
    string ingresos, deudas;
    cin.ignore();
    cout << "Ingrese el nombre de el cliente:" << endl;
    getline(cin, cliente.nombre);
    cout << "Ingrese el apellido de el cliente:" << endl;
    getline(cin, cliente.apellido);
    cout << "Ingrese la direccion de el cliente:" << endl;
    getline(cin, cliente.direccion);
    cout << "Ingrese el numero de telefono de el cliente:" << endl;
    getline(cin, cliente.telefono);
    cout << "Ingrese los ingresos mensuales de el cliente:" << endl;
    getline(cin, ingresos);
    cout << "Ingrese el valor de las deudas actuales de el cliente:" << endl;
    getline(cin, deudas);

    cliente.ingresos = stod(ingresos);
    cliente.deudas = stod(deudas);

    cout << "Ingrese el correo de el cliente:" << endl;
    getline(cin, cliente.nUsuario);
    cout << "Ingrese la contrasena de el cliente:" << endl;
    getline(cin, cliente.contrasena);

    cliente.ca = nullptr;
    cliente.cc = nullptr;
    cliente.c = nullptr;
    cliente.cdt = nullptr;

    tam++;
    Cliente *nuevo = new Cliente[tam];

    for(int i = 0; i < tam-1; i++)
    {
        nuevo[i] = clientes[i];
    }

    nuevo[tam-1] = cliente; 
    delete[] clientes;

    clientes = nuevo;
}

void mostrarClientes(Cliente *&clientes, int &tam)
{
    Cuenta_ahorro cao;
    for(int i = 0; i < tam; i++)
    {
        cout << "Cliente " << i+1 << ":" << endl;
        cout << "Nombre: " << clientes[i].nombre << endl;
        cout << "Apellido: " << clientes[i].apellido << endl;
        cout << "Dirección: " << clientes[i].direccion << endl;
        cout << "Teléfono: " << clientes[i].telefono << endl;
        cout << "Ingresos: " << clientes[i].ingresos << endl;
        cout << "Deudas: " << clientes[i].deudas << endl;
        cout << "Nombre de usuario: " << clientes[i].nUsuario << endl;
        cout << "Contraseña: " << clientes[i].contrasena << endl;
        // Imprimir detalles de cuentas de ahorro si existen
        if (clientes[i].ca != nullptr) {
            Cuenta_ahorro *temp = clientes[i].ca;
            do {
                cout << "Saldo de cuenta de ahorro: " << temp->saldo << endl;
                cout << "Interés de cuenta de ahorro: " << temp->interes << endl;
                temp = temp->next;
            } while (temp != clientes[i].ca);
        }

        // Imprimir detalles de cuentas corrientes si existen
        if (clientes[i].cc != nullptr) {
            Cuenta_corriente *temp = clientes[i].cc;
            do {
                cout << "Saldo de cuenta corriente: " << temp->saldo << endl;
                cout << "Plazo de cuenta corriente: " << temp->plazo << endl;
                temp = temp->next;
            } while (temp != clientes[i].cc);
        }

        // Imprimir detalles de créditos si existen
        if (clientes[i].c != nullptr) {
            Credito *temp = clientes[i].c;
            do {
                cout << "Saldo de crédito: " << temp->saldo << endl;
                cout << "Interés de crédito: " << temp->interes << endl;
                cout << "Plazo de crédito: " << temp->plazo << endl;
                temp = temp->next;
            } while (temp != clientes[i].c);
        }

        // Imprimir detalles de CDTs si existen
        if (clientes[i].cdt != nullptr) {
            CDT *temp = clientes[i].cdt;
            do {
                cout << "Saldo de CDT: " << temp->saldo << endl;
                cout << "Interés de CDT: " << temp->interes << endl;
                cout << "Plazo de CDT: " << temp->plazo << endl;
                temp = temp->next;
            } while (temp != clientes[i].cdt);
        }
        cout << endl;
    }
}

bool modificarClientes(Cliente *&clientes, int tam, string correo)
{
    for (int i = 0; i < tam; ++i) {
        if (clientes[i].nUsuario == correo) {
            cout << "Introduce el nuevo nombre del cliente: ";
            getline(cin, clientes[i].nombre);
            cout << "Introduce el nuevo apellido del cliente: ";
            getline(cin, clientes[i].apellido);
            cout << "Introduce la nueva dirección del cliente: ";
            getline(cin, clientes[i].direccion);
            cout << "Introduce el nuevo teléfono del cliente: ";
            getline(cin, clientes[i].telefono);
            cout << "Introduce los nuevos ingresos del cliente: ";
            cin >> clientes[i].ingresos;
            cout << "Introduce las nuevas deudas del cliente: ";
            cin >> clientes[i].deudas;

            // Modificar los datos de la cuenta de ahorro si existe
            if (clientes[i].ca != nullptr) {
                Cuenta_ahorro *temp = clientes[i].ca;
                do {
                    cout << "Introduce el nuevo saldo de la cuenta de ahorro: ";
                    string saldoStr;
                    getline(cin, saldoStr);
                    temp->saldo = stod(saldoStr);
                    cout << "Introduce el nuevo interés de la cuenta de ahorro: ";
                    string interesStr;
                    getline(cin, interesStr);
                    temp->interes = stod(interesStr);
                    temp = temp->next;
                } while (temp != clientes[i].ca);
            }

            // Modificar los datos de la cuenta corriente si existe
            if (clientes[i].cc != nullptr) {
                Cuenta_corriente *temp = clientes[i].cc;
                do {
                    cout << "Introduce el nuevo saldo de la cuenta corriente: ";
                    string saldoStr;
                    getline(cin, saldoStr);
                    temp->saldo = stod(saldoStr);
                    cout << "Introduce el nuevo plazo de la cuenta corriente: ";
                    string plazoStr;
                    getline(cin, plazoStr);
                    temp->plazo = stod(plazoStr);
                    temp = temp->next;
                } while (temp != clientes[i].cc);
            }

            // Modificar los datos del crédito si existe
            if (clientes[i].c != nullptr) {
                Credito *temp = clientes[i].c;
                do {
                    cout << "Introduce el nuevo saldo del crédito: ";
                    string saldoStr;
                    getline(cin, saldoStr);
                    temp->saldo = stod(saldoStr);
                    cout << "Introduce el nuevo interés del crédito: ";
                    string interesStr;
                    getline(cin, interesStr);
                    temp->interes = stod(interesStr);
                    cout << "Introduce el nuevo plazo del crédito: ";
                    string plazoStr;
                    getline(cin, plazoStr);
                    temp->plazo = stod(plazoStr);
                    temp = temp->next;
                } while (temp != clientes[i].c);
            }

            // Modificar los datos del CDT si existe
            if (clientes[i].cdt != nullptr) {
                CDT *temp = clientes[i].cdt;
                do {
                    cout << "Introduce el nuevo saldo del CDT: ";
                    string saldoStr;
                    getline(cin, saldoStr);
                    temp->saldo = stod(saldoStr);
                    cout << "Introduce el nuevo interés del CDT: ";
                    string interesStr;
                    getline(cin, interesStr);
                    temp->interes = stod(interesStr);
                    cout << "Introduce el nuevo plazo del CDT: ";
                    string plazoStr;
                    getline(cin, plazoStr);
                    temp->plazo = stod(plazoStr);
                    temp = temp->next;
                } while (temp != clientes[i].cdt);
            }

            return true; // Cliente encontrado y modificado
        }
    }
    return false; // Cliente no encontrado
}

bool eliminarCliente(Cliente *&clientes, int &tam, string correo)
{
    for (int i = 0; i < tam; ++i) {
        if (clientes[i].nUsuario == correo) {
            // Mover los clientes restantes una posición hacia atrás
            for (int j = i; j < tam - 1; ++j) {
                clientes[j] = clientes[j + 1];
            }
            
            // Redimensionar el arreglo
            Cliente* temp = new Cliente[tam - 1];
            for (int j = 0; j < tam - 1; ++j) {
                temp[j] = clientes[j];
            }
            delete[] clientes;
            clientes = temp;

            tam--; // Decrementar el tamaño del arreglo
            return true; // Cliente encontrado y eliminado
        }
    }
    return false; // Cliente no encontrado
}

bool realizarPrestamo(Cliente *&clientes, int &tam, string correo)
{
    for(int i = 0; i < tam; i++)
    {
        if(clientes[i].nUsuario == correo) //Buscar el cliente 
        {
            Credito *nuevo = new Credito; //Pedir memoria para el nuevo prestamo
            cout << "Ingrese el Saldo del credito:" << endl;
            cin >> nuevo->saldo;
            cout << "Ingrese el procentaje de Interes del credito:" << endl;
            cin >> nuevo->interes;
            cout << "Ingrese el Plazo del credito:" << endl;
            cin >> nuevo->plazo;
            Credito *temp = clientes[i].c;
            do
            {
                temp = temp->next;
            } while (temp != clientes[i].c); //Encontrar el ultimo prestamo del cliente
            temp->next = nuevo; //apunta el siguiente prestamo del ultimo al nuevo prestamo creado
            nuevo->next = clientes[i].c; //Enlazar los prestamos nuevamente
            return true; //Se completo exitosamente el prestamo
        }
    }
    return false; //No se encontro a el cliente especificado   
}
 
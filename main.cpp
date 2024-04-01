#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct usuario_empleado //estructura para el usuario de los empleados del banco
{
  string nombre;
  string contrasena;
};

struct Movimiento
{
    string info;
    double monto;
    Movimiento *next;
};

struct Cuenta_ahorro
{
    double saldoInicial;
    double saldo;
    double interes;
    Cuenta_ahorro *next;
    Movimiento *mnext;
};

struct Cuenta_corriente
{
    double saldoInicial;
    double saldo;
    int  plazo;
    Cuenta_corriente *next;
    Movimiento *mnext;
};

struct Credito
{
    double saldoInicial;
    double saldo;
    double interes;
    int plazo;
    Credito *next;
    Movimiento *mnext;
};

struct CDT
{
    double saldoInicial;
    double saldo;
    double interes;
    int plazo;
    CDT *next;
    Movimiento *mnext;
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
void liquidarProductos(Cliente &cliente);
void generarExtractos(Cliente *clientes, int numClientes);

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
        cin >> op;
        switch(op)
        {
            case 1:
            agregarCliente(clientes, tam);
            break;
            case 2:
            mostrarClientes(clientes, tam);
            break;
            case 3:
            cin.ignore();
            cout << "Ingrese el correo del cliente a modificar" << endl;
            getline(cin, correo);
            if(!modificarClientes(clientes, tam, correo))
            {
                cout << "Operacion fallida" << endl;
            }
            break;
            case 4:
            cin.ignore();
            cout << "Ingrese el correo del cliente a eliminar" << endl;
            getline(cin, correo);
            if(!eliminarCliente(clientes, tam, correo))
            {
                cout << "Operacion fallida" << endl;
            }
            break;
            case 5:
            cin.ignore();
            cout << "Ingrese el correo del cliente a realizar el prestamo" << endl;
            getline(cin, correo);
            if(!realizarPrestamo(clientes,tam,correo))
            {
                cout << "Operacion fallida" << endl;
            }
            break;
            case 6:
            generarExtractos(clientes, tam);
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
            nuevo->saldoInicial = nuevo->saldo;
            cout << "Ingrese el procentaje de Interes del credito:" << endl;
            cin >> nuevo->interes;
            cout << "Ingrese el Plazo del credito:" << endl;
            cin >> nuevo->plazo;
            Credito *temp = clientes[i].c;
            if(temp == nullptr) //Operacion para cuando no hay ningun prestamos realizado
            {
                clientes[i].c = nuevo;
                nuevo->next = nuevo;
                nuevo->mnext = nullptr;
                return true;
            }
            do
            {
                temp = temp->next;
            } while (temp != clientes[i].c); //Encontrar el ultimo prestamo del cliente
            temp->next = nuevo; //apunta el siguiente prestamo del ultimo al nuevo prestamo creado
            nuevo->next = clientes[i].c; //Enlazar los prestamos nuevamente
            nuevo->mnext = nullptr;
            return true; //Se completo exitosamente el prestamo
        }
    }
    return false; //No se encontro a el cliente especificado   
}

void liquidarProductos(Cliente &cliente) {
    // Liquidar intereses de la cuenta de ahorro
    if (cliente.ca != nullptr) {
        Cuenta_ahorro* tempCuentaAhorro = cliente.ca;
        do {
            double interesesAhorro = tempCuentaAhorro->saldo * tempCuentaAhorro->interes;
            tempCuentaAhorro->saldo += interesesAhorro;
            tempCuentaAhorro = tempCuentaAhorro->next;
        } while (tempCuentaAhorro != cliente.ca);
    }

    // Liquidar intereses de los CDTs
    if (cliente.cdt != nullptr) {
        CDT* tempCDT = cliente.cdt;
        do {
            double interesesCDT = (tempCDT->saldo * tempCDT->interes) * tempCDT->plazo;
            tempCDT->saldo += interesesCDT;
            tempCDT = tempCDT->next;
        } while (tempCDT != cliente.cdt);
    }

    // Liquidar intereses de los préstamos
    if (cliente.c != nullptr) {
        Credito* tempCredito = cliente.c;
        do {
            double interesesPrestamo = (tempCredito->saldo * tempCredito->interes) * tempCredito->plazo;
            tempCredito->saldo += interesesPrestamo;
            tempCredito = tempCredito->next;
        } while (tempCredito != cliente.c);
    }
}

void generarExtractos(Cliente *clientes, int numClientes) {
    int cont = 0;
    for (int i = 0; i < numClientes; ++i) {
        Cliente cliente = clientes[i];
        cout << "Extractos para el cliente: " << cliente.nombre << " " << cliente.apellido << endl;
        cout << "---------------------------------------------" << endl;
        liquidarProductos(cliente);
        // Extracto de cuenta de ahorro
        Cuenta_ahorro *ca = cliente.ca;
        if (ca != nullptr) {
            Cuenta_ahorro *inicio = ca;
            cont = 1;
            do {
                cout << "Cuenta de Ahorro: " << cont << endl;
                cout << "Saldo inicial del periodo: $" << fixed << setprecision(2) << ca->saldoInicial << endl;
                cout << "Saldo final: $" << fixed << setprecision(2) << ca->saldo << endl;
                if(ca->mnext != nullptr)
                {
                    cout << "----------------------Movimientos-----------------------" << endl;
                    Movimiento *m = ca->mnext;
                    do{
                        cout << "Descripcion: " << m->info << endl;
                        cout << m->monto << endl;
                        m = m->next;
                        cout << endl;
                    }while(m != ca->mnext);
                }
                cout << "---------------------------------------------" << endl;
                ca = ca->next;
                cont++;
            } while (ca != inicio);
        }

        // Extracto de cuenta corriente
        Cuenta_corriente *cc = cliente.cc;
        if (cc != nullptr) {
            Cuenta_corriente *inicio = cc;
            cont = 1;
            do {
                cout << "Cuenta Corriente:" << cont << endl;
                cout << "Saldo inicial del periodo: $" << fixed << setprecision(2) << cc->saldoInicial << endl;
                cout << "Saldo final a pagar: $" << fixed << setprecision(2) << cc->saldo << endl;
                if(cc->mnext != nullptr)
                {
                    cout << "----------------------Movimientos-----------------------" << endl;
                    Movimiento *m = cc->mnext;
                    do{
                        cout << "Descripcion: " << m->info << endl;
                        cout << m->monto << endl;
                        m = m->next;
                        cout << endl;
                    }while(m != cc->mnext);
                }
                cout << "---------------------------------------------" << endl;
                cc = cc->next;
            } while (cc != inicio);
        }

        // Extracto de crédito
        Credito *c = cliente.c;
        if (c != nullptr) {
            Credito *inicio = c;
            cont = 1;
            do {
                cout << "Crédito:" << cont << endl;
                cout << "Saldo inicial del periodo: $" << fixed << setprecision(2) << c->saldoInicial << endl;
                if(c->mnext != nullptr)
                {
                    cout << "----------------------Movimientos-----------------------" << endl;
                    Movimiento *m = c->mnext;
                    do{
                        cout << "Descripcion: " << m->info << endl;
                        cout << m->monto << endl;
                        m = m->next;
                        cout << endl;
                    }while(m != c->mnext);
                }
                cout << "Saldo final a pagar: $" << fixed << setprecision(2) << c->saldo << endl;
                cout << "---------------------------------------------" << endl;
                c = c->next;
            } while (c != inicio);
        }

        // Extracto de CDT
        CDT *cdt = cliente.cdt;
        if (cdt != nullptr) {
            CDT *inicio = cdt;
            cont = 1;
            do {
                cout << "CDT:" << cont << endl;
                cout << "Saldo inicial del periodo: $" << fixed << setprecision(2) << cdt->saldoInicial << endl;
                if(cdt->mnext != nullptr)
                {
                    cout << "----------------------Movimientos-----------------------" << endl;
                    Movimiento *m = cdt->mnext;
                    do{
                        cout << "Descripcion: " << m->info << endl;
                        cout << m->monto << endl;
                        m = m->next;
                        cout << endl;
                    }while(m != cdt->mnext);
                }
                cout << "Saldo final: $" << fixed << setprecision(2) << cdt->saldo << endl;
                cout << "---------------------------------------------" << endl;
                cdt = cdt->next;
            } while (cdt != inicio);
        }

        cout << endl;
    }
}
#include <iostream> 
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <list>

using namespace std;

struct Cuenta {
    string titular;
    float saldo;
    string contrasena; 
    float credito; 
    float ahorro;
    float saldoAhorro;
    float intereses = .1;
};

// Función para depositar dinero
void depositar(Cuenta &cuenta, float monto, list<string>& operaciones){
    if (monto > 0) {
        cuenta.saldo += monto;
    } else {
        cout << "Monto inválido.\n";
    }
    operaciones.push_back("Deposito\n");
}

// Función para retirar dinero
bool retirar(Cuenta &cuenta, float monto, list<string>& operaciones) {
    if (monto > 0 && monto <= cuenta.saldo) {
        cuenta.saldo -= monto;
        cout << "Retiro exitoso- Nuevo saldo: $"<<cuenta.saldo << endl;
        return true;
    } else {
        cout << "Fondos insuficientes o monto invalido.\n";
        return false;
    }
    operaciones.push_back("Retiro\n");
}

// Función para transferir dinero entre cuentas
void transferir(Cuenta &origen, Cuenta &destino, float monto, list<string>& operaciones) {
    if (monto > 0 && monto <= origen.saldo) {
        origen.saldo -= monto;
        destino.saldo += monto;
        cout << "Transferencia exitosa. Nuevo saldo de la cuenta de origen: $" << origen.saldo << "\n";
        cout << "Nuevo saldo de la cuenta de destino: $" << destino.saldo << "\n";
    } else {
        cout << "Fondos insuficientes o monto invalido.\n";
    }
    operaciones.push_back("Transferencia\n");
}

string nombre;
bool operacionesBasicasDeUnCuentaDebito(int opcion, Cuenta &cuenta1, Cuenta &cuenta2, list<string>& operaciones) {
    //int opcion;
    float monto;

    switch (opcion) {
        case 1:
            cout << "Ingrese monto a depositar: ";
            cin >> monto;
            depositar(cuenta1, monto, operaciones);
            break;
        case 2:
            cout << "Ingrese monto a retirar: ";
            cin >> monto;
            if (retirar(cuenta1, monto, operaciones) == true) {
                cout << "Retiro realizado con exito\n";
            } else {
                cout << "Retiro no realizado\n";
            }
            //retirar(cuenta1, monto);
            break;
        case 3:
            cout << "Ingrese monto a transferir a otra cuenta: ";
            cin >> monto;
            transferir(cuenta1, cuenta2, monto, operaciones);
            break;
        case 4:
            cout << "Operaciones realizadas:\n";
            for (string ope : operaciones) {
                cout << ope;
            }
            break;
        case 5:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion inválida.\n";
    }

    cout << "Saldo actual: $" << cuenta1.saldo << endl;

}

//funcion para encriptar la contraseña
string encriptar(const string &contrasena) {
    string textoEn = contrasena;
    string mapeo = "abcdefghij";
    for (char& c : textoEn) {
        if (isdigit(c)) {
            c = mapeo[c - '0'];
        }
    }
    for (char& c : textoEn) {
        if (isalnum(c)) {
            int aleatorio = rand() % 3;
            if (aleatorio == 0) c = rand() % 26 + 'a';
            else if (aleatorio == 1) c = rand() % 10 + '0';
            else c = rand() % 15 + 33;
        }
    }
    return textoEn;
}

int main() {
    int opcParacontinuar = 1; 
    Cuenta cuentas[10]; 
    int opc;
    list<string> operaciones;

    cout << "\nBienvenido a la aplicación de cuentas bancarias\n";
    while (true) {
        int i = 0;
        do {
            cout << "\n1. Crear usuario \n2. Salir:";
            std::cin >> opc;
            if (opc == 1) {
                cout << "Creando usuario...\n";
                string nombre, contrasena;
                cout << "Ingrese nombre de usuario: ";
                std::cin >> nombre;
                cout << "Ingrese contraseña: ";
                std::cin >> contrasena;
                cuentas[i] = Cuenta{nombre, 0, contrasena}; 

                cout << "Usuario creado con exito\n";
                cout << "Contraseña encriptada: " << encriptar(contrasena) << "\n";
                i++;
                cout << "Desea crear otro usuario? (1. Si, 2. No): ";
            } 
            if (opc == 2) {
                cout << "Gracias por usar la aplicacion\n";
                break;
            } 
        } while (opcParacontinuar == 1);

        int opcMenu1 = 1;
        int opc3;
        string nombreUsuario; 
        string nombreUsuarioCredito;
        string nombreUusuarioTransferir;

        do {
            cout << "\n1. Ingresar a Cuenta de debito\n2. Ingresar a cuenta de credito\n3. Ingresar a cuenta de Ahorro\n4. Salir\nSeleccione una opcion: ";
            cin >> opc3;
            string contrasena;
            switch (opc3) {
                case 1:
                    cout << "Ingresando a cuenta de debito...\n";
                    cout << "Ingresar nombre de usuario de forma correcta: ";
                    cin >> nombreUsuario;
                    cout << "Ingrese su contrasena: ";
                    cin >> contrasena;    
                    for (int i = 0; i < 10; i++) {
                        if (cuentas[i].titular == nombreUsuario&& cuentas[i].contrasena == contrasena) {
                            cout << "\n1. Depositar\n2. Retirar\n3. Transferir\n4. Consulta de operaciones\n5. Salir\nSeleccione una opcion: ";
                            int opcion;
                            cin >> opcion;
                            if (opcion == 3) {
                                cout << "Ingrese nombre de usuario a transferir: ";
                                    cin >> nombreUusuarioTransferir;
                                    for (int j = 0; j < 10; j++) {
                                        if (cuentas[j].titular == nombreUusuarioTransferir) {
                                            cout << "Usuario encontrado\n";
                                            cout << "Ingrese monto a transferir: ";
                                            float montoTransferir;
                                            cin >> montoTransferir;
                                            transferir(cuentas[i], cuentas[j], montoTransferir, operaciones);
                                            break;
                                        } 
                                }
                            } else {
                                operacionesBasicasDeUnCuentaDebito(opcion, cuentas[i], cuentas[i + 1], operaciones);
                                break;
                            }
                        } 
                    }
                    break;
                case 2:
                    cout << "Ingresando a cuenta de credito...\n";
                    cout << "Ingresar nombre de usuario de forma correcta: ";
                    cin >> nombreUsuarioCredito;
                    cout << "Ingrese su contrasena: ";
                    cin >> contrasena;    
                    for (int i = 0; i < 10; i++) {
                        if (cuentas[i].titular == nombreUsuarioCredito && cuentas[i].contrasena == contrasena) {
                            cout << "\n1. Solicitar credito\n2. Pagar credito\n3. Salir\nSeleccione una opcion: ";
                            int opcionCredito;
                            cin >> opcionCredito;
                            switch (opcionCredito) {
                                case 1:
                                    cout << "Solicitando credito...\n";
                                    cout << "Ingrese monto a solicitar: ";
                                    float montoCredito;
                                    cin >> montoCredito;
                                    cuentas[i].saldo += montoCredito;
                                    cuentas[i].credito += montoCredito;
                                    cout << "Credito solicitado exitosamente. Nuevo saldo: $" << cuentas[i].saldo << endl;
                                    break;
                                case 2:
                                    cout << "Pagando credito...\n";
                                    cout << "Tu credito a pagar es de " << cuentas[i].credito << "\n";
                                    cout << "Ingrese monto a pagar: ";
                                    float montoPagar;
                                    cin >> montoPagar;
                                    if (montoPagar == cuentas[i].credito) {
                                        cuentas[i].credito -= montoPagar;
                                        cout << "Pago exitoso. Nuevo saldo de credito a deber: $" << cuentas[i].credito << endl;
                                    } else {
                                        cout << "Monto a pagar excede el credito o es menor.\n";
                                    }
                                    break;
                                case 3:
                                    cout << "Saliendo...\n";
                                    break;
                                default:
                                    cout << "Opción invalida.\n";
                            }
                        }
                    }
                    break;
                case 3:
                string nombreUsuarioCredito;
                string contrasena;
                cout << "Ingresar nombre de usuario de forma correcta: ";
                cin >> nombreUsuarioCredito;
                cout << "Ingrese su contrasena: ";
                cin >> contrasena;    
                for (int i = 0; i < 10; i++) {
                    if (cuentas[i].titular == nombreUsuarioCredito && cuentas[i].contrasena == contrasena) {
                        cout << "Ingresando a la tarjeta de ahorro...\n";
                        cout << "Ingrese monto a depositar en la cuenta de ahorro: ";
                        float ahorro;
                        cin >> ahorro;
                        cuentas[i].saldoAhorro += ahorro;
                        cout << "Deposito exitoso. Nuevo saldo de ahorro: $" << cuentas[i].saldoAhorro << endl;
                    }}
                    
                break;
            }
        } while (opc3 != 4);
    }
    return 0;
}

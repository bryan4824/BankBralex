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
    // Verificar que el monto sea válido
    if (monto > 0) {
        cuenta.saldo += monto;
        //si el monto es mayor a 1000 se le suman intereses
    } else {
        cout << "Monto inválido.\n";
    }
    operaciones.push_back("Deposito\n");
}

// Función para retirar dinero
bool retirar(Cuenta &cuenta, float monto, list<string>& operaciones) {
    // Verificar que el monto sea válido y que haya suficiente saldo
    if (monto > 0 && monto <= cuenta.saldo) {
        //si el monto es mayor a 1000 se le suman intereses
        cuenta.saldo -= monto;
        cout << "Retiro exitoso- Nuevo saldo: $"<<cuenta.saldo << endl;
        return true;
        //si el monto es mayor a 1000 se le suman intereses
    } else {
        cout << "Fondos insuficientes o monto invalido.\n";
        return false;
    }
    // Agregar la operación a la lista de operaciones
    operaciones.push_back("Retiro\n");
}

// Función para transferir dinero entre cuentas
void transferir(Cuenta &origen, Cuenta &destino, float monto, list<string>& operaciones) {
    // Verificar que el monto sea válido y que haya suficiente saldo en la cuenta de origen
    if (monto > 0 && monto <= origen.saldo) {
        //si el monto es mayor a 1000 se le suman intereses
        origen.saldo -= monto;
        destino.saldo += monto;
        //Imprimir el nuevo saldo de la cuenta de origen y destino
        cout << "Transferencia exitosa. Nuevo saldo de la cuenta de origen: $" << origen.saldo << "\n";
        cout << "Nuevo saldo de la cuenta de destino: $" << destino.saldo << "\n";
    } else {
        //
        cout << "Fondos insuficientes o monto invalido.\n";
    }
    // Agregar la operación a la lista de operaciones
    operaciones.push_back("Transferencia\n");
}

string nombre;
// Función para mostrar el menú de operaciones básicas de una cuenta de débito
// Esta función recibe la opción seleccionada por el usuario y realiza la operación correspondiente
bool operacionesBasicasDeUnCuentaDebito(int opcion, Cuenta &cuenta1, Cuenta &cuenta2, list<string>& operaciones) {
    //int opcion;
    float monto;

    // Mostrar el menú de operaciones
    switch (opcion) {
        //opción 1: Depositar dinero
        case 1:
            cout << "Ingrese monto a depositar: ";
            cin >> monto;
            depositar(cuenta1, monto, operaciones);
            break;
            //opción 2: Retirar dinero
        // Verificar que el monto sea válido y que haya suficiente saldo
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
        // Transferir dinero entre cuentas
            cout << "Ingrese monto a transferir a otra cuenta: ";
            cin >> monto;
            // Verificar que el monto sea válido y que haya suficiente saldo en la cuenta de origen
            transferir(cuenta1, cuenta2, monto, operaciones);
            break;
        case 4:
        //opción 4: Consultar operaciones realizadas
            cout << "Operaciones realizadas:\n";
            //verificar que la lista de operaciones no esté vacía
            for (string ope : operaciones) {
                cout << ope;
            }
            break;
        case 5:
        //opción 5: Salir
            cout << "Saliendo...\n";
            break;
            //opción inválida
        default:
            cout << "Opcion inválida.\n";
    }
    // Mostrar el saldo actual de la cuenta
    cout << "Saldo actual: $" << cuenta1.saldo << endl;

}

//funcion para encriptar la contraseña
string encriptar(const string &contrasena) {
    // Inicializar la semilla para la generación de números aleatorios
    string textoEn = contrasena;
    string mapeo = "abcdefghij";
    // Reemplazar los dígitos por letras
    for (char& c : textoEn) {
        if (isdigit(c)) {
            c = mapeo[c - '0'];
        }
    }
    // Reemplazar letras por caracteres aleatorios
    for (char& c : textoEn) {
        // Verificar si el carácter es alfanumérico
        if (isalnum(c)) {
            // Generar un número aleatorio entre 0 y 2
            int aleatorio = rand() % 3;
            if (aleatorio == 0) c = rand() % 26 + 'a';
            else if (aleatorio == 1) c = rand() % 10 + '0';
            else c = rand() % 15 + 33;
        }
    }
    // Reemplazar letras por caracteres especiales
    return textoEn;
}

int main() {
    int opcParacontinuar = 1; 
    Cuenta cuentas[10]; 
    int opc;
    //lista de operaciones 
    list<string> operaciones;

    //mensaje de bienvenida
    cout << "\nBienvenido a la aplicación de cuentas bancarias\n";
    //mensaje de instrucciones
    //muestra el menú de opciones
    while (true) {
        int i = 0;
        do {
            //da la opcion de crear un usuario o salir
            cout << "\n1. Crear usuario \n2. Salir:";
            std::cin >> opc;
            //verifica que la opción sea válida
            if (opc == 1) {
                //pide al usuario que ingrese su nombre y contraseña
                cout << "Creando usuario...\n";
                string nombre, contrasena;
                cout << "Ingrese nombre de usuario: ";
                std::cin >> nombre;
                cout << "Ingrese contraseña: ";
                std::cin >> contrasena;
                //verifica que el nombre de usuario no esté vacío
                cuentas[i] = Cuenta{nombre, 0, contrasena}; 

                //mensaje de éxito
                cout << "Usuario creado con exito\n";
                cout << "Contraseña encriptada: " << encriptar(contrasena) << "\n";
                i++;
                //pide la opción de continuar creando usuarios o salir
                cout << "\nDesea crear otro usuario? (1. Si, 2. No): ";
            } 
            //verifica que la opción sea válida
            else if (opc == 2) {
                cout << "Gracias por usar la aplicacion\n";
                break;
            }
            //si la opcion es igaul 2 
            if (opc == 2) {
                cout << "Gracias por usar la aplicacion\n";
                break;
            } 
        } while (opcParacontinuar == 1);

        //declarar variables para el menú de cuentas
        int opcMenu1 = 1;
        int opc3;
        string nombreUsuario; 
        string nombreUsuarioCredito;
        string nombreUusuarioTransferir;
        
        //muestra el menú de cuentas
        do {
            cout << "\n1. Ingresar a Cuenta de debito\n2. Ingresar a cuenta de credito\n3. Ingresar a cuenta de Ahorro\n4. Salir\nSeleccione una opcion: ";
            cin >> opc3;
            string contrasena;
            //verifica que la opción digitada en el menu
            switch (opc3) {
                //opcion 1: ingresar a cuenta de debito
                case 1:
                    cout << "Ingresando a cuenta de debito...\n";
                    //pide al usuario que ingrese su nombre y contraseña
                    cout << "Ingresar nombre de usuario de forma correcta: ";
                    cin >> nombreUsuario;
                    cout << "Ingrese su contrasena: ";
                    cin >> contrasena;    
                    //busca el nombre de usuario en el arreglo de cuentas
                    for (int i = 0; i < 10; i++) {
                        //verifica que el nombre de usuario y la contraseña sean correctos
                        if (cuentas[i].titular == nombreUsuario&& cuentas[i].contrasena == contrasena) {
                            //muestra el menú de operaciones
                            cout << "\n1. Depositar\n2. Retirar\n3. Transferir\n4. Consulta de operaciones\n5. Salir\nSeleccione una opcion: ";
                            int opcion;
                            cin >> opcion;
                            //si el igual a 3 solicita el nombre de usuario a transferir
                            if (opcion == 3) {
                                //pide al usuario que ingrese el nombre de usuario a transferir
                                cout << "Ingrese nombre de usuario a transferir: ";
                                    cin >> nombreUusuarioTransferir;
                                    //busca el nombre de usuario en el arreglo de cuentas
                                    for (int j = 0; j < 10; j++) {
                                        //verifica que el nombre de usuario y la contraseña sean correctos
                                        if (cuentas[j].titular == nombreUusuarioTransferir) {
                                            cout << "Usuario encontrado\n";
                                            cout << "Ingrese monto a transferir: ";
                                            float montoTransferir;
                                            cin >> montoTransferir;
                                            //llama a la función transferir para realizar la transferencia
                                            transferir(cuentas[i], cuentas[j], montoTransferir, operaciones);
                                            break;
                                        } 
                                }
                            } else {
                                //llama a la función operacionesBasicasDeUnCuentaDebito para realizar la operación seleccionada
                                operacionesBasicasDeUnCuentaDebito(opcion, cuentas[i], cuentas[i + 1], operaciones);
                                break;
                            }
                        } 
                    }
                    break;
                    //opcion 2: ingresar a cuenta de credito
                case 2:
                //pide al usuario que ingrese su nombre y contraseña
                    cout << "Ingresando a cuenta de credito...\n";
                    cout << "Ingresar nombre de usuario de forma correcta: ";
                    cin >> nombreUsuarioCredito;
                    cout << "Ingrese su contrasena: ";
                    cin >> contrasena;    
                    //busca el nombre de usuario en el arreglo de cuentas
                    //verifica que el nombre de usuario y la contraseña sean correctos
                    for (int i = 0; i < 10; i++) {
                        if (cuentas[i].titular == nombreUsuarioCredito && cuentas[i].contrasena == contrasena) {
                            cout << "\n1. Solicitar credito\n2. Pagar credito\n3. Salir\nSeleccione una opcion: ";
                            int opcionCredito;
                            cin >> opcionCredito;
                            //evaluar la opción seleccionada
                            switch (opcionCredito) {
                                //en el caso de que la opción sea 1 solicita el monto a solicitar
                                case 1:
                                    cout << "Solicitando credito...\n";
                                    cout << "Ingrese monto a solicitar: ";
                                    float montoCredito;
                                    cin >> montoCredito;
                                    //el monto se suma al saldo y al credito
                                    cuentas[i].saldo += montoCredito;
                                    //se le suma el monto al credito
                                    cuentas[i].credito += montoCredito;
                                    cout << "Credito solicitado exitosamente. Nuevo saldo: $" << cuentas[i].saldo << endl;
                                    break;
                                    ///en el caso de que la opción sea 2 solicita el monto a pagar
                                case 2:
                                    cout << "Pagando credito...\n";
                                    cout << "Tu credito a pagar es de " << cuentas[i].credito << "\n";
                                    cout << "Ingrese monto a pagar: ";
                                    float montoPagar;
                                    cin >> montoPagar;
                                    //verifica que el monto a pagar no exceda el credito
                                    if (montoPagar == cuentas[i].credito) {
                                        cuentas[i].credito -= montoPagar;
                                        cout << "Pago exitoso. Nuevo saldo de credito a deber: $" << cuentas[i].credito << endl;
                                    } else {
                                        //si el monto a pagar es menor se da un mensaje de error
                                        cout << "Monto a pagar excede el credito o es menor.\n";
                                    }
                                    break;
                                case 3:
                                //opción 3: Salir
                                    cout << "Saliendo...\n";
                                    break;
                                    //opción inválida
                                default:
                                    cout << "Opción invalida.\n";
                            }
                        }
                    }
                    break;
                case 3:
                //en el caso de que la opción sea 3 solicita el monto a depositar
                string nombreUsuarioCredito;
                string contrasena;
                //pide al usuario que ingrese su nombre y contraseña
                cout << "Ingresar nombre de usuario de forma correcta: ";
                cin >> nombreUsuarioCredito;
                cout << "Ingrese su contrasena: ";
                cin >> contrasena;    
                //busca el nombre de usuario en el arreglo de cuentas
                for (int i = 0; i < 10; i++) {
                    //verifica que el nombre de usuario y la contraseña sean correctos
                    if (cuentas[i].titular == nombreUsuarioCredito && cuentas[i].contrasena == contrasena) {
                        //solicita el monto a depositar
                        cout << "Ingresando a la tarjeta de ahorro...\n";
                        cout << "Ingrese monto a depositar en la cuenta de ahorro: ";
                        float ahorro;
                        cin >> ahorro;
                        //el ahorro se suma al saldo y al saldo de ahorro
                        cuentas[i].saldoAhorro += ahorro;
                        cout << "Deposito exitoso. Nuevo saldo de ahorro: $" << cuentas[i].saldoAhorro << endl;
                    }}
                    
                break;
            }
            //mientras la opción no sea 4 se repite el menú
        } while (opc3 != 4);
    }
    return 0;
}

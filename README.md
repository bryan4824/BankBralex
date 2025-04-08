# BankBralex
# 💳 Simulador de Cuentas Bancarias en C++

Este proyecto es un **simulador de operaciones bancarias** desarrollado en C++, que permite gestionar cuentas de débito, crédito y ahorro. Es ideal como ejercicio de lógica, estructuras, manejo de contraseñas y simulación de un sistema básico financiero.

## 🚀 Funcionalidades

- **Crear múltiples usuarios** con nombre y contraseña.
- **Cuentas de Débito**:
  - Depositar
  - Retirar
  - Transferir entre cuentas
  - Consultar historial de operaciones

- **Cuentas de Crédito**:
  - Solicitar crédito
  - Pagar crédito

- **Cuentas de Ahorro** *(estructura base incluida, funcionalidad aún por implementar)*

- **Encriptación básica** de contraseñas (para demostración, no segura en producción).

## 🛠️ Tecnologías

- Lenguaje: **C++**
- Librerías estándar utilizadas:
  - `iostream`
  - `string`
  - `cstdlib`
  - `ctime`
  - `cctype`
  - `list`

## 📂 Estructura del Proyecto

- `main()`: Control principal del flujo del programa
- `struct Cuenta`: Estructura que representa una cuenta bancaria
- Funciones principales:
  - `depositar()`
  - `retirar()`
  - `transferir()`
  - `operacionesBasicasDeUnCuentaDebito()`
  - `encriptar()`

## 🧪 Cómo usarlo

1. Clona este repositorio:
    ```bash
    git clone https://github.com/tu_usuario/simulador-cuentas-bancarias.git
    cd simulador-cuentas-bancarias
    ```

2. Compila el archivo:
    ```bash
    g++ -o simulador main.cpp
    ```

3. Ejecuta el programa:
    ```bash
    ./simulador
    ```

4. Sigue las instrucciones en la terminal para crear usuarios y operar cuentas.

## ⚠️ Advertencias

- Este proyecto **no** usa cifrado real. La función de encriptación es meramente demostrativa.
- No se utiliza persistencia (los datos se pierden al cerrar el programa).

## ✅ Por hacer

- Implementar funcionalidades de cuenta de ahorro
- Agregar validaciones más robustas
- Persistencia de datos en archivos o base de datos
- Interfaz gráfica (opcional)

## 🧑‍💻 Autor

Creado por [Tu Nombre](https://github.com/tu_usuario) — Proyecto personal para práctica de estructuras en C++.

## 📄 Licencia

Este proyecto está bajo la Licencia MIT. Puedes hacer lo que quieras, ¡pero deja una estrellita si te fue útil! 🌟

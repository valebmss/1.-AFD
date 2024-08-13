# Autómata Finito Determinista (AFD) en C

Este proyecto implementa un Autómata Finito Determinista (AFD) en el lenguaje de programación C. El programa permite la simulación de un AFD, verificando si una cadena de entrada es aceptada por el autómata definido.

## Requisitos

Antes de comenzar, asegúrate de tener lo siguiente instalado en tu sistema:

- Sistema operativo Linux
- Compilador GCC
- Git (para clonar el repositorio)

## Instalación

### 1. Clonar el repositorio

Primero, clona el repositorio desde GitHub a tu máquina local:

```
https://github.com/valebmss/1.-AFD.git
```
### 2. Navegar al directorio del proyecto
Una vez clonado el repositorio, navega al directorio del proyecto:

```
cd 1.-AFD
```
### 3. Compilar el programa
Compila el archivo afd.c utilizando el compilador GCC:

```
gcc -o afd afd.c
```
Este comando generará un archivo ejecutable llamado afd.

### 4. Ejecutar el programa
Para ejecutar el programa, utiliza el siguiente comando:

```
./afd
```
### 5. Ingresar la cadena de entrada
Sigue las instrucciones del programa para ingresar una cadena de entrada y verificar si es aceptada por el AFD.

## Ejemplo de uso

```
./afd
```
### config.txt
Estados: q0,q1,q2

Símbolos: a,b

Estado inicial: q0
Estados de aceptación: q2

Transición: q0,a,q1

Transición: q1,b,q2

Transición: q1,a,q1

Transición: q2,a,q1

Transición: q2,b,q2

### Ingrese la cadena de entrada:

```
abbbabb

```
### Resultado: La cadena fue aceptada.



## Especificaciones
1. Para modificar el archivo de configuracion, ve a la carpeta del repositorio y modifica el 
```
config.txt
```
Despues repite los pasos anteriores para actualizar el ejecutable



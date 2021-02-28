# sfml_test
Pruebas de la libreria SFML en c++

## Librerias Requiridas:
* SFML

## Instrucciones de compilacion

### Instalar la libreria:
Para correr el programa se necesita la siguente libreria:
```
libsfml-dev
```
Se puede instalar con el manejador de paquetes preferido: eg 
```
sudo apt install libsfml-dev
```

### Compilacion

```
g++ -c sprite_test.cpp

g++ sprite_test.o -o sfml-app.o -lsfml-graphics -lsfml-window -lsfml-system
```

### Ejecucion

```
./sfml-app.o
```


## Programa

El programa se ve asi:

![Cosas](Images/Funcionamiento.png)
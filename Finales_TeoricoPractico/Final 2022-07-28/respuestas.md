# (1) Algoritmos Voraces

**Datos**:

- `n` peliculas.
- Para cada pelicula `i`, con 1 <= i <= n, tenes el horario de comienzo $c_i$ y del final $f_i$.
- No se puede ver dos peliculas a la vez.
- Tenemos que encontrar cuales de las `n` peliculas vamos a ver, tal que la cantidad sea **maxima**

### (a)

Se van a seleccionar primero las peliculas que esten mas prontas a terminar

### (b)

```LenguajeDeLaMateria
type Pelicula = tuple
                    nombre: String
                    comienzo: Nat
                    final: Nat
                end tuple
```

### (c)

El algoritmo recorrera un conjunto de peliculas que elegimos para ver, eligiendo la que termine antes, ordenandolos en una lista.

### (d)

```LenguajeDeLaMateria
fun VerPeliculas(p: Set of Pelicula) ret res: List of Pelicula
    var p_aux: Set of Pelicula
    p_aux:= set_copy(p)
    var peli: Pelicula

    do(!is_empty_set(p_aux)) --->
        peli:= SeleccionarPelicula(p_aux)
        elim(p_aux, peli)
        addr(res, p)
    od

    destroy_set(p_aux)
end fun

fun SeleccionarPelicula(p: Set of Pelicula) ret peli: Pelicula
    var p_aux: Set of Pelicula
    p_aux:= set_copy(p)
    var c: Pelicula

    peli:= get(p_aux)
    elim(p_aux, peli)

    do(!is_empty_set(p_aux)) --->
        c:= get(p_aux)
        elim(p_aux, c)
        if(c.final < res.final) then
            res:= c
        fi
    od

    destroy_set(p_aux)
end fun
```

---

# (2)

**Datos**:

- `n` ejercicios.
- Cada ejercicio `i`, con 1 <= i <= n tiene asociado un "valor de entrenamiento general" $e_i$.
- Cada ejercicio `i` requiere un esfuerzo de brazos $b_i$, un esfuerzo de zona media $z_i$ y un esfuerzo de piernas $p_i$.
- Tenemos que encontrar el **Maximo** valor de entrenamiento sin que el esfuerzo total en brazos supere el monto `B`, el esfuerzo total en zona media supere el monto `Z` y el esfuerzo total en piernas supere el monto `P`.

### (a) Backtracking

La funcion recursiva va a calcular el maximo valor de entrenamiento general eligiendo los ejercicios pertinentes. Toma como argumentos los `n` ejercicios, el esfuerzo maximo de brazo `B`, el esfuerzo maximo de zona media `Z` y el esfuerzo maximo de piernas `P`.

La llamada principal es Ejercicio(n, B, Z, P)

(n = i, j = B, x = Z, y = P)

    Ejercicio(i, j, x, y) = 

                |   0  ---> si (i = 0)  (Caso donde no tengo mas ejercicios que hacer)

                |   Ejercicio(i - 1, j, x, y)  ---> si ((i > 0) && ((b_i > j) || (z_i > j) || (p_i > j)))   (Caso donde no tengo fuerza para hacer los ejercicios)

                |   max(e_i + Ejercicio(i - 1, j - b_i, x - z_i, y - p_i), Ejercicio(i - 1, j, x, y))  ---> si ((i > 0) && (j > b_i) && (x > z_i) && (y > p_i))  (Caso donde elijo si me conviene hacer el ejercicio o no)

### (b) Programacion Dinamica

La tabla tiene 4 dimensiones puesto que tenemos 4 parametros en el backtracking.

La tabla se va a llenar de izquierda a derechea, de abajo a arriba.

```LenguajeDeLaMateria
type Ejercicio = tuple
                    valor: Nat
                    montoB: Nat
                    montoZ: Nat
                    montoP: Nat
                 end tuple

fun Ejercicio_dinamica(A: array[1...n] of Ejercicio, B: Nat, Z: Nat, P: Nat)ret res: Nat
    var ejercicios: array[1..n] of Ejercicio
    var tabla: array[0..n, 0..B, 0..Z, 0..P] of nat

    {- Copiamos el array A en ejercicios -}
    for i:= 0 to n do
        ejercicios[i]:= A[i]
    od

    {- Caso base -}
    for j:= 0 to B do
        for x:= 0 to Z do
            for y:= 0 to P do
                tabla[0, j, x, y]:= 0
            od
        od
    od

    for i = 1 to n do
        for j = 1 to B do
            for x = 1 to Z do
                for y = 1 to P do

                    {- Caso donde no puedo hacer el ejercicio -}
                    if(i>0 && (ejercicios[i].montoB > j || ejercicios[i].montoZ > x || ejercicios[i].montoP > y)) then 
                        tabla[i,j,x,y] := tabla[i-1,j,x,y]

                    {- Caso donde decido si hacer o no el ejercicio -}
                    else
                        tabla[i,j,x,y] = max(ejercicios[i].valor + tabla[i-1,j-ejercicios[i].montoB,x-ejercicios[i].montoZ],y-ejercicios[i].montoP),tabla[i-1,j,x,y]

                    fi
                od
            od
        od
    od

    res = tabla[n, B, Z, P]

end fun
```

---
# (3)

### (a)

* El proceso **q** es un selection sort, osea ordena un array menor a mayor.

* El proceso **r** tiene la forma de un insertion sort, osea ordena un array de menor a mayor.

* El proceso **p** combina los procesos **q** y **r**, primero ordena con **q** desde el principio del array hasta el (i-1) y luego con **r** lo ordena de i+1 hasta N, dejando al medio un "pivot".

### (b)

* **q** con un ciclo va a recorrer el arreglo desde 1 hasta una posicion especificada x, con otro bucle, desde una posicion mas que el anterior, va a busca el minimo del array y al encontrarlo va a intercambiar con swap la posicion actual j con la posicion del minimo.
* **r** recorre el arreglo con un ciclo for desde la posicion y hasta n(longitud del arreglo), con un ciclo while compara el valor en la posición m con la posición anterior y realiza un swap si es necesario (si es menor al anterior), ajustando el índice hacia atrás.
* **r** va a llamar primero a la procedimiento **q** para ordenar parcialmente desde la primera posicion hasta (i-1) y luego va a llamar al procedimiento **r** para ordenar desde (i+1) hasta N(longitud del arreglo).

### (c)

* En **q** en el peor de los casos el orden del procedimiento es $n^2$ ya que tenemos dos ciclos for (el procedimiento swap no cambia mucho al orden de la funcion).
* En **r** en el peor de los casos el orden del procedimiento es $n^2$ ya que tenemos dos ciclos for (el procedimiento swap no cambia mucho al orden de la funcion).
* En **p** va a ser la suma de los ordenes de **q** y **r**.

--- 

# (4) TADs

### (a)

```LenguajeDeLaMateria
type Stack of T = tuple
                    array: array[1..N] of T
                    size: Nat
                  end tuple

fun empty_stack() ret s: stack of T
    size:= 0
    s.array[1...size]
end fun

proc push(in e: T, in/out s: stack of T)
    s.array[size + 1]:= e
    s.size:= s.size + 1
end proc

proc destroy(in/out s:stack of T)
    s.size := 0
end proc

fun copy(in/out s:Stack of T) ret s1 Stack of T
    for i:= 1 to s.size do 
        s1.array[i]:= s.array[i]
    od
end fun

fun empty_stack() ret s: stack of T
    size:= 0
    s.array[1...size]
end fun

{- PRE: !is_empty_stack(s) -}
fun top(s: stack of T) ret e: T
    e:= s.array[s.size]
end fun

proc pop (in/out s:stack of T)
    s.array[s.size] := 0
    s.size := s.size - 1
end proc
```

### (d)

```LenguajeDeLaMateria
proc invert(in/out s: stack of T) 
    var s_copy: stack of T
    s_copy := empty_stack()
    
    do(!is_empty_stack(s)) --->
        push(top(s),s_copy)
        pop(s)
    od
    
    s := copy_stack(s_copy)

    destroy_stack(s_copy)
end proc
```
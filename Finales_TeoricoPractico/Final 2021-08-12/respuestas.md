# (1) Voraz

**Datos**:

- `n` facturas que pagar.
- Para cada factura `i` se sabe que dia $d_i$ va a llegar al domiciolio y el dia de vencimiento $v_i$.
- No se puede pagar si no ha llegado todavia xd.
- Se paga antes del vencimiento (se puede pagar tambien el mismo dia en el que vende).
- Se busca que el abuelo vaya la menor cantidad de veces a pagar las facturas.

### (a)

Se va a seleccionar las facturas que se venzan mas tarde.

### (b)

```LenguajeDeLaMateria
type Factura = tuple
                    d_i: Nat
                    v_i: Nat
               end tuple
```

### (c)

El algoritmo tomara un conjunto de Facturas, a la cual vamos a ir seleccionando la factura que tenga el dia de vencimiento mas tarde, el algoritmo devolvera cuantas facturas debera pagar.

### (d)

```LenguajeDeLaMateria
fun PagarFactura(s: Set of Factura) ret res: Nat
    var s_aux: Set of Factura
    s_aux = copy_set(s)
    var fac: Factura

    do(!is_empty_set(s_aux)) --->
        fact:= SeleccionarFactura(s_aux)
        elim(s_aux, fact)
        f:= f + 1
    od

    destroy_set(s_aux)
end fun

fun SeleccionarFactura(s: Set of Factura) ret res: Factura
    var s_aux: Set of Factura
    s_aux:= copy_set(s)
    var f: Factura

    res:= get(s_aux)
    elim(s_aux, res)

    do(!is_empty_set(s_aux)) --->
        f:= get(s_aux)
        elim(s_aux, f)
        
        if(res.v_i > f.v_i) then
            res:= f
        fi
    od

    destryo_set(s_aux)
end fun
```

---

# (2)

**Datos**:

- Tenemos `n` proyectos posibles a los cuales ofrecer servicio y la posibilidad de trabajar `H` horas como máximo. 
- Para cada proyecto `i` (de 1 hasta n) ya calcule la cantidad de horas $h_i$ que requiere de trabajo, y la paga $p_i$ que recibire si lo hago.
- Tenemos la posibilidad de pedirle a un amigo que nos ayude con algunos proyectos, en cuyo caso nos va a tomar la mitad de horas ($h_i/2$), pero vamos a comprar la mitad de dinero.
- Tenemos que calcular la maxima ganancia que podemos obtener eligiendo que proyecto tomar y cuando recurrir a la ayuda de nuestro amigo.

### (a) Backtracking

La funcion calcula la maxima ganancia que podemos generar sin exedernos del maximo de horas de trabajo. Los argumentos que toma son los `n` proyectos y las horas maximas `H` que podemos trabajar.

La llamada principal es Trabajar(n, H)

    Trabajar(i, j) = 
            |  0 ---> si ((i = 0) || (j = 0))
            |  Trabajar(i - 1, j) ---> si ((i > 0) && (((h_i / 2) > j) || (h_i > j)))
            |  Max(Max((p_i / 2) + Trabajar(i - 1, j - (h_i / 2)), Trabajar(i - 1, j)), Max(p_i + Trabajar(i - 1, j - h_i), Trabajar(i - 1, j))) ---> si ((h_i < j) && (i > 0))

### (b) Programacion Dinamica

La Tabla va a tener dimension 2x2, ya que tenemos solamente 2 argumentos.

La Tabla se llena de izquierda a derecha, de abajo a arriba

Creo que no xd

```LenguajeDeLaMateria
type Proyecto: tuple
            h_i: Nat
            p_i: Nat
               end tuple

fun trabajar(T: array[1...n] of Proyecto, n: nat, H: nat) ret p: nat
    var trabajo: array[1..n] of Proyecto
    var tabla: array[0..n,0..H] of nat
    
    {- Copiamos -}
    for i:= 1 to n do 
        trabajo[i]:= T[i]
    od
    
    {- Caso base -}
    for i:= 0 to n do
        tabla(i, 0):= 0
    od
    for j:= 0to H do
        tabla(0, j):= 0
    od
    
    for i:= 1 to n do
        for j:= 1 to H do
            if((i > 0) && ((trabajo[i].h_i / 2) > j) || trabajo[i].h_i > j) then
                tabla[i, j]:= tabla[i - 1, j]
            else
                tabla[i, j]:= max(max((trabajo[i].p_i / 2) + tabla[i - 1, j - (trabajo[i].h_i / 2)], tabla[i - 1, j]), max((trabajo[i].p_i) + tabla[i - 1, j - trabajo[i].h_i], tabla[i - 1, j]))
            fi
        od
    od
    
    {- Guardamos el resultado -}
    p:= tabla[n, H]

end fun
```

--- 

# (3) Comprension de algoritmos

### (a) ¿Que hace?

- La funcion `s` encuentra el menor elemento de un array.
- La funcion `t` encuentra el mayor elemento de un array.
- El procedimiento `r` ordena la primera mitad del array de menor a mayor y la segunda mitad de mayor a menor.

### (b) ¿Como lo hace?

- La funcion `s` tomo como argumentos un array `p` de naturales, dos naturales `v` y `w` y retorna un natural `y`. Al inicio de la funcion inicializa `y` con el valor de `v`, luego con un ciclo `for` va a ir recorriendo el array hasta `w` para encontrar el menor de los elementos.
- La funcion `t` tomo como argumentos un array `p` de naturales, dos naturales `v` y `w` y retorna un natural `y`. Al inicio de la funcion inicializa `y` con el valor de `v`, luego con un ciclo `for` va a ir recorriendo el array hasta `w` para encontrar el mayor de los elementos.
- El procedimiento `r` va a tomar como argumento un arreglo de naturales. Con un bucle `for` que va desde el primer elemento del array hasta la mitad, va poner primero al elemento mas chico del arreglo y luego en la ultima posicion al mayor de ellos, todo esto con la funcion `swap`.

### (c)

- `s` tiene orden constante al igual que `t`
- El procedimiento `r` tiene orden $n^2/2$ ya que $n/2*(n/2 + n/2) = n^2/4 + n^2/4 = n^2/2$

---

# (4) TADs

### (a)

```LenguajeDeLaMateria
type Stack of T = tuple
                    array: array[1..N] of T
                    size: Nat
                  end tuple

fun empty_stack() ret s: Stack of T
    s.size:= 0
end fun

proc push(in e: T, in/out s: Stack of T)
    s.size:= s.size + 1
    s.array[s.size]:= e
end proc

proc destroy(in/out s: Stack of T)
    s.size:= 0
end proc

fun copy(s: Stack of T) ret s_copy: Stack of T
    for i:= 0 to s.size do
        s_copy.array[i]:= s.array[i]
    od
    s_copy.size:= s.size
end fun

fun is_empty_stack(s: Stack of T) ret res: Bool
    res:= (s.size = 0)
end fun

{- PRE: !is_empty_stack(s) -}
fun top(s: stack of T) ret e: T
    e:= s.array[s.size]
end fun

{- PRE: !is_empty_stack(s) -}
proc pop(in/out s: stack of T)
    s.array[s.size]:= s.array[s.size - 1]
    s.size:= s.size - 1
end proc
```

### (c)

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

---

# (5) Para alumnos libres

Forma General
```LenguajeDeLaMateria
fun DyV(x) ret y
    if(x suficientemente pequeño/simple) then
        y:= ad_hoc(x)
    else
        {- Descomponemos x en x_1, x_2, ..., x_n -}
        for i:= 1 to a do
            y:= DyV(x_i)
        od
        {- Combinamos y_1, y_2, ..., y_a para obtener la solucion y de x -}
    fi
end fun
```
donde:
- a: Es el numero de llamadas recursivas
- b: Relacion dentre el tamaño de x y el de x_i, satisface que el | x_i | = | x | / b
- k: orden de descomponer y combinar es $n^k$

**Caracteristicas**:

- Hay una solucion para los casos sencillos
- Para los complejos, se divide o descompone el problema en subproblemas: 
    * Cada subproblema es de igual naturaleza que el original
    * El tamaño del subproblema es una fraccion del original
    * Se resuelve los subproblemas apelando al mismo algoritmo
- Se combina esas soluciones para obtener una solucion del original.

Un ejemplo de Divide y Venceras es la busqueda Binaria
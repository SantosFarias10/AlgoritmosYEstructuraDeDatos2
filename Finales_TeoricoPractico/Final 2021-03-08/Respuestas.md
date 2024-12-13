# (1) Voraz 

**Datos**

- N dias.
- N productos.
- Cada producto i tiene fecha de vencimiento $v_i$ contada desde el día en que llegás a la casa.
- Puede haber productos que ya esten vencidos ($v_i$ < 0).
- Comer un producto por dia, sin hacerte drama por comer algo vencido.
- Se pide indicar para cada día j con 1 <= j <= N que productos vas a comer.

### (a)

Se va a seleccionar primero la comida que hace mas tiempo este vencida, asi los primeros dias nos comemos los productos vencidos y hay mas chance de que al pasar los dias no comer mas productos vencidos.

### (b)

```LenguajeDeLaMateria
type Comida = tuple
                nombre: String
                vencimiento: Nat
              end tuple
```

### (c)

El algoritmo va a ir agarrando elementos de un conjunto de Comida que tenemos para nuestros N dias y va a ir seleccionando la que se vencio hace mas tiempo, agregandolo a un array resultante que presenta la comida que debemos comer en el "i-esimo" dia.

### (d)

```LenguajeDeLaMateria
fun MalenaHDP(S: Set of Comida, N: Nat) ret res: array[1...N] of Comida
    var S_aux: Set of Comida
    A_aux:= set_copy(S)
    var c: Comida
    var n: Nat
    n:= 1

    do(!is_empty_set(S_aux))--->
        c:= SeleccionarComida(S_aux, n)
        res[n]:= c
        elim_set(S_aux, c)
        n:= n + 1
    od

    destroy_set(S_aux)
end fun

fun SeleccionarComida(S: Set of Comida, N: Nat) ret res: Comida
    var S_aux: Set of Comida
    var c: Comida
    S_aux:= set_copy(S)
    res.vencimiento:= infinito

    do(!is_empty_set(S_aux))--->
        c:= get(S_aux)

        if(c.vencimiento < res.vencimiento) then
            res:= c
        fi
    od

    elim_set(S_aux, c)
    destroy_set(S_aux)
end fun
```

---

# (2) Backtracking

**Datos**:

- N productos.
- No vencen pero los tengo que pagar.
- Cada procuto i tiene un precio $p_i$ y un valor nutricional $s_i$.
- Presupuesto M.
- Se nos pide comer productos para obtener el máximo valor nutricional sin superar el presupuesto M.
- No hace falta comer todos los días ni vaciar la heladera.

### (a)

La función calcula el MÁXIMO valor nutricional obtenible con un presupuesto M y N productos, donde cada producto tiene un valor nutricional $s_i$ y un precio $p_i$.
Los argumentos que va a tomar nuestra función van a ser los N productos y nuestro presupuesto M.

### (b)

Cagao_hambre(N, M)

### (c)




---

# (3) Comprensión de algoritmos

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
fun empty_set() ret s: Set of T
    s.size:= 0
end fun

proc add(in e: T, in/out s: Set of T)
    if(!member(e, s)) then
        s.elems[s.size]:= e
        s.size:= s.size + 1
    fi
end fun

fun member(e: T, s: Set of T) ret b: bool
    var i: nat
    i:= 0
    b:= false

    do((i < s.size - 1) && !b) --->
        b:= s.elems[i] = e
        i:= i + 1
    od
end fun

{PRE: member(e, s)}
proc elim(in/out s: Set of T, in e: T)
    var i: Nat
    i:= 0

    do(i < s.size - 1) --->
        if(s.elems[i] = e) then
            for (j:= i + 1) to (s.size - 1) do
                s.elems[j + 1]:= s.elems[j]
            od
        fi
        i:= i + 1
    od
end proc

proc inters(in/out s: Set of T, in s0: Set of T)
    for i:= 0 to (s.size - 1) do
        if(!member(s.elems[i], s)) then
            elim(s, s.elems[i])
        fi
    od
end proc
```

### (b)

```LenguajeDeLaMateria
fun cerca(s: Set of Nat, i: Nat) ret res: Nat
    var s_aux: Set of Nat
    s_aux:= set_copy(s)
    var aux: Nat

    if(member(i, s_aux)) then
        res:= i
    else
        res:= get(s_aux)
        elim(s_aux, res)
        do(!is_empty_set(s_aux)) --->
            aux:= get(s_aux)
            if(aux - i < res - i) then
                res = aux
            fi
            elim(s_aux, aux)
        od
    fi

    destroy_set(s_aux)
end fun
```

---

# (5) Para libres

### (a)

La dimension de la tabla es NxM, ya que tenemos solamente 2 parametros en nuestra funcion Backtracking

### (b)

Como necesitamos valores anteriores para calcular los siguientes, tanto anteriores por fila como por columna. La formade llenado de la tabla es de izquierda a derecha y de abajo a arriba.
(NOTA: siempre que restemos el primer parametro es de izquierda a derecha, si restamos el segundo es de abajo a arriba, si es que le sumamos el primer parametro entonces es de derecha a izquierda, y si le sumamos el segundo es de arriba a abajo)

### (c)

NO.

Ejemplo de como hacer el codigo para rellenar la tabla

```LenguajeDeLaMateria
fun RellenarTabla(A: array[1...N] of Nat, B: array[1...N] of Nat, C: array[1...N] of Nat, M: Nat) ret res : Nat

    Var comida: array[1..N] of Nat
    Var precio: array[1..N] of Nat
    Var prote: array[1..N] of Nat
    Var saldo: Nat
    
    Var tabla: array[0...N,0...M] of nat
    
    {- Copiamos los valores -}
    for i :=1 to N do
        comida[i] = A[i]
        precio[i] = B[i]
        prote[i] = C[i]
    od
    
    saldo = M
    
    {- Primer caso cuando i siempre es 0 (el primer parametro) -}
    for j:= 0 to M do tabla[0, j] := 0 od
    
    {- Segundo y tercer caso -}
    for i :=1 to N do
        for j:= 1 to M do
        
        {- Caso cuando no podemos comprar porque no nos alcanza -}
        if(precio[i] > saldo && saldo > 0) then 
            tabla[i, j]:= tabla[i - 1, j] 
        {- Caso donde decidimos si compramos el producto o no -}
        else
            tabla[i, j]:= Max(prote[i] + tabla [i - 1, j - precio[i]], tabla[i - 1, j]) 
        fi
        
        od
    od
    
    {- Guardamos en resultado -}
    res:= tabla[N,M]
    
end fun
```
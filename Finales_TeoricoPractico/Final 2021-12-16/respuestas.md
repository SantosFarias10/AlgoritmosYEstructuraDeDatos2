# (1) Algoritmos voraces

**Datos**.

- Grafo dirigido G con costos no negativos en sus aristas, representado por su matriz de adyacencia, y un vertice `v` del mismo, **Dijkstra** calcula, para cada vertice `w` del grafo `G`, el costo del camino de costo minimo de `v` a `w`.

### (a)

```LenguajeDeLaMateria
Fun Artskjid(L: array[1..n, 1..n] of Nat, v: Nat) ret D: arrar[1..n]
    var c: NAt
    var C: Set of Nat

    for j:= 1 to n do
        D[j]:= L[j, v]
    od

    do(is_empty_set(C)) --->
        c:= "Elijo elemento c de C talque D[c] sea minimo"
        elim(C, c)

        for j in C do
            D[j]:= min(D[j], D[c] + L[j, c]) 
        od
    od
end fun
```

---

# (2) Backtracking

**Datos**:

- Disponemos de una cantidad de dinero `D`.
- Hay `n` objetos para comprar, cuyos precios hoy son $v_1, ..., v_n$.
- Suponemos que `D` es menor que la suma de todos los precios, por lo que tenemos que elegir cuales objetos comprar, es imposible comprar todos.
- Tenemos que encontrar el maximo monto que podemos gastar sin excedernos del dinero `D` disponible.

### (a)

La funcion calcula el maximo de dinero que puedo gastar sin excedernos del dinero disponible, Los argumentos que toma son los `n` objetos y el monto `D` del dinero disponible.

### (b)

La llamada principal es `Comprar(n, D)`.

### (c)

        Comprar(i, j) =
                |  0 ---> si ((i = 0) && (j > 0))
                |  Comprar(i - 1, j) ---> si ((i > 0) && (j < v_i))
                |  max(v_i + Comprar(i - 1, j - v_i), Comprar(i - 1, j)) ---> si ((i > 0) && (j > v_i))

---

# (3) Programacion Dinamica

Ejemplo: 

```
m(4, 1) = m(3, 1) + m(4, 2)
        = (m(2, 1) + m(3, 1)) + (m(3, 2) + m(4, 3))
        = (m(1, 1) + m(2, 2) + m(2, 2) + m(3, 3)) + (m(2, 2) + m(3, 3) + m(3, 3) + m(4, 4))
        = 3 + 1 + 1 + 2 + 1 + 2 + 2 + 5 = 17
```

```LenguajeDeLaMateria
fun m(C: array[1..n] of Nat, n: Nat, B: Nat) ret res: Nat
    var C_aux: array[1...n] of Nat
    var tabla: array[0...n, 0...n] of Nat

    for i:= 0 to n do
        for j:= 0 to n do
            if(i = j) then
                tabla[i, j]:= C_aux[i]
            fi
        od
    od

    for i:= 1 to n do
        for j:= n downto 1 do
            if(i > j) then 
                tabla[i, j]:= tabla[i - 1, j] + tabla[i, j + 1];
            fi
        od
    od

    res:= tabla[n, B]
end fun
```

--- 

# (4) Comprension de Algoritmos

### (a) ¿Que hace?

- La funcion `f` es una busqueda binaria, te dice si un elemento del array es igual a un numero que nosotros decidimos.
- La funcion `g` ve si dos arreglos tienen los mismo elementos.

### (b) ¿Como lo hace?

- `f` tomo como parametro un array de naturales `a`, un natural `i` (que indica el primer elemnto del arreglo), un natural `j` (indica el ultimo elemento del array) y un natural `x` (elemento a comparar), retorna un `b` boleano. Dentro de la funcion definimos variables auxiliares `d`, que va a ser el primer elemento del array `i`, `f`, el ultimo elemento del array y `e` donde vamos a asignarle la posicion de la mitad del array, que vamos a comprar con `x`. Entonces mientras `d` sea menor o igual al `f`, a `e` le asigamos el valor del elemento de la mitad del array (`d + f 'div' 2`), si el elemento a comparar `x` es menor que el elemento en la posicion `e` entonces decrementamos en 1 la posicion, si `x` es igual al elemento en la posicion `e` devolvemos `true`, y si `x` es mayor al elemento en la posicion `e` entonces incrementamos en 1 la posicion.

- `g` tomo como argumento dos array `a` y `b` y retornamos otro array `c` el cual va a marcar cuales posicion son iguales entre `a` y `b`, dentro de la funcion definimos un natural `i` para comparar las posiciones de los elementos de `a` y `b`. Mientras `i` sea menor que `n` (el tamaño del array) entonces la posicion `i` en `c` guardamos lo que retoran `f`, pasandole el array `a`, la primera posicion y la ultima, y el elemento a comparar `b[i]`.

### (c) Orden

- El orden de `f` es $n/2$.
- El orden de `g` es $n * n/2 = n^2/2$.

---

# (5) TADs

### (a)

```
type vipqueue= tuple
                    noVip: array[1..N] of T
                    vip: array[1..N] of T
                    sizeVip:= Nat
                    size:= Nat
               end tuple
```

### (b)

```
fun hayVip(q: vipqueue) ret b :bool
    var q_aux: vipqueue
    q_aux:= copy_vipqueue
    
    if(q_aux.sizeVip =0) then 
        b:= false
    else 
        b:= true
    if
end fun
    
fun first(q: vipqueue) ret res: T
    if(hayVip(q)) then
        res:= q.vip[0]
    else
        res:= q.noVip[0]
    fi
end fun

proc dequeue(in/out q:vipqueue)

    if(hayvip(q)) then
        for i:= 1 to size_vip - 1 do
            q.vip[i]:= q.vip[i+1]
        od
        q.sizeVip := q.sizeVip-1
    else
        for i:= 1 to size - 1 do
            q.noVip[i] := q.noVip[i + 1]
    od
    q.size := q.size - 1
    fi
end proc
```
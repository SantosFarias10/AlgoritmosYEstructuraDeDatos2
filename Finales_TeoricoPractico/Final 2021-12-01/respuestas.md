# (1) Algoritmos Voraces

**Datos**:

- Conocemos el valor actual $v^0_1, ..., v^0_n$ de `n` criptomonedas.
- La bola de cristal indica el valor que tendrá cada una de las criptomonedas durante los `m` dias siguientes, o sea, los valores $v^1_1, ..., v^m_1$ que tendrá la criptomoneda 1 dentro de 1 dia, ..., dentro de m dias respectivamente; los valores $v^1_2, ..., v^m_2$ que tendrá la criptomenda 2 dentro de 1 dia, ..., dentro de m dias respectivamente, etc. En general $v^j_i$ es el valor que tendrá la criptomoneda `i` dentro de `j` dias.
- Hay que calcular el maximo dinero posible a obtener al cabo de `m` dias comprando y vendiendo criptomonedas, a partir de una suma inicial de dinero `D`.
- Asumimos que siempre hay suficientes cantidad de cada criptomoneda para comprar y que no se va a cobrar comision alguna por la compra y venta.
- Asumimos que se pueden comprar fracciones de criptomonedas
- No siempre las criptomonedas incrementan su valor.

### (a)

Se va a seleccionar la criptomoneda que tenga mayor crecimiento en `j` dias.

### (b)

```LenguajeDeLaMateria
type Cripto = tuple
                valor = array[1..N] of Nat
                dias: Nat
              end tuple
```

### (c)

El algoritmo `Plata` buscara la mayor cantidad de dinero posible a obtener al cabo de `m` dias con un monto `D` de dinero.

### (d)

```LenguajeDeLaMateria
fun Plata(m: Nat, D: Nat s: Set of Cripto) ret res: Nat
    var c: Cripto
    var monto: Nat
    monto:= D
    s_aux: Set of Cripto
    s_aux:= set_copy(s)
    var cantidad: Nat

    for dia:= 0 to m-1 do
        c:= SeleccionarCripto(s_aux, dia)
        elim(s_aux, c)

        cantidad = monto / c.valor[dia]

        res:= cantidad * c.valor[dia]

        monto:= res
    od

    destroy_set(s_aux)
end fun

fun SeleccionarCripto(s: Set of Cripto, d: Nat) ret c: Cripto
    var s_aux: Set of Cripto
    s_aux:= set_copy(s)
    var i: Nat
    i = d
    var crip: Cripto

    c:= get(s_aux)
    elim(s_aux, c)
    do(!is_empty_set(s_aux)) --->
        cript:= geto(s_aux)
        elim(s_aux, cript)

        if(cript.valor(i + 1) - cript.valor[i] > c.valor[i + 1] - c.valor[i]) then
            c:= cripto
        fi
    od

    destroy_set(s_aux)
end fun
```

---

# (2)

**Datos**:

- Te vas `N` dias (con sus respectivas noches) de vacaciones.
- Para cada dia/noche `i` armaste un recorrido, donde estaras en una ciudad $C_i$.
- Contas con `M` pesos en total de presupuesto para gastar en alojamiento y para cada ciudad conoces el costo $k_i$ por noche del unico hotel que tiene.
- Cada noche `i` podes elegir entre dormir en el hotel de la ciudad, lo que te costara $k_i$, o dormir en una carpa que llevaste, que te cuesta 0.
- Tenes una tabla que indica para cada ciudad `i`, la puntuacion $p_i$ del hotel.
- Tenemos que encontrar la maxima puntuacion obtenible eligiendo en que ciudades dormiras en hotel, de manera tal que el presupuesto total gastado no supere el monto `M`.
- Si decidimos dormir en carpa en alguna ciudad, la puntuacion correspondiente para la misma sera 0.

### (a) Backtracking

La funcion va a calcular la maxima puntuacion de hoteles obtenibles yendome `i` dias de viaje con un monto `j`

La llamada principal es `Dormir(N, M)`

    Dormir(i, j) = 
        |  0 ---> si ((j <= 0) || (i = 0))
        |  Dormir(i - 1, j) ---> ((k_i > j))
        |  max(p_i + Dormir(i - 1, j - k_i), Dormir(i - 1, j)) ---> si ((j > k_i) && (i > 0))

### (b) Programacion Dinamica

La tabla va a tener dimension 2x2 ya que solamente tenemos dos parametros.

La tabla se llenara de izquierda a derecha, de abaj0 a arriba.

No creo que se pueda llenar de otra forma xd.

```LenguajeDeLaMateria
type Dias = tuple
                k_i: Nat
                p_i: Nat
            end tuple

Fun Dormir(D: array[1..n] of Dias, M: Nat) ret res: Nat
    var Lugares: array[1..n] of Dias
    var Tabla: array[0...n, 0...m] of Nat

    {- Copiamos -}
    for i:= 1 to n do
        lugares[i]:= D[i]
    od

    {- Caso base -}
    for j:= 0 to m
        Tabla[0, i]:= 0
    od
    for i:= 0 to n do
        Tabla[i, 0]:= 0
    od

    for i:= 1 to n do
        for j:= 1 to m do
            {- Caso donde no nos alcanza para pagar -}
            if(Lugares[i].k_i > j) then
                Tabla[i, j]:= Tabla[i - 1, j]
            {- Caso donde decidimos -}
            else 
                Tabla[i, j]:= max(Lugares[i].p_i + Tabla[i - 1, j - Lugares[i].k_i], Tabla[i - 1, j])
            fi
        od
    od

    res:= Tabla[n, m]
end fun
```

---

# (3) Comprensión de algoritmos

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
type List of T = tuple
                    array: array[1..n] of T
                    size: Nat
                 end tuple

fun empty() ret l: List of T
    l.size:= 0
end fun

proc addl(in e: T, in/out l: List of T)
    l.size:= l.size + 1
    l.array[size]:= e
end proc

{- PRE: !is_empty(l) -}
proc tail(in/out l: List of T)
    for i:= 0 to l.size - 1 do
        l.array[i]:= l.array[i + 1]
    od
    l.size:= l.size - 1
end proc

proc concat(in/out l: List of T, in l0: List of T)
    for i:= 0 to l0.size do
        l.array[l.size + 1]:= l0.array[i]
    od
    l.size:= l.size + l0.size
end proc

fun length(l: List of T) ret n: nat
    n:= l.size
end fun

proc drop(in/out l: List of T, in n: Nat)
    for i:= 0 to l.size - n do
        l.array[i]:= l.array[i + n]
    od
    l.size:= l.size - n
end proc
```

### (b)

si

### (c)

es de orden constante xd

### (d)

```LenguajeDeLaMateria
fun mezclar(l: List of T, l1: List of T) ret l2: List of T
    var l_aux: List of T
    var l1_aux: List of T

    l_aux:= list_copy(l)
    l1_aux:= list_copy(l1)

    for i:= 0 to n do
        if(i `mod` 2 = 0) then
            l2.array[i]:= l_aux.array[i]
        else
            l2.array[i]:= l1_aux.array[i]
        fi
    od

    destroy_list(l_aux)
    destroy_list(l1_aux)
end fun
```

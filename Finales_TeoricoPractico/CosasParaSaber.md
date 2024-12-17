# (1) Selection Sort

```
{- PRE: n>= 0 && a = A -}
proc selection_sor(in/out a: array[1..n] of T)
    var minp: Nat

    for i:= 1 to (n - 1) do
        minp:= min_pos_from(a, i);
        swap(a, i, minp)
    od
end proc
{- POS: 'a' está ordenado y es permutación de 'A' -}

{- PRE: 0 < i <= n -}
fun min_pos_from(a: array[1..n], i: Nat) ret minp: Nat
    minp:= 1

    for (j:= i + 1) to n do
        if(a[j] < a[minp]) then
            minp:= j
        fi
    od
end fun
{- POST: a[minp] es el minimo de a[i, n] -}

proc swap(in/out a: array[1...n] of T, in i, j: Nat)
    aux: T
    aux:= a[i]
    a[i]:= a[j]
    a[j]:= aux
end proc
```

![EjemploSelection_sort.png](../Imagenes/EjemploSelection_sort)

---

# (2) Insertion Sort

```
{- PRE: n >= 0 && a = A -}
proc insertion_sort(in/out a: array[1...n] of T)    
    for i:= 2 to n do
        insert(a, i)
    od
end proc
{- POST: 'a' esta ordenado y es permutacion de 'A' -}

{- PRE: 0 < i <= n && a = A -}
proc insert(in/out a: array[1..n] of T, in i: Nat)
    var j: Nat
    j:= i

    do(j > 1 && a[j] < a[j - 1]) --->
        swap(a, j - 1, j)
        j:= j - 1
    od
end proc
{- POST: a[1, i] esta ordenado && 'a' es permutacion de 'A' -}
```

---

# (4) Merge Sort

```

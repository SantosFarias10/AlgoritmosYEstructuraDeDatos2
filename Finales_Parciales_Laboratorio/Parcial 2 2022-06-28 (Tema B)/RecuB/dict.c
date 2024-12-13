#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "string.h"

struct _dict_t {
  struct _node_t *words;
  struct _node_t * definitions;
  size_t size;
};

struct _node_t {
  string elem;
  struct _node_t *next;
};

static bool invrep(dict_t d) {
  node_t word = d->words;
  node_t def = d->definitions;
  unsigned int count = 0u;

  if(d == NULL){
    return false;
  } else {
    if(dict_length(d) != d->size){
      return false;
    }

    while(word != NULL && def != NULL){
      count++;
      word = word->next;
      def = def->next;
    }

    if(count != dict_length(d)){
      return false;
    }

    if(word != NULL || def != NULL){
      return false;
    }
  }

  return true;
}

// returns the amount of nodes to skip when adding a new word
/* Devuelve la cantidad de nodos a saltar al agregar una nueva palabra, calcula la cantidad de nodos que se deben saltar al agregar una nueva palabra al diccionario. Esto puede ser útil si el diccionario está ordenado y se desea insertar la nueva palabra en la posición correcta. */
static int nodes_to_skip(dict_t dict, string word) {
  unsigned int numberToSkip = 0;  /* Inicializamos el contador de nodos a saltar */
  node_t current = dict->words; /* Apunta a la primera palabra de la lista de palabras */

  /* Recorremos la lista mientras el nodo actual no sea NULL y la palabra en el nodo actual sea menor que la nueva palabra (alfabeticamente) */
  while(current != NULL && string_compare(current->elem, word) < 0){
    numberToSkip++; /* Incrementamos el contador */
    current = current->next;  /* Avanzamos al siguiente nodo */
  }

  return numberToSkip;
}

// returns the position of the word on the list of nodes (0 being the first node)
// returns -1 if the word is not on the dict
static int find_index_of_key(dict_t dict, string word) {
  int index = 0;

  node_t aux = dict->words;

  while(aux != NULL){
    if(string_eq(aux->elem, word)){
      return index;
    } else {
      index++;
      aux = aux->next;
    }
  }

  return index;
}

dict_t dict_empty(void) {
  dict_t dict = malloc(sizeof(struct _dict_t));

  dict->words = NULL;
  dict->definitions = NULL;
  dict->size = 0u;

  assert(invrep(dict) && dict_length(dict) == 0);
}

static node_t create_node(string elem) {

    /* COMPLETAR */

}

static node_t destroy_node(node_t node) {

    /* COMPLETAR */

}

dict_t dict_add(dict_t dict, string word, string def) {

    /* COMPLETAR */

}

string dict_search(dict_t dict, string word) {

    /* COMPLETAR */

}

bool dict_exists(dict_t dict, string word) {

    /* COMPLETAR */

}

unsigned int dict_length(dict_t dict) {

    /* COMPLETAR */

}

// removes the "index" element of the "list" list of nodes
static node_t remove_on_index(node_t list, int index) {

    /* COMPLETAR */

}

dict_t dict_remove(dict_t dict, string word) {
  assert(invrep(dict));
  int index = find_index_of_key(dict, word);
  if (index != -1) {
    dict->words = remove_on_index(dict->words, index);
    dict->definitions = remove_on_index(dict->definitions, index);
    dict->size--;
  }
  assert(invrep(dict));
  return dict;
}

dict_t dict_remove_all(dict_t dict) {

    /* COMPLETAR */

}

void dict_dump(dict_t dict, FILE *file) {

    /* COMPLETAR */
    /* tip: use fprintf(file, "%s : %s\n", string_ref(word), string_ref(def)); to save to file  */

}

dict_t dict_destroy(dict_t dict) {
  dict = dict_remove_all(dict);
  free(dict);
  dict = NULL;
  return dict;
}

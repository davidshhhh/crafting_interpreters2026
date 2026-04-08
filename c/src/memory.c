#include <stdlib.h>                         // Required for malloc, realloc, and free
#include "memory.h"                         // Pulls in our own memory declarations
#include "vm.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  // 1. If the new size is zero, we are 'freeing' the memory 
  if (newSize == 0) {                       
    free(pointer);                          // Tell the OS we no longer need this block
    return NULL;                            // Return NULL to indicate the pointer is now empty
  }

  // 2. Use the standard C realloc to resize, create, or move the memory block
  void* result = realloc(pointer, newSize); 
  
  // 3. Handle 'Out of Memory' errors (The VM cannot continue if this fails)
  if (result == NULL) exit(1);              // If the OS refuses to give us RAM, crash immediately
  
  return result;                            // Return the pointer to the new/resized memory
}

static void freeObject(Obj* object) {
  switch (object->type) {
    case OBJ_STRING: {
      ObjString* string = (ObjString*)object;
      // Chapter 19 chall question - flexible array member
      // reallocate(object, sizeof(ObjString) + string->length + 1, 0);
      FREE_ARRAY(char, string->chars, string->length + 1);
      FREE(ObjString, object);
      break;
    }
  }
}

void freeObjects() {
  Obj* object = vm.objects;
  while (object != NULL) {
    Obj* next = object->next;
    freeObject(object);
    object = next;
  }
}
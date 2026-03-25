#include <stdio.h>
#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

/*

int main(int argc, const char* argv[]) {
  Chunk chunk;
  initChunk(&chunk);


  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_RETURN, 123);
  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  return 0;
}

*/



// test code for challenge question 1 :chapter 14  added line number tracking to the chunk
int main(int argc, const char* argv[]) {
  initVM();
  Chunk chunk;
  initChunk(&chunk);

  // Simple test: 5 instructions total
  // 4 on line 123, 1 on line 124
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);  // instruction 0
  writeChunk(&chunk, constant, 123);      // instruction 1
  writeChunk(&chunk, OP_CONSTANT, 123);  // instruction 2
  writeChunk(&chunk, constant, 123);      // instruction 3
  writeChunk(&chunk, OP_RETURN, 124);    // instruction 4
  writeChunk(&chunk, OP_NEGATE, 123);    // instruction 5

  constant = addConstant(&chunk, 3.4);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_ADD, 123);

  constant = addConstant(&chunk, 5.6);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_DIVIDE, 123);

  disassembleChunk(&chunk, "test chunk");
  interpret(&chunk);
  freeVM();
  
  // printf("\n=== OLD METHOD (wasteful) ===\n");
  // printf("Would store line for EVERY instruction:\n");
  // printf("Lines array: [123, 123, 123, 123, 124]\n");
  // printf("Total integers stored: 5\n");
  
  // printf("\n=== NEW METHOD (efficient) ===\n");
  // printf("Only stores when line CHANGES:\n");
  // printf("Lines array: [(offset:0, line:123), (offset:4, line:124)]\n");
  // printf("Total integers stored: %d\n", chunk.lineCount);
  
  // printf("\n=== SAVINGS ===\n");
  // printf("Old method: %d integers\n", chunk.count);
  // printf("New method: %d integers\n", chunk.lineCount);
  // printf("Space saved: %d integers (%.0f%% reduction)\n", 
  //        chunk.count - chunk.lineCount,
  //        ((float)(chunk.count - chunk.lineCount) / chunk.count) * 100);
  
  freeChunk(&chunk);
  return 0;
}

// gcc -Iinclude src/*.c -o clox && ./clox  // use this to compile and run the program
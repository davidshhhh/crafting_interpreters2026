#include <stdlib.h>
#include <stdint.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  chunk->lineCount = 0;
  chunk->lineCapacity = 0;
  initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(LineStart, chunk->lines, chunk->lineCapacity); // Challenge question 1 :chapter 14 
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}


void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code,
        oldCapacity, chunk->capacity);

  }

  chunk->code[chunk->count] = byte;
  chunk->count++;



  if (chunk->lineCount > 0 && chunk->lines[chunk->lineCount - 1].line == line) {
    return;
  }



  if (chunk->lineCapacity < chunk->lineCount + 1) {
    int oldCapacity = chunk->lineCapacity;
    chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
    chunk->lines = GROW_ARRAY(LineStart, chunk->lines,
                              oldCapacity, chunk->lineCapacity);
  }

  LineStart* lineStart = &chunk->lines[chunk->lineCount++];
  lineStart->offset = chunk->count - 1;
  lineStart->line = line;
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}


// Challenge question 1 :chapter 14  added this function to find the line number for a given instruction
int getLine(Chunk* chunk, int instruction) {    // 
  int start = 0;                         // Binary search.
  int end = chunk->lineCount - 1;        // We know it’s in the array.

  for (;;) {                               // Loop until we find the correct line.
    int mid = (start + end) / 2;           // Check if the instruction is before, at, or after the midpoint.
    LineStart* line = &chunk->lines[mid];  // If the instruction is before the midpoint, it must be in the first half.
    if (instruction < line->offset) {.     // If the instruction is after the midpoint, it must be in the second half.
      end = mid - 1;
    } else if (mid == chunk->lineCount - 1 ||
        instruction < chunk->lines[mid + 1].offset) {
      return line->line;
    } else {
      start = mid + 1;
    }
  }
}

void writeConstant(Chunk* chunk, Value value, int line) {
  int index = addConstant(chunk, value);                    // Challenge question 2 :chapter 14 added this function to write a constant with line number
  if (index < 256) {                                        // If the index fits in a single byte, emit the OP_CONSTANT instruction followed by the index.
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, (uint8_t)index, line);
  } else {                                                  // Otherwise, emit the OP_CONSTANT_LONG instruction followed by the three bytes of the index.
    writeChunk(chunk, OP_CONSTANT_LONG, line);                  // 
    writeChunk(chunk, (uint8_t)(index & 0xff), line);           // Emit the least significant byte of the index.
    writeChunk(chunk, (uint8_t)((index >> 8) & 0xff), line);    // Emit the middle byte of the index.
    writeChunk(chunk, (uint8_t)((index >> 16) & 0xff), line);   // Emit the most significant byte of the index.
  }
}
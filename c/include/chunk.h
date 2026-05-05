#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"
#include <stdint.h>

typedef enum {
  OP_CONSTANT,
  OP_NIL,
  OP_TRUE,
  OP_FALSE,
  OP_POP,
  OP_GET_LOCAL,
  OP_SET_LOCAL,
  OP_GET_LOCAL_LONG,
  OP_SET_LOCAL_LONG,
  OP_GET_GLOBAL,
  OP_DEFINE_GLOBAL,
  OP_SET_GLOBAL,
  OP_GET_UPVALUE,
  OP_SET_UPVALUE,
  OP_GET_PROPERTY,
  OP_SET_PROPERTY,
  OP_EQUAL,
  OP_GREATER,
  OP_LESS,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NOT,
  OP_NEGATE,
  OP_DUP,
  OP_CONSTANT_LONG, // <-- Challenge question 2 :chapter 14 added this new opcode for constants 
  OP_PRINT,
  OP_JUMP,
  OP_JUMP_IF_FALSE,
  OP_LOOP,
  OP_CALL,
  OP_CLOSURE,
  OP_CLOSE_UPVALUE,
  OP_RETURN,
  OP_CLASS,
} OpCode;

// Challenge question 1 :chapter 14
typedef struct {
  int offset;
  int line;
} LineStart;

// Challenge question 1 :chapter 14  added line number tracking to the chunk
typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  ValueArray constants;
  int lineCount;            // Number of entries in the lines array.
  int lineCapacity;         // Capacity of the lines array.
  LineStart* lines;         // Array of line number information.
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
void writeConstant(Chunk* chunk, Value value, int line); // Challenge question 2 :chapter 14 added this function to write a constant with line number
int addConstant(Chunk* chunk, Value value);

int getLine(Chunk* chunk, int instruction); // Challenge question 1 :chapter 14  added this function to get the line number for a given instruction

#endif
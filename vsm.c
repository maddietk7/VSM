/*
 * Program: vsm.c
 * Purpose: Simulates the VSM
 * Author:  Maddie TK
 * Date:    10/11/2021
 */

#include <stdio.h>


//Switch cases; Op-Codes in Hex
#define MAXMEM 1024
#define EOC 0x0
#define LOAD 0x1
#define STORE 0x2
#define READ 0x3
#define WRITE 0x4
#define ADD 0x5
#define SUB 0x6
#define MUL 0x7
#define DIV 0x8
#define MOD 0x9
#define NEG 0xa
#define NOP 0xb
#define JUMP 0xc
#define JNEG 0xd
#define JZERO 0xe
#define HALT 0xf


//functions
void getInput(unsigned short instructionRegister, unsigned short mem[], unsigned short instructionCounter);
unsigned short getOpCode(unsigned short inst);
unsigned short getM(unsigned short inst);
unsigned short getOperand(unsigned short inst);
void dump(short accumulator, unsigned short instructionCounter, unsigned short instructionRegister, unsigned short opCode, unsigned short operand, unsigned short mem[]);



int main(){
  short accumulator = 0;
  int m;
  unsigned short instructionCounter = 0;
  unsigned short instructionRegister;
  unsigned short opCode = 1;
  unsigned short operand = 0;
  unsigned short mem[MAXMEM];
  getInput(instructionCounter, mem, instructionRegister);
  do{
    instructionRegister = mem[instructionCounter];
    m = getM(instructionRegister);
    operand = getOperand(instructionRegister);
    opCode = getOpCode(instructionRegister);
    instructionCounter++;
    switch(opCode){

      case LOAD:
        if(m == 0){
          accumulator = mem[operand/2];
        }
        else{
          accumulator = operand;
        }
        break;

      case STORE:
        mem[operand/2] = accumulator;
        break;

      case READ:
        scanf("%hx\n", &mem[operand/2]);
        break;

      case WRITE:
        printf("%d\n", mem[operand/2]);
        break;

      case ADD:
        if(m == 0){
          accumulator = mem[operand/2] + accumulator;
        }
        else{
          accumulator = operand + accumulator;
        }
        break;

      case SUB:
        if(m == 0){
          accumulator = accumulator - mem[operand/2];
        }
        else{
          accumulator = accumulator - operand;
        }
        break;

      case MUL:
        if(m == 0){
          accumulator = accumulator * mem[operand/2];
        }
        else{
          accumulator = accumulator * operand;
        }
        break;

      case DIV:
        if(m == 0){
          accumulator = accumulator / mem[operand/2];
        }
        else{
          accumulator = accumulator / operand;
        }
        break;

      case MOD:
        if(m == 0){
          accumulator = accumulator % mem[operand/2];
        }
        else{
          accumulator = accumulator % operand;
        }
        break;

      case NEG:
        accumulator = -accumulator;
        break;

      case NOP:
        break;

      case JUMP:
        instructionCounter = operand/2;
        break;

      case JNEG:
        if(accumulator < 0){
          instructionCounter = operand/2;
        }
        break;

      case JZERO:
        if(accumulator == 0){
          instructionCounter = operand/2;
        }
        break;

      case HALT:
        break;
    }

  }while(opCode != HALT && opCode !=EOC);
   dump(accumulator, instructionCounter, instructionRegister, opCode, operand, mem);
}



/*
 * Function: getInput
 * Purpose: Stores the input values into the memory array.
 *
 * Parameters:
 *    mem: the memory array
 *
 * Returns: Void
 */
void getInput(unsigned short instructionRegister, unsigned short mem[], unsigned short instructionCounter){
     instructionCounter = 0;
     while(scanf("%hx", &instructionRegister) != EOF){
       mem[instructionCounter++] = instructionRegister;
       if (instructionRegister == EOC) break;
     }
   }//getInput



/*
 * Function: getOpCode
 * Purpose: Retreives the Op-Code of the instruction
 *
 * Parameters:
 *    inst: the current instruction
 *
 * Returns: Op-Code
 */
unsigned short getOpCode(unsigned short inst){
  inst = inst >> 12;
  return inst;
}//getOpCode



/*
 * Function: getM
 * Purpose: Retreives the M of the instruction
 *
 * Parameters:
 *    inst: the current instruction
 *
 * Returns: M
 */
unsigned short getM(unsigned short inst){
  if((inst & 0x800) == 0){
    return 0;
  }
  return 1;
}//getM



/*
 * Function: getOperand
 * Purpose: Retreives the operand of the instruction
 *
 * Parameters:
 *    inst: the current instruction
 *
 * Returns: operand
 */
unsigned short getOperand(unsigned short inst){
  inst = inst & 0x7FF;
  return inst;
}//getOperand



/*
 * Function: dump
 * Purpose: Retreives the Op-Code of the instruction
 *
 * Parameters:
 *    accumulator: accumulator register
 *    instructionCounter: next instruction to be executed
 *    instructionRegister: current instruction being executed
 *    opCode:   operation currently being preformed
 *    operand:  the memory location that the current instruction opperates
 *    mem:      memory array
 *
 * Returns: Void
 */
void dump(short accumulator, unsigned short instructionCounter, unsigned short instructionRegister, unsigned short opCode, unsigned short operand, unsigned short mem[]){
  short current;
  printf("REGISTERS:\n");
  printf("accumulator                  0x%04x\n", accumulator);
  printf("instructionCounter:          0x%04hx\n", instructionCounter);
  printf("instructionRegister:         0x%04hx\n", instructionRegister);
  printf("opCode:                      0x%1hx\n", getOpCode(instructionRegister));
  printf("operand:                     0x%04hx\n", getOperand(instructionRegister));

  printf("\nCODE:\n");
  printf("       0   1   2   3   4   5   6   7   8   9\n");
  for(int row = 0; row < 10; row++){
    printf("00%d0  ",row);
    for(int col = 0; col < 5; col++){
      current = mem[(5*row) + col];
      printf("%.2x  %.2x  ",(current >> 8) & 0xff, current & 0xff);
    }
    printf("\n");
  }

  printf("\nDATA:\n");
  printf("      0   1   2   3   4   5   6   7   8   9\n");
  for(int row = 0; row < 10; row++){
  printf("%d  ", (row*10)+1024);
  for(int col = 0; col < 5; col++){
    current = mem[512+((5*row) + col)];
    printf("%.2x  %.2x  ",(current >> 8) &0xff, current & 0xff);
  }
  printf("\n");
 }
}//dump

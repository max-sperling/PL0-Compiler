#pragma once
/**
 * \author Prof. Dr.-Ing. Arnold Beck, Max Sperling
 */

enum Opcode
{
  /*--- Stack operations -------------------------------------------------------------------------------*/
  PuValVrLocl,/*00 (short Val)                                  [Stacks value of local Variable]        */
  PuValVrMain,/*01 (short Val)                                  [Stacks value of main Variable]         */
  PuValVrGlob,/*02 (short Val, short IdxProc)                   [Stacks value of global variable]       */
  PuAdrVrLocl,/*03 (short Addr)                                 [Stacks addresse of local variable]     */
  PuAdrVrMain,/*04 (short Addr)                                 [Stacks addresse of main variable]      */
  PuAdrVrGlob,/*05 (short Addr, short IdxProc)                  [Stacks addresse of global variable]    */
  PuConst    ,/*06 (short Idx)                                  [Stacks constant]                       */
  StoreVal   ,/*07 ()                                           [Stores value at address]               */
  PutVal     ,/*08 ()                                           [Prints value from the stack to stdout] */
  GetVal     ,/*09 ()                                           [Writes value from stdin to the stack]  */
  /*--- Arithmetic operations --------------------------------------------------------------------------*/
  MinusPrefix,/*0A ()                                           [Minus prefix]                          */
  Odd        ,/*0B ()                                           [Is odd? --> 0/1]                       */
  Add        ,/*0C ()                                           [Addition]                              */
  Sub        ,/*0D ()                                           [Subtraction]                           */
  Mul        ,/*0E ()                                           [Multiplication]                        */
  Div        ,/*0F ()                                           [Division]                              */
  CmpEQ      ,/*10 ()                                           [Is = ? --> 0/1]                        */
  CmpNE      ,/*11 ()                                           [Is # ? --> 0/1]                        */
  CmpLT      ,/*12 ()                                           [Is < ? --> 0/1]                        */
  CmpGT      ,/*13 ()                                           [Is > ? --> 0/1]                        */
  CmpLE      ,/*14 ()                                           [Is <=? --> 0/1]                        */
  CmpGE      ,/*15 ()                                           [Is >=? --> 0/1]                        */
  /*--- Jump operations --------------------------------------------------------------------------------*/
  Call       ,/*16 (short IdxProc)                              [Procedure call]                        */
  EntryProc  ,/*17 (short LenCode, short IdxProc, short LenVar) [Procedure entry]                       */
  RetProc    ,/*18 ()                                           [Procedure return]                      */
  Jmp        ,/*19 (short RelAdr)                               [Jump (condition from stack)]           */
  Jnot       ,/*1A (short RelAdr)                               [Jump not (condition from stack)]       */
  /*--- Other operations -------------------------------------------------------------------------------*/
  PutStrg    ,/*1B (char[] String)                              [Prints out a string]                   */
  EndOfCode   /*1C ()                                           [End of the code]                       */
  /*----------------------------------------------------------------------------------------------------*/
};

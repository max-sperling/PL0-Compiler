#pragma once
/**
 * \author Prof. Dr.-Ing. Arnold Beck, Max Sperling
 */

enum Opcode
{
  /*--- Stack operations --------------------------------------------------------*/
  PuValVrLocl,/*00 (short Displ)  [Kellern Wert lokale  Variable]                */
  PuValVrMain,/*01 (short Displ)  [Kellern Wert Main    Variable]                */
  PuValVrGlob,/*02 (short Displ, short Proc)  [Kellern Wert globale Variable]    */
  PuAdrVrLocl,/*03 (short Displ)  [Kellern Adresse lokale  Variable]             */
  PuAdrVrMain,/*04 (short Displ)  [Kellern Adresse Main    Variable]             */
  PuAdrVrGlob,/*05 (short Displ, short Proc) [Kellern Adresse globale Variable]  */
  PuConst    ,/*06 (short Index)  [Kellern einer Konstanten]                     */
  StoreVal   ,/*07 ()             [Speichern Wert -> Adresse, beides aus Keller] */
  PutVal     ,/*08 ()             [Ausgabe eines Wertes aus Keller nach stdout]  */
  GetVal     ,/*09 ()             [Eingabe eines Wertes von  stdin -> Keller ]   */
  /*--- Arithmetic operations ---------------------------------------------------*/
  MinusPrefix,/*0A ()             [Vorzeichen -]                                 */
  Odd        ,/*0B ()             [ungerade -> 0/1]                              */
  Add        ,/*0C ()             [Addition]                                     */
  Sub        ,/*0D ()             [Subtraktion ]                                 */
  Mul        ,/*0E ()             [Multiplikation ]                              */
  Div        ,/*0F ()             [Division ]                                    */
  CmpEQ      ,/*10 ()             [Vergleich = -> 0/1]                           */
  CmpNE      ,/*11 ()             [Vergleich # -> 0/1]                           */
  CmpLT      ,/*12 ()             [Vergleich < -> 0/1]                           */
  CmpGT      ,/*13 ()             [Vergleich > -> 0/1]                           */
  CmpLE      ,/*14 ()             [Vergleich <=-> 0/1]                           */
  CmpGE      ,/*15 ()             [Vergleich >=-> 0/1]                           */
  /*--- Jump operations ---------------------------------------------------------*/
  Call       ,/*16 (short ProzNr) [Prozeduraufruf]                               */
  EntryProc  ,/*17 (short lenCode, short ProcIdx, lenVar) [Prozedureingang]      */
  RetProc    ,/*18 ()             [Prozedurruecksprung]                          */
  Jmp        ,/*19 (short RelAdr) [SPZZ innerhalb der Funktion]                  */
  Jnot       ,/*1A (short RelAdr) [SPZZ innerhalb der Funkt.,Beding.aus Keller]  */
  /*--- Other operations --------------------------------------------------------*/
  PutStrg    ,/*1B (char[])       [Gibt Zeichenkette aus]                        */
  EndOfCode   /*1C                [Signalisiert Ende des Bytecodes]              */
  /*-----------------------------------------------------------------------------*/
};

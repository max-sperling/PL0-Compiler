#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "Symbols.hpp"
#include "common/Token.hpp"

#include <string>
#include <stack>
#include <deque>

namespace pl0compiler {

class IRCodeCreator
{
public:
    void AddSymbol(void* tok);
    void AddProcedure(void* tok);
    void RetProcedure(void* tok);
    void AddVariable(void* tok);
    void AddConstant(void* tok);

    void CodeStart(void* tok);
    void ProcedureStart(void* tok);
    void ProcedureEnd(void* tok);
    void BeforeAssignment(void* tok);
    void AfterAssignment(void* tok);
    void InputNumber(void* tok);
    void OutputNumber(void* tok);
    void Negation(void* tok);
    void Addition(void* tok);
    void Subtraction(void* tok);
    void Multiplication(void* tok);
    void Division(void* tok);
    void ConstByVal(void* tok);
    void IdentByName(void* tok);
    void Odd(void* tok);
    void Equal(void* tok);
    void NotEqual(void* tok);
    void Smaller(void* tok);
    void Larger(void* tok);
    void LessOrEqual(void* tok);
    void GreaterOrEqual(void* tok);
    void Comparison(void* tok);
    void Condition(void* tok);
    void BranchEnd(void* tok);
    void While(void* tok);
    void LoopEnd(void* tok);
    void CallProcedure(void* tok);
    void OutputString(void* tok);
    void CodeEnd(void* tok);

    std::deque<char> getBinary();

private:
    enum Opcode
    {
        /*--- Stack instructions ---*/
        PuValVrLocl,    /*00 (short Displ)  [Kellern Wert lokale  Variable]             */
        PuValVrMain,    /*01 (short Displ)  [Kellern Wert Main    Variable]             */
        PuValVrGlob,    /*02 (short Displ,short Proc)  [Kellern Wert globale Variable]  */
        PuAdrVrLocl,    /*03 (short Displ)  [Kellern Adresse lokale  Variable]          */
        PuAdrVrMain,    /*04 (short Displ)  [Kellern Adresse Main    Variable]          */
        PuAdrVrGlob,    /*05 (short Displ,short Proc) [Kellern Adresse globale Variable]*/
        PuConst,        /*06 (short Index)  [Kellern einer Konstanten]                  */
        StoreVal,       /*07 ()           [Speichern Wert -> Adresse, beides aus Keller]*/
        PutVal,         /*08 ()           [Ausgabe eines Wertes aus Keller nach stdout] */
        GetVal,         /*09 ()           [Eingabe eines Wertes von  stdin -> Keller ]  */
        /*--- Arithmetic instructions ---*/
        VzMinus,        /*0A ()           [Vorzeichen -]                                */
        OpOdd,          /*0B ()           [ungerade -> 0/1]                             */
        OpAdd,          /*0C ()           [Addition]                                    */
        OpSub,          /*0D ()           [Subtraktion ]                                */
        OpMult,         /*0E ()           [Multiplikation ]                             */
        OpDiv,          /*0F ()           [Division ]                                   */
        CmpEq,          /*10 ()           [Vergleich = -> 0/1]                          */
        CmpNe,          /*11 ()           [Vergleich # -> 0/1]                          */
        CmpLt,          /*12 ()           [Vergleich < -> 0/1]                          */
        CmpGt,          /*13 ()           [Vergleich > -> 0/1]                          */
        CmpLe,          /*14 ()           [Vergleich <=-> 0/1]                          */
        CmpGe,          /*15 ()           [Vergleich >=-> 0/1]                          */
        /*--- Jump instructions ---*/
        Call,           /*16 (short ProzNr) [Prozeduraufruf]                            */
        RetProc,        /*17 ()           [Ruecksprung]                                 */
        Jmp,            /*18 (short RelAdr) [SPZZ innerhalb der Funktion]               */
        Jnot,           /*19 (short RelAdr) [SPZZ innerhalb der Funkt.,Beding.aus Keller]*/
        EntryProc,      /*1A (short lenCode,short ProcIdx,lenVar)                       */
        /*--- Additional instructions ---*/
        PutStrg,        /*1B (char[])                                                   */
        Pop,            /*1C               Entfernt einen Wert aus dem Stack            */
        Swap,           /*1D               Austausch Adressse gegen Wert                */
    };

    enum AddrOrVal
    {
        Addr,
        Val
    };

    void writeCode(Opcode code, std::vector<short> param = std::vector<short>());
    void writeString(std::string value);
    void writeInt(int value);
    void writeShortToAddr(int startAddr, short value);
    void writeIntToAddr(int startAddr, int value);

    bool pushVarByName(const common::Token* const tok, AddrOrVal addrOrVal);
    bool pushConstByName(const common::Token* const tok);
    bool pushConstByVal(const common::Token* const tok);
    bool pushProcByName(const common::Token* const tok);

    std::deque<char> m_binary;
    Symbols m_symbols;

    std::stack<int> m_procStartAddr;
    char m_cmpOp;
    std::stack<int> m_jumpStartAddr;
};

}

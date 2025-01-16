using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Antlr4.Runtime.Misc;

namespace jack_compiler.Listener
{
    internal partial class CompileListener
    {
        public override void EnterClassVarDec([NotNull] JackParserParser.ClassVarDecContext context)
        {
            currentClassVarDecType = context.type().GetText();
        }

        public override void ExitClassVarDec([NotNull] JackParserParser.ClassVarDecContext context)
        {
            symbolTable.Dump();
            currentClassVarDecType = String.Empty;
        }

        public override void EnterLastID([NotNull] JackParserParser.LastIDContext context)
        {
            symbolTable.Define(context.ID().GetText(), currentClassVarDecType, VarKind.FIELD);
        }

        public override void EnterListedID([NotNull] JackParserParser.ListedIDContext context)
        {
            symbolTable.Define(context.ID().GetText(), currentClassVarDecType, VarKind.FIELD);
        }

        string currentClassVarDecType = String.Empty;
    }
}

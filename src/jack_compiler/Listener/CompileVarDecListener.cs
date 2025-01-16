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
        public override void EnterVarDec([NotNull] JackParserParser.VarDecContext context)
        {
            var type = context.type().GetText();
            foreach (var id in context.ID())
            {
                symbolTable.Define(id.GetText(), type, VarKind.VAR);
            }
            base.EnterVarDec(context);
        }

        public override void ExitVarDec([NotNull] JackParserParser.VarDecContext context)
        {
            base.ExitVarDec(context);
            symbolTable.Dump();
        }
    }
}

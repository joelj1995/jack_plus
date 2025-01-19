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
        public override void EnterSubroutineDec([NotNull] JackParserParser.SubroutineDecContext context)
        {
            subroutineName = context.ID().GetText();
        }

        public override void EnterParameterList([NotNull] JackParserParser.ParameterListContext context)
        {
            foreach (var param in context.parameter())
            {
                var type = param.type().GetText();
                var name = param.ID().GetText();
                symbolTable.Define(name, type, VarKind.ARG);
            }
            
        }

        public override void ExitSubroutineVarDecs([NotNull] JackParserParser.SubroutineVarDecsContext context)
        {
            writer.WriteFunction($"{className}.subroutineName", symbolTable.VarCount(VarKind.VAR));
            writer.PushIndent();
        }

        public override void ExitSubroutineBody([NotNull] JackParserParser.SubroutineBodyContext context)
        {
            symbolTable.ResetLocals();
            writer.PopIndent();
            nLocals = 0;
        }

        string subroutineName = String.Empty;
    }
}

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
            var id = context.ID().GetText();
            writer.WriteFunction($"{className}.{id}", 0);
            writer.PushIndent();
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

        public override void ExitSubroutineBody([NotNull] JackParserParser.SubroutineBodyContext context)
        {
            symbolTable.ResetLocals();
            writer.PopIndent();
        }
    }
}

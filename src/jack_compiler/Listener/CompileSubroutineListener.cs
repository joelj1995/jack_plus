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
            symbolTable.Reset();
            writer.PushIndent();
        }

        public override void ExitSubroutineBody([NotNull] JackParserParser.SubroutineBodyContext context)
        {
            writer.PopIndent();
        }
    }
}

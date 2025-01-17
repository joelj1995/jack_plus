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
        public override void ExitLetStatement([NotNull] JackParserParser.LetStatementContext context)
        {
            var idx = symbolTable.IndexOf(context.ID().GetText());
            writer.WritePop(JackVMWriter.JackSegment.LOCAL, idx);
        }
    }
}

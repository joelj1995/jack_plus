using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Antlr4.Runtime.Misc;

namespace jack_compiler.Listener
{
    internal partial class CompileListener : JackParserBaseListener
    {
        public CompileListener(JackVMWriter writer, IDictionary<string, int> classArguments) 
        {
            this.writer = writer;
            this.classArguments = classArguments;
        }

        public override void EnterClass([NotNull] JackParserParser.ClassContext context)
        {
            this.className = context.ID().GetText();
        }

        public override void ExitClass([NotNull] JackParserParser.ClassContext context)
        {
            writer.Flush();
        }

        private string className = string.Empty;
        private readonly JackVMWriter writer;
        private readonly SymbolTable symbolTable = new SymbolTable();
        private int labelIdx = 0;
        private IDictionary<string, int> classArguments;
    }
}

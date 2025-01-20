using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Antlr4.Runtime.Misc;

namespace jack_compiler
{
    internal class ClassArgumentsListener : JackParserBaseListener
    {
        public ClassArgumentsListener(IDictionary<string, int> current) 
        {
            ClassArgumentNumber = current;
        }

        public IDictionary<string, int> ClassArgumentNumber { get; private set; }

        public override void EnterClass([NotNull] JackParserParser.ClassContext context)
        {
            this.className = context.ID().GetText();
        }

        public override void EnterClassVarDec([NotNull] JackParserParser.ClassVarDecContext context)
        {
            currentClassVarDecType = context.type().GetText();
            currentClassVarDecKind = context.classVarDecType().GetText();
        }

        public override void EnterLastID([NotNull] JackParserParser.LastIDContext context)
        {
            switch (currentClassVarDecKind)
            {
                case "field":
                    fieldCount++;
                    break;
                case "static":
                    break;
                default: throw new NotImplementedException(currentClassVarDecKind);
            }
        }

        public override void ExitClass([NotNull] JackParserParser.ClassContext context)
        {
            ClassArgumentNumber[className] = fieldCount;
            fieldCount = 0;
        }

        private string className = string.Empty;
        string currentClassVarDecType = String.Empty;
        string currentClassVarDecKind = String.Empty;
        int fieldCount = 0;
    }
}

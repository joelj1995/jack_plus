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
        public override void EnterTermIntConst([NotNull] JackParserParser.TermIntConstContext context)
        {
            var val = int.Parse(context.GetText());
            writer.WritePush(JackVMWriter.JackSegment.CONSANT, val);
        }

        public override void EnterTermStrConst([NotNull] JackParserParser.TermStrConstContext context)
        {
            var value = context.GetText();
            value = value.Substring(1, value.Length - 2);
            writer.WritePush(JackVMWriter.JackSegment.CONSANT, value.Length);
            writer.WriteCall("String.new", 1);
            for (int i = 0; i < value.Length; i++)
            {
                writer.WritePush(JackVMWriter.JackSegment.CONSANT, value[i]);
                writer.WriteCall("String.appendChar", 2);
            }
        }

        public override void EnterTermID([NotNull] JackParserParser.TermIDContext context)
        {
            var value = context.GetText();
            var kind = symbolTable.KindOf(value);
            var idx = symbolTable.IndexOf(value);
            switch (kind)
            {
                case VarKind.NONE:
                    
                    break;
                case VarKind.STATIC:
                    // TODO
                    break;
                case VarKind.FIELD:
                    // TODO
                    break;
                case VarKind.ARG:
                    // TODO
                    break;
                case VarKind.VAR:
                    writer.WritePush(JackVMWriter.JackSegment.LOCAL, idx);
                    break;
                default: throw new NotImplementedException();
            }
        }
    }
}

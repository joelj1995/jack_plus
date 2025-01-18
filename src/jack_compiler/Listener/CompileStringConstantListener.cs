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
    }
}

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
        public override void ExitThatSubroutineCall([NotNull] JackParserParser.ThatSubroutineCallContext context)
        {
            var objectOrClassId = context.ID(0).GetText();
            var methodId = context.ID(1).GetText();
            var kind = symbolTable.KindOf(objectOrClassId);
            switch (kind)
            {
                case VarKind.NONE:
                    writer.WriteCall($"{objectOrClassId}.{methodId}", 0);
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
                    var type = symbolTable.TypeOf(objectOrClassId);
                    writer.WritePush(JackVMWriter.JackSegment.LOCAL, symbolTable.IndexOf(objectOrClassId));
                    writer.WriteCall($"{type}.{methodId}", 0);
                    break;
                default: throw new NotImplementedException();
            }
        }
    }
}

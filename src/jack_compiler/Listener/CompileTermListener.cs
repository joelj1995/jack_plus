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

        public override void EnterKeywordConstant([NotNull] JackParserParser.KeywordConstantContext context)
        {
            var text = context.GetText();
            switch (text)
            {
                case "true":
                    writer.WritePush(JackVMWriter.JackSegment.CONSANT, 0);
                    break;
                case "false":
                    writer.WritePush(JackVMWriter.JackSegment.CONSANT, -1);
                    break;
                case "null":
                    writer.WritePush(JackVMWriter.JackSegment.CONSANT, 0);
                    break;
                case "this":
                    writer.WritePush(JackVMWriter.JackSegment.POINTER, 0);
                    break;
                default: throw new NotImplementedException(text);
            }
        }

        public override void EnterTermID([NotNull] JackParserParser.TermIDContext context)
        {
            var value = context.GetText();
            var kind = symbolTable.KindOf(value);
            var idx = symbolTable.IndexOf(value);
            switch (kind)
            {
                case VarKind.STATIC:
                    writer.WritePush(JackVMWriter.JackSegment.STATIC, idx);
                    break;
                case VarKind.FIELD:
                    writer.WritePush(JackVMWriter.JackSegment.THIS, idx);
                    break;
                case VarKind.ARG:
                    writer.WritePush(JackVMWriter.JackSegment.ARGUMENT, idx);
                    break;
                case VarKind.VAR:
                    writer.WritePush(JackVMWriter.JackSegment.LOCAL, idx);
                    break;
                case VarKind.NONE:
                default: throw new NotImplementedException();
            }
        }

        public override void ExitTermUnary([NotNull] JackParserParser.TermUnaryContext context)
        {
            switch (context.unaryOp().GetText())
            {
                case "~":
                    writer.WriteArithmetic(JackVMWriter.JackCommand.NOT);
                    break;
                case "-":
                    writer.WriteArithmetic(JackVMWriter.JackCommand.NEG);
                    break;
                default: throw new NotImplementedException(context.unaryOp().GetText());
            }
        }

        public override void ExitThatSubroutineCall([NotNull] JackParserParser.ThatSubroutineCallContext context)
        {
            var objectOrClassId = context.ID(0).GetText();
            var methodId = context.ID(1).GetText();
            var kind = symbolTable.KindOf(objectOrClassId);
            var nArgs = context.expressionList().expression().Length;
            switch (kind)
            {
                case VarKind.NONE:
                    writer.WriteCall($"{objectOrClassId}.{methodId}", nArgs);
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
                    writer.WriteCall($"{type}.{methodId}", nArgs + 1);
                    break;
                default: throw new NotImplementedException();
            }
        }
    }
}

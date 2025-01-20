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
        public override void ExitLetArrayIndex([NotNull] JackParserParser.LetArrayIndexContext context)
        {
            writer.WriteArithmetic(JackVMWriter.JackCommand.ADD);
        }

        public override void ExitLetVarStatement([NotNull] JackParserParser.LetVarStatementContext context)
        {
            var value = context.ID().GetText();
            var idx = symbolTable.IndexOf(value);
            var kind = symbolTable.KindOf(value);
            switch (kind)
            {
                case VarKind.STATIC:
                    writer.WritePop(JackVMWriter.JackSegment.STATIC, idx);
                    break;
                case VarKind.FIELD:
                    writer.WritePop(JackVMWriter.JackSegment.THIS, idx);
                    break;
                case VarKind.ARG:
                    writer.WritePop(JackVMWriter.JackSegment.ARGUMENT, idx);
                    break;
                case VarKind.VAR:
                    writer.WritePop(JackVMWriter.JackSegment.LOCAL, idx);
                    break;
                case VarKind.NONE:
                default: throw new NotImplementedException();
            }
        }

        public override void EnterLetArrayStatement([NotNull] JackParserParser.LetArrayStatementContext context)
        {
            var value = context.ID().GetText();
            var idx = symbolTable.IndexOf(value);
            var kind = symbolTable.KindOf(value);
            switch (kind)
            {
                case VarKind.STATIC:
                    writer.WritePop(JackVMWriter.JackSegment.STATIC, idx);
                    break;
                case VarKind.FIELD:
                    writer.WritePop(JackVMWriter.JackSegment.THIS, idx);
                    break;
                case VarKind.ARG:
                    writer.WritePop(JackVMWriter.JackSegment.ARGUMENT, idx);
                    break;
                case VarKind.VAR:
                    writer.WritePop(JackVMWriter.JackSegment.LOCAL, idx);
                    break;
                case VarKind.NONE:
                default: throw new NotImplementedException();
            }
        }

        public override void ExitLetArrayStatement([NotNull] JackParserParser.LetArrayStatementContext context)
        {
            writer.WritePop(JackVMWriter.JackSegment.TEMP, 0);
            writer.WritePop(JackVMWriter.JackSegment.POINTER, 1);
            writer.WritePush(JackVMWriter.JackSegment.TEMP, 0);
            writer.WritePop(JackVMWriter.JackSegment.THAT, 0);
        }

        public override void EnterIfStatement([NotNull] JackParserParser.IfStatementContext context)
        {
            
        }

        public override void ExitIfStatementExpression([NotNull] JackParserParser.IfStatementExpressionContext context)
        {
            writer.WriteArithmetic(JackVMWriter.JackCommand.NOT);
            var skipLabel = labelIdx;
            labels.Push(skipLabel);
            writer.WriteIf($"{className}_{labelIdx}");
            labelIdx++;
        }

        public override void ExitIfStatements([NotNull] JackParserParser.IfStatementsContext context)
        {
            var skipLabel = labels.Pop();
            var skipElseLabel = labelIdx;
            labels.Push(skipLabel);
            labelIdx++;
            writer.WriteGoto($"{className}_{skipElseLabel}");
            writer.WriteLabel($"{className}_{skipLabel}");
        }

        public override void ExitElseStatements([NotNull] JackParserParser.ElseStatementsContext context)
        {
            var skipElseLabel = labels.Pop();
            writer.WriteLabel($"{className}_{skipElseLabel}");
        }

        public override void EnterWhileStatement([NotNull] JackParserParser.WhileStatementContext context)
        {
            writer.WriteLabel($"{className}_{labelIdx}");
            labels.Push(labelIdx);
            labelIdx++;
        }

        public override void ExitWhileStatementExpression([NotNull] JackParserParser.WhileStatementExpressionContext context)
        {
            writer.WriteArithmetic(JackVMWriter.JackCommand.NOT);
            labels.Push(labelIdx);
            writer.WriteIf($"{className}_{labelIdx}");
            labelIdx++;
        }

        public override void ExitWhileStatement([NotNull] JackParserParser.WhileStatementContext context)
        {
            var exitLoopLabel = labels.Pop();
            var loopLabel = labels.Pop();
            writer.WriteGoto($"{className}_{loopLabel}");
            writer.WriteLabel($"{className}_{exitLoopLabel}");
            labels.Push(labelIdx);
            labelIdx++;
        }

        public override void ExitDoStatement([NotNull] JackParserParser.DoStatementContext context)
        {
            writer.WritePop(JackVMWriter.JackSegment.TEMP, 0);
        }

        public override void ExitReturnStatement([NotNull] JackParserParser.ReturnStatementContext context)
        {
            if (context.expression() == null)
            {
                writer.WritePush(JackVMWriter.JackSegment.CONSTANT, 0);
            }
            writer.WriteReturn();
        }
    }
}

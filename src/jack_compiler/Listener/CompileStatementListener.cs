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
            ifLabels.Push(new IfLabels
            {
                SkipIf = labelIdx++,
                SkipElse = labelIdx++,
            });
        }

        public override void ExitIfStatementExpression([NotNull] JackParserParser.IfStatementExpressionContext context)
        {
            var labels = ifLabels.Peek();
            writer.WriteArithmetic(JackVMWriter.JackCommand.NOT);
            writer.WriteIf($"{className}_{labels.SkipIf}");
            labelIdx++;
        }

        public override void ExitIfStatements([NotNull] JackParserParser.IfStatementsContext context)
        {
            var labels = ifLabels.Peek();
            writer.WriteGoto($"{className}_{labels.SkipElse}");
            writer.WriteLabel($"{className}_{labels.SkipIf}");
        }

        public override void ExitElseStatements([NotNull] JackParserParser.ElseStatementsContext context)
        {
            
        }

        public override void ExitIfStatement([NotNull] JackParserParser.IfStatementContext context)
        {
            var labels = ifLabels.Peek();
            writer.WriteLabel($"{className}_{labels.SkipElse}");
            ifLabels.Pop();
        }

        public override void EnterWhileStatement([NotNull] JackParserParser.WhileStatementContext context)
        {
            writer.WriteLabel($"{className}_{labelIdx}");
            whileLabels.Push(labelIdx);
            labelIdx++;
        }

        public override void ExitWhileStatementExpression([NotNull] JackParserParser.WhileStatementExpressionContext context)
        {
            writer.WriteArithmetic(JackVMWriter.JackCommand.NOT);
            whileLabels.Push(labelIdx);
            writer.WriteIf($"{className}_{labelIdx}");
            labelIdx++;
        }

        public override void ExitWhileStatement([NotNull] JackParserParser.WhileStatementContext context)
        {
            var exitLoopLabel = whileLabels.Pop();
            var loopLabel = whileLabels.Pop();
            writer.WriteGoto($"{className}_{loopLabel}");
            writer.WriteLabel($"{className}_{exitLoopLabel}");
            whileLabels.Push(labelIdx);
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

        private Stack<int> whileLabels = new Stack<int>();
        private Stack<IfLabels> ifLabels = new Stack<IfLabels>();
    }

    public record IfLabels
    {
        public int SkipIf { get; init; }
        public int SkipElse { get; init; }
    };
}

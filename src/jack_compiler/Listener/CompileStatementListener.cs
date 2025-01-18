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

        public override void EnterIfStatement([NotNull] JackParserParser.IfStatementContext context)
        {
            writer.WriteLabel($"{className}_{labelIdx}");
            labels.Push(labelIdx);
            labelIdx++;
        }

        public override void ExitIfStatement([NotNull] JackParserParser.IfStatementContext context)
        {
        }

        public override void EnterWhileStatement([NotNull] JackParserParser.WhileStatementContext context)
        {
            writer.WriteLabel($"{className}_{labelIdx}");
            labels.Push(labelIdx);
            labelIdx++;
        }

        public override void ExitWhileStatementExpression([NotNull] JackParserParser.WhileStatementExpressionContext context)
        {

            labels.Push(labelIdx);
            writer.WriteIf($"{className}_{labelIdx}");
            labelIdx++;
        }

        public override void ExitWhileStatement([NotNull] JackParserParser.WhileStatementContext context)
        {
            var exitLoopLabel = labels.Pop();
            var loolLabel = labels.Pop();
            writer.WriteIf($"{className}_{loolLabel}");
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
                writer.WritePush(JackVMWriter.JackSegment.CONSANT, 0);
            }
            writer.WriteReturn();
        }
    }
}

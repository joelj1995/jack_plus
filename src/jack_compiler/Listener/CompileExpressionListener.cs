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
        public override void ExitExpressionPart([NotNull] JackParserParser.ExpressionPartContext context)
        {
            var op = context.op().GetText();
            switch (op)
            {
                case "+":
                    writer.WriteArithmetic(JackVMWriter.JackCommand.ADD);
                    break;
                case "-":
                    writer.WriteArithmetic(JackVMWriter.JackCommand.SUB);
                    break;
                case "*":
                    writer.WriteCall("Math.multiply", 2);
                    break;
                case "/":
                    writer.WriteCall("Math.divide", 2);
                    break;
                case "&":
                    writer.WriteArithmetic(JackVMWriter.JackCommand.AND);
                    break;
                case "|":
                    writer.WriteArithmetic(JackVMWriter.JackCommand.OR);
                    break;
                case "<":
                    writer.WriteArithmetic(JackVMWriter.JackCommand.LT);
                    break;
                case ">":
                    writer.WriteArithmetic(JackVMWriter.JackCommand.GT);
                    break;
                case "=":
                    writer.WriteArithmetic(JackVMWriter.JackCommand.EQ);
                    break;
                default: throw new NotImplementedException(op);
            }
        }
    }
}

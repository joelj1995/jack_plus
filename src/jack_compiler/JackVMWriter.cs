using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Antlr4.Runtime.Atn.SemanticContext;

namespace jack_compiler
{
    internal class JackVMWriter
    {
        public enum JackSegment
        {
            CONSANT,
            ARGUMENT,
            LOCAL,
            STATIC,
            THIS,
            THAT,
            POINTER,
            TEMP
        }

        public enum JackCommand
        {
            ADD,
            SUB,
            NEG,
            EQ,
            GT,
            LT,
            AND,
            OR,
            NOT
        }

        public JackVMWriter(StreamWriter writer)
        {
            this.writer = new IndentedTextWriter(writer, "    ");
        }

        public void WritePush(JackSegment segment, int index)
        {
            string segmentName = String.Empty;
            switch (segment)
            {
                case JackSegment.CONSANT:
                    segmentName = "constant";
                    break;
                case JackSegment.ARGUMENT:
                    segmentName = "argument";
                    break;
                case JackSegment.LOCAL:
                    segmentName = "local";
                    break;
                case JackSegment.STATIC:
                    segmentName = "static";
                    break;
                case JackSegment.THIS:
                    segmentName = "this";
                    break;
                case JackSegment.THAT:
                    segmentName = "that";
                    break;
                case JackSegment.POINTER:
                    segmentName = "pointer";
                    break;
                case JackSegment.TEMP:
                    segmentName = "temp";
                    break;
            }
            writer.WriteLine($"push {segmentName} {index}");
        }

        public void WritePop(JackSegment segment, int index)
        {
            string segmentName = String.Empty;
            switch (segment)
            {
                case JackSegment.CONSANT: throw new InvalidOperationException();
                case JackSegment.ARGUMENT:
                    segmentName = "argument";
                    break;
                case JackSegment.LOCAL:
                    segmentName = "local";
                    break;
                case JackSegment.STATIC:
                    segmentName = "static";
                    break;
                case JackSegment.THIS:
                    segmentName = "this";
                    break;
                case JackSegment.THAT:
                    segmentName = "that";
                    break;
                case JackSegment.POINTER:
                    segmentName = "pointer";
                    break;
                case JackSegment.TEMP:
                    segmentName = "temp";
                    break;
            }
            writer.WriteLine($"pop {segmentName} {index}");
        }

        public void WriteArithmetic(JackCommand command)
        {
            switch (command)
            {
                case JackCommand.ADD:
                    writer.WriteLine("add");
                    break;
                case JackCommand.SUB:
                    writer.WriteLine("sub");
                    break;
                case JackCommand.NEG:
                    writer.WriteLine("neg");
                    break;
                case JackCommand.EQ:
                    writer.WriteLine("eq");
                    break;
                case JackCommand.GT:
                    writer.WriteLine("gt");
                    break;
                case JackCommand.LT:
                    writer.WriteLine("lt");
                    break;
                case JackCommand.AND:
                    writer.WriteLine("and");
                    break;
                case JackCommand.OR:
                    writer.WriteLine("or");
                    break;
                case JackCommand.NOT:
                    writer.WriteLine("not");
                    break;
                default: throw new NotImplementedException(command.ToString());
            }
        }

        public void WriteLabel(string label)
        {
            var temp = writer.Indent;
            writer.Indent = 0;
            writer.WriteLine($"label {label}");
            writer.Indent = temp;
        }

        public void WriteIf(string label)
        {
            writer.WriteLine($"if-goto {label}");
        }

        public void WriteCall(string name, int nArgs)
        {
            writer.WriteLine($"call {name} {nArgs}");
        }

        public void WriteFunction(string name, int nArgs)
        {
            writer.WriteLine($"function {name} {nArgs}");
        }

        public void WriteReturn()
        {
            writer.WriteLine("return");
        }

        public void Flush()
        {
            writer.Flush();
        }

        public void PushIndent()
        {
            writer.Indent++;
        }

        public void PopIndent()
        {
            writer.Indent--;
        }

        private readonly IndentedTextWriter writer;
    }
}

using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace jack_compiler
{
    internal class JackVMWriter
    {
        public JackVMWriter(StreamWriter writer)
        {
            this.writer = new IndentedTextWriter(writer, "    ");
        }

        public void WritePush()
        {

        }

        public void WritePop()
        {

        }

        public void WriteArithmetic()
        {

        }

        public void WriteLabel(string label)
        {

        }

        public void WriteIf(string label)
        {

        }

        public void WriteCall(string name, int nArgs)
        {

        }

        public void WriteFunction(string name, int nArgs)
        {
            writer.WriteLine($"function {name} {nArgs}");
        }

        public void WriteReturn()
        {

        }

        public void Flush()
        {
            writer.Flush();
        }

        private readonly IndentedTextWriter writer;
    }
}

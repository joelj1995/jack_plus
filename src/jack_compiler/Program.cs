using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using jack_compiler.Listener;

internal class Program
{
    private static void Main(string[] args)
    {
        if (args.Length == 0) 
        {
            Console.Error.WriteLine("Must specify a file name");
            return;
        }
        var fileStream = File.OpenRead(args[0]);
        var outFileStream = File.Open("out.vm", FileMode.Create);
        AntlrInputStream stream = new AntlrInputStream(fileStream);
        JackParserLexer lexer = new JackParserLexer(stream);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        JackParserParser parser = new JackParserParser(tokens);
        ParseTreeWalker walker = new ParseTreeWalker();
        CompileListener compiler = new CompileListener(
            new jack_compiler.JackVMWriter(new StreamWriter(outFileStream))
            {

            });
        IParseTree tree = parser.@class();
        walker.Walk(compiler, tree);
    }
}
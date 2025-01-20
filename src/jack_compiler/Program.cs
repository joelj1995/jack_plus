using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using jack_compiler;
using jack_compiler.Listener;

internal class Program
{
    private static void Main(string[] args)
    {
        if (args.Length == 0) 
        {
            Console.Error.WriteLine("Must specify a directory.");
            return;
        }
        var outFileStream = File.Open("out.vm", FileMode.Create);
        Dictionary<string, int> classArguments = new();
        classArguments["String"] = 3;
        foreach (var f in Directory.EnumerateFiles(args[0]))
        {
            if (f.EndsWith(".jack"))
            {
                var fullPath = Path.Combine(args[0], f);
                Console.WriteLine($"Processing: {fullPath}");
                var fileStream = File.OpenRead(fullPath);
                AntlrInputStream stream = new AntlrInputStream(fileStream);
                JackParserLexer lexer = new JackParserLexer(stream);
                CommonTokenStream tokens = new CommonTokenStream(lexer);
                JackParserParser parser = new JackParserParser(tokens);
                ParseTreeWalker walker = new ParseTreeWalker();
                var listener = new ClassArgumentsListener(classArguments);
                IParseTree tree = parser.@class();
                walker.Walk(listener, tree);
            }
        }
        foreach (var f in Directory.EnumerateFiles(args[0]))
        {
            if (f.EndsWith(".jack"))
            {
                var fullPath = Path.Combine(args[0], f);
                Console.WriteLine($"Processing: {fullPath}");
                var fileStream = File.OpenRead(fullPath);
                AntlrInputStream stream = new AntlrInputStream(fileStream);
                JackParserLexer lexer = new JackParserLexer(stream);
                CommonTokenStream tokens = new CommonTokenStream(lexer);
                JackParserParser parser = new JackParserParser(tokens);
                ParseTreeWalker walker = new ParseTreeWalker();
                CompileListener compiler = new CompileListener(
                    new jack_compiler.JackVMWriter(new StreamWriter(outFileStream) { }),
                    classArguments);
                IParseTree tree = parser.@class();
                walker.Walk(compiler, tree);
            }
        }
    }
}
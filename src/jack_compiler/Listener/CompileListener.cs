﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Antlr4.Runtime.Misc;

namespace jack_compiler.Listener
{
    internal class CompileListener : JackParserBaseListener
    {
        public override void EnterClass([NotNull] JackParserParser.ClassContext context)
        {
            Console.WriteLine("Got here");
        }
    }
}

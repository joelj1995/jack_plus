using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace jack_compiler
{
    internal enum VarKind
    {
        STATIC,
        FIELD,
        ARG,
        VAR,
        NONE
    }

    internal record SymbolTableEntry
    {
        public required string Name { get; init; }
        public required VarKind Kind { get; init; }
        public required string Type { get; init; }
        public required int Index { get; init; }
    }

    internal class SymbolTable
    {
        public void Reset()
        {
            entries.Clear();
        }

        public void Define(string name, string type, VarKind kind)
        {
            entries.Add(name, new SymbolTableEntry
            {
                Name = name,
                Kind = kind,
                Type = type,
                Index = VarCount(kind)
            });
        }

        public int VarCount(VarKind kind)
        {
            try
            {
                return entries.Values.Where(v => v.Kind == kind).Max(e => e.Index);
            }
            catch (InvalidOperationException)
            {
                return 0;
            }
        }

        public VarKind KindOf(string name)
        {
            SymbolTableEntry? entry = null;
            entries.TryGetValue(name, out entry);
            if (entry == null)
            {
                return VarKind.NONE;
            }
            else
            {
                return entry.Kind;
            }
        }

        public string TypeOf(string name)
        {
            return entries[name].Type;
        }

        public int IndexOf(string name)
        {
            return entries[name].Index;
        }

        public void Dump()
        {
            Console.WriteLine("Contents:");
            foreach (var entry in entries)
            {
                Console.WriteLine($"{entry.Key}\t{entry.Value.Kind}\t{entry.Value.Index}\t{entry.Value.Type}");
            }
        }

        private readonly Dictionary<string, SymbolTableEntry> entries = new();
    }
}

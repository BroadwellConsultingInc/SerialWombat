using System;
using System.IO;
using IntelHex;

namespace HexToLines
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                return;
            }
            HexData m = new HexData(args[0],false);
            m.TwoColumn(args[1]);

        }
    }
}

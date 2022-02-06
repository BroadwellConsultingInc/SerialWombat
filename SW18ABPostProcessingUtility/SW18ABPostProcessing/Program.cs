using System;
using System.IO;
using IntelHex;
namespace SW18ABPostProcessing
{
    class Program
    {
        static void Main(string[] args)
        {
            uint baseAddr = 0x4000;
            uint length = 0x20000-0x4000;

            baseAddr *= 2;
            length *= 2;
            HexData m = new HexData(args[0],true);
            byte x =(byte) m.Memory[(UInt32)0x55E00];
            m.Fill32(baseAddr, baseAddr + length, 0x00FFFFFF);
            m.Memory[(UInt32)(0x1F800 * 2)] = (byte)0x23;
            m.Memory[(UInt32)(0x1F800 * 2 + 1)] = (byte)0xCD; // Magic number indicating programmed.
            m.Memory[(UInt32)(0x1F800 * 2 + 2)] = (byte)0x00; // Magic number indicating programmed.
            UInt16 crc = m.Crc16citt(0x8000, 0x1F800*2);
           
            m.Memory[(UInt32)(0x1F804 * 2 + 1)] = (byte)(crc >> 8);
            m.Memory[(UInt32)(0x1F804 * 2 )] = (byte)(crc & 0xFF); // CRC.
            byte b = (byte)m.Memory[(UInt32)(0x1FC04 * 2)];
            b =(byte) m.Memory[(UInt32)(0x1FC04 * 2 + 1)];

            UInt32 highest =  m.HighestAddress;
            string path = Path.GetDirectoryName(args[0]);
            StreamWriter sw = new StreamWriter($"{path}\\CRCed_Full.hex");
            sw.Write(m.toHexFileString(0, highest + 1));
            sw.Close();

            m.Crop(baseAddr,baseAddr + length);

            sw = new StreamWriter($"{path}\\CRCed_App.hex");
            sw.Write(m.toHexFileString(baseAddr, baseAddr + length + 1));
            sw.Close();
            sw = new StreamWriter($"{path}\\CRCed_App_rle.c");
            sw.Write(m.toSW18BootloaderArray(baseAddr, baseAddr + length));
            sw.Close();
            Console.WriteLine(String.Format("CRC = 0x{0:X}",crc));
            Console.WriteLine(crc);

            HexData rleCheck = new HexData();
            rleCheck.loadSW18BootloaderArray($"{path}\\CRCed_App_rle.c");
            sw = new StreamWriter($"{path}\\rleCheck.hex");
            sw.Write(rleCheck.toHexFileString(baseAddr, baseAddr + length + 1));
            sw.Close();
            


        }
    }
}

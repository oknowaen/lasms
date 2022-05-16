#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cstring>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Mem
{
	static constexpr u32 MAX_MEM = 1024 * 64;
	Byte Data[MAX_MEM];

	void Initialise()
	{
		for (u32 i = 0; i < MAX_MEM; i++)
		{
			Data[i] = 0;
		}
	}

	// read 1 byte
	Byte operator[](u32 Address) const
	{
		// assert gere address is < max_mem
		return Data[Address];
	}

	// read 1 byte
	Byte& operator[](u32 Address)
	{
		// assert gere address is < max_mem
		return Data[Address];
	}
};

struct CPU
{
	Byte PC; //program counter
	Word SP; //stack pointer

	Byte A, X, Y; //registers

	void Reset(Mem& memory)
	{
		PC = 0x0000;
		SP = 0x0100;
		A = X = Y = 0;
		memory.Initialise();
	}

	Byte FetchByte(u32& Cycles, Mem& memory)
	{
		Byte Data = memory[PC];
		PC++;
		Cycles--;
		return Data;
	}

	// opcodes
	static constexpr Byte
		INS_LDA_IM = 0xA1,
		INS_LDX_IM = 0xA2,
		INS_LDY_IM = 0xA3,
		INS_PTS = 0x8B,
		INS_ADD = 0xE4,
		INS_INC = 0x5A,
		INS_END = 0xFF;

	void Execute(u32 Cycles, Mem& memory)
	{
		while (Cycles > 0)
		{
			Byte Ins = FetchByte(Cycles, memory);
			switch (Ins)
			{
			case INS_LDA_IM:
			{
				Byte Value = FetchByte(Cycles, memory);
				A = Value;
			} break;
			case INS_END:
			{
				Byte Value = FetchByte(Cycles, memory);
				exit((int)Value);
			} break;
			case INS_LDX_IM:
			{
				Byte Value = FetchByte(Cycles, memory);
				X = Value;
			} break;
			case INS_LDY_IM:
			{
				Byte Value = FetchByte(Cycles, memory);
				Y = Value;
			} break;
			case INS_PTS:
			{
				std::cout << (int)A << std::endl;
			} break;
			case INS_ADD:
			{
				A = X + Y;
			} break;
			case INS_INC:
			{
				Byte Register = FetchByte(Cycles, memory);

				if (Register == (int)0) A++;
				else if (Register == (int)1) X++;
				else if (Register == (int)2) Y++;
			} break;
			default:
			{
				printf("Instruction not handled: %d\n", Ins);
			} break;
			}
		}
	}
};

int main()
{
	Mem mem;
	CPU cpu;

	cpu.Reset(mem);

	std::cout << "What bin: ";
	std::string filename;
	std::cin >> filename;

	std::ifstream infile(filename, std::fstream::in);

	char csline[33];
	std::string sline;

	std::getline(infile, sline);

	strcpy_s(csline, sline.c_str());

	std::array<Byte, 32> byteArray;

	for (unsigned int i = 0; i < byteArray.size(); i++)
	{
		byteArray.at(i) = (Byte)csline[i];
	}

	for (u32 i = 0x0000; i < (u32)32; i++)
	{
		mem.Data[i] = byteArray.at(i);
	}

	cpu.Execute(3, mem);

	return 0;

}
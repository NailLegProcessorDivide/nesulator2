#pragma once
#include <cstdint>

namespace JCPU {
	namespace J6502 {
		class CPU6502;

		typedef void (CPU6502::* opPointer6502)();

		typedef uint8_t(CPU6502::* readfun)();
		typedef uint16_t(CPU6502::* readjmpfun)();
		typedef void (CPU6502::* writefun)(uint8_t);

		typedef uint8_t(*readmemfun)(uint16_t, void*);
		typedef void(*writememfun)(uint16_t, uint8_t, void*);

		struct AddressMode {
			readfun rf;
			writefun wf;
		};
		extern const AddressMode adrA;
		extern const AddressMode adrAbs;
		extern const AddressMode adrAbsX;
		extern const AddressMode adrAbsY;
		extern const AddressMode adrImm;
		extern const AddressMode adrImp;
		extern const AddressMode adrInd;
		extern const AddressMode adrXInd;
		extern const AddressMode adrIndY;
		extern const AddressMode adrRel;
		extern const AddressMode adrZpg;
		extern const AddressMode adrZpgX;
		extern const AddressMode adrZpgY;

		struct AddressJumpMode {
			readjmpfun rf;
		};
		extern const AddressJumpMode adrJAbs;
		extern const AddressJumpMode adrJInd;
		//using opPointer6502 = void (CPU6502::*)();

		//
		class CPU6502 {
		public:
			//CPU6502();
			CPU6502(readmemfun _readmem, writememfun _writemem, void*);
			void setReadFunc(readmemfun _readmem);
			void setWriteFunc(writememfun _writemem);
			void setMemPtr(void*);
			void step();
			void setA(uint8_t);
			void setX(uint8_t);
			void setY(uint8_t);
			void setS(uint8_t);
			void setFlags(uint8_t);
			uint8_t getA();
			uint8_t getX();
			uint8_t getY();
			uint8_t getS();
			uint8_t getFlags();

		private:
			uint8_t A;
			uint8_t X;
			uint8_t Y;
			uint8_t S;
			uint8_t FLAGS;
			uint16_t PC;
			uint8_t intTable;

			const struct
			{
				uint8_t C = 0;
				uint8_t Z = 1;
				uint8_t I = 2;
				uint8_t D = 3;
				uint8_t B = 4;
				uint8_t U = 5;
				uint8_t V = 6;
				uint8_t N = 7;
			}flagpos;

			void push(uint8_t);
			uint8_t pull();

			uint8_t(*readmem)(uint16_t, void*);
			void (*writemem)(uint16_t, uint8_t, void*);
			void* mem;
			//void (CPU6502::*opmap[256])(void);

			void interuptHandle();
		public:
			uint8_t aRead();
			void aWrite(uint8_t);

			uint8_t absRead();
			void absWrite(uint8_t);

			uint8_t absXRead();
			void absXWrite(uint8_t);

			uint8_t absYRead();
			void absYWrite(uint8_t);

			uint8_t immRead();
			void immWrite(uint8_t);

			uint8_t impRead();
			void impWrite(uint8_t);

			uint8_t indRead();
			void indWrite(uint8_t);

			uint8_t xIndRead();
			void xIndWrite(uint8_t);

			uint8_t indYRead();
			void indYWrite(uint8_t);

			uint8_t relRead();
			void relWrite(uint8_t);

			uint8_t zpgRead();
			void zpgWrite(uint8_t);

			uint8_t zpgXRead();
			void zpgXWrite(uint8_t);

			uint8_t zpgYRead();
			void zpgYWrite(uint8_t);

			uint16_t jmpAbsRead();
			uint16_t jmpIndRead();

			void lock();

			template<const AddressMode&>
			void ADC();

			template<const AddressMode&>
			void AND();

			template<const AddressMode&>
			void ASL();

			template<const AddressMode&>
			void BCC();

			template<const AddressMode&>
			void BCS();

			template<const AddressMode&>
			void BEQ();

			template<const AddressMode&>
			void BIT();

			template<const AddressMode&>
			void BMI();

			template<const AddressMode&>
			void BNE();

			template<const AddressMode&>
			void BPL();

			template<const AddressMode&>
			void BRK();

			template<const AddressMode&>
			void BVC();

			template<const AddressMode&>
			void BVS();

			template<const AddressMode&>
			void CLC();

			template<const AddressMode&>
			void CLD();

			template<const AddressMode&>
			void CLI();

			template<const AddressMode&>
			void CLV();

			template<const AddressMode&>
			void CMP();

			template<const AddressMode&>
			void CPX();

			template<const AddressMode&>
			void CPY();

			template<const AddressMode&>
			void DEC();

			template<const AddressMode&>
			void DEX();

			template<const AddressMode&>
			void DEY();

			template<const AddressMode&>
			void EOR();

			template<const AddressMode&>
			void INC();

			template<const AddressMode&>
			void INX();

			template<const AddressMode&>
			void INY();

			template<const AddressJumpMode&>
			void JMP();

			template<const AddressJumpMode&>
			void JSR();

			template<const AddressMode&>
			void LDA();

			template<const AddressMode&>
			void LDX();

			template<const AddressMode&>
			void LDY();

			template<const AddressMode&>
			void LSR();

			template<const AddressMode&>
			void NOP();

			template<const AddressMode&>
			void ORA();

			template<const AddressMode&>
			void PHA();

			template<const AddressMode&>
			void PHP();

			template<const AddressMode&>
			void PLA();

			template<const AddressMode&>
			void PLP();

			template<const AddressMode&>
			void ROL();

			template<const AddressMode&>
			void ROR();

			template<const AddressMode&>
			void RTI();

			template<const AddressMode&>
			void RTS();

			template<const AddressMode&>
			void SBC();

			template<const AddressMode&>
			void SEC();

			template<const AddressMode&>
			void SED();

			template<const AddressMode&>
			void SEI();

			template<const AddressMode&>
			void STA();

			template<const AddressMode&>
			void STX();

			template<const AddressMode&>
			void STY();

			template<const AddressMode&>
			void TAX();

			template<const AddressMode&>
			void TAY();

			template<const AddressMode&>
			void TSX();

			template<const AddressMode&>
			void TXA();

			template<const AddressMode&>
			void TXS();

			template<const AddressMode&>
			void TYA();
			//public:
			//void XXX();

		};
		extern const opPointer6502 opmap6502[256];
		extern const uint16_t NMIvec;
		extern const uint16_t BRKvec;
		extern const uint16_t RSTvec;

		extern const uint8_t NMIind;
		extern const uint8_t BRKind;
		extern const uint8_t IRQind;
		extern const uint8_t RSTind;

		//extern opPointer6502 opmap2;

	//opPointer6502 opmap[] = {};

	//                         0,                        1,    2,    3,    4,                      5,                      6,    7,                      8,                      9,                  A,
	//	CPU6502::BRK< impRead,  impWrite>, CPU6502::ORA<xIndRead, xIndWrite>, CPU6502::lock, CPU6502::lock, CPU6502::lock, CPU6502::ORA<zpgRead, zpgWrite>, CPU6502::ASL<zpgRead, zpgWrite>, CPU6502::lock, CPU6502::PHP<impRead, impWrite>, CPU6502::ORA<immRead, immWrite>, CPU6502::ASL<aRead, aWrite>
	//};
	}
}
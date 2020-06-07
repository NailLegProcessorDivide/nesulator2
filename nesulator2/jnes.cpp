#include <cstdint>
#include "jnes.h"

namespace JCPU {

	uint8_t noRead(uint16_t, void*) {
		return 0;
	}
	void noWrite(uint16_t, void*) {
	}

	namespace J6502 {
		const uint16_t NMIvec = 0xFFFA;
		const uint16_t RSTvec = 0xFFFC;
		const uint16_t BRKvec = 0xFFFE;//irq or break

		const uint8_t NMIind = 1;
		const uint8_t RSTind = 2;
		const uint8_t IRQind = 4;
		const uint8_t BRKind = 8;

		const AddressMode adrA    = { &(CPU6502::aRead   ), &(CPU6502::aWrite   ) };
		const AddressMode adrAbs  = { &(CPU6502::absRead ), &(CPU6502::absWrite ) };
		const AddressMode adrAbsX = { &(CPU6502::absXRead), &(CPU6502::absXWrite) };
		const AddressMode adrAbsY = { &(CPU6502::absYRead), &(CPU6502::absYWrite) };
		const AddressMode adrImm  = { &(CPU6502::immRead ), &(CPU6502::immWrite ) };
		const AddressMode adrImp  = { &(CPU6502::impRead ), &(CPU6502::impWrite ) };
		const AddressMode adrInd  = { &(CPU6502::indRead ), &(CPU6502::indWrite ) };
		const AddressMode adrXInd = { &(CPU6502::xIndRead), &(CPU6502::xIndWrite) };
		const AddressMode adrIndY = { &(CPU6502::indYRead), &(CPU6502::indYWrite) };
		const AddressMode adrRel  = { &(CPU6502::relRead ), &(CPU6502::relWrite ) };
		const AddressMode adrZpg  = { &(CPU6502::zpgRead ), &(CPU6502::zpgWrite ) };
		const AddressMode adrZpgX = { &(CPU6502::zpgXRead), &(CPU6502::zpgXWrite) };
		const AddressMode adrZpgY = { &(CPU6502::zpgYRead), &(CPU6502::zpgYWrite) };

		const AddressJumpMode adrJAbs = { &(CPU6502::jmpAbsRead) };
		const AddressJumpMode adrJInd = { &(CPU6502::jmpIndRead) };

		//
		const opPointer6502 opmap6502[] = {
			//                         0,                       1,                      2,               3,                       4,                        5,                        6,                7,
			//                         8,                       9,                      A,               B,                       C,                        D,                        E,                F,
				&(CPU6502::BRK< adrImp>),&(CPU6502::ORA<adrXInd>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::ORA< adrZpg>),&(CPU6502::ASL<adrZpg >),&(CPU6502::lock),//00
				&(CPU6502::PHP< adrImp>),&(CPU6502::ORA< adrImm>),&(CPU6502::ASL<  adrA>),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::ORA< adrAbs>),&(CPU6502::ASL<adrAbs >),&(CPU6502::lock),//08
				&(CPU6502::BPL< adrRel>),&(CPU6502::ORA<adrIndY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::ORA<adrZpgX>),&(CPU6502::ASL<adrZpgX>),&(CPU6502::lock),//10
				&(CPU6502::CLC< adrImp>),&(CPU6502::ORA<adrAbsY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::ORA<adrAbsX>),&(CPU6502::ASL<adrAbsX>),&(CPU6502::lock),//18
				&(CPU6502::JSR<adrJAbs>),&(CPU6502::AND<adrXInd>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::BIT< adrZpg>),&(CPU6502::AND< adrZpg>),&(CPU6502::ROL<adrZpg >),&(CPU6502::lock),//20
				&(CPU6502::PLP< adrImp>),&(CPU6502::AND< adrImm>),&(CPU6502::ROL<  adrA>),&(CPU6502::lock),&(CPU6502::BIT< adrAbs>),&(CPU6502::AND< adrAbs>),&(CPU6502::ROL<adrAbs >),&(CPU6502::lock),//28
				&(CPU6502::BMI< adrRel>),&(CPU6502::AND<adrIndY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::AND<adrZpgX>),&(CPU6502::ROL<adrZpgX>),&(CPU6502::lock),//30
				&(CPU6502::SEC< adrImp>),&(CPU6502::AND<adrAbsY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::AND<adrAbsX>),&(CPU6502::ROL<adrAbsX>),&(CPU6502::lock),//38
				&(CPU6502::RTI< adrImp>),&(CPU6502::EOR<adrXInd>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::EOR< adrZpg>),&(CPU6502::LSR<adrZpg >),&(CPU6502::lock),//40
				&(CPU6502::PHA< adrImp>),&(CPU6502::EOR< adrImm>),&(CPU6502::LSR<  adrA>),&(CPU6502::lock),&(CPU6502::JMP<adrJAbs>),&(CPU6502::EOR< adrAbs>),&(CPU6502::LSR<adrAbs >),&(CPU6502::lock),//48
				&(CPU6502::BVC< adrRel>),&(CPU6502::EOR<adrIndY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::EOR<adrZpgX>),&(CPU6502::LSR<adrZpgX>),&(CPU6502::lock),//50
				&(CPU6502::CLI< adrImp>),&(CPU6502::EOR<adrAbsY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::EOR<adrAbsX>),&(CPU6502::LSR<adrAbsX>),&(CPU6502::lock),//58
				&(CPU6502::RTS< adrImp>),&(CPU6502::ADC<adrXInd>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::ADC< adrZpg>),&(CPU6502::ROR<adrZpg >),&(CPU6502::lock),//60
				&(CPU6502::PLA< adrImp>),&(CPU6502::ADC< adrImm>),&(CPU6502::ROR<  adrA>),&(CPU6502::lock),&(CPU6502::JMP<adrJInd>),&(CPU6502::ADC< adrAbs>),&(CPU6502::ROR<adrAbs >),&(CPU6502::lock),//68
				&(CPU6502::BVS< adrRel>),&(CPU6502::ADC<adrIndY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::ADC<adrZpgX>),&(CPU6502::ROR<adrZpgX>),&(CPU6502::lock),//70
				&(CPU6502::SEI< adrImp>),&(CPU6502::ADC<adrAbsY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::ADC<adrAbsX>),&(CPU6502::ROR<adrAbsX>),&(CPU6502::lock),//78
				&(CPU6502::lock        ),&(CPU6502::STA<adrXInd>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::STY< adrZpg>),&(CPU6502::STA< adrZpg>),&(CPU6502::STX<adrZpg >),&(CPU6502::lock),//80
				&(CPU6502::DEY< adrImp>),&(CPU6502::lock        ),&(CPU6502::TXA<  adrA>),&(CPU6502::lock),&(CPU6502::STY< adrAbs>),&(CPU6502::STA< adrAbs>),&(CPU6502::STX<adrAbs >),&(CPU6502::lock),//88
				&(CPU6502::BCC< adrRel>),&(CPU6502::STA<adrIndY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::STY<adrZpgX>),&(CPU6502::STA<adrZpgX>),&(CPU6502::STX<adrZpgY>),&(CPU6502::lock),//90
				&(CPU6502::TYA< adrImp>),&(CPU6502::STA<adrAbsY>),&(CPU6502::TXS<adrImp>),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::STA<adrAbsX>),&(CPU6502::lock        ),&(CPU6502::lock),//98
				&(CPU6502::LDY< adrImm>),&(CPU6502::LDA<adrXInd>),&(CPU6502::LDX<adrImm>),&(CPU6502::lock),&(CPU6502::LDY< adrZpg>),&(CPU6502::LDA< adrZpg>),&(CPU6502::LDX<adrZpg >),&(CPU6502::lock),//A0
				&(CPU6502::TAY< adrImp>),&(CPU6502::LDA<adrXInd>),&(CPU6502::TAX<adrImp>),&(CPU6502::lock),&(CPU6502::LDY< adrAbs>),&(CPU6502::LDA< adrAbs>),&(CPU6502::LDX<adrAbs >),&(CPU6502::lock),//A8
				&(CPU6502::BCS< adrRel>),&(CPU6502::LDA<adrIndY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::LDY<adrZpgX>),&(CPU6502::LDA<adrZpgX>),&(CPU6502::LDX<adrZpgY>),&(CPU6502::lock),//B0
				&(CPU6502::CLV< adrImp>),&(CPU6502::LDA<adrAbsY>),&(CPU6502::TSX<adrImp>),&(CPU6502::lock),&(CPU6502::LDY<adrAbsX>),&(CPU6502::LDA<adrAbsX>),&(CPU6502::LDX<adrAbsY>),&(CPU6502::lock),//B8
				&(CPU6502::CPY< adrImm>),&(CPU6502::CMP<adrXInd>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::CPY< adrZpg>),&(CPU6502::CMP< adrZpg>),&(CPU6502::DEC< adrZpg>),&(CPU6502::lock),//C0
				&(CPU6502::INY< adrImp>),&(CPU6502::CMP<adrXInd>),&(CPU6502::DEX<adrImp>),&(CPU6502::lock),&(CPU6502::CPY< adrAbs>),&(CPU6502::CMP< adrAbs>),&(CPU6502::DEC< adrAbs>),&(CPU6502::lock),//C8
				&(CPU6502::BNE< adrRel>),&(CPU6502::CMP<adrIndY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::CMP<adrZpgX>),&(CPU6502::DEC<adrZpgX>),&(CPU6502::lock),//D0
				&(CPU6502::CLD< adrImp>),&(CPU6502::CMP<adrAbsY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::CMP<adrAbsX>),&(CPU6502::DEC<adrAbsX>),&(CPU6502::lock),//D8
				&(CPU6502::CPX< adrImm>),&(CPU6502::SBC<adrXInd>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::CPX< adrZpg>),&(CPU6502::SBC< adrZpg>),&(CPU6502::INC< adrZpg>),&(CPU6502::lock),//E0
				&(CPU6502::INX< adrImp>),&(CPU6502::SBC<adrXInd>),&(CPU6502::NOP<adrImp>),&(CPU6502::lock),&(CPU6502::CPX< adrAbs>),&(CPU6502::SBC< adrAbs>),&(CPU6502::INC< adrAbs>),&(CPU6502::lock),//E8
				&(CPU6502::BEQ< adrRel>),&(CPU6502::SBC<adrIndY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::SBC<adrZpgX>),&(CPU6502::INC<adrZpgX>),&(CPU6502::lock),//F0
				&(CPU6502::SED< adrImp>),&(CPU6502::SBC<adrAbsY>),&(CPU6502::lock       ),&(CPU6502::lock),&(CPU6502::lock        ),&(CPU6502::SBC<adrAbsX>),&(CPU6502::INC<adrAbsX>),&(CPU6502::lock),//F8
		};

		CPU6502::CPU6502(readmemfun _readmem, writememfun _writemem, void* _mem) : A(0), X(0), Y(0), S(0xff), PC(0), FLAGS(0), mem(_mem), intTable(2), readmem(_readmem), writemem(_writemem) {
		}

		void CPU6502::step() {
			interuptHandle();
			(this->*opmap6502[readmem(PC++, mem)])();
		}

		void CPU6502::interuptHandle() {
			if (intTable) {
				PC += 2;
				push(PC >> 8);
				push(PC & 0xff);
				push(FLAGS);
				FLAGS |= 1 << flagpos.B;
				if (intTable & BRKind) {
					PC = readmem(BRKvec, mem)<<8 + readmem(BRKvec + 1, mem);
				}
				else if (intTable & IRQind) {
					PC = readmem(BRKvec, mem)<<8 + readmem(BRKvec + 1, mem);
				}
				else if (intTable & NMIind) {
					PC = readmem(NMIvec, mem)<<8 + readmem(NMIvec + 1, mem);
				}
				else if (intTable & RSTind) {
					PC = readmem(RSTvec, mem)<<8 + readmem(RSTvec + 1, mem);
				}
			}
		}

		void CPU6502::setReadFunc(readmemfun _readmem) {
			readmem = _readmem;
		}
		void CPU6502::setWriteFunc(writememfun _writemem) {
			writemem = _writemem;
		}
		void CPU6502::setMemPtr(void* _mem) {
			mem = _mem;
		}
		void CPU6502::setA(uint8_t _A) {
			A = _A;
		}
		void CPU6502::setX(uint8_t _X) {
			X = _X;
		}
		void CPU6502::setY(uint8_t _Y){
			Y = _Y;
		}
		void CPU6502::setS(uint8_t _S) {
			S = _S;
		}
		void CPU6502::setFlags(uint8_t f) {
			FLAGS = f;
		}

		uint8_t CPU6502::getA() {
			return A;
		}
		uint8_t CPU6502::getX() {
			return X;
		}
		uint8_t CPU6502::getY() {
			return Y;
		}
		uint8_t CPU6502::getS() {
			return S;
		}
		uint8_t CPU6502::getFlags() {
			return FLAGS;
		}

		void CPU6502::push(uint8_t v) {
			writemem(S--, v, mem);
		}

		uint8_t CPU6502::pull() {
			return readmem(++S, mem);
		}

		uint8_t CPU6502::aRead() {
			return A;
		}
		void CPU6502::aWrite(uint8_t v) {
			A = v;
		}

		uint8_t CPU6502::absRead() {
			uint16_t add = readmem(PC++, mem) << 8;
			add |= readmem(PC++, mem);
			return readmem(add, mem);
		}
		void CPU6502::absWrite(uint8_t v) {
			uint16_t add = readmem(PC++, mem) << 8;
			add |= readmem(PC++, mem);
			writemem(add, v, mem);
		}

		uint8_t CPU6502::absXRead() {
			uint16_t add = readmem(PC++, mem) << 8;
			add |= readmem(PC++, mem);
			return readmem(add + X, mem);
		}
		void CPU6502::absXWrite(uint8_t v) {
			uint16_t add = readmem(PC++, mem) << 8;
			add |= readmem(PC++, mem);
			writemem(add + X, v, mem);
		}

		uint8_t CPU6502::absYRead() {
			uint16_t add = readmem(PC++, mem) << 8;
			add |= readmem(PC++, mem);
			return readmem(add + Y, mem);
		}
		void CPU6502::absYWrite(uint8_t v) {
			uint16_t add = readmem(PC++, mem) << 8;
			add |= readmem(PC++, mem);
			writemem(add + Y, v, mem);
		}

		uint8_t CPU6502::immRead() {
			return readmem(PC++, mem);
		}
		void CPU6502::immWrite(uint8_t) {
		}

		uint8_t CPU6502::impRead() {
			return 0;
		}
		void CPU6502::impWrite(uint8_t) {

		}

		uint8_t CPU6502::indRead() {
			uint16_t addadd = readmem(PC++, mem) << 8;
			addadd |= readmem(PC++, mem);
			uint16_t add = readmem(addadd++, mem) << 8;
			add |= readmem(addadd, mem);
			return readmem(add, mem);
		}
		void CPU6502::indWrite(uint8_t v) {
			uint16_t addadd = readmem(PC++, mem) << 8;
			addadd |= readmem(PC++, mem);
			uint16_t add = readmem(addadd++, mem) << 8;
			add |= readmem(addadd, mem);
			writemem(add, v, mem);
		}

		uint8_t CPU6502::xIndRead() {
			uint16_t addadd = readmem(PC++, mem) << 8;
			addadd |= (uint8_t)(readmem(PC++, mem) + X);
			uint16_t add = readmem(addadd, mem) << 8;
			add |= readmem(addadd, mem);
			return readmem(add, mem);
		}
		void CPU6502::xIndWrite(uint8_t v) {
			uint16_t addadd = readmem(PC++, mem) << 8;
			addadd |= (uint8_t)(readmem(PC++, mem) + X);
			uint16_t add = readmem(addadd, mem) << 8;
			add |= readmem(addadd, mem);
			writemem(add, v, mem);
		}

		uint8_t CPU6502::indYRead() {
			uint16_t addadd = readmem(PC++, mem) << 8;
			addadd |= readmem(PC++, mem);
			uint16_t add = readmem(addadd, mem) << 8;
			add |= (uint8_t)(readmem(addadd, mem) + Y);
			return readmem(add, mem);
		}
		void CPU6502::indYWrite(uint8_t v) {
			uint16_t addadd = readmem(PC++, mem) << 8;
			addadd |= readmem(PC++, mem);
			uint16_t add = readmem(addadd, mem) << 8;
			add |= (uint8_t)(readmem(addadd, mem) + Y);
			writemem(add, v, mem);
		}

		uint8_t CPU6502::relRead() {
			return readmem(PC++, mem);
		}
		void CPU6502::relWrite(uint8_t) {

		}

		uint8_t CPU6502::zpgRead() {
			return readmem(readmem(PC++, mem), mem);
		}
		void CPU6502::zpgWrite(uint8_t v) {
			writemem(readmem(PC++, mem), v, mem);
		}

		uint8_t CPU6502::zpgXRead() {
			return readmem((uint8_t)(readmem(PC++, mem) + X), mem);
		}
		void CPU6502::zpgXWrite(uint8_t v) {
			writemem((uint8_t)(readmem(PC++, mem) + X), v, mem);
		}

		uint8_t CPU6502::zpgYRead() {
			return readmem((uint8_t)(readmem(PC++, mem) + Y), mem);
		}
		void CPU6502::zpgYWrite(uint8_t v) {
			writemem((uint8_t)(readmem(PC++, mem) + Y), v, mem);
		}


		uint16_t CPU6502::jmpAbsRead() {
			uint16_t addadd = readmem(PC++, mem) << 8;
			addadd |= readmem(PC++, mem);
			return addadd;
		}
		uint16_t CPU6502::jmpIndRead() {
			uint16_t addadd = readmem(PC++, mem) << 8;
			addadd |= readmem(PC++, mem);
			uint16_t add = readmem(addadd, mem) << 8;
			add |= (uint8_t)(readmem(addadd, mem));
			return add;

		}

		template<const AddressMode& am>
		void CPU6502::ADC() {
			uint16_t new_A = A + (this->*am.rf)() + (FLAGS >> flagpos.C) & 1;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z | 1 << flagpos.C | 1 << flagpos.V);
			if (new_A & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (new_A & 0x80) {
				FLAGS |= 1 << flagpos.V;
			}
			if (new_A == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
			if (new_A & 0x100) {
				FLAGS |= 1 << flagpos.C;
			}
			A = new_A;
		}

		template<const AddressMode& am>
		void CPU6502::AND() {
			A &= (this->*am.rf)();
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if (A & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (A == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::ASL() {
			uint16_t val = (this->*am.rf)() << 1;
			(this->*am.wf)(val);
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z | 1 << flagpos.C);
			if (val & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (val == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
			if (val & 0x100) {
				FLAGS |= 1 << flagpos.C;
			}
		}

		template<const AddressMode& am>
		void CPU6502::BCC() {
			uint8_t offset = (this->*am.rf)();
			if ((FLAGS & 1 << flagpos.C) == 0) {
				PC += offset;
			}
		}
		template<const AddressMode& am>
		void CPU6502::BCS() {
			uint8_t offset = (this->*am.rf)();
			if ((FLAGS & 1 << flagpos.C) != 0) {
				PC += offset;
			}
		}

		template<const AddressMode& am>
		void CPU6502::BEQ() {
			uint8_t offset = (this->*am.rf)();
			if ((FLAGS & 1 << flagpos.Z) != 0) {
				PC += offset;
			}
		}

		template<const AddressMode& am>
		void CPU6502::BIT() {
			uint8_t val = (this->*am.rf)() & A;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z | 1 << flagpos.V);
			if (val & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (val == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
			if (val & 0x40) {
				FLAGS |= 1 << flagpos.V;
			}
		}

		template<const AddressMode& am>
		void CPU6502::BMI() {
			uint8_t offset = (this->*am.rf)();
			if ((FLAGS & 1 << flagpos.N) != 0) {
				PC += offset;
			}
		}

		template<const AddressMode& am>
		void CPU6502::BNE() {

			uint8_t offset = (this->*am.rf)();
			if ((FLAGS & 1 << flagpos.Z) == 0) {
				PC += offset;
			}
		}

		template<const AddressMode& am>
		void CPU6502::BPL() {
			uint8_t offset = (this->*am.rf)();
			if ((FLAGS & 1 << flagpos.N) == 0) {
				PC += offset;
			}
		}

		template<const AddressMode&>
		void CPU6502::BRK() {
			intTable |= BRKind;
		}

		template<const AddressMode& am>
		void CPU6502::BVC() {
			uint8_t offset = (this->*am.rf)();
			if ((FLAGS & 1 << flagpos.V) == 0) {
				PC += offset;
			}
		}

		template<const AddressMode& am>
		void CPU6502::BVS() {
			uint8_t offset = (this->*am.rf)();
			if ((FLAGS & 1 << flagpos.V) != 0) {
				PC += offset;
			}
		}

		template<const AddressMode& am>
		void CPU6502::CLC() {
			FLAGS &= ~(1 << flagpos.C);
		}

		template<const AddressMode& am>
		void CPU6502::CLD() {
			FLAGS &= ~(1 << flagpos.D);

		}

		template<const AddressMode& am>
		void CPU6502::CLI() {
			FLAGS &= ~(1 << flagpos.I);
		}

		template<const AddressMode& am>
		void CPU6502::CLV() {
			FLAGS &= ~(1 << flagpos.V);
		}

		template<const AddressMode& am>
		void CPU6502::CMP() {
			uint16_t val = A - (this->*am.rf)();
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z | 1 << flagpos.C);
			if (val & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (val == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
			if (val & 0x100) {
				FLAGS |= 1 << flagpos.C;
			}
		}

		template<const AddressMode& am>
		void CPU6502::CPX() {
			uint16_t val = X - (this->*am.rf)();
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z | 1 << flagpos.C);
			if (val & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (val == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
			if (val & 0x100) {
				FLAGS |= 1 << flagpos.C;
			}
		}

		template<const AddressMode& am>
		void CPU6502::CPY() {
			uint16_t val = Y - (this->*am.rf)();
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z | 1 << flagpos.C);
			if (val & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (val == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
			if (val & 0x100) {
				FLAGS |= 1 << flagpos.C;
			}
		}

		template<const AddressMode& am>
		void CPU6502::DEC() {
			uint8_t val = (this->*am.rf)() - 1;
			(this->*am.wf)(val);
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if (val & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (val == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::DEX() {
			X--;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if (X & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (X == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::DEY() {
			Y--;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if (Y & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (Y == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::EOR() {
			A ^= (this->*am.rf)();
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if (A & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (A == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::INC() {
			uint8_t val = (this->*am.rf)() + 1;
			(this->*am.wf)(val);
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if (val & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (val == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::INX() {
			X++;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if (X & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (X == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::INY() {
			Y++;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if (Y & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (Y == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressJumpMode& am>
		void CPU6502::JMP() {
			PC = (this->*am.rf)();
		}

		template<const AddressJumpMode& am>
		void CPU6502::JSR() {
			uint16_t add = (this->*am.rf)();
			PC += 2;
			push(PC >> 8);
			push(PC & 0xff);
			PC = add;
		}

		template<const AddressMode& am>
		void CPU6502::LDA() {
			A = (this->*am.rf)();
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if (A & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (A == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::LDX() {
			X = (this->*am.rf)();
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if (X & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (X == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::LDY() {
			Y = (this->*am.rf)();
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if (Y & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (Y == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::LSR() {
			uint8_t val = (this->*am.rf)();//val is old val not new val so flags are easier
			(this->*am.wf)(val >> 1);
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z | 1 << flagpos.C);
			//N gets zeroed
			if ((val & 0xFD) == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
			if ((val & 0x1) != 0) {
				FLAGS |= 1 << flagpos.C;
			}
		}

		template<const AddressMode& am>
		void CPU6502::NOP() {

		}

		template<const AddressMode& am>
		void CPU6502::ORA() {
			A |= (this->*am.rf)();
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if (A & 0x80) {
				FLAGS |= 1 << flagpos.N;
			}
			if (A == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::PHA() {
			push(A);
		}

		template<const AddressMode& am>
		void CPU6502::PHP() {
			push(FLAGS);
		}

		template<const AddressMode& am>
		void CPU6502::PLA() {
			A = pull();
		}

		template<const AddressMode& am>
		void CPU6502::PLP() {
			FLAGS = pull();
		}

		template<const AddressMode& am>
		void CPU6502::ROL() {
			uint16_t val = (this->*am.rf)() << 1 | (FLAGS >> flagpos.C) & 1;
			(this->*am.wf)(val);
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z | 1 << flagpos.C);
			if ((val & 0x80) != 0) {
				FLAGS |= 1 << flagpos.N;
			}
			if (val == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
			if ((val & 0x100) != 0) {
				FLAGS |= 1 << flagpos.C;
			}
		}

		template<const AddressMode& am>
		void CPU6502::ROR() {
			uint16_t val = (this->*am.rf)();
			(this->*am.wf)((val >> 1) | ((FLAGS << 8) - flagpos.C) & 1);
			FLAGS &= ~(1 << flagpos.N);
			if ((FLAGS & (1 << flagpos.C)) != 0) {
				FLAGS |= 1 << flagpos.N;
			}
			FLAGS &= ~((1 << flagpos.Z) | (1 << flagpos.C));
			if (((val & 0xFD) == 0) && ((FLAGS & (1 << flagpos.N)) == 0)) {
				FLAGS |= 1 << flagpos.Z;
			}
			if ((val & 0x1) != 0) {
				FLAGS |= 1 << flagpos.C;
			}
		}

		template<const AddressMode& am>
		void CPU6502::RTI() {
			FLAGS = pull();
			PC = 0;
			PC |= pull();
			PC |= pull() << 8;
		}

		template<const AddressMode& am>
		void CPU6502::RTS() {
			PC = 0;
			PC |= pull();
			PC |= pull() << 8;
		}

		template<const AddressMode& am>
		void CPU6502::SBC() {
			uint16_t val = A - (this->*am.rf)() - (FLAGS >> flagpos.C) & 1;
			A = val;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z | 1 << flagpos.C | 1 << flagpos.V);
			if ((val & 0x80) != 0) {
				FLAGS |= 1 << flagpos.N;
			}
			if ((val & 0x80) != 0) {
				FLAGS |= 1 << flagpos.V;
			}
			if (val == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
			if ((val & 0x100) != 0) {
				FLAGS |= 1 << flagpos.C;
			}
		}

		template<const AddressMode& am>
		void CPU6502::SEC() {
			FLAGS |= 1 << flagpos.C;
		}

		template<const AddressMode& am>
		void CPU6502::SED() {
			FLAGS |= 1 << flagpos.D;
		}

		template<const AddressMode& am>
		void CPU6502::SEI() {
			FLAGS |= 1 << flagpos.I;
		}

		template<const AddressMode& am>
		void CPU6502::STA() {
			(this->*am.wf)(A);
		}

		template<const AddressMode& am>
		void CPU6502::STX() {
			(this->*am.wf)(X);
		}

		template<const AddressMode& am>
		void CPU6502::STY() {

			(this->*am.wf)(Y);
		}

		template<const AddressMode& am>
		void CPU6502::TAX() {
			X = A;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if ((A & 0x80) != 0) {
				FLAGS |= 1 << flagpos.N;
			}
			if (A == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::TAY() {
			Y = A;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if ((A & 0x80) != 0) {
				FLAGS |= 1 << flagpos.N;
			}
			if (A == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::TSX() {
			X = S;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if ((X & 0x80) != 0) {
				FLAGS |= 1 << flagpos.N;
			}
			if (X == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::TXA() {

			A = X;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if ((X & 0x80) != 0) {
				FLAGS |= 1 << flagpos.N;
			}
			if (X == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::TXS() {
			S = X;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if ((X & 0x80) != 0) {
				FLAGS |= 1 << flagpos.N;
			}
			if (X == 0) {
				FLAGS |= 1 << flagpos.Z;
			}
		}

		template<const AddressMode& am>
		void CPU6502::TYA() {
			A = Y;
			FLAGS &= ~(1 << flagpos.N | 1 << flagpos.Z);
			if ((Y & 0x80) != 0) {
			FLAGS |= 1 << flagpos.N;
		}
		if (Y == 0) {
			FLAGS |= 1 << flagpos.Z;
		}
		}

		void CPU6502::lock() {

		}
	}
}
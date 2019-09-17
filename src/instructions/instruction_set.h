#pragma once
#ifndef INSTRUCTION_INCLUDE_H
#define INSTRUCTION_INCLUDE_H

#include "aritmetic/adc.h"
#include "aritmetic/add.h"
#include "aritmetic/and.h"
#include "aritmetic/ccf.h"
#include "aritmetic/cp.h"
#include "aritmetic/cpl.h"
#include "aritmetic/daa.h"
#include "aritmetic/dec.h"
#include "aritmetic/inc.h"
#include "aritmetic/or.h"
#include "aritmetic/sbc.h"
#include "aritmetic/scf.h"
#include "aritmetic/sub.h"
#include "aritmetic/xor.h"

#include "branch/call.h"
#include "branch/jp.h"
#include "branch/jr.h"
#include "branch/ret.h"
#include "branch/reti.h"
#include "branch/rst.h"

#include "misc/di.h"
#include "misc/ei.h"
#include "misc/halt.h"
#include "misc/nop.h"
#include "misc/rla.h"
#include "misc/rlca.h"
#include "misc/rra.h"
#include "misc/rrca.h"
#include "misc/stop.h"

#include "transfer/ld.h"
#include "transfer/ldh.h"
#include "transfer/pop.h"
#include "transfer/push.h"

#include "instruction_group_prefix.h"

class InstructionSet
{
    public:
        InstructionSet()
        {  
            Adc adc;
            Add addInst;
            And andInst;
            Ccf ccf;
            Cp cp;
            Cpl cpl;
            Daa daa;
            Dec dec;
            Inc inc;
            Or or;
            Sbc sbc;
            Scf scf;
            Sub sub;
            Xor xor;

            add(adc.group);
            add(addInst.group);
            add(andInst.group);
            add(ccf.group);
            add(cp.group);
            add(cpl.group);
            add(daa.group);
            add(dec.group);
            add(inc.group);
            add(or.group);
            add(sbc.group);
            add(scf.group);
            add(sub.group);
            add(xor.group);

            Call call;
            Jp jp;
            Jr jr;
            Ret ret;
            Reti reti;
            Rst rst;

            add(call.group);
            add(jp.group);
            add(jr.group);
            add(ret.group);
            add(reti.group);
            add(rst.group);

            Di di;         
            Ei ei;  
            Halt halt; 
            Nop nop;
            Rla rla;
            Rlca rlca;
            Rra rra;
            Rrca rrca;
            Stop stop;  

            add(di.group);
            add(ei.group);
            add(halt.group);
            add(nop.group);
            add(rla.group);
            add(rlca.group);
            add(rra.group);
            add(rrca.group);
            add(stop.group);

            Ld ld;
            Ldh ldh;
            Pop pop;
            Push push;

            add(ld.group);
            add(ldh.group);
            add(pop.group);
            add(push.group);

            add(instructionGroupPrefix.group);
        }

        InstructionGroupPrefix instructionGroupPrefix;
        std::map<unsigned char, Instruction> set;       

    private:
        void add(std::map<unsigned char, Instruction> instructionGroup)
        {
            set.insert(instructionGroup.begin(), instructionGroup.end());
        }
};

#endif // INSTRUCTION_INCLUDE_H
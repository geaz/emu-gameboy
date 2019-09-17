#pragma once
#ifndef INSTRUCTION_INCLUDE_H
#define INSTRUCTION_INCLUDE_H

#include "aritmetic/add.h"
#include "aritmetic/sub.h"
#include "aritmetic/and.h"
#include "aritmetic/or.h"
#include "aritmetic/inc.h"
#include "aritmetic/dec.h"
#include "aritmetic/daa.h"
#include "aritmetic/scf.h"
#include "aritmetic/adc.h"
#include "aritmetic/sbc.h"
#include "aritmetic/xor.h"
#include "aritmetic/cp.h"
#include "branch/rst.h"
#include "branch/ret.h"
#include "branch/jp.h"
#include "branch/jr.h"
#include "branch/call.h"
#include "transfer/ld.h"
#include "transfer/push.h"
#include "transfer/pop.h"
#include "misc/nop.h"
#include "misc/stop.h"
#include "misc/halt.h"
#include "misc/ei.h"
#include "misc/di.h"
#include "instruction_group_prefix.h"

class InstructionSet
{
    public:
        InstructionSet()
        {  
            Add addInst;
            Sub sub;
            And andInst;
            Or or;
            Inc inc;
            Dec dec;
            Daa daa;
            Scf scf;
            Adc adc;
            Sbc sbc;
            Xor xor;
            Cp cp;
            add(addInst.group);
            add(sub.group);
            add(andInst.group);
            add(or.group);
            add(inc.group);
            add(dec.group);
            add(daa.group);
            add(scf.group);
            add(adc.group);
            add(sbc.group);
            add(xor.group);
            add(cp.group);

            Rst rst;
            Ret ret;
            Jp jp;
            Jr jr;
            Call call;
            add(rst.group);
            add(ret.group);
            add(jp.group);
            add(jr.group);
            add(call.group);

            Ld ld;
            Pop pop;
            Push push;
            add(ld.group);
            add(pop.group);
            add(push.group);

            Nop nop;
            Stop stop;  
            Halt halt;     
            Ei ei;
            Di di;       
            add(nop.group);
            add(stop.group);
            add(halt.group);
            add(ei.group);
            add(di.group);

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
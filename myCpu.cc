// Copyright 2009-2018 NTESS. Under the terms
// of Contract DE-NA0003525 with NTESS, the U.S.
// Government retains certain rights in this software.
// 
// Copyright (c) 2009-2018, NTESS
// All rights reserved.
// 
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.
#include <sst/core/sst_config.h>
#include "myCpu.h"
#include "iostream"







myCpu::myCpu( SST::ComponentId_t id, SST::Params& params ) :
	SST::Component(id){

	output.init("Simple InternoCPU -" + getName() + "-> ", 1, 0, SST::Output::STDOUT);
	printFreq  = params.find<SST::Cycle_t>("printFrequency", 5);
	maxRepeats = params.find<SST::Cycle_t>("repeats", 10);
	std::string temp  = params.find<std::string>("filepath","./mcpat/ProcessorDescriptionFiles/Xeon.xml");
	fb = new char[temp.size()+1];
	std::copy(temp.begin(), temp.end(), fb);
	fb[temp.size()]='\0';
    	registerClock("100MHz", new SST::Clock::Handler<myCpu>(this, &myCpu::clockTick));

    	registerAsPrimaryComponent();
    	primaryComponentDoNotEndSim();
}

myCpu::~myCpu() {
	
}

void myCpu::setup() {
	output.verbose(CALL_INFO, 1, 0, "Cpu is being setup with 1 cores and 4 registers and 100Mhz frequency.\n");
}

void myCpu::finish() {
	output.verbose(CALL_INFO, 1, 0, "Cpu is being shuting down.......\n");
}

bool myCpu::clockTick( SST::Cycle_t currentCycle ) {

	if( currentCycle % printFreq == 0 ) {
	
        std::cout<<"i am doing work \t Repeat cycle:"<<repeats<<std::endl;
		std::cout<<"McPAT is going to configure with the XML given\n";
	
	}

	repeats++;

	if( repeats > maxRepeats ) {
		primaryComponentOKToEndSim();
		return true;
	} else {
		return false;
	}
}


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

#ifndef _CPU_H
#define _CPU_H

#include <sst/core/component.h>
#include <sst/core/elementinfo.h>
#include <iostream>

class myCpu : public SST::Component {

public:
	myCpu( SST::ComponentId_t id, SST::Params& params );
	~myCpu();

	void setup();
	void finish();

	bool clockTick( SST::Cycle_t currentCycle );

	SST_ELI_REGISTER_COMPONENT(
		myCpu,
		"mcpu",
		"InternoCpu",
		SST_ELI_ELEMENT_VERSION( 1, 0, 0 ),
		"My cpu",
		COMPONENT_CATEGORY_PROCESSOR
	)

	SST_ELI_DOCUMENT_PARAMS(
		{ "printFrequency", "How frequently to print a message from the component", "5" },
		{ "repeats", "Number of repetitions to make", "10" },
		{ "filepath","filepath","./mcpat/ProcessorDescriptionFiles/Xeon.xml"}
	)

private:
	SST::Output output;
	SST::Cycle_t maxRepeats;
	SST::Cycle_t repeats;
	SST::Cycle_t printFreq;
	char * fb;

};


#endif


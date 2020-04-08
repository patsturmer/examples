/** Generated by YAKINDU Statechart Tools code generator. */
/* Implements a standard statechart trace handler which adapts to the
 * YET tracing library.
 */


#include "TictocTracer.h"
#include "TictocMeta.h"

#include <string.h>
#include <stdlib.h>


static sc_string default_scope_name = "tictoc";


static yet_value_serializer feature_value_serializer[] = {
	yet_serialize_void,
	yet_serialize_void,
	yet_serialize_void,
	yet_serialize_void,
	yet_serialize_sc_integer,
	yet_serialize_sc_integer,
	yet_serialize_sc_integer,
	yet_serialize_sc_boolean,
	yet_serialize_sc_integer,
	yet_serialize_sc_real
};

static char* featureName(sc_integer featureId)
{
	return TictocMeta_feature_names[featureId];
}

static char* featureValue(sc_integer featureId, const void* valuePtr, char* buf)
{
	return (feature_value_serializer[featureId])(valuePtr, buf);
}

static char* stateName(sc_integer stateId)
{
	return TictocMeta_state_names[stateId];
}

static uint8_t dispatchMessage(yet_scope *scope, yet_message * msg, char *fqn);

void tictoc_init_sc_tracer(yet_sc_tracer *tracer, Tictoc* machine)
{
	if (tracer != sc_null) {
		yet_init_sc_tracer(tracer, machine, dispatchMessage);

		tracer->scope.name = default_scope_name;
		tracer->traceinfoProvider.featureName = featureName;
		tracer->traceinfoProvider.featureValue = featureValue;
		tracer->traceinfoProvider.stateName = stateName;
		
		machine->trace_handler = &(tracer->traceEventHandler);
		
	}
}


// Implementation of yet_handler callback function. Handles incoming stimuli and call appropriate state machine function.
static uint8_t dispatchMessage(yet_scope *scope, yet_message * msg, char *fqn)
{
	yet_sc_tracer* tracer = scope->instance;
//	TictocTracer* tracer = scope->instance;
	char* member;
	member = fqn;
	
	if(strcmp(member, "toggle") == 0) {
		// Skip one message; this should not be re-raised on host
		tracer->skip_raised_in_event++; // TODO: this is not optimal check if we can get rid of it
		tictocIface_raise_toggle(tracer->machine);
		return 0;
	}
	if(strcmp(member, "count") == 0) {
		sc_integer converted = atoi(msg->value);
		tictocIface_set_count(tracer->machine, converted);
		return 0;
	}
	if(strcmp(member, "delay") == 0) {
		sc_integer converted = atoi(msg->value);
		tictocIface_set_delay(tracer->machine, converted);
		return 0;
	}
	if(strcmp(member, "x") == 0) {
		sc_integer converted = atoi(msg->value);
		tictocIface_set_x(tracer->machine, converted);
		return 0;
	}
	if(strcmp(member, "b") == 0) {
		sc_boolean converted = (msg->value[0] == 't');
		tictocIface_set_b(tracer->machine, converted);
		return 0;
	}
	if(strcmp(member, "y") == 0) {
		sc_integer converted = atoi(msg->value);
		tictocIfaceFoo_set_y(tracer->machine, converted);
		return 0;
	}
	
	
	return -2;
}


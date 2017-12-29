#include "MenuFlow.h"

state_t currentState = INITIAL;

state_t getCurrentState() {
	return currentState;
}

int menuHandler(event_t *evt) {
	switch (currentState) {
		case INITIAL: {
			if(evt->type == GO_ADD)
				currentState = ADD;
			else if(evt->type == GO_REMOVE)
				currentState = REMOVE;
			else if(evt->type == GO_EDIT)
				currentState = EDIT;
			else if(evt->type == GO_WATCH)
				currentState = WATCH;
			else if(evt->type == GO_BACK)
				currentState = DONE;
			else if(evt->type == GO_SERVICES)
				currentState = SERVICES;
			else
				return 0;

			break;
		}
		case ADD: {
			if(evt->type == GO_BACK)
				currentState = INITIAL;
			else
				return 0;

			break;
		}
		case REMOVE: {
			if(evt->type == GO_BACK)
				currentState = INITIAL;
			else
				return 0;

			break;
		}
		case EDIT: {
			if(evt->type == GO_BACK)
				currentState = INITIAL;
			else
				return 0;

			break;
		}
		case WATCH: {
			if(evt->type == GO_BACK)
				currentState = INITIAL;
			else
				return 0;

			break;
		}
		case SERVICES: {
			if(evt->type == GO_BACK)
				currentState = INITIAL;
			else
				return 0;

			break;
		}
		case DONE:
			break;
	}

	return 1;
}

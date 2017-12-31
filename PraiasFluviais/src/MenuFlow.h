
#ifndef MENUFLOW_H_
#define MENUFLOW_H_

/**
 *  @file MenuFlow.h
 */

/** @fn state_t getCurrentState()
 *  @brief Gets the current state of the state machine.
 *  @return Current state of the state machine
 */

/** @fn int menuHandler(event_t *evt)
 *  @brief Handles the events received by the state machine.
 *  @return Returns 1 if it handled the event successfully and 0 otherwise.
 */

/** @brief Enumeration with the possible states of the state machine. */
typedef enum {
	INITIAL,	/**< Initial state. */
	ADD,		/**< Add state. */
	REMOVE,		/**< Remove state. */
	EDIT,		/**< Edit state. */
	SERVICES,	/**< Services state */
	SEARCH,		/**< Search state */
	DONE		/**< Final state */
} state_t;

/** @brief Enumeration with the possible types of the events that the state machine receives. */
typedef enum {
	GO_BACK,	/**< Go back. */
	GO_ADD,		/**< Go add. */
	GO_REMOVE,	/**< Go remove. */
	GO_EDIT,	/**< Go edit. */
	GO_SERVICES,/**< Go services. */
	GO_SEARCH	/**< Go search. */
} ev_type_t;

/**
 * 	@struct event_t
 *  @brief Struct of an event.
 */
typedef struct {

	/** @brief Type of the event. */
	ev_type_t type;
} event_t;

state_t getCurrentState();
int menuHandler(event_t *evt);

#endif /* MENUFLOW_H_ */

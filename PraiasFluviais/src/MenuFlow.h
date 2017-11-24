
#ifndef MENUFLOW_H_
#define MENUFLOW_H_

typedef enum {INITIAL, ADD, REMOVE, EDIT, WATCH, DONE} state_t;
typedef enum {GO_BACK, GO_ADD, GO_REMOVE, GO_EDIT, GO_WATCH} ev_type_t;

/**
 * @brief variable representing a State Machine's event
 */
typedef struct {
	ev_type_t type;
} event_t;

/**
 * @brief Gets the current State Machine's state
 * @return Returns the current State Machine's state
 */
state_t getCurrentState();

/**
 * @brief Gets the current State Machine's state
 * @param evt Event sent to the State Machine
 * @return Returns 0 if event does not alter anything or 1 if it successfully updates the State Machine's state
 */
int menuHandler(event_t *evt);

#endif /* MENUFLOW_H_ */

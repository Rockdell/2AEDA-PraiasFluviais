
#ifndef MENUFLOW_H_
#define MENUFLOW_H_

typedef enum {INITIAL, ADD, REMOVE, EDIT, WATCH, DONE} state_t;
typedef enum {GO_BACK, GO_ADD, GO_REMOVE, GO_EDIT, GO_WATCH} ev_type_t;

typedef struct {
	ev_type_t type;
} event_t;

state_t getCurrentState();
int menuHandler(event_t *evt);

#endif /* MENUFLOW_H_ */

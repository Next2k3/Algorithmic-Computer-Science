class DFA:
    def __init__(self):
        self.states = set()
        self.initial_state = None
        self.transitions = {}
        self.final_states = set()

    def add_state(self, state):
        self.states.add(state)

    def set_initial_state(self, state):
        self.initial_state = state

    def set_final_state(self, state):
        self.final_states.add(state)

    def add_transition(self, from_state, input_char, to_state):
        if from_state not in self.transitions:
            self.transitions[from_state] = {}
        self.transitions[from_state][input_char] = to_state

    def transition(self, state, char):
        if state not in self.transitions or char not in self.transitions[state]:
            raise ValueError(f"No transition from state {state} on {char}")
        return self.transitions[state][char]

    def is_final(self, state):
        return state in self.final_states

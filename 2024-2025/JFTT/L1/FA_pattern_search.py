from automaton_builder import DFA

def build_char_set(pattern, text):
    return ''.join(set(pattern + text))

def longest_suffix(pattern, text):
    max_suffix_len = 0
    for i in range(1, min(len(pattern), len(text)) + 1):
        if pattern[:i] == text[-i:]:
            max_suffix_len = i
    return max_suffix_len

def construct_fa(pattern, alphabet):
    dfa = DFA()
    pattern_length = len(pattern)

    for i in range(pattern_length + 1):
        dfa.add_state(i)

    dfa.set_initial_state(0)
    dfa.set_final_state(pattern_length)

    for i in range(pattern_length + 1):
        for char in alphabet:
            next_state = longest_suffix(pattern, pattern[:i] + char)
            dfa.add_transition(i, char, next_state)

    return dfa

def search_with_fa(pattern, text):
    alphabet = build_char_set(pattern, text)
    dfa = construct_fa(pattern, alphabet)
    state = dfa.initial_state
    match_count = 0
		
    for idx, char in enumerate(text):
        try:
            state = dfa.transition(state, char)
        except ValueError:
            state = dfa.initial_state

        if dfa.is_final(state):
            match_pos = idx - len(pattern) + 1
            print(f"Match at index {match_pos}")
            match_count += 1

    return match_count
    


from automaton_builder import DFA

def build_char_set(pattern, text):
    return ''.join(set(pattern + text))

def compute_prefix_func(pattern):
    pi = [0] * len(pattern)
    k = 0
    for q in range(1, len(pattern)):
        while k > 0 and pattern[k] != pattern[q]:
            k = pi[k - 1]
        if pattern[k] == pattern[q]:
            k += 1
        pi[q] = k
    return pi

def kmp_transition(state, char, pattern, pi):
    while state > 0 and (state >= len(pattern) or pattern[state] != char):
        state = pi[state - 1]
    if state < len(pattern) and pattern[state] == char:
        return state + 1
    return 0

def construct_kmp_dfa(pattern, alphabet):
    dfa = DFA()
    pi = compute_prefix_func(pattern)
    pattern_length = len(pattern)

    for i in range(pattern_length + 1):
        dfa.add_state(i)

    dfa.set_initial_state(0)
    dfa.set_final_state(pattern_length)

    for i in range(pattern_length + 1):
        for char in alphabet:
            next_state = kmp_transition(i, char, pattern, pi)
            dfa.add_transition(i, char, next_state)

    return dfa

def search_with_kmp(pattern, text):
    alphabet = build_char_set(pattern, text)
    dfa = construct_kmp_dfa(pattern, alphabet)
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


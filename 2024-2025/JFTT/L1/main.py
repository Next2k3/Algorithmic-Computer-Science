import sys
from FA_pattern_search import search_with_fa
from KMP_pattern_search import search_with_kmp

def main():
    if len(sys.argv) != 4:
        print("Usage: <algorithm> <pattern> <file>")
        sys.exit(1)

    algorithm = sys.argv[1]
    pattern = sys.argv[2]
    file_path = sys.argv[3]

    if algorithm not in {"FA", "KMP"}:
        print("Invalid algorithm. Use 'FA' or 'KMP'")
        sys.exit(1)

    try:
        with open(file_path, 'r') as file:
            content = file.read()
            if algorithm == 'FA':
                total_matches = search_with_fa(pattern, content)
            else:
                total_matches = search_with_kmp(pattern, content)
            print(f"Pattern found {total_matches} times.")
    except FileNotFoundError:
        print(f"File '{file_path}' not found.")

if __name__ == "__main__":
    main()

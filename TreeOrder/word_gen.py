lines = []

filename = "words.txt"

try:
    with open(filename, "r") as file:
        lines = file.read().splitlines()
except FileNotFoundError:
    print(f"Error: {filename} not found.")
    exit()

formatted_list = ', '.join([f'"{word}"' for word in lines])

num_words = len(lines)

print("Total number of words:", num_words)

print("Every 1000th word:")
for i, word in enumerate(lines[::1000]):
    print(f'"{word}",')


import os

directory = '../../Engine/'
result = [os.path.join(dp, f) for dp, dn, filenames in os.walk(directory) for f in filenames if (os.path.splitext(f)[1] == '.cpp' or os.path.splitext(f)[1] == '.h')]

total_lines = 0

for file in result:
    with open(file, "rb") as f:
        lines = sum(1 for _ in f)
        print(f'{file} - {lines} lines')
        total_lines += lines


print(f'---------------- Total lines: {total_lines} ----------------')
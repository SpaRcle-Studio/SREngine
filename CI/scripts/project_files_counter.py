import sys, os, operator, subprocess
from glob import glob

try:
    from columnar import columnar
except ImportError:
    subprocess.run([sys.executable, '-m', 'pip', 'install', 'columnar'])
    from columnar import columnar

def main() -> bool:
    print('start script...')

    files = []
    patterns = ['*.cpp', '*.h', '*.hpp', 'CmakeLists.txt']
    
    exclude_patterns = [
        'Physics\\libs', 'EvoVulkan\\Depends', 
        'libs\\freetype', 'libs\\FbxLoader', 'libs\\cmp_core', 'libs\\glew', 
        'libs\\glfw', 'Audio\\libs', 'Utils\\libs', 'libs\\harfbuzz',
        'libs\\imgui', 'libs\\imgui-node-editor', 'libs\\ImGuizmo', 'libs\\inc', 
        'EvoVulkan\\Core\\libs'
    ]
    
    repo_path = '../Engine'
    
    print('collect files...')
    
    for dir,_,_ in os.walk(repo_path):
        for pattern in patterns:
            files.extend(glob(os.path.join(dir, pattern))) 
    
    for pattern in exclude_patterns:
        files = [file for file in files if not pattern in file]
    
    table = []
    
    print('collect lines...')
    
    for file in files:
        current_file_lines = 0
        empty_lines = 0
        try: 
            with open(f"{file}", 'r', encoding="utf8") as fp:
                for line in fp:
                    current_file_lines += 1  
                    if line == '\n':
                        empty_lines += 1
            table.append([file, current_file_lines, empty_lines, 0])
        except:
            print(f'failed to open file: {file}')

    print('sorting...')

    table.sort(key=lambda value: value[1])
    
    print('calculating total lines...')
    
    total = 0
    empty_total = 0
    
    for i, entry in enumerate(table):
        total += entry[1]
        empty_total += entry[2]
        table[i][3] = total

    headers = ['file', 'lines', 'empty', 'total']

    table = columnar(table, headers, no_borders=True)
    print(table)
            
    print(f'Total files: {len(files)}')
    print(f'Total lines: {total}')
    print(f'Total empty lines: {empty_total}')
    print(f'Total code lines: {total - empty_total}')
    print(f'Avg code lines in file: {round((total - empty_total) / len(files))}')
    
    return True

if __name__ == "__main__":
    if not main():
        input()
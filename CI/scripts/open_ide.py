import sys, os, subprocess
from distutils.version import StrictVersion

try:
    import winapps
except:
    subprocess.run([sys.executable, '-m', 'pip', 'install', 'winapps'])
    import winapps

CLION_IDE_TYPE = 'CLion'

def print_log(msg: str):
    print(f'[LOG] {msg}')

def is_version_greater(version: str, other: str) -> bool:
    return StrictVersion(version) > StrictVersion(other)

def find_ide(ide: str) -> sys.path:
    print_log(f"Try to find {ide} IDE")

    if ide == CLION_IDE_TYPE:
        clion : winapps.InstalledApplication = None
        for item in winapps.list_installed():
            if str(item).lower().count('clion'):
                print_log(f'Found: {item}')
                
                if clion == None or is_version_greater(item.version, clion.version):
                    clion = item
            pass
        pass

        if clion != None:
            location = str(clion.install_location).replace('\\', '/')
            return f'\"{location}/bin/clion64.exe\"'
    else:
        print_log(f"Unsupported IDE!")

    return None

def open_clion(path: sys.path):
    subprocess.Popen(f'{path} ./../', stdout=subprocess.PIPE)

def main() -> bool:
    if len(sys.argv) != 2:
        print_log('Invalid args!')
        return False

    ide_type = sys.argv[1]
    ide_path = find_ide(ide_type)  

    if ide_path == None:
        print_log('Ide not found!')
        return False

    print_log(f'Ide found at {ide_path}')
    print_log(f'Open the {ide_type} IDE')

    if ide_type == CLION_IDE_TYPE:
        open_clion(ide_path)
    else:
        print_log(f"Unsupported IDE!")
        return False

    return True

if __name__ == "__main__":
    if not main():
        os.system('pause')
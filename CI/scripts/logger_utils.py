import sys, os


def init_utf8_console():
    sys.stdout.reconfigure(encoding='utf-8')


def log_decorator(enabled):
    def wrapper(method):
        return method if enabled else (lambda self, *args: None)
    return wrapper


class Logger:
    DEBUG = True

    def __init__(self):
        self.log_file = ""
        self.log_prefix = "[SpaRcle Codegen]"

    def create_log_file(self, log_file):
        self.log_file = log_file.replace("/", "\\")

        print(f'{self.log_prefix} Create log file to: {log_file}')

        if os.path.isdir(log_file):
            raise ValueError(f"Log file path is a directory: {log_file}")

        # delete old log file
        if os.path.isfile(log_file):
            os.remove(log_file)

        os.makedirs(os.path.dirname(log_file), exist_ok=True)
        with open(log_file, "w", encoding="utf-8") as log:
            log.write(f'{self.log_prefix} Log file created.\n')


    def log_info(self, message, end='\n'):
        message = f'{self.log_prefix} [INFO] {message}'
        print(message, end=end)
        with open(self.log_file, "a", encoding="utf-8") as log:
            log.write(f'{message}{end}')


    def log_check(self, message, end='\n'):
        message = f'{self.log_prefix} [CHECK] {message}'
        print(message, end=end)
        with open(self.log_file, "a", encoding="utf-8") as log:
            log.write(f'{message}{end}')


    @log_decorator(DEBUG)
    def log_debug(self, message, end='\n'):
        message = f'{self.log_prefix} [DEBUG] {message}'
        print(message, end=end)
        with open(self.log_file, "a", encoding="utf-8") as log:
            log.write(f'{message}{end}')


    def log_fatal_error(self, message, end='\n'):
        message = f'{self.log_prefix} [FATAL] {message}'
        print(message, end=end)
        with open(self.log_file, "a", encoding="utf-8") as log:
            log.write(f'{message}{end}')
        message = f'Fatal error occurred. Check log file: "{self.log_file}"\n' + message + end
        raise RuntimeError(message)
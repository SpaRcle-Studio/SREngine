//
// Created by Monika on 02.11.2021.
//

/// TODO: move to platform class!

#include <Utils/Common/Stacktrace.h>

#include <Utils/macros.h>

#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

#ifdef SR_ANDROID
    std::string SR_UTILS_NS::GetStacktrace() {
        return "Android not support stack trace!";
    }
#endif

#ifdef SR_LINUX
    std::string SR_UTILS_NS::GetStacktrace() {
        return "Linux implementation does not yet support stack trace!";
    }
#endif

#ifdef SR_WIN32

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "dbghelp.lib")

#include <windows.h>
#include <Psapi.h>

#pragma pack( push, before_imagehlp, 8 )
#include <imagehlp.h>
#pragma pack( pop, before_imagehlp )

struct module_data {
    std::string image_name;
    std::string module_name;
    void *base_address{};
    DWORD load_size{};
};

class symbol {
    typedef IMAGEHLP_SYMBOL64 sym_type;
    sym_type *sym;
    static const int max_name_len = 1024;

public:
    symbol(HANDLE process, DWORD64 address) : sym((sym_type *)::operator new(sizeof(*sym) + max_name_len)) {
        memset(sym, '\0', sizeof(*sym) + max_name_len);
        sym->SizeOfStruct = sizeof(*sym);
        sym->MaxNameLength = max_name_len;
        DWORD64 displacement;

        SymGetSymFromAddr64(process, address, &displacement, sym);
    }

    std::string name() { return std::string(sym->Name); }
    std::string undecorated_name() {
        if (*sym->Name == '\0')
            return "<couldn't map PC to fn name>";
        std::vector<char> und_name(max_name_len);
        UnDecorateSymbolName(sym->Name, &und_name[0], max_name_len, UNDNAME_COMPLETE);
        return std::string(&und_name[0], strlen(&und_name[0]));
    }
};

class get_mod_info {
    HANDLE process;
    static const int buffer_length = 4096;
public:
    explicit get_mod_info(HANDLE h) : process(h) {}

    module_data operator()(HMODULE module) {
        module_data ret;
        char temp[buffer_length];
        MODULEINFO mi;

        GetModuleInformation(process, module, &mi, sizeof(mi));
        ret.base_address = mi.lpBaseOfDll;
        ret.load_size = mi.SizeOfImage;

        GetModuleFileNameEx(process, module, temp, sizeof(temp));
        ret.image_name = temp;
        GetModuleBaseName(process, module, temp, sizeof(temp));
        ret.module_name = temp;
        std::vector<char> img(ret.image_name.begin(), ret.image_name.end());
        std::vector<char> mod(ret.module_name.begin(), ret.module_name.end());
        SymLoadModule64(process, 0, &img[0], &mod[0], (DWORD64)ret.base_address, ret.load_size);
        return ret;
    }
};

std::ostringstream builder;

#ifdef SR_MSVC
DWORD getStack(EXCEPTION_POINTERS* ep) {
    HANDLE process = GetCurrentProcess();
    HANDLE hThread = GetCurrentThread();
    int frame_number=0;
    DWORD offset_from_symbol=0;
    IMAGEHLP_LINE64 line = {0};
    std::vector<module_data> modules;
    DWORD cbNeeded;
    std::vector<HMODULE> module_handles(1);

    // Load the symbols:
    // WARNING: You'll need to replace <pdb-search-path> with either NULL
    // or some folder where your clients will be able to find the .pdb file.
    if (!SymInitialize(process,NULL, false))
        throw (std::logic_error("Unable to initialize symbol handler"));
    DWORD symOptions = SymGetOptions();
    symOptions |= SYMOPT_LOAD_LINES | SYMOPT_UNDNAME;
    SymSetOptions(symOptions);
    EnumProcessModules(process, &module_handles[0], module_handles.size() * sizeof(HMODULE), &cbNeeded);
    module_handles.resize(cbNeeded/sizeof(HMODULE));
    EnumProcessModules(process, &module_handles[0], module_handles.size() * sizeof(HMODULE), &cbNeeded);
    std::transform(module_handles.begin(), module_handles.end(), std::back_inserter(modules), get_mod_info(process));
    void *base = modules[0].base_address;

    // Setup stuff:
    CONTEXT* context = ep->ContextRecord;
#ifdef _M_X64
    STACKFRAME64 frame;
    frame.AddrPC.Offset = context->Rip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrStack.Offset = context->Rsp;
    frame.AddrStack.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context->Rbp;
    frame.AddrFrame.Mode = AddrModeFlat;
#else
    STACKFRAME64 frame;
        frame.AddrPC.Offset = context->Eip;
        frame.AddrPC.Mode = AddrModeFlat;
        frame.AddrStack.Offset = context->Esp;
        frame.AddrStack.Mode = AddrModeFlat;
        frame.AddrFrame.Offset = context->Ebp;
        frame.AddrFrame.Mode = AddrModeFlat;
#endif
    line.SizeOfStruct = sizeof line;
    IMAGE_NT_HEADERS *h = ImageNtHeader(base);
    DWORD image_type = h->FileHeader.Machine;
    int n = 0;

    // Build the string:
    do {
        if ( frame.AddrPC.Offset != 0 ) {
            std::string fnName = symbol(process, frame.AddrPC.Offset).undecorated_name();
            builder << fnName;
            if (SymGetLineFromAddr64( process, frame.AddrPC.Offset, &offset_from_symbol, &line))
                builder << "  " /*<< line.FileName*/ << "(" << line.LineNumber << ")\n";
            else builder << "\n";
            if (fnName == "main")
                break;
            if (fnName == "RaiseException") {
                // This is what we get when compiled in Release mode:
                return EXCEPTION_EXECUTE_HANDLER;
            }
        }
        else
            builder << "(No Symbols: PC == 0)";
        if (!StackWalk64(image_type, process, hThread, &frame, context, NULL,
                         SymFunctionTableAccess64, SymGetModuleBase64, NULL))
            break;
        if (++n > 10)
            break;
    } while (frame.AddrReturn.Offset != 0);

    SymCleanup(process);

    return EXCEPTION_EXECUTE_HANDLER;
}
#endif

void GetStacktraceImpl() {
#ifdef SR_MSVC
    __try {
        int f = 0;
        f = 7 / f;   // Trigger a divide-by-zero exception
    } __except(getStack(GetExceptionInformation())) { }
#endif
}

std::string SR_UTILS_NS::GetStacktrace() {
    GetStacktraceImpl();
    return builder.str();
}

#endif

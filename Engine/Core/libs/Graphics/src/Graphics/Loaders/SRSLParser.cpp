//
// Created by Monika on 12.04.2022.
//

#include <Utils/Common/VectorUtils.h>
#include <Graphics/Loaders/SRSLParser.h>

bool SR_GRAPH_NS::SRSL::RemoveComments(SR_GRAPH_NS::SRSL::SRSLCode &code) {
    bool multiple = false;

    for (auto pIt = code.begin(); pIt != code.end(); ) {
        repeat:
        auto begin = pIt->find("/*");
        auto end = pIt->find("*/", begin == std::string::npos ? 0 : begin + 2);
        auto comment = pIt->find("//");

        if (multiple) {
            if (end != std::string::npos) {
                pIt->resize(end);
                multiple = false;
                goto repeat;
            }
            else {
                pIt = code.erase(pIt);
                continue;
            }
        }

        if (comment != std::string::npos && comment < begin) {
            *pIt = pIt->substr(0, comment);
            goto repeat;
        }

        if (begin != std::string::npos && end != std::string::npos) {
            pIt->replace(begin, (end - begin) + 2, "");
            goto repeat;
        }
        else if (begin != std::string::npos) {
            pIt->resize(begin);
            multiple = true;
            goto repeat;
        }

        if (pIt->empty()) {
            pIt = code.erase(pIt);
        }
        else
            ++pIt;
    }

    return true;
}

std::optional<SR_GRAPH_NS::SRSL::SRSLParseData> SR_GRAPH_NS::SRSL::Parse(SR_GRAPH_NS::SRSL::SRSLCode &code) {
    std::string merged = SR_UTILS_NS::VectorUtils::Merge(code);

    merged = SR_UTILS_NS::StringUtils::ReplaceAllRecursive(merged, { "  ", "\t", "\n" }, " ");

    merged = SR_UTILS_NS::StringUtils::ReplaceAllRecursive(merged, { "; ", " ;", ";;" }, ";");
    merged = SR_UTILS_NS::StringUtils::ReplaceAllRecursive(merged, { "( ", " (" }, "(");
    merged = SR_UTILS_NS::StringUtils::ReplaceAllRecursive(merged, { ") ", " )" }, ")");
    merged = SR_UTILS_NS::StringUtils::ReplaceAllRecursive(merged, { "{ ", " {" }, "{");
    merged = SR_UTILS_NS::StringUtils::ReplaceAllRecursive(merged, { "} ", " }" }, "};");

    /// -------------------------------------------

    SRSLParseData parseData;

    SRSLStructs::iterator struct_iter;
    SRSLFunctions::iterator func_iter;

    /// -------------------------------------------

    uint64_t position = 0;
    uint32_t deep = 0;

    enum class State {
        Global, Struct, Function
    } state = State::Global;

    auto isStruct = [](const std::string& instruct) -> bool {
        return instruct.find("struct") != std::string::npos && instruct.find("{") != std::string::npos;
    };

    auto isFunction = [](const std::string& instruct) -> bool {
        return instruct.find("{") != std::string::npos;
    };

    do
    {
        uint64_t semicolon = merged.find(";", position);
        uint64_t open = merged.find("{", position);

        if (semicolon == std::string::npos && open == std::string::npos)
            semicolon = merged.size() - 1; /// end of file

        const auto next = SR_MIN(semicolon, open);

        auto instruction = merged.substr(position, (next - position) + 1);
        position = next + 1;

        if (instruction == "};" && (--deep) == 0) {
            state = State::Global;
            continue;
        }

        switch (state) {
            case State::Global: {
                if (instruction.find("{") != std::string::npos)
                    break;

                parseData.vars.emplace_back(instruction.substr(0, instruction.find(";")));

                continue;
            }
            case State::Struct:
                struct_iter->code.append(instruction).append("\n");
                continue;
            case State::Function: {
                auto funcOpenPos = instruction.find("(");
                while (funcOpenPos != std::string::npos) {
                    auto funcNamePos = instruction.rfind(" ", funcOpenPos);

                    if (funcNamePos == std::string::npos) {
                        funcNamePos = -1;
                    }

                    func_iter->calls.insert(SR_UTILS_NS::StringUtils::GetBetween(instruction, funcNamePos, funcOpenPos));

                    funcOpenPos = instruction.find("(", funcOpenPos + 1);
                }

                func_iter->code
                        .append(std::string(deep, '\t'))
                        .append(instruction)
                        .append("\n");

                if (instruction.find("{") != std::string::npos)
                    ++deep;

                continue;
            }
            default:
                SRAssert(false);
        }

        if (isStruct(instruction)) {
            auto&& tokens = SR_UTILS_NS::StringUtils::Split(instruction.substr(0, instruction.find("{")), " ");

            if (tokens.size() != 2) {
                SR_ERROR("SRSL::Parse() : struct parse syntax error!");
                return {};
            }

            state = State::Struct;

            parseData.structs.emplace_back(SRSLStruct { tokens[1], std::string() });
            struct_iter = std::prev(parseData.structs.end());

            ++deep;

            continue;
        }

        if (isFunction(instruction)) {
            const auto function = instruction.substr(0, instruction.find("{"));
            const auto argOpen = function.find("(");
            const auto argClose = function.find(")");

            if (argClose == std::string::npos || argOpen == std::string::npos) {
                SR_ERROR("SRSL::Parse() : function args parse syntax error!");
                return {};
            }

            auto&& tokens = SR_UTILS_NS::StringUtils::Split(function.substr(0, argOpen), " ");

            if (tokens.size() != 2) {
                SR_ERROR("SRSL::Parse() : function parse syntax error!");
                return {};
            }

            SRSLFunc func;
            func.name = tokens[1];
            func.args = SR_UTILS_NS::StringUtils::GetBetween(function, argOpen, argClose);
            func.retType = tokens[0];
            func.calls = {};

            parseData.functions.emplace_back(func);
            func_iter = std::prev(parseData.functions.end());
            ++deep;

            state = State::Function;

            continue;
        }
    }
    while (position != merged.size());

    return parseData;
}

bool SR_GRAPH_NS::SRSL::PreProcess(SR_GRAPH_NS::SRSL::SRSLCode &code, std::map<std::string, std::string> defines) {
    return true;
}

std::string SR_GRAPH_NS::SRSL::GenerateFunctions(const SRSLFunctions& functions, const std::string& callFrom) {
    std::string code;

    std::vector<std::pair<SRSLFunc, bool>> used;
    used.reserve(functions.size());
    for (auto& func : functions)
        used.emplace_back(std::make_pair(func, false));

    std::list<std::string> callstack;
    auto haveInCallstack = [&callstack](const std::string& name) -> bool {
        for (auto& elem : callstack) {
            if (elem == name)
                return true;
        }

        return false;
    };

    std::function<void(const SRSLFunc&)> getFunctions;
    getFunctions = [&getFunctions, &used, &haveInCallstack, &callstack](const SRSLFunc& func) {
        for (const auto& call : func.calls) {
            if (haveInCallstack(call)) {
                continue;
            }

            auto findIter = std::find_if(used.begin(), used.end(), [call](const std::pair<SRSLFunc, bool>& func) -> bool {
                return func.first.name == call;
            });

            if (findIter != used.end()) {
                findIter->second = true;

                callstack.push_back(call);
                getFunctions(findIter->first);
                callstack.pop_back();
            }
        }
    };

    auto findIter = std::find_if(used.begin(), used.end(), [callFrom](const std::pair<SRSLFunc, bool>& func) -> bool {
        return func.first.name == callFrom;
    });

    if (findIter == used.end()) {
        return std::string();
    }

    callstack.push_back(callFrom);
    getFunctions(findIter->first);
    callstack.pop_back();

    /// ---------------------------------------------

    for (auto& [function, isUsed] : used) {
        if (!isUsed)
            continue;

        code += SR_UTILS_NS::Format("%s %s(%s) {\n%s}\n\n",
                                    function.retType.c_str(),
                                    function.name.c_str(),
                                    function.args.c_str(),
                                    function.code.c_str());
    }

    return code;
}

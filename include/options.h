#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include <string>
#include <cctype>
#include <map>
#include <list>
#include <initializer_list>
#include <vector>
#include <functional>

namespace op {

struct OptionState {
    int pos;
    std::vector<std::string>& args;
    std::vector<int>& argstate;
};

using OpParser = std::function<void(OptionState state)>;


class OpController {
 private:
    using ParserCont = std::list<OpParser>;
    using ParserId = typename ParserCont::iterator;
    using ParserMap = std::map<std::string, ParserId>;

    ParserCont parser_res_;
    ParserMap parser_map_;
    

    bool isFlagSet(const std::string& option) {
        if (option.size() < 2)
            return false;
        return option[0] == '-' && std::isalpha(option[1]);
    }

    bool isFlag(const std::string& option) {
        if (option.size() < 3)
            return false;
        return option[0] == '-' && option[1] == '-';
    }

 public:
    struct Exception {
        std::string msg;
    };

    OpController() = default;

    void addParser(std::initializer_list<std::string>&& flags, OpParser&& parser) {
        parser_res_.emplace_back(std::move(parser));
        auto pos = std::prev(parser_res_.end());
        for (auto flag : flags) parser_map_.emplace(flag, pos);
    }

    void ProcessArgs(int argc, char** argv) {
        std::vector<std::string> args(argc);
        for (int i = 0; i < argc; i++)
            args[i] = argv[i];

        std::vector<int> argstate(argc, 0);

        for (int pos = 1; pos < argc; pos++) {
            if (!argstate[pos]) {
                if (isFlagSet(args[pos]))
                    for (int i = 1; i < args[pos].size(); i++) {
                        std::string flag(2, '-');
                        flag[1] = args[pos][i];
                        if(parser_map_.find(flag) == parser_map_.end())
                            throw Exception{"Flag " + flag + " is not allowed!"};
                        else
                            parser_map_[flag]->operator()(OptionState{pos, args, argstate});
                    }
                else if (isFlag(args[pos])) {
                    std::string flag = args[pos];
                    if(parser_map_.find(flag) == parser_map_.end())
                        throw Exception{"Flag " + flag + " is not allowed!"};
                    else
                        parser_map_[flag]->operator()(OptionState{pos, args, argstate});
                }
            }
        }

    }
    

};

} // namespace op

#endif // _OPTIONS_H_

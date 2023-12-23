#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <map>

namespace json {
    struct Node;
    using Null = std::monostate; // std::monostate is a type that can only have one value
    using Bool = bool;
    using Int = int64_t;
    using Float = double;
    using String = std::string;
    using Array = std::vector<Node>;
    using Object = std::map<std::string, Node>;
    using Value = std::variant<Null, Bool, Int, Float, String, Array, Object>; // std::variant is a type that can have multiple types

    struct  Node
    {
        Value value;
        Node(): value(Null()) {}
        Node(Value v): value(v) {}

        auto& operator[](const std::string& key) {
            if (auto obj = std::get_if<Object>(&value)) { // std::get_if is a function that returns a pointer to the value if the type is correct, otherwise it returns nullptr
                return (*obj)[key];
            }
            throw std::runtime_error("no such object");
        }
        auto operator[](size_t index) {
            if (auto arr = std::get_if<Array>(&value)) {
                return arr->at(index);
            }
            throw std::runtime_error("no such index");
        }
        void push(const Node& node) {
            if (auto arr = std::get_if<Array>(&value)) {
                arr->push_back(node);
            }
            throw std::runtime_error("no such index");
        }
    };

    class Parser {
    public:
        std::string_view json_str; // std::string_view is a type that is a reference to a string
        size_t pos = 0;

        void parse_whitespace() {
            while (pos < json_str.size() && std::isspace(json_str[pos])) { // std::isspace is a function that returns true if the character is a whitespace, including \n, \t, \r, etc.
                pos++;
            }
        }

        auto parse_null() -> std::optional<Null> {
            if (json_str.substr(pos, 4) == "null") {
                pos += 4;
                return Null();
            }
            return {};
        }
    };
    
}
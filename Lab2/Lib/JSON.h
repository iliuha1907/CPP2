#include <vector> 
#include <map> 
#include <unordered_map> 
#include <variant> 
#include <string> 
#include <utility> 
#include <iostream> 
#include <initializer_list> 
#include <optional> 
#include <variant>

#pragma warning(disable:4996) 

class JSON;
using Value = std::variant<void*,
    bool,
    int,
    double,
    std::string,
    JSON>;
using KeyValue = std::map<std::string, Value>;
using Array = std::vector<Value>;

class JSON {
public:
    using Object = std::variant<KeyValue, Array>;

    class JSONIterator : public std::iterator<std::input_iterator_tag, Value> {
    public:

        typedef std::variant<Array::iterator, KeyValue::iterator> iterator;
        typedef std::variant<Array::const_iterator, KeyValue::const_iterator> const_iterator;

        JSONIterator(iterator it) {
            this->it = it;
        }

        bool operator!=(JSONIterator const& other) const {
            return !(it == other.it);
        }

        bool operator==(JSONIterator const& other) const {
            if (it.index() != other.it.index()) return false;
            if (std::holds_alternative<KeyValue::iterator>(it)) {
                auto f = std::get<KeyValue::iterator>(it);
                auto s = std::get<KeyValue::iterator>(other.it);
                return f == s;
            }
            else if (std::holds_alternative<Array::iterator>(it)) {
                auto f = std::get<Array::iterator>(it);
                auto s = std::get<Array::iterator>(other.it);
                return f == s;
            }
        }

        typename JSONIterator::reference operator*() const {
            if (std::holds_alternative<KeyValue::iterator>(it)) {
                return std::get<KeyValue::iterator>(it)->second;
            }
            else {
                return *std::get<Array::iterator>(it);
            }
        }

        JSONIterator& operator++() {
            if (std::holds_alternative<KeyValue::iterator>(it)) {
                it = ++std::get<KeyValue::iterator>(it);
            }
            else {
                it = ++std::get<Array::iterator>(it);
            }
            return *this;
        }

    private:
        iterator it;
    };

    JSONIterator begin();

    JSONIterator end();

    JSON();

    JSON(Array array);

    JSON(std::initializer_list<Value>);

    JSON(std::initializer_list<std::pair<const std::string, Value>>);

    JSON(const JSON& json);

    void add(const std::string& key, Value value);

    void add(const Value& value);

    void edit(const std::string& forKey, const Value& newValue);

    void edit(int atIndex, const Value& newValue);

    void remove(const std::string& forKey);

    void remove(int atIndex);

    template<typename T>
    std::optional<T> getVal(const std::string& key);

    std::optional<Array> asArray();

    bool isEmpty();

    bool isArray();

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& out, const JSON& j);

    friend std::ostream& operator<<(std::ostream& out, const Value& v);

    friend bool operator==(const JSON& l, const JSON& r);

    friend bool operator!=(const JSON& l, const JSON& r);

    friend bool operator==(const Value& l, const Value& r);

    friend bool operator!=(const Value& l, const Value& r);

private:
    Object root;

    std::string dictToString(const KeyValue& map) const;

    std::string arrayToString(const Array& array) const;

    static std::string valueToString(const Value& value);

};

template<typename T>
std::optional<T> JSON::getVal(const std::string& key) {
    if (std::holds_alternative<KeyValue>(root)) {
        KeyValue v_map = std::get<KeyValue>(root);
        try {
            return std::optional<T>{std::get<T>(v_map[key])};
        }
        catch (std::bad_variant_access ex) {
            return std::nullopt;
        }
    }
    else {
        return std::nullopt;
    }
}
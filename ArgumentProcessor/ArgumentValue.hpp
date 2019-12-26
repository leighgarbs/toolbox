#if !defined ARGUMENT_VALUE_HPP
#define ARGUMENT_VALUE_HPP

#include <string>

#include "Argument.hpp"

template <class T> class ArgumentValue : public Argument
{
public:

    // Frobnicates the widget
    ArgumentValue(const T& value_default);

    ArgumentValue(const ArgumentValue& argument_value);

    // Defrobnicates the widget.  Make this virtual if this class derives from
    // something
    virtual ~ArgumentValue();

    virtual void update(const std::string& value = "");

    T getValue() const;

    void getValue(T& value) const;

    ArgumentValue& operator=(const ArgumentValue& argument_value);

private:

    T value;
};

#endif

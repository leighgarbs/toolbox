#include "ArgumentValue.hpp"

#include "ArgumentValueBase.hpp"

//==============================================================================
template <class T> ArgumentValue<T>::ArgumentValue() :
    ArgumentValueBase()
{
}

//==============================================================================
template <class T> ArgumentValue<T>::~ArgumentValue()
{
}

//==============================================================================
template <class T> ArgumentValue<T>&
ArgumentValue<T>::operator=(const ArgumentValue& argument_value)
{
    ArgumentValueBase::operator=(argument_value);

    // Don't do anything if we're assigning to ourselves
    if (this != &argument_value)
    {
        value = argument_value.value;
    }

    return *this;
}

#include <iterator>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include "ArgumentProcessor.hpp"

#include "ArgumentType.hpp"
#include "OptionalArgument.hpp"
#include "PositionalArgument.hpp"

//==============================================================================
ArgumentProcessor::ArgumentProcessor() :
    next_positional_argument(positional_arguments.end()),
    current_optional_argument(optional_arguments.end())
{
    // It's a safe bet users will always want the program name registered.
    // Positional arguments won't work correctly otherwise.
    registerName();
}

//==============================================================================
ArgumentProcessor::~ArgumentProcessor()
{
    for (std::list<PositionalArgument*>::iterator i =
             positional_arguments.begin();
         i != positional_arguments.end();
         ++i)
    {
        delete *i;
    }

    for (std::unordered_map<std::string, OptionalArgument*>::iterator i =
             optional_arguments.begin();
         i != optional_arguments.end();
         ++i)
    {
        delete i->second;
    }
}

//==============================================================================
void ArgumentProcessor::registerPositionalArgument(
    const std::string& name,
    const std::string& description,
    ArgumentType       type)
{
    //positional_arguments.push_back(new PositionalArgument(name, description));

    // If we just added the first positional argument then we have to start
    // processing positional arguments from here.  There's nowhere else to
    // process from.
    if (positional_arguments.size() == 1)
    {
        next_positional_argument = positional_arguments.begin();
    }

    // The idea here is to support processing additional arguments after we've
    // already processed a set of existing ones.  Probably not a very likely use
    // case but it seems nice.
    if (next_positional_argument == positional_arguments.end())
    {
        next_positional_argument = std::prev(positional_arguments.end());
    }
}

//==============================================================================
void ArgumentProcessor::registerOptionalArgument(
        const std::string&                     name,
        const std::string&                     description,
        ArgumentType                           type,
        const std::unordered_set<std::string>& aliases)
{
    // Stores the name twice, which is a bit inefficient.  Also ignores aliases
    // in the map, for now.
    //optional_arguments[name] = new OptionalArgument(name, description, aliases);
}

//==============================================================================
void ArgumentProcessor::process(const std::string& argument)
{
    // There is a two-dimensional state machine here, represented by the
    // next_positional_argument and current_optional_argument iterator class
    // members.

    // If we're not already processing an optional argument, try to find one
    // that matches the current argument.
    if (current_optional_argument == optional_arguments.end())
    {
        current_optional_argument = optional_arguments.find(argument);
    }

    // Are we processing an optional argument?  This if can be true multiple
    // times for the same value of the current_optional_argument iterator.  This
    // will happen for all optional arguments that themselves take arguments.
    if (current_optional_argument != optional_arguments.end())
    {
        current_optional_argument->second->process(argument);

        // Stop processing this optional argument only when it says it's done.
        if (current_optional_argument->second->isSatisfied())
        {
            current_optional_argument = optional_arguments.end();
        }
    }
    else
    {
        // It's not optional, so process it as a positional argument.
        (*next_positional_argument)->process(argument);

        // We're ready for the next positional argument.
        ++next_positional_argument;
    }
}

//==============================================================================
void ArgumentProcessor::process(const std::list<std::string>& arguments)
{
    for (std::list<std::string>::const_iterator i = arguments.begin();
         i != arguments.end();
         ++i)
    {
        process(*i);
    }
}

//==============================================================================
void ArgumentProcessor::process(int argc, char** argv)
{
    for (int i = 0; i < argc; ++i)
    {
        process(argv[i]);
    }
}
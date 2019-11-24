#include "ArgumentProcessor.hpp"

//==============================================================================
ArgumentProcessor::ArgumentProcessor(int argc, char** argv)
{
    // Store the arguments
    for (int i = 1; i < argc; i++)
    {
        arguments.push_back(argv[i]);
    }
}

//==============================================================================
ArgumentProcessor::~ArgumentProcessor()
{
}

//==============================================================================
// If implemented, operator= should follow this template
//==============================================================================
ArgumentProcessor&
ArgumentProcessor::operator=(const ArgumentProcessor& template_class)
{
    // Don't do anything if we're assigning to ourselves
    if (this != &template_class)
    {
        // Do something
    }

    return *this;
}

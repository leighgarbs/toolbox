 // General-purpose timestamp-based log utility
// Leigh Garbs

#if !defined LOG_HPP
#define LOG_HPP

#include <iostream>

class Log
{
  public:

    // Log constructor; initializes output_stream
    Log(std::ostream& output_stream = std::cout);

    // Log destructor; does nothing
    ~Log();

    // Sets the output stream to write log messages to
    void setOutputStream(std::ostream& output_stream);

    // Returns the output stream to write log messages to
    std::ostream& getOutputStream() const;

    // Writes a standard log message
    void write(const std::string& message);

    // Writes a warning log message
    void writeWarning(const std::string& message);

    // Writes an error log message
    void writeError(const std::string& message);

    // Flushes the current output stream
    void flush();

    // Causes log timestamps to be generated in GMT
    void useGreenwichMeanTime();

    // Causes log timestamps to be generated in local time
    void useLocalTime();

  private:

    // Enumerates the different supported time formats
    enum TimeFormat
    {
      GMT,
      LOCAL
    };

    // Generates a timestamp to prepend to log messages
    void generateTimestamp(std::string& timestamp);

    // The output stream to write log messages to
    std::ostream* output_stream;

    // The time format log timestamps are currently generated in
    TimeFormat current_time_format;
};

inline void Log::setOutputStream(std::ostream& output_stream)
{
  this->output_stream = &output_stream;
}

inline std::ostream& Log::getOutputStream() const
{
  return *output_stream;
}

inline void Log::useGreenwichMeanTime()
{
  current_time_format = GMT;
}

inline void Log::useLocalTime()
{
  current_time_format = LOCAL;
}

#endif
#ifndef B1EC6DDE_DF12_43D7_A3CC_23F9DC92A806
#define B1EC6DDE_DF12_43D7_A3CC_23F9DC92A806

#include "Core/Log.h"

#include <exception>
#include <string>

namespace fts
{
    class Exception : public std::exception, public std::string
    {
    public:
        Exception(void) throw() {}

        Exception(std::string msg) throw() : std::string(std::move(msg)) {}

        virtual ~Exception(void) throw() {}

        virtual const char *what(void) const throw() { return c_str(); }
    };

    class FileException : public Exception
    {
    public:
        FileException(const std::string_view &file_path,
                      const std::string_view &msg) throw()
            : Exception(fmt::format("File exception from \"{}\", error: {}",
                                    file_path, msg))
        {
        }

        virtual ~FileException(void) throw() {}
    };

} // namespace fts

#endif /* B1EC6DDE_DF12_43D7_A3CC_23F9DC92A806 */

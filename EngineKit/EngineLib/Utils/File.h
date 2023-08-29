#ifndef __FILE_H__
#define __FILE_H__


#include "Core/Base.h"
#include "Utils/Exception.h"


namespace fts
{
    namespace File
    {
        void Read(const std::string &file_path, std::string &content);
        void Write(const std::string &file_path, const std::string &content);

    } // namespace File
} // namespace fts

#endif // __FILE_H__
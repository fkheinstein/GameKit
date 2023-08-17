#ifndef __RESOURCEPATH_H__
#define __RESOURCEPATH_H__

#pragma once



namespace fts
{
    std::string getRootResourcePath();

    std::string getGameExampleRootPath();
    std::string getGameCmdRootPath();

    std::string getPathRelativeRoot(const std::string& path);

    std::string getPathGameExample(const std::string& path);
    std::string getPathGameCmd(const std::string& path);

    std::string getPathRelativeBinary(const std::string& path);
}
#endif // __RESOURCEPATH_H__
cmake_minimum_required(VERSION 3.0)

project("Lua54")

set(LUA_VERSION "lua-5.4.6")


#include_directories(../../src/lua-5.4.6)

add_library(Lua54 STATIC

    ../../src/Lua/src/lvm.c
    ../../src/Lua/src/lzio.c
    ../../src/Lua/src/lapi.c
    ../../src/Lua/src/lauxlib.c
    ../../src/Lua/src/lbaselib.c
    ../../src/Lua/src/lcode.c
    ../../src/Lua/src/lcorolib.c
    ../../src/Lua/src/lctype.c
    ../../src/Lua/src/ldblib.c
    ../../src/Lua/src/ldebug.c
    ../../src/Lua/src/ldo.c
    ../../src/Lua/src/ldump.c
    ../../src/Lua/src/lfunc.c
    ../../src/Lua/src/lgc.c
    ../../src/Lua/src/linit.c
    ../../src/Lua/src/liolib.c
    ../../src/Lua/src/llex.c
    ../../src/Lua/src/lmathlib.c
    ../../src/Lua/src/lmem.c
    ../../src/Lua/src/loadlib.c
    ../../src/Lua/src/lobject.c
    ../../src/Lua/src/lopcodes.c
    ../../src/Lua/src/loslib.c
    ../../src/Lua/src/lparser.c
    ../../src/Lua/src/lstate.c
    ../../src/Lua/src/lstring.c
    ../../src/Lua/src/lstrlib.c
    ../../src/Lua/src/ltable.c
    ../../src/Lua/src/ltablib.c
    ../../src/Lua/src/ltm.c
    ../../src/Lua/src/luac.c
    ../../src/Lua/src/lundump.c
    ../../src/Lua/src/lutf8lib.c
)

set_property(TARGET Lua54 PROPERTY FOLDER "ThirdPartyLibraries")


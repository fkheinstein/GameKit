#ifndef __SPCH_H__
#define __SPCH_H__


#include "Core/PlatformDetection.h"



#include <stdint.h>

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <future>

#include <map>
#include <cassert>
#include <tuple>
#include <stack> 
#include <stdexcept>


#include <random>
#include <unordered_map>

//C++17
#include <cstdint>
#include <string_view>

#include <variant>
#include <optional>



#include <Core/Base.h>
#include <Core/Log.h>
#include <Core/Assert.h>
#include <Core/Macro.h>



//stb
#include <stb_image.h>
#include <stb_image_write.h>


//spdlog
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/fmt/ostr.h>




//eventpp
#include <eventpp/eventqueue.h>
#include <eventpp/eventdispatcher.h>
#include <eventpp/callbacklist.h>
#include <eventpp/mixins/mixinfilter.h>



#include <Utils/Init.h>
#include <Utils/Exception.h>
#include <Utils/Timing.h>

#include <Utils/OpenGLLibInclude.h>
#include <Utils/GlmInclude.h>


#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>
#include <Events/WindowEvent.h>
#include <Events/EventManager.h>
#include <eventpp/utilities/argumentadapter.h>


#ifdef FTS_IMGUI
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>
#endif


#endif // __SPCH_H__
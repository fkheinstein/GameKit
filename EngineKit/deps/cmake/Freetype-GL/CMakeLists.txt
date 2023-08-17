cmake_minimum_required(VERSION 3.0)

project("freetype-gl")





if(WIN32)

include_directories(${FREETYPE_INCLUDE_DIRS})
#include_directories(../../src/freetype)

elseif(UNIX)

 include_directories(/usr/include/freetype2/)

endif()




add_library(freetype-gl  


	../../src/freetype-gl/distance-field.c
	../../src/freetype-gl/distance-field.h
	../../src/freetype-gl/edtaa3func.c
	../../src/freetype-gl/edtaa3func.h
	../../src/freetype-gl/platform.c
	../../src/freetype-gl/platform.h
	../../src/freetype-gl/texture-atlas.c
	../../src/freetype-gl/texture-atlas.h
	../../src/freetype-gl/texture-font.c
	../../src/freetype-gl/texture-font.h
	../../src/freetype-gl/utf8-utils.c
	../../src/freetype-gl/utf8-utils.h
	../../src/freetype-gl/vec234.h
	../../src/freetype-gl/vector.c
	../../src/freetype-gl/vector.h 
	
	../../src/freetype-gl/ftgl-utils.h
	../../src/freetype-gl/ftgl-utils.c

	../../src/freetype-gl/freetype-gl.h
	

)



target_link_libraries(freetype-gl ${FREETYPE_LIBRARY})
set_property(TARGET freetype-gl PROPERTY FOLDER "ThirdPartyLibraries")



#ifndef __GLMINCLUDE_H__
#define __GLMINCLUDE_H__



#ifdef WIN32

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX // prevent windows redefining min/max
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

//#pragma comment( lib, "version.lib" )

#include <windows.h>
#endif //_WIN32


#endif


// ---------------------------------------------------------------------------------------------------------------------
// GLM
// ---------------------------------------------------------------------------------------------------------------------
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>



#include <glm/gtx/norm.hpp>
#undef GLM_ENABLE_EXPERIMENTAL


#include <glm/gtx/compatibility.hpp>

#include <glm/gtc/noise.hpp>
#include <glm/gtc/random.hpp> // for glm::linearRand
#endif // __GLMINCLUDE_H__
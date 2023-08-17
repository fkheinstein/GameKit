#ifndef BC28379C_C172_4B97_80E9_CD2B50E118A0
#define BC28379C_C172_4B97_80E9_CD2B50E118A0

#include <Core/Assert.h>

/////////////////////////////////////////////////////////////////////////////////////////
bool GLLogCall(const char* functionName, const char* fileName, int line);

/////////////////////////////////////////////////////////////////////////////////////////
void GLClearError();

#define GLCall(x) GLClearError();\
    x;\
    FTS_ASSERT(GLLogCall(#x, __FILE__, __LINE__))




#endif /* BC28379C_C172_4B97_80E9_CD2B50E118A0 */

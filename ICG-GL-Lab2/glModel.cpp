#pragma warning (disable : 4996)
#include "glModel.h"
#include <cstdlib>
#include <wchar.h>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
// Debug output function
static void APIENTRY debugOutput
	(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	GLvoid* userParam
	)
{
	FILE* f;
	f = fopen("debug_output.txt","a");
	if(f)
	{
		char debSource[32], debType[32], debSev[32];
		bool Error(false);

		if(source == GL_DEBUG_SOURCE_API_ARB)
			strcpy(debSource, "OpenGL");
		else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
			strcpy(debSource, "Windows");
		else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
			strcpy(debSource, "Shader Compiler");
		else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
			strcpy(debSource, "Third Party");
		else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)
			strcpy(debSource, "Application");
		else if (source == GL_DEBUG_SOURCE_OTHER_ARB)
			strcpy(debSource, "Other");
		else
			assert(0);

		if(type == GL_DEBUG_TYPE_ERROR)
			strcpy(debType, "error");
		else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR)
			strcpy(debType, "deprecated behavior");
		else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)
			strcpy(debType, "undefined behavior");
		else if(type == GL_DEBUG_TYPE_PORTABILITY)
			strcpy(debType, "portability");
		else if(type == GL_DEBUG_TYPE_PERFORMANCE)
			strcpy(debType, "performance");
		else if(type == GL_DEBUG_TYPE_OTHER)
			strcpy(debType, "message");
		else if(type == GL_DEBUG_TYPE_MARKER)
			strcpy(debType, "marker");
		else if(type == GL_DEBUG_TYPE_PUSH_GROUP)
			strcpy(debType, "push group");
		else if(type == GL_DEBUG_TYPE_POP_GROUP)
			strcpy(debType, "pop group");
		else
			assert(0);

		if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)
		{
			strcpy(debSev, "high");
			//Error = true;
		}
		else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)
			strcpy(debSev, "medium");
		else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)
			strcpy(debSev, "low");
		else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
			strcpy(debSev, "notification");
		else
			assert(0);

		fprintf(f,"%s: %s(%s) %d: %s\n", debSource, debType, debSev, id, message);
		assert(!Error);
		fclose(f);
	}
}
glModel::glModel() :
	normalDirect(1.0f),
	hDevC(NULL)
{
	ZeroMemory(&shaderAttribLocs,sizeof(shaderAttribLocs));
	materialP.refAmbient = glm::vec3(0.2f);
	materialP.refDiffuse = glm::vec3(1.0f);
	materialP.refSpecular = glm::vec3(0.0f);
	materialP.emission = glm::vec3(0.0f);
	materialP.Shininess = 10.0f;
	lightsP[mLight0].attenuation_constant = 1.0f;
	lightsP[mLight0].attenuation_linear = 0.05f;
	lightsP[mLight0].attenuation_quadratic = 0.0025f;
	lightsP[mLight0].ambient = glm::vec3(1.0f);
	lightsP[mLight0].diffuse = glm::vec3(1.0f);
	lightsP[mLight0].specular = glm::vec3(1.0f);
	lightsP[mLight0].position = glm::vec4(-10.0f,90.0f,-200.0f,1.0f);
	X = glm::vec3(1.0f,0.0f,0.0f);
	Y = glm::vec3(0.0f,1.0f,0.0f);
	Z = glm::vec3(0.0f,0.0f,1.0f);
	ZeroMemory(&modelStates,sizeof(bitStates));
}

glModel::~glModel(void)
{
	glDeleteBuffers(bufCount,buffers);
	glDeleteVertexArrays(VAOcount,VAOs);
	glDeleteTextures(texCount,modelTextures);
}




bool glModel::init()
{
	GLuint error = OGLCheckError(errorString,L"Init",1024);
	if(error > 0) {
		MessageBox(handle,errorString,L"ICG GL Lab2", MB_OK | MB_ICONERROR);
		return false;
	}
	//if(error == 0 && !glewIsSupported("GL_ARB_debug_output")) {
	//	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	//	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	//	glDebugMessageCallbackARB(debugOutput, NULL);
	//}
	bool globRes = true;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearDepth(1.0f);

	error = OGLCheckError(errorString,L"init",1024);
	if(error > 0 /*|| !modelStates.useShadersflg*/) {
		MessageBox(handle,errorString,L"ICG GL Lab2", MB_OK | MB_ICONERROR);
		globRes = false;
	}
	lookCamera(glm::vec3(70.0f, 50.0f, -50.00f), glm::vec3(0.0f, 0.0f, 0.0f),false);
	error = OGLCheckError(errorString,L"Init",1024);
	if(error > 0) {
		globRes = false;
	}
	return globRes;
}
bool glModel::initBuffers() {
	bool globRes = true;
	GLuint error = 0U;

	if(globRes)
		modelStates.bufferBind = 1;
	else
		modelStates.bufferBind = 0;
	return globRes;
}

void glModel::swapDevBuffers() {
	glFlush();
	if(hDevC)
		SwapBuffers(hDevC);
	else {
		MessageBox(handle,L"Error switch buffers. DoubleBuffer error!",L"GL_MODEL CLASS", MB_OK | MB_ICONEXCLAMATION);
		PostQuitMessage(EXIT_FAILURE);
	}

}
void glModel::RebindShaderAttributes(GLuint &currentVAO_ID, GLuint &currentBufID, GLuint vertCount, GLuint sideVertCount) // *
{

}
void glModel::RebindNormalShaderAttributes(GLuint &currentVAO_ID, GLuint &currentBufID, GLuint vertCount, GLuint sideVertCount) {

}
void glModel::unbindShaderAttributes() {


}
void glModel::unbindNormalShaderAttributes() {

}
void glModel::draw()
{
	GLuint error = OGLCheckError(errorString,L"draw",1024);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	swapDevBuffers();
	error = OGLCheckError(errorString,L"draw",1024);
	if(error > 0) {
		MessageBox(handle,errorString,L"ICG GL Lab-2", MB_OK | MB_ICONERROR);
	}
}

bool glModel::LoadTexture(LPCWSTR filename,FIBITMAP **dib, int &tWidth, int &tHeight, int &tBPP) {
	FREE_IMAGE_FORMAT fif;
	HMODULE hdl = GetModuleHandle(NULL);
	vector<WCHAR> full_path(MAX_PATH);
	GetModuleFileName(hdl,&full_path[0],MAX_PATH);

	wstring str(&full_path[0]);
	UINT t = str.rfind(L'\\');
	str.resize(++t);
	str = str + wstring(filename);
	fif = FreeImage_GetFIFFromFilenameU(str.c_str());
	if(fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilenameU(str.c_str());
	if(fif == FIF_UNKNOWN) {
		swprintf(errorString,L"FI error open file %S, type = %S",filename,FreeImage_GetFormatFromFIF(fif));
		MessageBox(handle,errorString, L"ICG GL Lab-2", MB_OK | MB_ICONERROR);
		return false;
	}
	if(dib && FreeImage_FIFSupportsReading(fif)) {
		*dib = FreeImage_LoadU(fif,str.c_str());
	}
	else if(!dib) {
		swprintf(errorString,L"FI error write data to dib, no address",filename,FreeImage_GetFormatFromFIF(fif));
		MessageBox(handle, errorString, L"ICG GL Lab-2", MB_OK | MB_ICONERROR);
		return false;
	}
	else {
		swprintf(errorString,L"FI error reading file %S, type = %S",filename,FreeImage_GetFormatFromFIF(fif));
		MessageBox(handle, errorString, L"ICG GL Lab-2", MB_OK | MB_ICONERROR);
		return false;
	}
	str.clear();
	full_path.clear();
	if(*dib != NULL) {
		int OriginalWidth = FreeImage_GetWidth(*dib);
		int OriginalHeight = FreeImage_GetHeight(*dib);

		tWidth = OriginalWidth;
		tHeight = OriginalHeight;

		if(tWidth == 0 || tHeight == 0)
		{
			FreeImage_Unload(*dib);
			return false;
		}

		tBPP = FreeImage_GetBPP(*dib);
		GLint maxTexSize = 0;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE,&maxTexSize);
		if(tWidth > maxTexSize) tWidth = maxTexSize;
		if(tHeight > maxTexSize) tHeight = maxTexSize;

		if(!GLEW_ARB_texture_non_power_of_two)
		{
			tWidth = 1 << (int)floor((log((float)tWidth) / log(2.0f)) + 0.5f); 
			tHeight = 1 << (int)floor((log((float)tHeight) / log(2.0f)) + 0.5f);
		}

		if(tWidth != OriginalWidth || tHeight != OriginalHeight)
		{
			FIBITMAP *rdib = FreeImage_Rescale(*dib, tWidth, tHeight, FILTER_BICUBIC);
			FreeImage_Unload(*dib);
			*dib = rdib;
		}


	}
	return true;
}
#define isPowOf2(x) !((x)&((x)-1))
bool glModel::initTextures(const GLboolean bGenMipMaps, GLint curAF) {
#ifdef FREEIMAGE_LIB
	FreeImage_Initialise();
#endif
	FIBITMAP *dib(NULL);
	BYTE *bDataPtr(NULL);
	const WCHAR *texName = L"textures\\cobblestones.tex.jpg";
	int texWidth, texHeight, texBPP;
	if(!LoadTexture(texName,&dib,texWidth,texHeight,texBPP)) {
		swprintf(errorString,1024,L"Texture \'%S\' loading failed!",texName);
		MessageBox(handle,errorString,L"ICG GL Lab-2", MB_OK | MB_ICONERROR);
		return false;
	}
	bDataPtr = FreeImage_GetBits(dib);
	if(bDataPtr == NULL || texWidth == 0 || texHeight == 0) {
		return false;
	}
	GLenum dataFormat = texBPP == 32 ? GL_BGRA : texBPP == 24 ? GL_BGR : 0;
	if(dataFormat == 0) {
		return false;
	}
	glDeleteTextures(texCount,modelTextures);
	glGenTextures(texCount,modelTextures);
	glBindTexture(GL_TEXTURE_2D,modelTextures[cobTex]);
	if(GLEW_EXT_texture_filter_anisotropic && curAF > 1) {
		int maxAFval = 0;
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,&maxAFval);
		if(!isPowOf2(curAF)) {
			curAF = (int)ceil(log(double(curAF))/log(2.0)) + 1;
		}
		if(curAF > maxAFval)
			curAF = maxAFval;
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAX_ANISOTROPY_EXT,curAF);
	}
	if(bGenMipMaps) {
		int num_mipmaps = (int)ceil(log(double(max(texWidth,texHeight)))/log(2.0)) + 1;
		if(GLEW_ARB_texture_storage) {
			glTexStorage2D(GL_TEXTURE_2D,num_mipmaps,GL_RGBA8,texWidth,texHeight);
			glTexSubImage2D(GL_TEXTURE_2D,0,0,0,texWidth,texHeight,dataFormat,GL_UNSIGNED_BYTE,bDataPtr);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,texWidth,texHeight,0,dataFormat,GL_UNSIGNED_BYTE,bDataPtr);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR); // trilinear filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else {
		if(GLEW_ARB_texture_storage) {
			glTexStorage2D(GL_TEXTURE_2D,1,GL_RGBA8,texWidth,texHeight);
			glTexSubImage2D(GL_TEXTURE_2D,0,0,0,texWidth,texHeight,dataFormat,GL_UNSIGNED_BYTE,bDataPtr);
		}
		else {
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_BASE_LEVEL,0);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAX_LEVEL,0);
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,texWidth,texHeight,0,dataFormat,GL_UNSIGNED_BYTE,bDataPtr);
		}
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // bilinear filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
	GLuint error = OGLCheckError(errorString,L"initTextures",1024);
	FreeImage_Unload(dib);
#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialise();
#endif
	return true;
}

void glModel::lookCamera(const glm::vec3 &pos, const glm::vec3 &ref, bool RotateAroundReference) {

	this->Position = pos;
	this->Reference = ref;

	Z = glm::normalize(Position - Reference);
	X = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), Z));
	Y = glm::cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	calculateViewMatrix();
}

///////////////////////////////////////////////////////////////////////////////
// configure projection and viewport
///////////////////////////////////////////////////////////////////////////////
void glModel::setViewport(int w, int h)
{
	if(h == 0) h = 1;
	this->width = GLfloat(w);
	this->height = GLfloat(h);
	GLfloat aspect(0.0f); 
	if(w >= h) {
		aspect = width / height;
	}
	else {
		aspect = height / width;
	}
	glViewport(0,0,w,h);
	matrices.Model = glm::translate(glm::vec3(0.0f));
	matrices.Projection = glm::perspective(45.0f, aspect,  0.01f, 10000.0f);
}
///////////////////////////////////////////////////////////////////////////////
// rotate the camera
///////////////////////////////////////////////////////////////////////////////
void glModel::rotateCamera(int x, int y)
{
	if(modelStates.mouseLeftDown)
	{
		// moving by x, by y (of window)
		GLfloat dx = GLfloat(x) - mouseX;
		GLfloat dy = GLfloat(y) - mouseY;
		// setting up sensetivity
		float Sensitivity = 1.00f;

		if(dx != 0)
		{
			// moving left/right
			GLfloat DeltaX = dx * Sensitivity;
			// rotate our basic vector's around physical Y
			X = glm::rotate(X, DeltaX, glm::vec3(0.0f, 1.0f, 0.0f));
			Y = glm::rotate(Y, DeltaX, glm::vec3(0.0f, 1.0f, 0.0f));
			Z = glm::rotate(Z, DeltaX, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if(dy != 0)
		{
			// moving top/bottom
			GLfloat DeltaY = dy * Sensitivity;

			Y = glm::rotate(Y, DeltaY, X);
			Z = glm::rotate(Z, DeltaY, X);

			if(Y.y < 0.0f)
			{
				Z = glm::vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = glm::cross(Z, X);
			}
		}
		Reference = Z * glm::length(Position);  
		calculateViewMatrix();
		mouseX = GLfloat(x);
		mouseY = GLfloat(y);
	}
}



///////////////////////////////////////////////////////////////////////////////
// zoom the camera
///////////////////////////////////////////////////////////////////////////////
void glModel::zoomCamera(int delta)
{
	if(delta < 0) {
		Position += Reference * 0.025f;
	}
	else if(delta > 0) {	
		Position -= Reference * 0.025f;
	}
	calculateViewMatrix();
}
// Calculate view matrix
void glModel::calculateViewMatrix() {
	matrices.View = glm::mat4x4(X.x,Y.x,Z.x,0.0f,X.y,Y.y,Z.y,0.0f,X.z,Y.z,Z.z,0.0f,-glm::dot(X,Position),-glm::dot(Y,Position),-glm::dot(Z,Position),1.0f);
}
void glModel::moveCameraByKB(int Keys) {
	float Speed = 5.0f;

	if(Keys & 0x40) Speed *= 2.0f;
	if(Keys & 0x80) Speed *= 0.5f;

	float Distance = Speed * 0.05f;

	glm::vec3 Forward = Z, Right = X, Up = Y;

	Up *= Distance;
	Right *= Distance;
	Forward *= Distance;

	glm::vec3 Movement;

	if(Keys & 0x01) Movement -= Forward;
	if(Keys & 0x02) Movement += Forward;
	if(Keys & 0x04) Movement -= Right;
	if(Keys & 0x08) Movement += Right;
	if(Keys & 0x10) Movement += Up;
	if(Keys & 0x20) Movement -= Up;

	Position += Movement;
	Reference += Movement;
	calculateViewMatrix();
}
bool glModel::loadDialog(LPCWSTR dialogTitle, LPWSTR filename, LPCWSTR filter) {
	static WCHAR cwd[MAX_PATH] = {0};
	GetCurrentDirectory(MAX_PATH,cwd);
	OPENFILENAME ofn;
	ZeroMemory(&ofn,sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = handle;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = FILENAME_MAX;
	ofn.lpstrTitle = dialogTitle;
	ofn.lpstrInitialDir = cwd;
	ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING 
		| OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST;
	if(GetOpenFileName(&ofn) == NULL) {
		if(CommDlgExtendedError() == FALSE) {
			MessageBox(handle,L"Some error with dialog init/run",L"GL_MODEL CLASS", MB_OK | MB_ICONEXCLAMATION);
		}
		else {
			MessageBox(handle,L"File not choose. You did cancel operation",L"GL_MODEL CLASS", MB_OK | MB_ICONEXCLAMATION);
		}
		return false;
	}
	return true;
}
#define closeFile(fp) \
	if(fp) { \
	fclose(fp); \
	fp = NULL; \
	} 

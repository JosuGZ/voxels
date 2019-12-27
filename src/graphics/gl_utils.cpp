#include "gl_utils.h"

#include <iostream>
#include <GL/glew.h>

void glCheckError(const char *msg, bool abort_) {
  switch (glGetError()) {
    // OpenGL 2
    case GL_NO_ERROR:
      return;
    case GL_INVALID_ENUM:
      std::cout << msg << ": GL_INVALID_ENUM" << std::endl;
      if (abort_) abort();
      return;
    case GL_INVALID_VALUE:
      std::cout << msg << ": GL_INVALID_VALUE" << std::endl;
      if (abort_) abort();
      return;
    case GL_INVALID_OPERATION:
      std::cout << msg << ": GL_INVALID_OPERATION" << std::endl;
      if (abort_) abort();
      return;
    case GL_STACK_OVERFLOW:
      std::cout << msg << ": GL_STACK_OVERFLOW" << std::endl;
      if (abort_) abort();
      return;
    case GL_STACK_UNDERFLOW:
      std::cout << msg << ": GL_STACK_UNDERFLOW" << std::endl;
      if (abort_) abort();
      return;
    case GL_OUT_OF_MEMORY:
      std::cout << msg << ": GL_OUT_OF_MEMORY" << std::endl;
      if (abort_) abort();
      return;
    case GL_TABLE_TOO_LARGE:
      std::cout << msg << ": GL_TABLE_TOO_LARGE" << std::endl;
      if (abort_) abort();
      return;
    // OpenGL 3
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      std::cout << msg << ": GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
      if (abort_) abort();
      return;
    default:
      std::cout << msg << ": unknown error" << std::endl;
      if (abort_) abort();
      return;
  }
}

SET(CMAKE_SYSTEM_NAME Windows)
SET(HOME "$ENV{HOME}")
SET(CMAKE_C_COMPILER "${HOME}/mxe-minimal/usr/bin/x86_64-w64-mingw32.static-gcc")
SET(CMAKE_CXX_COMPILER "${HOME}/mxe-minimal/usr/bin/x86_64-w64-mingw32.static-g++")
SET(CMAKE_RC_COMPILER ${HOME}/mxe-minimal/usr/bin/x86_64-w64-mingw32.static-windres)
SET(CMAKE_FIND_ROOT_PATH ${HOME}/mxe-minimal/usr/x86_64-w64-mingw32.static/)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

project(ctelebot C)
cmake_minimum_required(VERSION 2.8)

option(BUILD_STATIC_LIBS "Build the static library" OFF)
option(BUILD_SHARED_LIBS "Build the shared library" ON)

#============================== VERSION ================================
set(LIB_VERSION_MAJOR 1)
set(LIB_VERSION_MINOR 1)
set(LIB_VERSION_PATCH 1)
set(LIB_VERSION_STRING ${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH})
#=======================================================================

# проверка зависимостей
find_library(LIB_JANSSON "jansson" REQUIRED)
if("LIB_JANSSON-NOTFOUND" STREQUAL ${LIB_JANSSON})
	message("libjansson not found!")
else()
	message("libjansson found")
endif()

find_library(LIB_CURL "curl" REQUIRED)
if("LIB_CURL-NOTFOUND" STREQUAL ${LIB_CURL})
	message("libcurl not found!")
else()
	message("libcurl found")
endif()

#список хедеров для установки
set(CT_PUBLIC_HDRS 
	include/ct_api.h
    include/ct_buffer.h
    include/ct_common.h
    include/ct_message.h
    #остальные хедеры не нужны для использования библиотеки
)

#указываем путь для хедеров
include_directories(BEFORE ./include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Werror -Wall -std=gnu99") #-Os -g3
aux_source_directory(./src SRC_LIST)

if (BUILD_STATIC_LIBS OR BUILD_SHARED_LIBS)

	if (BUILD_STATIC_LIBS)
        message("build static lib")
		add_library(${PROJECT_NAME}_static STATIC ${SRC_LIST})
        target_link_libraries(${PROJECT_NAME}_static STATIC
	        ${LIB_JANSSON}
            ${LIB_CURL}
        )
		install(TARGETS ${PROJECT_NAME}_static DESTINATION lib)
	endif (BUILD_STATIC_LIBS)

	if (BUILD_SHARED_LIBS)
        message("build shared lib")
		add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
        target_link_libraries(${PROJECT_NAME} 
	        ${LIB_JANSSON}
            ${LIB_CURL}
        )
		install(TARGETS ${PROJECT_NAME} DESTINATION lib)
		set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${LIB_VERSION_STRING} SOVERSION ${LIB_VERSION_MAJOR})
	endif (BUILD_SHARED_LIBS)

	install(FILES ${CT_PUBLIC_HDRS} DESTINATION include/ctelebot)

else (BUILD_STATIC_LIBS OR BUILD_SHARED_LIBS)

	message(FATAL_ERROR "no target for build!")

endif (BUILD_STATIC_LIBS OR BUILD_SHARED_LIBS)

add_custom_target(uninstall
	COMMAND xargs rm -v < install_manifest.txt
)


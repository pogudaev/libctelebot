project(ctelebot C)
cmake_minimum_required(VERSION 2.8)

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

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Werror -Wall -std=gnu99")
aux_source_directory(./src SRC_LIST)
add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

install(FILES ${CT_PUBLIC_HDRS} DESTINATION include)

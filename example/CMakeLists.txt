cmake_minimum_required(VERSION 2.8)

project(bot C)

find_library(LIB_CTELEBOT "ctelebot" REQUIRED)
if("LIB_CTELEBOT-NOTFOUND" STREQUAL ${LIB_CTELEBOT})
    message("libctelebot not found!")
else()
    message("libctelebot found")
endif()

set(SOURCE_LIST
    main.c
)

add_executable(${PROJECT_NAME} ${SOURCE_LIST})
target_link_libraries(${PROJECT_NAME} 
	${LIB_CTELEBOT}
)



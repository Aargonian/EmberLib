set(SOURCES ${CONFIG_HEADER}
	    include/arraylist_new.h
		old/arraylist_old.h
	    src/arraylist_new.c)

add_library(EmberLib STATIC ${SOURCES})
add_executable(demo src/main.c)

target_include_directories(EmberLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(demo EmberLib)

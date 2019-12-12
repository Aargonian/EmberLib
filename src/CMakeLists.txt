set(header_path ${CMAKE_CURRENT_SOURCE_DIR}/../include/EmberLib)
set(headers ${CONFIG_HEADER}
            ${header_path}/arraylist_new.h
            ${header_path}/heap.h
            ${header_path}/old/arraylist_old.h
            ${header_path}/IO/EmberFile.h
            ${header_path}/Util/EmberString.h)
set(sources arraylist_new.c 
            heap.c
            IO/EmberFile.c
            Util/EmberString.c)

add_library(EmberLib STATIC ${headers} ${sources})
target_include_directories(EmberLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

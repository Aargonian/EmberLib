set(header_path ${CMAKE_CURRENT_SOURCE_DIR}/../include/EmberLib)
set(headers ${CONFIG_HEADER}
            ${header_path}/IO/EmberFile.h
            ${header_path}/Util/EmberString.h
            ${header_path}/Util/EmberList.h)
set(sources Util/EmberList.c
            Util/EmberString.c
            IO/EmberFile.c)

add_library(EmberLib STATIC ${headers} ${sources})
target_include_directories(EmberLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

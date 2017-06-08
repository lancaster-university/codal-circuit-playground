project(codal-samd21-mbed)

include("${CODAL_UTILS_LOCATION}")

# find sources and headers
RECURSIVE_FIND_DIR(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/${CODAL_TARGET_DEVICE}" "*.h")
RECURSIVE_FIND_FILE(SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${CODAL_TARGET_DEVICE}" "*.c??")

RECURSIVE_FIND_DIR(TOP_LEVEL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" "*.h")
RECURSIVE_FIND_DIR(TOP_LEVEL_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/source" "*.c??")

# force include conf_clocks...
set(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} -imacros \"${CMAKE_CURRENT_SOURCE_DIR}/conf_clocks.h\"" PARENT_SCOPE)
set(CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} -imacros \"${CMAKE_CURRENT_SOURCE_DIR}/conf_clocks.h\"" PARENT_SCOPE)

string(TOLOWER "${CODAL_TARGET_PROCESSOR}" TARGET_PROCESSOR)

set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -mcpu=cortex-m0plus -mthumb -T\"${CMAKE_CURRENT_LIST_DIR}/ld/${TARGET_PROCESSOR}.ld\"" PARENT_SCOPE)
set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} -mcpu=cortex-m0plus -mthumb -T\"${CMAKE_CURRENT_LIST_DIR}/ld/${TARGET_PROCESSOR}.ld\"" PARENT_SCOPE)
set(CMAKE_SYSTEM_PROCESSOR "armv7-m" PARENT_SCOPE)

# add them
include_directories("${INCLUDE_DIRS}" "${TOP_LEVEL_INCLUDE_DIRS}")

# create our target
add_library(codal-samd21-mbed "${SOURCE_FILES}" "${TOP_LEVEL_SOURCE_FILES}")

target_link_libraries(
    codal-samd21-mbed
    codal-mbed
)

# expose it to parent cmake.
target_include_directories(codal-samd21-mbed PUBLIC ${INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/")

if(CODAL_HEADER_EXTRACTION)
    RECURSIVE_FIND_FILE(INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${codal.target.device}" "*.h")
    HEADER_FILES(INCLUDE_FILES2 ".")

    file(COPY ${INCLUDE_FILES} DESTINATION "../../build/codal-samd21-mbed/includes")
    file(COPY ${INCLUDE_FILES2} DESTINATION "../../build/codal-samd21-mbed/includes")
endif()

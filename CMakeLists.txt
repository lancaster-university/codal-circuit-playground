project(codal-circuit-playground)

include("${CODAL_UTILS_LOCATION}")

# find sources and headers
list(APPEND SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/asm/CortexContextSwitch.s")

RECURSIVE_FIND_DIR(TOP_LEVEL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" "*.h")
RECURSIVE_FIND_FILE(TOP_LEVEL_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/source" "*.c??")
RECURSIVE_FIND_DIR(MODEL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/model" "*.h")
RECURSIVE_FIND_FILE(MODEL_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/model" "*.c??")

# force include conf_clocks...
set(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} -include \"${CMAKE_CURRENT_SOURCE_DIR}/inc/conf_clocks.h\"" PARENT_SCOPE)
set(CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} -include \"${CMAKE_CURRENT_SOURCE_DIR}/inc/conf_clocks.h\"" PARENT_SCOPE)

string(TOLOWER "${CODAL_TARGET_PROCESSOR}" TARGET_PROCESSOR)

set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -mcpu=cortex-m0plus -mthumb -T\"${CMAKE_CURRENT_LIST_DIR}/ld/${TARGET_PROCESSOR}.ld\"" PARENT_SCOPE)
set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} -mcpu=cortex-m0plus -mthumb -T\"${CMAKE_CURRENT_LIST_DIR}/ld/${TARGET_PROCESSOR}.ld\"" PARENT_SCOPE)
set(CMAKE_SYSTEM_PROCESSOR "armv7-m" PARENT_SCOPE)

# add them
include_directories(${INCLUDE_DIRS} ${TOP_LEVEL_INCLUDE_DIRS} ${MODEL_INCLUDE_DIRS})

# create our target
add_library(codal-circuit-playground ${SOURCE_FILES} ${TOP_LEVEL_SOURCE_FILES} ${MODEL_SOURCE_FILES})

target_link_libraries(
    codal-circuit-playground
    codal-samd21
)

# expose it to parent cmake.
target_include_directories(codal-circuit-playground PUBLIC ${MODEL_INCLUDE_DIRS} ${TOP_LEVEL_INCLUDE_DIRS})
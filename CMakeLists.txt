project(CODAL_SAMD21_MBED)

include(${PROJECT_SOURCE_DIR}/utils/cmake/util.cmake)

# find sources and headers
RECURSIVE_FIND_DIR(INCLUDE_DIRS "./${codal.target.device}" "*.h")
RECURSIVE_FIND_FILE(SOURCE_FILES "./${codal.target.device}" "*.c??")

# add them
include_directories("${INCLUDE_DIRS}")

# create our target
add_library(MBED_CLASSIC "${SOURCE_FILES}")

target_link_libraries(
    CODAL_SAMD21_MBED
    mbed-classic
    codal
)

# expose it to parent cmake.
target_include_directories(CODAL_SAMD21_MBED PUBLIC ${INCLUDE_DIRS})

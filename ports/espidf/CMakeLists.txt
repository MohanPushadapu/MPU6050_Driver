target_sources(${COMPONENT_LIB} PRIVATE
    src/espidf.cpp
)

target_include_directories(${COMPONENT_LIB} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

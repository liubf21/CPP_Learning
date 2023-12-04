add_executable(unit_test
    doctest.h
    subject_test.cpp
    scoresheet_test.cpp
)

set_target_properties(unit_test PROPERTIES
	CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES doctest.h
    subject_test.cpp
    scoresheet_test.cpp
)
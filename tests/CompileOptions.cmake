# Warnings and compile options
# Compile Options
#target_compile_options(${TargetName} PRIVATE -fpermissive)
#target_compile_options(-fprofile-arcs -ftest-coverage)

#SET(GCC_COVERAGE_LINK_FLAGS    "-coverage -lgcov")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

#set(FSL_FEATURE_ADC_HAS_CTRL_LPWRMODE true)

function(AddCompileOptions TargetName)
target_compile_options(
${TargetName}
PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Wpedantic
    -g3
    -O0
    #-pedantic-errors
    #-Werror=pedantic

    -Wconversion
    $<$<COMPILE_LANGUAGE:C>:-Wimplicit>
    $<$<COMPILE_LANGUAGE:C>:-Wunused>

    #$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    #$<$<COMPILE_LANGUAGE:CXX>:-Wabi>
    $<$<CXX_COMPILER_ID:GNU>:-Wsuggest-final-types>
    $<$<CXX_COMPILER_ID:GNU>:-Wmaybe-uninitialized>
    $<$<CXX_COMPILER_ID:GNU>:-Wdouble-promotion>
    $<$<CXX_COMPILER_ID:GNU>:-fconcepts>
    #$<$<CXX_COMPILER_ID:GNU>:-Wnull-dereference>
    -Winit-self

    #$<$<CXX_COMPILER_ID:GNU>:-Wduplicated-cond>
    #$<$<CXX_COMPILER_ID:GNU>:-Wduplicated-branches>
    #$<$<CXX_COMPILER_ID:GNU>:-Wlogical-op>
    #$<$<CXX_COMPILER_ID:GNU>:-Wrestrict>
    $<$<C_COMPILER_ID:GNU>:$<$<COMPILE_LANGUAGE:C>:-Wjump-misses-init>>
    $<$<COMPILE_LANGUAGE:CXX>:-Wold-style-cast>
    -Wshadow
)
endfunction()


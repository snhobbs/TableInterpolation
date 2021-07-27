target_link_libraries( ${TargetName} asan)
#target_link_libraries( ${TargetName} tsan)
target_link_libraries( ${TargetName} ubsan)
#target_link_libraries( ${TargetName} msan)

target_compile_options(
${TargetName}
PRIVATE
    -fsanitize=address
    -fno-omit-frame-pointer
    -fsanitize=undefined)


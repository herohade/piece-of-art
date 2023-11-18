set(doctest_include_folder "../../doctest")

file(READ ${doctest_include_folder}/parts/doctest_fwd.h fwd)
file(READ ${doctest_include_folder}/parts/doctest.cpp impl)

file(WRITE  ${doctest_include_folder}/doctest.h "// ====================================================================== lgtm [cpp/missing-header-guard]\n")
file(APPEND ${doctest_include_folder}/doctest.h "// == DO NOT MODIFY THIS FILE BY HAND - IT IS AUTO GENERATED BY CMAKE! ==\n")
file(APPEND ${doctest_include_folder}/doctest.h "// ======================================================================\n")
file(APPEND ${doctest_include_folder}/doctest.h "${fwd}\n")
file(APPEND ${doctest_include_folder}/doctest.h "#ifndef DOCTEST_SINGLE_HEADER\n")
file(APPEND ${doctest_include_folder}/doctest.h "#define DOCTEST_SINGLE_HEADER\n")
file(APPEND ${doctest_include_folder}/doctest.h "#endif // DOCTEST_SINGLE_HEADER\n")
file(APPEND ${doctest_include_folder}/doctest.h "\n${impl}")

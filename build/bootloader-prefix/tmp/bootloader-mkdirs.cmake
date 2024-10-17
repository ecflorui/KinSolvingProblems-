# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/singh/esp/v4.4.8/esp-idf/components/bootloader/subproject"
  "C:/Users/singh/KinSolvingProblemsTM/build/bootloader"
  "C:/Users/singh/KinSolvingProblemsTM/build/bootloader-prefix"
  "C:/Users/singh/KinSolvingProblemsTM/build/bootloader-prefix/tmp"
  "C:/Users/singh/KinSolvingProblemsTM/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/singh/KinSolvingProblemsTM/build/bootloader-prefix/src"
  "C:/Users/singh/KinSolvingProblemsTM/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/singh/KinSolvingProblemsTM/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()

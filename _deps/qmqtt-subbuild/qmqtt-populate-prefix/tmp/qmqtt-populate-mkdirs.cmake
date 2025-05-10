# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/cassim/Csociety/Qt/Projects/IOT/SmartRoom/_deps/qmqtt-src")
  file(MAKE_DIRECTORY "/home/cassim/Csociety/Qt/Projects/IOT/SmartRoom/_deps/qmqtt-src")
endif()
file(MAKE_DIRECTORY
  "/home/cassim/Csociety/Qt/Projects/IOT/SmartRoom/_deps/qmqtt-build"
  "/home/cassim/Csociety/Qt/Projects/IOT/SmartRoom/_deps/qmqtt-subbuild/qmqtt-populate-prefix"
  "/home/cassim/Csociety/Qt/Projects/IOT/SmartRoom/_deps/qmqtt-subbuild/qmqtt-populate-prefix/tmp"
  "/home/cassim/Csociety/Qt/Projects/IOT/SmartRoom/_deps/qmqtt-subbuild/qmqtt-populate-prefix/src/qmqtt-populate-stamp"
  "/home/cassim/Csociety/Qt/Projects/IOT/SmartRoom/_deps/qmqtt-subbuild/qmqtt-populate-prefix/src"
  "/home/cassim/Csociety/Qt/Projects/IOT/SmartRoom/_deps/qmqtt-subbuild/qmqtt-populate-prefix/src/qmqtt-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/cassim/Csociety/Qt/Projects/IOT/SmartRoom/_deps/qmqtt-subbuild/qmqtt-populate-prefix/src/qmqtt-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/cassim/Csociety/Qt/Projects/IOT/SmartRoom/_deps/qmqtt-subbuild/qmqtt-populate-prefix/src/qmqtt-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

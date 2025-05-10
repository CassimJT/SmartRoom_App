# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appSmartRoom_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appSmartRoom_autogen.dir/ParseCache.txt"
  "appSmartRoom_autogen"
  )
endif()

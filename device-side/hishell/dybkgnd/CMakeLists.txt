cmake_minimum_required(VERSION 3.10)
project(dybkgnd)
aux_source_directory(. DIR_SRCS)
add_executable(dybkgnd ${DIR_SRCS})
target_link_libraries(dybkgnd gobject-2.0 cairo)
include_directories(${GLIB_INCLUDE_DIRS} ${LIBRSVG_INCLUDE_DIR} ${Cairo_INCLUDE_DIRS} ${MINIGUI_INCLUDE_DIRS} ${MGEFF_INCLUDE_DIRS})
target_link_libraries(dybkgnd ${MINIGUI_LIBRARIES} ${MGEFF_LIBRARIES} ${LIBRSVG_LIBRARIES} ${GLIB_LIBRARIES}) 
install(TARGETS dybkgnd DESTINATION ${CMAKE_INSTALL_PREFIX}/libexec/)
install(FILES res/wallpaper-bottom.jpg DESTINATION ${CMAKE_INSTALL_PREFIX}/libexec/res/)
install(FILES res/wallpaper-top.jpg DESTINATION ${CMAKE_INSTALL_PREFIX}/libexec/res/)

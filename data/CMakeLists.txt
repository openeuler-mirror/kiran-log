# pc file
file(GLOB PC_IN_FILES ./*.pc.in)

foreach(PC_IN_FILE IN LISTS PC_IN_FILES)
  string(REGEX REPLACE ".+/(.+)\\..*" "\\1" PC_FILE ${PC_IN_FILE})
  configure_file(${PC_IN_FILE} ${PROJECT_BINARY_DIR}/data/${PC_FILE})

  install(FILES ${PROJECT_BINARY_DIR}/data/${PC_FILE}
          DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig)
endforeach()

# zlog默认会将zlog.conf作为轮转锁文件，若配置不可写，则会导致初始化失败。
# NOTE:
#   此处安装的zlog.conf文件的权限只有Owner可写，Group和World不可写。
#   需要合入zlog更新Patch，给zlog加入rotate lock file = program支持。
#   合入后，当rotate lock file = program时，rotate lock file会映射到/tmp/zlog/${UID}-${PROGRAM_NAME}.lock
# See also: 
# 1. https://atomgit.com/src-openeuler/zlog/pull/31
# 2. Ones #113752
install(
  FILES ${PROJECT_SOURCE_DIR}/data/zlog.conf
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
  DESTINATION ${CMAKE_INSTALL_FULL_SYSCONFDIR}/${PROJECT_NAME}/)

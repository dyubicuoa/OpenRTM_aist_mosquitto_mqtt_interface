cmake_minimum_required(VERSION 3.10)
project(MosquittoInterface)
 
# ビルドオプション
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")
 
# includeディレクトリを追加
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(/usr/include/coil-2.0)
include_directories(/usr/include/openrtm-2.0)
include_directories(/usr/include/openrtm-2.0/rtm/idl)

# サブディレクトリのCMakeListsを読み込む
add_subdirectory(src)

install(TARGETS OutPortMosquittoPublisher InPortMosquittoSubscriber
        LIBRARY DESTINATION /usr/local/lib)

# 出力ディレクトリを指定（必要に応じて）
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
 
# ライブラリ1: OutPortMosquittoPublisher.so
add_library(OutPortMosquittoPublisher SHARED
    OutPortMosquittoPublisher.cpp
    MosquittoPublisher.cpp
)

# ライブラリ2: InPortMosquittoSubscriber.so
add_library(InPortMosquittoSubscriber SHARED
    InPortMosquittoSubscriber.cpp
    MosquittoSubscriber.cpp
)

# lib 接頭辞を削除
set_target_properties(OutPortMosquittoPublisher PROPERTIES PREFIX "")
set_target_properties(InPortMosquittoSubscriber PROPERTIES PREFIX "")

# 共通リンクライブラリ
target_link_libraries(OutPortMosquittoPublisher
    mosquittopp
    RTC2
    omnithread
    omniORB4
    omniDynamic4
)

target_link_libraries(InPortMosquittoSubscriber
    mosquittopp
    RTC2
    omnithread
    omniORB4
    omniDynamic4
)

target_compile_options(OutPortMosquittoPublisher PRIVATE -Wno-deprecated-declarations)
target_compile_options(InPortMosquittoSubscriber PRIVATE -Wno-deprecated-declarations)

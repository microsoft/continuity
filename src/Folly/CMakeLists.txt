## Download folly, but don't pull in its CMake build definition (we only want to build/publish a piece of it)

FetchContent_Declare(
    folly
    URL "https://github.com/facebook/folly/archive/v2019.09.30.00.zip"
    URL_HASH SHA512=2edb1e0b50a75604530d8bdcc35cacef500cb8b1466d546b3a201882da69cfba1b91493225b71d5bcf99f610d5b1668b115edebcfb25f9e36dc75e8632afaa58)
FetchContent_GetProperties(folly)
if(NOT folly_POPULATED)
    message(STATUS "Downloading folly...")
    FetchContent_Populate(folly)
endif()

## Create the folly build target

list(APPEND HEADERS
    ${folly_SOURCE_DIR}/folly/AtomicBitSet.h
    ${folly_SOURCE_DIR}/folly/AtomicHashArray-inl.h
    ${folly_SOURCE_DIR}/folly/AtomicHashArray.h
    ${folly_SOURCE_DIR}/folly/AtomicHashMap-inl.h
    ${folly_SOURCE_DIR}/folly/AtomicHashMap.h
    ${folly_SOURCE_DIR}/folly/AtomicIntrusiveLinkedList.h
    ${folly_SOURCE_DIR}/folly/AtomicLinkedList.h
    ${folly_SOURCE_DIR}/folly/AtomicUnorderedMap.h
    ${folly_SOURCE_DIR}/folly/Benchmark.h
    ${folly_SOURCE_DIR}/folly/Bits.h
    ${folly_SOURCE_DIR}/folly/CachelinePadded.h
    ${folly_SOURCE_DIR}/folly/ClockGettimeWrappers.h
    ${folly_SOURCE_DIR}/folly/ConcurrentSkipList-inl.h
    ${folly_SOURCE_DIR}/folly/ConcurrentSkipList.h
    ${folly_SOURCE_DIR}/folly/Conv.h
    ${folly_SOURCE_DIR}/folly/CPortability.h
    ${folly_SOURCE_DIR}/folly/CppAttributes.h
    ${folly_SOURCE_DIR}/folly/CpuId.h
    ${folly_SOURCE_DIR}/folly/Demangle.h
    ${folly_SOURCE_DIR}/folly/detail/AtomicHashUtils.h
    ${folly_SOURCE_DIR}/folly/detail/AtomicUnorderedMapUtils.h
    ${folly_SOURCE_DIR}/folly/detail/DiscriminatedPtrDetail.h
    ${folly_SOURCE_DIR}/folly/detail/FileUtilDetail.h
    ${folly_SOURCE_DIR}/folly/detail/FingerprintPolynomial.h
    ${folly_SOURCE_DIR}/folly/detail/Futex.h
    ${folly_SOURCE_DIR}/folly/detail/GroupVarintDetail.h
    ${folly_SOURCE_DIR}/folly/detail/IPAddress.h
    ${folly_SOURCE_DIR}/folly/detail/IPAddressSource.h
    ${folly_SOURCE_DIR}/folly/detail/MemoryIdler.h
    ${folly_SOURCE_DIR}/folly/detail/MPMCPipelineDetail.h
    ${folly_SOURCE_DIR}/folly/detail/RangeCommon.h
    ${folly_SOURCE_DIR}/folly/detail/RangeSse42.h
    ${folly_SOURCE_DIR}/folly/detail/SlowFingerprint.h
    ${folly_SOURCE_DIR}/folly/detail/SocketFastOpen.h
    ${folly_SOURCE_DIR}/folly/detail/StaticSingletonManager.h
    ${folly_SOURCE_DIR}/folly/detail/ThreadLocalDetail.h
    ${folly_SOURCE_DIR}/folly/detail/TurnSequencer.h
    ${folly_SOURCE_DIR}/folly/DiscriminatedPtr.h
    ${folly_SOURCE_DIR}/folly/dynamic-inl.h
    ${folly_SOURCE_DIR}/folly/dynamic.h
    ${folly_SOURCE_DIR}/folly/DynamicConverter.h
    ${folly_SOURCE_DIR}/folly/Exception.h
    ${folly_SOURCE_DIR}/folly/ExceptionString.h
    ${folly_SOURCE_DIR}/folly/ExceptionWrapper.h
    ${folly_SOURCE_DIR}/folly/Executor.h
    ${folly_SOURCE_DIR}/folly/Expected.h
    ${folly_SOURCE_DIR}/folly/FBString.h
    ${folly_SOURCE_DIR}/folly/FBVector.h
    ${folly_SOURCE_DIR}/folly/File.h
    ${folly_SOURCE_DIR}/folly/FileUtil.h
    ${folly_SOURCE_DIR}/folly/Fingerprint.h
    ${folly_SOURCE_DIR}/folly/Format-inl.h
    ${folly_SOURCE_DIR}/folly/Format.h
    ${folly_SOURCE_DIR}/folly/FormatArg.h
    ${folly_SOURCE_DIR}/folly/FormatTraits.h
    ${folly_SOURCE_DIR}/folly/Function.h
    ${folly_SOURCE_DIR}/folly/GroupVarint.h
    ${folly_SOURCE_DIR}/folly/Hash.h
    ${folly_SOURCE_DIR}/folly/Indestructible.h
    ${folly_SOURCE_DIR}/folly/IndexedMemPool.h
    ${folly_SOURCE_DIR}/folly/IntrusiveList.h
    ${folly_SOURCE_DIR}/folly/IPAddress.h
    ${folly_SOURCE_DIR}/folly/IPAddressException.h
    ${folly_SOURCE_DIR}/folly/IPAddressV4.h
    ${folly_SOURCE_DIR}/folly/IPAddressV6.h
    ${folly_SOURCE_DIR}/folly/json.h
    ${folly_SOURCE_DIR}/folly/Lazy.h
    ${folly_SOURCE_DIR}/folly/Likely.h
    ${folly_SOURCE_DIR}/folly/LockTraits.h
    ${folly_SOURCE_DIR}/folly/MacAddress.h
    ${folly_SOURCE_DIR}/folly/MapUtil.h
    ${folly_SOURCE_DIR}/folly/Math.h
    ${folly_SOURCE_DIR}/folly/Memory.h
    ${folly_SOURCE_DIR}/folly/MicroLock.h
    ${folly_SOURCE_DIR}/folly/MicroSpinLock.h
    ${folly_SOURCE_DIR}/folly/MoveWrapper.h
    ${folly_SOURCE_DIR}/folly/MPMCPipeline.h
    ${folly_SOURCE_DIR}/folly/MPMCQueue.h
    ${folly_SOURCE_DIR}/folly/Optional.h
    ${folly_SOURCE_DIR}/folly/PackedSyncPtr.h
    ${folly_SOURCE_DIR}/folly/Padded.h
    ${folly_SOURCE_DIR}/folly/Portability.h
    ${folly_SOURCE_DIR}/folly/portability/Asm.h
    ${folly_SOURCE_DIR}/folly/portability/Atomic.h
    ${folly_SOURCE_DIR}/folly/portability/Builtins.h
    ${folly_SOURCE_DIR}/folly/portability/Config.h
    ${folly_SOURCE_DIR}/folly/portability/Constexpr.h
    ${folly_SOURCE_DIR}/folly/portability/Dirent.h
    ${folly_SOURCE_DIR}/folly/portability/Event.h
    ${folly_SOURCE_DIR}/folly/portability/Fcntl.h
    ${folly_SOURCE_DIR}/folly/portability/GFlags.h
    ${folly_SOURCE_DIR}/folly/portability/GMock.h
    ${folly_SOURCE_DIR}/folly/portability/GTest.h
    ${folly_SOURCE_DIR}/folly/portability/IOVec.h
    ${folly_SOURCE_DIR}/folly/portability/Libgen.h
    ${folly_SOURCE_DIR}/folly/portability/Malloc.h
    ${folly_SOURCE_DIR}/folly/portability/Math.h
    ${folly_SOURCE_DIR}/folly/portability/Memory.h
    ${folly_SOURCE_DIR}/folly/portability/PThread.h
    ${folly_SOURCE_DIR}/folly/portability/Sockets.h
    ${folly_SOURCE_DIR}/folly/portability/Stdio.h
    ${folly_SOURCE_DIR}/folly/portability/Stdlib.h
    ${folly_SOURCE_DIR}/folly/portability/String.h
    ${folly_SOURCE_DIR}/folly/portability/SysFile.h
    ${folly_SOURCE_DIR}/folly/portability/Syslog.h
    ${folly_SOURCE_DIR}/folly/portability/SysMembarrier.h
    ${folly_SOURCE_DIR}/folly/portability/SysResource.h
    ${folly_SOURCE_DIR}/folly/portability/SysStat.h
    ${folly_SOURCE_DIR}/folly/portability/SysSyscall.h
    ${folly_SOURCE_DIR}/folly/portability/SysTime.h
    ${folly_SOURCE_DIR}/folly/portability/SysTypes.h
    ${folly_SOURCE_DIR}/folly/portability/SysUio.h
    ${folly_SOURCE_DIR}/folly/portability/Time.h
    ${folly_SOURCE_DIR}/folly/portability/Unistd.h
    ${folly_SOURCE_DIR}/folly/portability/Windows.h
    ${folly_SOURCE_DIR}/folly/Preprocessor.h
    ${folly_SOURCE_DIR}/folly/ProducerConsumerQueue.h
    ${folly_SOURCE_DIR}/folly/Random-inl.h
    ${folly_SOURCE_DIR}/folly/Random.h
    ${folly_SOURCE_DIR}/folly/Range.h
    ${folly_SOURCE_DIR}/folly/RWSpinLock.h
    ${folly_SOURCE_DIR}/folly/ScopeGuard.h
    ${folly_SOURCE_DIR}/folly/SharedMutex.h
    ${folly_SOURCE_DIR}/folly/Singleton-inl.h
    ${folly_SOURCE_DIR}/folly/Singleton.h
    ${folly_SOURCE_DIR}/folly/SingletonThreadLocal.h
    ${folly_SOURCE_DIR}/folly/small_vector.h
    ${folly_SOURCE_DIR}/folly/SocketAddress.h
    ${folly_SOURCE_DIR}/folly/sorted_vector_types.h
    ${folly_SOURCE_DIR}/folly/SpinLock.h
    ${folly_SOURCE_DIR}/folly/stop_watch.h
    ${folly_SOURCE_DIR}/folly/String-inl.h
    ${folly_SOURCE_DIR}/folly/String.h
    ${folly_SOURCE_DIR}/folly/Subprocess.h
    ${folly_SOURCE_DIR}/folly/Synchronized.h
    ${folly_SOURCE_DIR}/folly/ThreadCachedInt.h
    ${folly_SOURCE_DIR}/folly/ThreadLocal.h
    ${folly_SOURCE_DIR}/folly/TimeoutQueue.h
    ${folly_SOURCE_DIR}/folly/TokenBucket.h
    ${folly_SOURCE_DIR}/folly/traits.h
    ${folly_SOURCE_DIR}/folly/Try-inl.h
    ${folly_SOURCE_DIR}/folly/Try.h
    ${folly_SOURCE_DIR}/folly/Unicode.h
    ${folly_SOURCE_DIR}/folly/Unit.h
    ${folly_SOURCE_DIR}/folly/Uri-inl.h
    ${folly_SOURCE_DIR}/folly/Uri.h
    ${folly_SOURCE_DIR}/folly/Varint.h
    stubs/double-conversion/double-conversion.h
    stubs/glog/logging.h
    stubs/sys/mman.h
    stubs/sys/time.h
    stubs/unistd.h)

list(APPEND HEADERS_WINDOWS
    ${folly_SOURCE_DIR}/folly/portability/SysMman.h)

list(APPEND SOURCES
    ${folly_SOURCE_DIR}/folly/lang/Assume.cpp
    ${folly_SOURCE_DIR}/folly/json_pointer.cpp
    ${folly_SOURCE_DIR}/folly/Format.cpp
    ${folly_SOURCE_DIR}/folly/String.cpp
    ${folly_SOURCE_DIR}/folly/container/detail/F14Table.cpp
    ${folly_SOURCE_DIR}/folly/Conv.cpp
    ${folly_SOURCE_DIR}/folly/portability/string.cpp
    ${folly_SOURCE_DIR}/folly/Demangle.cpp
    ${folly_SOURCE_DIR}/folly/dynamic.cpp
    ${folly_SOURCE_DIR}/folly/json.cpp
    ${folly_SOURCE_DIR}/folly/hash/SpookyHashV2.cpp
    ${folly_SOURCE_DIR}/folly/ScopeGuard.cpp
    ${folly_SOURCE_DIR}/folly/Unicode.cpp
    ${folly_SOURCE_DIR}/folly/memory/detail/MallocImpl.cpp
    ${folly_SOURCE_DIR}/folly/lang/ColdClass.cpp
    stubs/folly/SafeAssert_EmptyImpl.cpp)

list(APPEND SOURCES_WINDOWS
    ${folly_SOURCE_DIR}/folly/portability/SysMman.cpp)

add_library(folly)

target_sources(folly
    PUBLIC
        ${HEADERS}
        $<$<PLATFORM_ID:Windows>:${HEADERS_WINDOWS}>
    PRIVATE
        ${SOURCES}
        $<$<PLATFORM_ID:Windows>:${SOURCES_WINDOWS}>)

target_compile_definitions(folly PRIVATE ${PROJECT_COMPILE_DEFINITIONS})

target_include_directories(folly
    PUBLIC
        ${folly_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/stubs
    PRIVATE
        ${BOOST_ROOT}/include)

target_link_options(folly
    PUBLIC
        $<$<PLATFORM_ID:Windows>:/NATVIS:${CMAKE_CURRENT_SOURCE_DIR}/Folly.natvis>)

#ifndef _FW_FILEWATCHERIMPL_H
#define _FW_FILEWATCHERIMPL_H
#pragma once

#include "FileWatcher.h"

#define FILEWATCHER_PLATFORM_WIN32 1
#define FILEWATCHER_PLATFORM_LINUX 2
#define FILEWATCHER_PLATFORM_KQUEUE 3

#if defined(_WIN32)
#   define FILEWATCHER_PLATFORM FILEWATCHER_PLATFORM_WIN32
#elif defined(__APPLE_CC__) || defined(BSD)
#   define FILEWATCHER_PLATFORM FILEWATCHER_PLATFORM_KQUEUE
#elif defined(__linux__)
#   define FILEWATCHER_PLATFORM FILEWATCHER_PLATFORM_LINUX
#endif

namespace fs
{
    struct WatchStruct;

    class FileWatcherImpl
    {
    public:
        ///
        ///
        FileWatcherImpl() {}

        ///
        ///
        virtual ~FileWatcherImpl() {}

        /// Add a directory watch
        /// @exception FileNotFoundException Thrown when the requested directory does not exist
        virtual WatchID addWatch(
            const String& directory,
            std::function<void(WatchID watchid, const String& dir, const String& filename, Action action)> watcher,
            bool recursive) = 0;

        /// Remove a directory watch. This is a brute force lazy search O(nlogn).
        virtual void removeWatch(const String& directory) = 0;

        /// Remove a directory watch. This is a map lookup O(logn).
        virtual void removeWatch(WatchID watchid) = 0;

        /// Updates the watcher. Must be called often.
        virtual void update() = 0;

        /// Handles the action
        virtual void handleAction(WatchStruct* watch, const String& filename, unsigned long action) = 0;
    
    }; // end FileWatcherImpl
} // namespace fs

#endif // _FW_FILEWATCHERIMPL_H_

#ifndef _FW_FILEWATCHERLINUX_H_
#define _FW_FILEWATCHERLINUX_H_
#pragma once

#include "FileWatcherImpl.h"

#if FILEWATCHER_PLATFORM == FILEWATCHER_PLATFORM_LINUX

#include <map>
#include <sys/types.h>

namespace fs
{
    /// Implementation for Linux based on inotify.
    /// @class FileWatcherLinux
    class FileWatcherLinux : public FileWatcherImpl
    {
    public:
        /// type for a map from WatchID to WatchStruct pointer
        typedef std::map<WatchID, WatchStruct*> WatchMap;

    public:
        ///
        ///
        FileWatcherLinux();

        ///
        ///
        virtual ~FileWatcherLinux();

        /// Add a directory watch
        /// @exception FileNotFoundException Thrown when the requested directory does not exist
        WatchID addWatch(const String& directory, FileWatchListener* watcher, bool recursive);

        /// Remove a directory watch. This is a brute force lazy search O(nlogn).
        void removeWatch(const String& directory);

        /// Remove a directory watch. This is a map lookup O(logn).
        void removeWatch(WatchID watchid);

        /// Updates the watcher. Must be called often.
        void update();

        /// Handles the action
        void handleAction(WatchStruct* watch, const String& filename, unsigned long action);

    private:
        /// Map of WatchID to WatchStruct pointers
        WatchMap mWatches;
        /// The last watchid
        WatchID mLastWatchID;
        /// inotify file descriptor
        int mFD;
        /// time out data
        struct timeval mTimeOut;
        /// File descriptor set
        fd_set mDescriptorSet;

    }; // end FileWatcherLinux

} // namespace fs

#endif // FILEWATCHER_PLATFORM_LINUX

#endif // _FW_FILEWATCHERLINUX_H_
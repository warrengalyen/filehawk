#ifndef _FW_FILEWATCHEROSX_H_
#define _FW_FILEWATCHEROSX_H_
#pragma once

#include "FileWatcherImpl.h"

#if FILEWATCHER_PLATFORM == FILEWATCHER_PLATFORM_KQUEUE
#include <map>
#include <sys/types.h>

namespace fs
{
    /// Implementation for OSX based on kqueue.
    /// @class FileWatcherOSX
    class FileWatcherOSX : public FileWatcherImpl
    {
    public:
        /// type for a map from WatchID to WatchStruct pointer
        typedef std::map<WatchID, WatchStruct*> WatchMap;

    public:
        ///
        ///
        FileWatcherOSX();

        ///
        ///
        virtual ~FileWatcherOSX();

        /// Add a directory watch
        /// @exception FileNotFoundException Thrown when the requested directory does not exist
        WatchID addWatch(const String& directory, EventHandler watcher, bool recursive);

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
        /// The descriptor for the kqueue
        int mDescriptor;
        /// time out data
        struct timespec mTimeOut;
        /// WatchID allocator
        int mLastWatchID;

    }; // end FileWatcherOSX

} // namespace fs

#endif // __APPLE_CC__

#endif // _FW_FILEWATCHEROSX_H_
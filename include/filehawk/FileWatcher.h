#ifndef _FW_FILEWATCHER_H_
#define _FW_FILEWATCHER_H_
#pragma once

#include <string>
#include <stdexcept>
#include <functional>

namespace fs
{
    using String = std::string;
    using WatchID = unsigned long;
    
    // forward declarations
    class FileWatcherImpl;

    /// Base exception class
    /// @class Exception
    class Exception : public std::runtime_error
    {
    public:
        Exception(const String& message)
            : std::runtime_error(message)
        {}
    };

    /// Exception thrown when a file is not found.
    /// @class FileNotFoundException
    class FileNotFoundException : public Exception
    {
    public:
        FileNotFoundException()
            : Exception("File not found")
        {}

        FileNotFoundException(const String& filename)
            : Exception("File not found (" + filename + ")")
        {}
    };

    /// Actions to listen for. Rename will send two events, one for
    /// the deletion of the old file, and one for the creation of the
    /// new file.
    namespace Actions
    {
        enum Action
        {
            /// Sent when a file is created or renamed
            Add = 1,
            /// Sent when a file is deleted or renamed
            Delete = 2,
            /// Sent when a file is modified
            Modified = 4
        };
    };
    typedef Actions::Action Action;

    using EventHandler = std::function<void(WatchID watchid, const String& dir, const String& filename, Action action)>;

    /// Listens to files and directories and dispatches events
    /// to notify the parent program of the changes.
    /// @class FileWatcher
    class FileWatcher
    {
    public:
        ///
        ///
        FileWatcher();

        ///
        ///
        virtual ~FileWatcher();

        /// Add a directory watch. Same as the other addWatch, but doesn't have recursive option.
        /// For backwards compatibility.
        /// @exception FileNotFoundException Thrown when the requested directory does not exist
        WatchID addWatch(const String& directory, std::function<void(WatchID watchid, const String& dir, const String& filename, Action action)> handler);

        /// Add a directory watch
        /// @exception FileNotFoundException Thrown when the requested directory does not exist
        WatchID addWatch(const String& directory, std::function<void(WatchID watchid, const String& dir, const String& filename, Action action)> handler, bool recursive);

        /// Remove a directory watch. This is a brute force search O(nlogn).
        void removeWatch(const String& directory);

        /// Remove a directory watch. This is a map lookup O(logn).
        void removeWatch(WatchID watchid);

        /// Updates the watcher. Must be called often.
        void update();

    private:
        /// The implementation
        FileWatcherImpl* mImpl;
    }; // end FileWatcher

};  // namespace fs

#endif // _FW_FILEWATCHER_H_
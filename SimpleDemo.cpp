#include <filehawk/FileWatcher.h>
#include <iostream>

int main(int argc, char** argv)
{
	try
	{
		// create the file watcher object
		fs::FileWatcher fileWatcher;

		// add a directory watch to the system
        // this scans the `test/` directory for any changes
		fs::WatchID watchID = fileWatcher.addWatch("test", [](
			fs::WatchID watchID, const std::string& dir, const std::string filename, fs::Action action
		) -> void {
			std::cout << "DIR ( " << dir << " ) FILE ( " << filename << " ) has event " << action << std::endl;
		});
		
		std::cout << "Press ^C to exit demo" << std::endl;

		// loop until a key is pressed
		while (true)
		{
			fileWatcher.update();
		}
	}
	catch (std::exception& e)
	{
		fprintf(stderr, "An exception has occurred: %s\n", e.what());
	}

	return 0;
}

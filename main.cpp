#include <iostream>
#include <Magick++.h>
using namespace Magick;

int main(int argc, char** argv)
{
	if (argc < 3) {
		std::cout << "Too few arguments" << std::endl;
		return 1;
	}

#ifdef _WIN32
	InitializeMagick(*argv);
#endif

	Image background, retain;
	try {
		background.read(argv[1]);
		if (background.baseColumns() != background.baseRows()) {
			std::cout << "Not a square image" << std::endl;
			return 1;
		}

		retain = background;
		retain.resize({ 1080, 1080 });

		background.gaussianBlur(100.0, 5.0);
		background.resize({ 1920, 1920 });
		background.crop({ 1920, 1080, 0, 420 });
		background.colorize(50, { 0, 0, 0 });
		background.composite(retain, 420, 0);
		background.write(argv[2]);
	}
	catch (Exception & e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

#include "application.h"

int main(int argc, char* argv[]) 
{ 
    Application application = Application();
    if (!application.initialize())
    {
        return -1;
    }

	application.run();

	application.cleanup();
	return 0;
}

#include <iostream>

using namespace std;

extern "C" {
int mainMetaData();
int mux(char* ainputfile, char* vinputfile, char* outfile);
}

int main()
{
//    int ret = mainMetaData();
    int ret = mux("audio.mp4", "video.mp4", "mux.mp4");

    std::cout << "return: " << ret << std::endl;
    return 0;
}

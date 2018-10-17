#include <iostream>
#include <string>
#include <vector>
#include "Socket.h"
#include "FileManager.h"

int main()
{
	
	Socket socket;
	std::vector<char> data;
	while (true)
	{
		char buffer[512];

		int bytesRead = socket.readData(buffer, sizeof(buffer));

		if (bytesRead)
			data.insert(data.end(), buffer, buffer + bytesRead);
		else
			break;
		
	}
	FileManager fileManager;
	fileManager.writeFile(data, "testFile.txt");
	socket.disconnect();
    
}


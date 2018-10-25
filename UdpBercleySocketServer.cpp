#include <iostream>
#include <string>
#include "Socket.h"
#include "FileManager.h"

int main()
{
	
	Socket socket;
	FileManager fileManager;
	char buffer[1024];
	while (true)
	{
		int bytesRead = socket.readData(buffer, 1024);
		if(bytesRead>0)
			if (!(fileManager.writeFile(buffer, "D:\\TableScan Turbo+++.rar")))
			{
				std::cout << "Write in file error" << std::endl;
				break;
			}
					
	}

	fileManager.closeStream();
	socket.disconnect();
    
}


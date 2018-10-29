#include <iostream>
#include <string>
#include "Socket.h"
#include "FileManager.h"

int main()
{
	
	Socket socket;
	FileManager fileManager;
	char opperationBuffer[8];
	char fileBuffer[1024];
	int command = 0;

	while (true)
	{
		int bytesRead = socket.reciveCommand(opperationBuffer);
		if (bytesRead == 8)
		{
			command = atoi(opperationBuffer);
			break;
		}
			 
	}
	switch (command)
	{
		case FileManager::Commands::comReciveFileSize:
		{
			while (true)
			{
				int bytesRead = socket.readData(opperationBuffer, 8);
				if (bytesRead == 8)
				{
					fileManager.setFileSize(atoi(opperationBuffer));
					break;
				}

			}
			break;
		}
		case FileManager::Commands::comResiveFile:
		{
			while (true)
			{
				int bytesRead = socket.readData(fileBuffer, 1024);
				if (bytesRead > 0)
					if (!(fileManager.writeFile(fileBuffer, fileManager.getFileName())))
					{
						std::cout << "Write in file error" << std::endl;
						break;
					}
			}
			break;
		}
		case FileManager::Commands::comReciveFileNameSize:
		{
			while (true)
			{
				int bytesRead = socket.readData(opperationBuffer, 8);
				if (bytesRead == 8)
				{
					fileManager.setFileNameSize(atoi(opperationBuffer));
					break;
				}
			}
			break;
		}
		
		case FileManager::Commands::comReciveFileName:
		{ 
			char* fileName = new char[fileManager.getFileNameSize()];
			while (true)
			{
				int bytesRead = socket.readData(fileName, fileManager.getFileNameSize());
				if (bytesRead == fileManager.getFileNameSize())
				{
					fileManager.setFileName(fileName);
					break;
				}
			}
			delete[] fileName;
			break;
		}
		default:
		{
			std::cout << "command incorrect" << std::endl;
			break;
		}
	}
	
	
	fileManager.closeStream();
	socket.disconnect();
    
}


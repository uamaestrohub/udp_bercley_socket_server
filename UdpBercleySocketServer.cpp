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
						std::cout << "Recive file size: " << atoi(opperationBuffer) << std::endl;
						
						break;
					}

				}
				break;
			}
			case FileManager::Commands::comResiveFile:
			{
				std::cout << "Start write in file: "<<std::endl << std::endl;
				while (true)
				{
					int bytesRead = socket.readData(fileBuffer, 1024);
					if (bytesRead > 0)
					{
						if (!(fileManager.writeFile(fileBuffer, fileManager.getFileName())))
						{
							std::cout << "Write in file error" << std::endl;
							break;
						}
						std::cout << "Write in file bytes: "<< bytesRead << std::endl;

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
						std::cout << "Set fileNameSize: " << atoi(opperationBuffer) << std::endl;
						break;
					}
				}
				break;
			}

			case FileManager::Commands::comReciveFileName:
			{
				char* fileName = new char[fileManager.getFileNameSize()+1];
				while (true)
				{
					int bytesRead = socket.readData(fileName, fileManager.getFileNameSize()+1);
					if (bytesRead == fileManager.getFileNameSize()+1)
					{
						fileManager.setFileName(fileName);
						std::cout << "Set file Name: " << fileName << std::endl;
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
		}
	}
	fileManager.closeStream();
	socket.disconnect();
}


namespace gmk
{
	r_string getFileContent(r_string _path)
	{
		FILE* file;
		r_string content;

		r_int32 fileSize;
		r_int8* fileContent;

		fopen_s(&file, _path.c_str(), "rb+");

		if (!file)
			return "ERROR";

		fseek(file, 0, SEEK_END);

		fileSize = ftell(file);

		if (fileSize <= 0)
		{
			fclose(file);
			return "ERROR";
		}

		fseek(file, 0, SEEK_SET);

		fileContent = new r_int8[fileSize + 1];

		if (fread_s(fileContent, fileSize, sizeof(r_int8), fileSize, file) != fileSize)
		{
			fclose(file);
			delete fileContent;
			return "ERROR";
		}

		fileContent[fileSize] = 0;

		content = fileContent;

		fclose(file);

		delete fileContent;
		return content;
	}
}
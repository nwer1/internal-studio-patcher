#include <iostream>
#include <fstream>
#include <filesystem>

constexpr size_t offsets[] = {
	0x6f58bda, 0x6f58c16, 0x6f58c1f, 0x6f58c57, 0x6f58c60, 0x6f58c8f, 0x6f58c98, 0x6f58cba, 0x6f58d1a, 0x6f58d23
};

int main(int argc, const char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " path_to_roblox_studio" << std::endl;
		return 0;
	}

	if (std::filesystem::path(argv[1]).is_absolute())
	{
		std::fstream file(argv[1], std::ios::in | std::ios::out | std::ios::binary);
		if (file)
        {
			int successRate = 0;

			for (size_t offset : offsets)
			{
				file.seekp((std::streamoff)offset, std::ios::beg);
				file.put((char)0xFF);

				if (file.good())
					successRate++;
			}

			std::cout << successRate << "/" << std::size(offsets) << " successfully patched!" << std::endl;
        }
	}
	else
		std::cout << "Invalid path!" << std::endl;
}

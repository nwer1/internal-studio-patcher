#include <iostream>
#include <fstream>
#include <filesystem>

constexpr size_t offsets[] = {
	0x2833aea, 0x2833b26, 0x2833b2f, 0x2833b67, 0x2833b70, 0x2833b9f, 0x2833ba8, 0x2833bca, 0x2833c2a, 0x2833c33
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
				file.seekp(static_cast<std::streamoff>(offset), std::ios::beg);
				file.put(static_cast<char>(0xFF));

				if (file.good())
					successRate++;
			}

			std::cout << successRate << "/" << std::size(offsets) << " successfully patched!" << std::endl;
        }
	}
	else
		std::cout << "Invalid path!" << std::endl;
}

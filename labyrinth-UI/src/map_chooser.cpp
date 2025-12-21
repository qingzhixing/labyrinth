#include <map_chooser.h>
#include <iostream>
#include <vector>
#include <game_controller.h>
#include <filesystem>
#include <game_info.h>
#include <ui_utilities.h>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

static vector<string> GetMapFilesInCurrentDirectory()
{
	vector<string> map_files;
	// 遍历当前目录下的所有文件
	for (const auto &entry : std::filesystem::directory_iterator("."))
	{
		if (entry.path().extension() == ".txt")
		{
			// 去掉路径中的 "**/"
			// 查找最后一个 '/' 字符的索引
			size_t last_slash_index = entry.path().string().find_last_of('/');
			// 提取文件名部分
			string map_file_name = entry.path().string().substr(last_slash_index + 1);
			map_files.push_back(map_file_name);
		}
	}
	return map_files;
}

pair<string, bool> ChooseMap()
{
	string map_file_path;

	vector<string> map_files = GetMapFilesInCurrentDirectory();
	if (map_files.empty())
	{
		cout << "当前目录下没有地图文件! " << endl;
		cout << "    如果你想要添加地图,请将地图文件放入当前目录下!" << endl
			 << endl;
		cout << "游戏自动结束!" << endl;

		return make_pair("", false);
	}

	bool choose_ok = false;
	while (!choose_ok)
	{

		ClearScreen();

		cout << "请选择你想要游玩的地图!" << endl;

		// 打印.txt名称,并编号
		for (size_t i = 0; i < map_files.size(); ++i)
		{
			cout << i << ". " << map_files[i] << endl;
		}

		cout << "请输入地图编号 (输入 \"quit!\" 以退出选择!):" << endl;

		string chosen_str;
		cin >> chosen_str;

		if (chosen_str == "quit!")
		{
			cout << "退出选择!" << endl;
			return make_pair("", false);
		}

		if (cin.fail() || chosen_str.empty())
		{
			cout << "输入无效! 请重新输入!" << endl;
			cin.clear();
			// 忽略输入缓冲区中的剩余字符
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		try
		{
			map_file_path = map_files[std::stoi(chosen_str)];
		}
		catch (const std::invalid_argument &e)
		{
			cout << "输入 \"" << chosen_str << "\" 不是一个有效的整数! 请重新输入!" << endl;
			continue;
		}
		catch (const std::out_of_range &e)
		{
			cout << "输入 \"" << chosen_str << "\" 超出了整数范围! 请重新输入!" << endl;
			continue;
		}

		// 判断地图index范围
		if (std::stoi(chosen_str) < 0 || std::stoi(chosen_str) >= map_files.size())
		{
			cout << "输入 \"" << chosen_str << "\" 超出了地图范围! 请重新输入!" << endl;
			continue;
		}

		// 判断地图是否合法,若不合法则返回错误给用户
		auto error_code = GameController::ValidateMap(
			("./" + GAME_CORE_EXECUTABLE_NAME),
			map_file_path);
		if (error_code != ErrorCode::SUCCESS)
		{
			cout << "地图文件 \"" << map_file_path << "\" 不合法! 请重新选择!" << endl;
			cout << "错误码: " << error_code << endl;
			continue;
		}

		choose_ok = true;
	}

	return make_pair(map_file_path, true);
}

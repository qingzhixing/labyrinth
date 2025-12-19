#pragma once
#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <map_validator.h>
#include <map_row_processor.h>
#include <map_builder.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <utility>
#include <types/error_code.h>

class MapParser
{
public:
	/**
	 * @brief 读取地图数据 - 从文件流中读取地图数据并构建 GameMapExtend 对象
	 * @param map_stream 输入文件流，用于读取地图数据
	 * @return pair<GameMapExtend, ErrorCode> 包含构建的地图对象和错误码的对
	 */
	static std::pair<GameMapExtend, ErrorCode>
	ReadMapData(std::ifstream &map_stream)
	{
		std::vector<MapRow> map_data;
		MapCoordinateRecorder recorder;
		int line_index = 0;
		int expected_columns = 0;

		std::string current_line_str;
		while (std::getline(map_stream, current_line_str))
		{
			line_index++;

			// 验证地图大小
			if (!MapValidator::ValidateSize(
					line_index, static_cast<int>(current_line_str.length())))
			{
				return std::make_pair(
					GameMapExtend(),
					ErrorCode::MAP_TOO_LARGE);
			}

			// 验证行长度一致性
			if (!MapValidator::ValidateLineLengths(
					expected_columns,
					static_cast<int>(current_line_str.length()),
					line_index))
			{
				return std::make_pair(
					GameMapExtend(),
					ErrorCode::MAP_INCONSISTENT_ROW);
			}

			// 处理单行数据
			auto line_result = MapRowProcessor::ProcessRow(
				current_line_str,
				line_index,
				recorder);
			if (line_result.second != ErrorCode::SUCCESS)
			{
				return std::make_pair(
					GameMapExtend(),
					line_result.second);
			}

			map_data.push_back(std::move(line_result.first));

			// 设置期望的列数（只在第一行设置）
			if (expected_columns == 0)
			{
				expected_columns = static_cast<int>(current_line_str.length());
			}
		}

		// 构建最终的地图对象
		return MapBuilder::BuildFinalMap(
			map_data,
			recorder,
			line_index,
			expected_columns);
	}

	static std::pair<GameMapExtend, ErrorCode>
	ParseMapFile(const std::string &map_file_path)
	{
		GameMapExtend game_map;

		// Check The Map File Exists
		if (std::filesystem::exists(map_file_path) == false)
		{
			DebugLog(
				LogLevel::ERROR,
				"Map file not found: %s",
				map_file_path.c_str());
			return std::make_pair(
				std::move(game_map),
				ErrorCode::MAP_FILE_NOT_FOUND);
		}

		// Check The Map File Is Not A Directory
		if (std::filesystem::is_directory(map_file_path))
		{
			DebugLog(
				LogLevel::ERROR,
				"Map file is a directory: %s", map_file_path.c_str());
			return std::make_pair(
				std::move(game_map),
				ErrorCode::MAP_FILE_IS_DIRECTORY);
		}

		auto game_map_stream = std::ifstream(map_file_path);
		if (game_map_stream.is_open() == false)
		{
			DebugLog(LogLevel::ERROR,
					 "Failed to open map file: %s", map_file_path.c_str());
			return std::make_pair(
				std::move(game_map),
				ErrorCode::MAP_FILE_NOT_FOUND);
		}

		ErrorCode read_map_error_code =
			ErrorCode::DEFAULT_ERROR_CODE;

		// 读取地图数据
		std::tie(game_map, read_map_error_code) =
			ReadMapData(game_map_stream);

		if (read_map_error_code != ErrorCode::SUCCESS)
		{
			DebugLog(LogLevel::ERROR,
					 read_map_error_code.toMessage());
			return std::make_pair(std::move(game_map), read_map_error_code);
		}

		return std::make_pair(std::move(game_map), ErrorCode::SUCCESS);
	}
};

#endif // MAP_PARSER_H
#include <argument_validator.h>
#include <testkit.h>
#include <map>

UnitTest(CheckMissingParameters_Invalid)
{
	ParsedResult parsed_result{};
	ErrorCode error_code =
		CheckMissingParameters(parsed_result);
	assert(
		error_code ==
		ErrorCode::MISSING_PARAMETERS);
}

UnitTest(CheckMissingParameters_Valid)
{
	ParsedResult parsed_result{
		.map_file = "map.txt",
		.direction = "up",
	};
	ErrorCode error_code =
		CheckMissingParameters(parsed_result);
	assert(error_code == ErrorCode::SUCCESS);
}

UnitTest(ValidateMoveDirection_Invalid)
{
	std::string direction_str = "invalid";
	auto [direction, error_code] =
		ValidateMoveDirection(direction_str);
	assert(
		error_code ==
		ErrorCode::INVALID_MOVE_DIRECTION);
}

UnitTest(ValidateMoveDirection_Valid)
{
	for (
		const auto &[direction_str, direction] :
		std::map<std::string, Direction>{
			{"up", Direction::UP},
			{"down", Direction::DOWN},
			{"left", Direction::LEFT},
			{"right", Direction::RIGHT},
		})
	{
		auto [validated_direction, error_code] =
			ValidateMoveDirection(direction_str);
		assert(error_code == ErrorCode::SUCCESS);
		assert(validated_direction == direction);
	}
}

UnitTest(ValidateParsedResult_Invalid_MissingParameters)
{
	ParsedResult parsed_result{};
	auto result_with_error_code =
		ValidateParsedResult(parsed_result);
	assert(
		result_with_error_code.error_code ==
		ErrorCode::MISSING_PARAMETERS);
}

UnitTest(ValidateParsedResult_Invalid_InvalidMoveDirection)
{
	std::string valid_map_path = "map_test_" + std::to_string(rand()) + ".txt";
	// 创建一个空文件
	std::ofstream map_file(valid_map_path);
	map_file.close();

	ParsedResult parsed_result{
		.map_file = valid_map_path,
		.direction = "invalid",
	};
	auto result_with_error_code =
		ValidateParsedResult(parsed_result);

	// 删除测试文件
	std::remove(valid_map_path.c_str());

	assert(
		result_with_error_code.error_code ==
		ErrorCode::INVALID_MOVE_DIRECTION);
}

UnitTest(ValidateParsedResult_Invalid_MapFileNotFound)
{
	std::string invalid_map_path =
		"map_test_" +
		std::to_string(rand()) +
		".txt";
	ParsedResult parsed_result{
		.map_file = invalid_map_path,
		.direction = "up",
	};
	auto result_with_error_code =
		ValidateParsedResult(parsed_result);

	assert(
		result_with_error_code.error_code ==
		ErrorCode::MAP_FILE_NOT_FOUND);
}

UnitTest(ValidateParsedResult_Valid)
{
	std::string valid_map_path =
		"map_test_" +
		std::to_string(rand()) +
		".txt";

	std::ofstream map_file(valid_map_path);
	map_file
		<< ".." << std::endl
		<< "0@" << std::endl;
	map_file.close();

	ParsedResult parsed_result{
		.map_file = valid_map_path,
		.direction = "up",
	};
	auto result_with_error_code =
		ValidateParsedResult(parsed_result);

	// 删除测试文件
	std::remove(valid_map_path.c_str());

	auto [validated_game_context, error_code] = result_with_error_code;

	assert(error_code == ErrorCode::SUCCESS);

	auto &game_map =
		validated_game_context.game_map;
	auto &direction =
		validated_game_context.direction;
	auto &map_file_path =
		validated_game_context.map_file_path;

	assert(direction == Direction::UP);
	assert(map_file_path == valid_map_path);
	assert(game_map.player_coordinate == Coordinate(1, 0));
	assert(game_map.map_data[1][0] == MapCellType::PLAYER);
}
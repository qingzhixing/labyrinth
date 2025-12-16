#include <map_coordinate_recorder.h>
#include <testkit.h>

class MapCoordinateRecorderTest
{
public:
	static bool IsPlayerCell(MapCellType cell_type)
	{
		return MapCoordinateRecorder::IsPlayerCell(cell_type);
	}
	static bool IsDestinationCell(MapCellType cell_type)
	{
		return MapCoordinateRecorder::IsDestinationCell(cell_type);
	}
};

UnitTest(MapCoordinateRecorder_IsPlayerCell)
{
	MapCoordinateRecorderTest recorderTest;
	assert(recorderTest.IsPlayerCell(MapCellType::PLAYER));
	assert(recorderTest.IsPlayerCell(MapCellType::PLAYER_AT_DESTINATION));
	assert(!recorderTest.IsPlayerCell(MapCellType::SPACE));
	assert(!recorderTest.IsPlayerCell(MapCellType::DESTINATION));
	assert(!recorderTest.IsPlayerCell(MapCellType::WALL));
}

UnitTest(MapCoordinateRecorder_IsDestinationCell)
{
	MapCoordinateRecorderTest recorderTest;
	assert(recorderTest.IsDestinationCell(MapCellType::DESTINATION));
	assert(recorderTest.IsDestinationCell(MapCellType::PLAYER_AT_DESTINATION));
	assert(!recorderTest.IsDestinationCell(MapCellType::SPACE));
	assert(!recorderTest.IsDestinationCell(MapCellType::PLAYER));
	assert(!recorderTest.IsDestinationCell(MapCellType::WALL));
}

UnitTest(MapCoordinateRecorder_RecordPlayerIfNeeded_Valid)
{
	MapCoordinateRecorder recorder;
	GameCoreErrorCode result = recorder.RecordPlayerIfNeeded(
		MapCellType::PLAYER, 1, 1);
	assert(result == GameCoreErrorCode::SUCCESS);
	assert(recorder.GetPlayerCoordinate() == Coordinate(1, 1));
}

UnitTest(MapCoordinateRecorder_RecordPlayerIfNeeded_NotAPlayerCell)
{
	MapCoordinateRecorder recorder;
	GameCoreErrorCode result = recorder.RecordPlayerIfNeeded(
		MapCellType::SPACE, 1, 1);
	assert(result == GameCoreErrorCode::SUCCESS);
	assert(!recorder.HasPlayer());
}

UnitTest(MapCoordinateRecorder_RecordPlayerIfNeeded_MultiplePlayers)
{
	MapCoordinateRecorder recorder;
	GameCoreErrorCode result = recorder.RecordPlayerIfNeeded(
		MapCellType::PLAYER, 1, 1);
	assert(result == GameCoreErrorCode::SUCCESS);
	assert(recorder.GetPlayerCoordinate() == Coordinate(1, 1));
	result = recorder.RecordPlayerIfNeeded(
		MapCellType::PLAYER, 2, 2);
	assert(result == GameCoreErrorCode::MAP_MULTIPLE_PLAYER);
	assert(recorder.HasPlayer());
}

UnitTest(MapCoordinateRecorder_RecordDestinationIfNeeded_Valid)
{
	MapCoordinateRecorder recorder;
	GameCoreErrorCode result = recorder.RecordDestinationIfNeeded(
		MapCellType::DESTINATION, 1, 1);
	assert(result == GameCoreErrorCode::SUCCESS);
	assert(recorder.GetDestination() == Coordinate(1, 1));
}

UnitTest(MapCoordinateRecorder_RecordDestinationIfNeeded_NotADestinationCell)
{
	MapCoordinateRecorder recorder;
	GameCoreErrorCode result = recorder.RecordDestinationIfNeeded(
		MapCellType::SPACE, 1, 1);
	assert(result == GameCoreErrorCode::SUCCESS);
	assert(!recorder.HasDestination());
}

UnitTest(MapCoordinateRecorder_RecordDestinationIfNeeded_MultipleDestinations)
{
	MapCoordinateRecorder recorder;
	GameCoreErrorCode result = recorder.RecordDestinationIfNeeded(
		MapCellType::DESTINATION, 1, 1);
	assert(result == GameCoreErrorCode::SUCCESS);
	assert(recorder.GetDestination() == Coordinate(1, 1));
	result = recorder.RecordDestinationIfNeeded(
		MapCellType::DESTINATION, 2, 2);
	assert(result == GameCoreErrorCode::MAP_MULTIPLE_DESTINATION);
	assert(recorder.HasDestination());
}
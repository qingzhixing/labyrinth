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

// TODO: Unimplement
// UnitTest(MapCoordinateRecorder_RecordPlayerIfNeeded)
// {
// 	MapCoordinateRecorder recorder;
// }
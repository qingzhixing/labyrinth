#include <map_row_processor.h>
#include <testkit.h>

UnitTest(TestMapLineProcessor)
{
	MapCoordinateRecorder recorder;
	auto result = MapRowProcessor::ProcessRow(
		".@..0", 1, recorder);

	assert(result.second == ErrorCode::SUCCESS);
	assert(result.first.size() == 5);

	assert(result.first[0] == MapCellType::SPACE);
	assert(result.first[1] == MapCellType::DESTINATION);
	assert(result.first[2] == MapCellType::SPACE);
	assert(result.first[3] == MapCellType::SPACE);
	assert(result.first[4] == MapCellType::PLAYER);

	assert(recorder.GetPlayerCoordinate() == Coordinate(0, 4));
}
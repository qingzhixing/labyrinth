#include <map_row_processor.h>

std::pair<MapRow, ErrorCode>
MapRowProcessor::ProcessRow(
	const std::string &row_str,
	int row_index,
	MapCoordinateRecorder &recorder)
{
	MapRow map_row;

	for (size_t column = 0; column < row_str.length(); column++)
	{
		char ch = row_str[column];
		auto cell_type = GetMapCellType(ch);

		// 验证单元格类型
		if (!MapValidator::ValidateCellType(
				cell_type, ch, row_index))
		{
			return make_pair(
				MapRow(),
				ErrorCode::INVALID_MAP_FORMAT);
		}

		map_row.push_back(cell_type);

		// 记录坐标
		auto record_error = recorder.RecordCoordinates(
			cell_type, row_index - 1, static_cast<int>(column));
		if (record_error != ErrorCode::SUCCESS)
		{
			return make_pair(MapRow(), record_error);
		}
	}

	return make_pair(
		move(map_row),
		ErrorCode::SUCCESS);
}
#include <map_line_processor.h>

std::pair<MapLine, ErrorCode>
MapLineProcessor::ProcessLine(
	const std::string &line_str,
	int line_index,
	MapCoordinateRecorder &recorder)
{
	MapLine map_line;

	for (size_t column = 0; column < line_str.length(); column++)
	{
		char ch = line_str[column];
		auto cell_type = GetMapCellType(ch);

		// 验证单元格类型
		if (!MapValidator::ValidateCellType(
				cell_type, ch, line_index))
		{
			return make_pair(
				MapLine(),
				ErrorCode::INVALID_MAP_FORMAT);
		}

		map_line.push_back(cell_type);

		// 记录坐标
		auto record_error = recorder.RecordCoordinates(
			cell_type, line_index - 1, static_cast<int>(column));
		if (record_error != ErrorCode::SUCCESS)
		{
			return make_pair(MapLine(), record_error);
		}
	}

	return make_pair(
		move(map_line),
		ErrorCode::SUCCESS);
}
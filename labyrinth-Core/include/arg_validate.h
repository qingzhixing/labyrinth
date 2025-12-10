#pragma once
#ifndef ARG_VALIDATE_H
#define ARG_VALIDATE_H

#include <arg_result.h>

/**
 * @brief Validate the parsed result.
 *
 * @param parsedResult The parsed result.
 * @return ValidatedGameContextWithErrorCode The validated game context with error code.
 */
ValidatedGameContextWithErrorCode ValidateParsedResult(const ParsedResult &parsedResult);

/**
 * @brief Check for missing parameters in the parsed result.
 *
 * @param parsedResult The parsed result.
 * @return GameCoreErrorCode The error code if parameters are missing, otherwise SUCCESS.
 */
GameCoreErrorCode CheckMissingParameters(const ParsedResult &parsedResult);

/**
 * @brief Validate the move direction.
 *
 * @param move_direction The move direction string.
 * @return [Direction, GameCoreErrorCode] The validated direction with error code.
 */
std::pair<Direction, GameCoreErrorCode> ValidateMoveDirection(const std::string &move_direction);

/**
 * @brief Validate the player ID.
 *
 * @param player_id The player ID string.
 * @return [int, GameCoreErrorCode] The validated player ID with error code.
 */
std::pair<int, GameCoreErrorCode> ValidatePlayerID(const std::string &player_id);

/**
 * @brief Validate the map file.
 *
 * @param map_file The map file string.
 * @return [GameMap, GameCoreErrorCode] The validated map file with error code.
 */
std::pair<GameMap, GameCoreErrorCode> ValidateMapFile(const std::string &map_file);

#endif // ARG_VALIDATE_H
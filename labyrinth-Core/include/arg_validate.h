#pragma once
#ifndef ARG_VALIDATE_H
#define ARG_VALIDATE_H

#include <parsed_result.h>

/**
 * @brief Validate the parsed result.
 *
 * @param parsedResult The parsed result.
 * @return GameCoreErrorCode The error code of the validation.
 */
GameCoreErrorCode ValidateParsedResult(const ParsedResult &parsedResult);

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
 * @return GameCoreErrorCode The error code of the validation.
 */
GameCoreErrorCode ValidateMoveDirection(const std::string &move_direction);

/**
 * @brief Validate the player ID.
 *
 * @param player_id The player ID string.
 * @return GameCoreErrorCode The error code of the validation.
 */
GameCoreErrorCode ValidatePlayerID(const std::string &player_id);

/**
 * @brief Validate the map file.
 *
 * @param map_file The map file string.
 * @return GameCoreErrorCode The error code of the validation.
 */
GameCoreErrorCode ValidateMapFile(const std::string &map_file);
#endif // ARG_VALIDATE_H

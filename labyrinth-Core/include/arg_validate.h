#pragma once
#ifndef ARG_VALIDATE_H
#define ARG_VALIDATE_H

#include <arg_result.h>

/**
 * @brief Validate the parsed result.
 *
 * @param parsed_result The parsed result.
 * @return ValidatedGameContextWithErrorCode The validated game context with error code.
 */
ValidatedGameContextWithErrorCode ValidateParsedResult(const ParsedResult &parsed_result);

/**
 * @brief Check for missing parameters in the parsed result.
 *
 * @param parsed_result The parsed result.
 * @return GameCoreErrorCode The error code if parameters are missing, otherwise SUCCESS.
 */
GameCoreErrorCode CheckMissingParameters(const ParsedResult &parsed_result);

/**
 * @brief Validate the move direction.
 *
 * @param move_direction The move direction string.
 * @return [Direction, GameCoreErrorCode] The validated direction with error code.
 */
std::pair<Direction, GameCoreErrorCode> ValidateMoveDirection(const std::string &move_direction);

#endif // ARG_VALIDATE_H
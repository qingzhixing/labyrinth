#pragma once
#ifndef ARGUMENT_VALIDATOR_H
#define ARGUMENT_VALIDATOR_H

#include <argument_result.h>
#include <types/core_error_code.h>
#include <types/direction.h>

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
 * @param direction The move direction string.
 * @return [Direction, GameCoreErrorCode] The validated direction with error code.
 */
std::pair<Direction, GameCoreErrorCode> ValidateMoveDirection(const std::string &direction);

#endif // ARG_VALIDATE_H
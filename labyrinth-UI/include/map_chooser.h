#pragma once
#ifndef MAP_CHOOSER_H
#define MAP_CHOOSER_H

#include <string>
#include <utility>

/**
 * @brief 选择地图
 *
 *
 * @return std::pair<std::string, bool> 地图文件路径和是否成功选择
 * 用户输入quit! 则返回空字符串和false,否则一直选择直到选择了一个有效地图
 */
std::pair<std::string, bool> ChooseMap();

#endif // MAP_CHOOSER_H

/*
 * Copyright © 2026 Deluge Community Firmware contributors
 *
 * This file is part of The Synthstrom Audible Deluge Firmware.
 *
 * The Synthstrom Audible Deluge Firmware is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 */

#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>

namespace deluge::dsp::timestretch::akai {

/// The Akai S950/S1000 grain (cycle) length range. Short cycles give the tight, cyclic "chatter" of the S950; long
/// cycles give the smeared, vocal-like sound of the S1000's wide crossfades.
constexpr int32_t kMinWindowMs = 8;
constexpr int32_t kMaxWindowMs = 50;
constexpr int32_t kDefaultWindowMs = 24;

constexpr int32_t kMinWindowTimes100 = kMinWindowMs * 100;
constexpr int32_t kMaxWindowTimes100 = kMaxWindowMs * 100;
constexpr int32_t kDefaultWindowTimes100 = kDefaultWindowMs * 100;

/// Unpatched params are displayed on a 0..50 menu scale. Map the full parameter range onto that scale first so that
/// the seven-segment display agrees with the grain length the DSP uses.
constexpr int32_t paramToMenuValue(int32_t paramValue) {
	uint64_t position = static_cast<uint64_t>(paramValue) + 2147483648ull;
	int32_t menuValue = static_cast<int32_t>((position * 50 + (1ull << 31)) >> 32);
	if (menuValue < 0) {
		return 0;
	}
	if (menuValue > 50) {
		return 50;
	}
	return menuValue;
}

constexpr int32_t menuToWindowTimes100(int32_t menuValue) {
	int32_t value = std::clamp<int32_t>(menuValue, 0, 50);
	return kMinWindowTimes100 + (value * (kMaxWindowTimes100 - kMinWindowTimes100) + 25) / 50;
}

constexpr int32_t paramToWindowTimes100(int32_t paramValue) {
	return menuToWindowTimes100(paramToMenuValue(paramValue));
}

constexpr int32_t windowTimes100ToParam(int32_t windowTimes100) {
	if (windowTimes100 <= kMinWindowTimes100) {
		return std::numeric_limits<int32_t>::min();
	}
	if (windowTimes100 >= kMaxWindowTimes100) {
		return std::numeric_limits<int32_t>::max();
	}
	int64_t menuValue =
	    (static_cast<int64_t>(windowTimes100 - kMinWindowTimes100) * 50 + (kMaxWindowTimes100 - kMinWindowTimes100) / 2)
	    / (kMaxWindowTimes100 - kMinWindowTimes100);
	return static_cast<int32_t>(menuValue * 85899345 - 2147483648ll);
}

constexpr int32_t defaultGrainParamValue() {
	return windowTimes100ToParam(kDefaultWindowTimes100);
}

inline int32_t windowSamples(int32_t windowTimes100, int32_t sampleRate) {
	int64_t samples = (static_cast<int64_t>(windowTimes100) * sampleRate + 50000) / 100000;
	if (samples < 32) {
		return 32;
	}
	if (samples > 16384) {
		return 16384;
	}
	return static_cast<int32_t>(samples);
}

} // namespace deluge::dsp::timestretch::akai

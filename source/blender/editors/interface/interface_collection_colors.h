/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 * Collection Color Helpers
 * Improved visual distinction for collections and hierarchies.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* ===== COLLECTION COLOR PALETTE ===== */

/**
 * Generate a distinct color for a collection based on its index or hash.
 * Uses a perceptually balanced palette for better visual distinction.
 *
 * \param index: Collection index or hash value.
 * \param r_color: Output color (RGB 0-1).
 */
void ui_collection_color_get(int index, float r_color[3]);

/**
 * Generate a color based on string hash (useful for collection names).
 */
void ui_collection_color_from_name(const char *name, float r_color[3]);

/**
 * Get a color for a specific nesting level in a hierarchy.
 * Useful for indented tree views or nested collections.
 *
 * \param level: Nesting depth (0 = root, 1 = first child, etc.).
 * \param r_color: Output color (RGB 0-1).
 */
void ui_collection_color_from_level(int level, float r_color[3]);

/**
 * Lighten or darken a collection color based on state (hover, selected).
 *
 * \param base_color: Base collection color (RGB 0-1).
 * \param is_selected: True if collection is selected.
 * \param is_hovered: True if collection is hovered.
 * \param r_color: Output adjusted color (RGB 0-1).
 */
void ui_collection_color_adjust_state(const float base_color[3],
                                      bool is_selected,
                                      bool is_hovered,
                                      float r_color[3]);

#ifdef __cplusplus
}
#endif

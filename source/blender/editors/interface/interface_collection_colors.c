/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 * Collection Color Helpers Implementation
 * Improved visual distinction for collections.
 */

#include "interface_collection_colors.h"

#include "BLI_hash.h"
#include "BLI_math_color.h"
#include "BLI_math_vector.h"
#include "BLI_string.h"

#include <cmath>

/* ===== PERCEPTUALLY BALANCED COLOR PALETTE ===== */

/**
 * Palette of 12 distinct, perceptually balanced colors.
 * Chosen to be distinguishable and accessible.
 */
static const float COLLECTION_PALETTE[][3] = {
    {0.26f, 0.59f, 0.98f}, /* Blue */
    {0.61f, 0.15f, 0.69f}, /* Purple */
    {0.30f, 0.69f, 0.31f}, /* Green */
    {1.00f, 0.60f, 0.00f}, /* Orange */
    {0.96f, 0.26f, 0.21f}, /* Red */
    {0.00f, 0.74f, 0.83f}, /* Cyan */
    {0.76f, 0.30f, 0.52f}, /* Pink */
    {0.55f, 0.76f, 0.29f}, /* Lime */
    {0.61f, 0.49f, 0.14f}, /* Brown */
    {0.38f, 0.49f, 0.55f}, /* Blue Gray */
    {0.91f, 0.12f, 0.39f}, /* Deep Pink */
    {0.20f, 0.60f, 0.86f}, /* Light Blue */
};

static const int PALETTE_SIZE = sizeof(COLLECTION_PALETTE) / sizeof(COLLECTION_PALETTE[0]);

/* ===== COLOR GENERATION ===== */

void ui_collection_color_get(int index, float r_color[3])
{
  /* Use modulo to cycle through palette */
  const int palette_index = index % PALETTE_SIZE;
  copy_v3_v3(r_color, COLLECTION_PALETTE[palette_index]);
}

void ui_collection_color_from_name(const char *name, float r_color[3])
{
  if (!name || !name[0]) {
    /* Default to first color for unnamed collections */
    copy_v3_v3(r_color, COLLECTION_PALETTE[0]);
    return;
  }

  /* Hash the name to get a stable color */
  const uint hash = BLI_hash_string(name);
  const int index = hash % PALETTE_SIZE;
  copy_v3_v3(r_color, COLLECTION_PALETTE[index]);
}

void ui_collection_color_from_level(int level, float r_color[3])
{
  /* Use a subset of colors for hierarchy levels to maintain consistency */
  const int hierarchy_palette[] = {0, 2, 4, 6, 8}; /* Blue, Green, Red, Pink, Brown */
  const int palette_count = sizeof(hierarchy_palette) / sizeof(hierarchy_palette[0]);

  const int clamped_level = level % palette_count;
  const int palette_index = hierarchy_palette[clamped_level];

  copy_v3_v3(r_color, COLLECTION_PALETTE[palette_index]);

  /* Slightly adjust saturation based on depth for subtle variation */
  const float saturation_factor = 1.0f - (level * 0.05f);
  const float hsv[3] = {0.0f, 0.0f, 0.0f};
  float hsv_out[3];

  rgb_to_hsv_v(r_color, hsv_out);
  hsv_out[1] *= CLAMPIS(saturation_factor, 0.5f, 1.0f); /* Reduce saturation slightly */
  hsv_to_rgb_v(hsv_out, r_color);
}

void ui_collection_color_adjust_state(const float base_color[3],
                                      bool is_selected,
                                      bool is_hovered,
                                      float r_color[3])
{
  copy_v3_v3(r_color, base_color);

  if (is_selected) {
    /* Brighten selected collections */
    float hsv[3];
    rgb_to_hsv_v(r_color, hsv);
    hsv[2] = fminf(hsv[2] * 1.3f, 1.0f); /* Increase value/brightness */
    hsv[1] = fminf(hsv[1] * 1.1f, 1.0f); /* Slightly more saturated */
    hsv_to_rgb_v(hsv, r_color);
  }
  else if (is_hovered) {
    /* Slightly lighten hovered collections */
    float hsv[3];
    rgb_to_hsv_v(r_color, hsv);
    hsv[2] = fminf(hsv[2] * 1.15f, 1.0f); /* Subtle brightness increase */
    hsv_to_rgb_v(hsv, r_color);
  }
}

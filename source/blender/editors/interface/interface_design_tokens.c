/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 * Design System Tokens Implementation
 * Initialization and management of centralized UI design values.
 */

#include "interface_design_tokens.h"
#include "DNA_userdef_types.h"  /* For bTheme */

/* Global design tokens instance */
struct DesignTokens g_design_tokens = {0};

/**
 * Default token values (light theme baseline).
 * These are applied on startup and can be overridden by theme data.
 */
static void design_tokens_set_defaults(struct DesignTokens *tokens)
{
  /* Colors (RGBA 8-bit) */
  /* Primary palette */
  RGBA_UCHAR_ARGS_SET(tokens->colors.primary_bg, 60, 63, 68, 255);
  RGBA_UCHAR_ARGS_SET(tokens->colors.primary_fg, 240, 240, 240, 255);
  RGBA_UCHAR_ARGS_SET(tokens->colors.primary_alt, 70, 73, 78, 255);

  /* Interactive states */
  RGBA_UCHAR_ARGS_SET(tokens->colors.interactive_hover, 90, 93, 98, 255);
  RGBA_UCHAR_ARGS_SET(tokens->colors.interactive_active, 100, 180, 255, 255);
  RGBA_UCHAR_ARGS_SET(tokens->colors.interactive_disabled, 80, 83, 88, 200);

  /* Feedback */
  RGBA_UCHAR_ARGS_SET(tokens->colors.success, 76, 175, 80, 255);
  RGBA_UCHAR_ARGS_SET(tokens->colors.warning, 255, 193, 7, 255);
  RGBA_UCHAR_ARGS_SET(tokens->colors.error, 244, 67, 54, 255);
  RGBA_UCHAR_ARGS_SET(tokens->colors.info, 33, 150, 243, 255);

  /* Focus/accessibility */
  RGBA_UCHAR_ARGS_SET(tokens->colors.focus_ring, 100, 200, 255, 200);
  RGBA_UCHAR_ARGS_SET(tokens->colors.focus_ring_alt, 255, 255, 100, 200);

  /* Node editor */
  RGBA_UCHAR_ARGS_SET(tokens->colors.node_bg, 60, 60, 60, 255);
  RGBA_UCHAR_ARGS_SET(tokens->colors.node_header, 100, 100, 100, 255);
  RGBA_UCHAR_ARGS_SET(tokens->colors.node_socket, 180, 180, 180, 255);

  /* Spacing (pixels) */
  tokens->spacing.xs = 2;
  tokens->spacing.sm = 4;
  tokens->spacing.md = 8;
  tokens->spacing.lg = 12;
  tokens->spacing.xl = 16;
  tokens->spacing.xxl = 24;

  /* Borders & Radius */
  tokens->borders.border_width = 1;
  tokens->borders.border_width_focus = 2;  /* Will be scaled by UI_SCALE_FAC */
  tokens->borders.radius_small = 2.0f;
  tokens->borders.radius_default = 4.0f;
  tokens->borders.radius_large = 6.0f;

  /* Typography (pixels) */
  tokens->typography.font_size_xs = 10;
  tokens->typography.font_size_sm = 11;
  tokens->typography.font_size_md = 12;
  tokens->typography.font_size_lg = 14;
  tokens->typography.line_height_tight = 12;
  tokens->typography.line_height_normal = 15;
  tokens->typography.line_height_loose = 18;

  /* Button style */
  tokens->button.padding_horizontal = 8;
  tokens->button.padding_vertical = 4;
  tokens->button.min_height = 24;
  tokens->button.corner_radius = 4.0f;
  tokens->button.border_width = 1;
}

/**
 * Initialize tokens from current theme.
 * Maps theme colors into semantic token values.
 */
void interface_design_tokens_init(const struct bTheme *theme)
{
  /* Start with defaults */
  design_tokens_set_defaults(&g_design_tokens);

  /* TODO: Map theme wcol_* values to semantic token colors
   * This allows tokens to respect user theme preferences
   * while providing a consistent API for new UI code.
   */
}

/**
 * Get global design tokens.
 */
struct DesignTokens *interface_design_tokens_get(void)
{
  return &g_design_tokens;
}

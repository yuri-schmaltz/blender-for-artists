/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 * Button Style Consolidation Implementation
 * Unified button rendering pipeline for consistent UI appearance.
 */

#include "interface_button_styles.h"
#include "interface_design_tokens.h"
#include "DNA_userdef_types.h"

/* ===== APPEARANCE GENERATION ===== */

/**
 * Dispatch to variant-specific appearance function.
 */
UIButtonAppearance ui_button_appearance_get(
    UIButtonVariant variant,
    const struct DesignTokens *tokens,
    bool is_hovered,
    bool is_pressed,
    bool is_disabled)
{
  switch (variant) {
    case UI_BUTTON_VARIANT_PRIMARY:
      return ui_button_appearance_primary(tokens, is_hovered, is_pressed, is_disabled);
    case UI_BUTTON_VARIANT_SECONDARY:
      return ui_button_appearance_secondary(tokens, is_hovered, is_pressed, is_disabled);
    case UI_BUTTON_VARIANT_TERTIARY:
      return ui_button_appearance_tertiary(tokens, is_hovered, is_pressed, is_disabled);
    case UI_BUTTON_VARIANT_DANGER:
      return ui_button_appearance_danger(tokens, is_hovered, is_pressed, is_disabled);
    case UI_BUTTON_VARIANT_GHOST:
      return ui_button_appearance_ghost(tokens, is_hovered, is_pressed, is_disabled);
    default:
      /* Fallback to secondary */
      return ui_button_appearance_secondary(tokens, is_hovered, is_pressed, is_disabled);
  }
}

/**
 * PRIMARY: High emphasis, filled background.
 * Used for main call-to-action (e.g., "Save", "Confirm", "Create").
 */
UIButtonAppearance ui_button_appearance_primary(
    const struct DesignTokens *tokens,
    bool is_hovered,
    bool is_pressed,
    bool is_disabled)
{
  UIButtonAppearance app = {0};

  /* Base: blue-ish interactive color */
  copy_v4_fl(app.bg_color, 0.0f);
  app.bg_color[0] = 0.4f;  /* R */
  app.bg_color[1] = 0.6f;  /* G */
  app.bg_color[2] = 0.9f;  /* B */
  app.bg_color[3] = 1.0f;  /* A */

  /* Hover: lighter blue */
  copy_v4_v4(app.bg_color_hover, app.bg_color);
  app.bg_color_hover[0] += 0.1f;
  app.bg_color_hover[1] += 0.1f;
  app.bg_color_hover[2] = 1.0f;

  /* Pressed: darker blue */
  copy_v4_v4(app.bg_color_pressed, app.bg_color);
  app.bg_color_pressed[0] -= 0.1f;
  app.bg_color_pressed[1] -= 0.1f;
  app.bg_color_pressed[2] -= 0.05f;

  /* Text: white */
  copy_v4_fl(app.text_color, 1.0f);
  copy_v4_v4(app.text_color_hover, app.text_color);
  copy_v4_v4(app.text_color_pressed, app.text_color);

  /* Disabled: gray with low opacity */
  copy_v3_fl(app.text_color_disabled, 0.6f);
  app.text_color_disabled[3] = 0.5f;

  /* Border: subtle */
  copy_v4_fl(app.border_color, 0.2f);
  app.border_color[3] = 0.3f;

  /* Dimensions */
  app.padding_h = tokens->button.padding_horizontal;
  app.padding_v = tokens->button.padding_vertical;
  app.min_height = tokens->button.min_height;
  app.corner_radius = tokens->button.corner_radius;
  app.border_width = 0;  /* No border for filled primary */

  return app;
}

/**
 * SECONDARY: Medium emphasis, outlined background.
 * Used for secondary actions alongside primary.
 */
UIButtonAppearance ui_button_appearance_secondary(
    const struct DesignTokens *tokens,
    bool is_hovered,
    bool is_pressed,
    bool is_disabled)
{
  UIButtonAppearance app = {0};

  /* Base: transparent with border */
  copy_v4_fl(app.bg_color, 0.0f);
  app.bg_color[3] = 0.0f;  /* Transparent */

  copy_v4_v4(app.bg_color_hover, app.bg_color);
  app.bg_color_hover[0] = 0.2f;
  app.bg_color_hover[1] = 0.2f;
  app.bg_color_hover[2] = 0.2f;
  app.bg_color_hover[3] = 0.1f;

  copy_v4_v4(app.bg_color_pressed, app.bg_color_hover);
  app.bg_color_pressed[3] = 0.2f;

  /* Text: foreground color */
  copy_v3_fl(app.text_color, 0.9f);
  app.text_color[3] = 1.0f;
  copy_v4_v4(app.text_color_hover, app.text_color);
  copy_v4_v4(app.text_color_pressed, app.text_color);

  copy_v3_fl(app.text_color_disabled, 0.6f);
  app.text_color_disabled[3] = 0.5f;

  /* Border: subtle gray */
  copy_v3_fl(app.border_color, 0.5f);
  app.border_color[3] = 0.4f;

  app.padding_h = tokens->button.padding_horizontal;
  app.padding_v = tokens->button.padding_vertical;
  app.min_height = tokens->button.min_height;
  app.corner_radius = tokens->button.corner_radius;
  app.border_width = tokens->button.border_width;

  return app;
}

/**
 * TERTIARY: Low emphasis, text-only appearance.
 * Used for optional/supplementary actions.
 */
UIButtonAppearance ui_button_appearance_tertiary(
    const struct DesignTokens *tokens,
    bool is_hovered,
    bool is_pressed,
    bool is_disabled)
{
  UIButtonAppearance app = {0};

  /* Base: no background, no border */
  copy_v4_fl(app.bg_color, 0.0f);
  copy_v4_fl(app.bg_color_hover, 0.0f);
  copy_v4_fl(app.bg_color_pressed, 0.0f);

  /* Text: foreground, underlined on hover */
  copy_v3_fl(app.text_color, 0.8f);
  app.text_color[3] = 1.0f;
  copy_v3_fl(app.text_color_hover, 0.6f);
  app.text_color_hover[2] = 1.0f;  /* Slightly blue on hover */
  app.text_color_hover[3] = 1.0f;
  copy_v4_v4(app.text_color_pressed, app.text_color_hover);

  copy_v3_fl(app.text_color_disabled, 0.5f);
  app.text_color_disabled[3] = 0.4f;

  /* No border */
  copy_v4_fl(app.border_color, 0.0f);

  app.padding_h = tokens->button.padding_horizontal * 0.5f;  /* Reduced padding */
  app.padding_v = tokens->button.padding_vertical * 0.5f;
  app.min_height = tokens->button.min_height - 4;  /* Smaller minimum height */
  app.corner_radius = tokens->button.corner_radius;
  app.border_width = 0;

  return app;
}

/**
 * DANGER: Destructive action alert state.
 * Used for delete/destructive actions that need user confirmation.
 */
UIButtonAppearance ui_button_appearance_danger(
    const struct DesignTokens *tokens,
    bool is_hovered,
    bool is_pressed,
    bool is_disabled)
{
  UIButtonAppearance app = {0};

  /* Base: red-ish warning color */
  app.bg_color[0] = 0.9f;  /* R (red) */
  app.bg_color[1] = 0.3f;  /* G */
  app.bg_color[2] = 0.3f;  /* B */
  app.bg_color[3] = 1.0f;  /* A */

  /* Hover: lighter red */
  copy_v4_v4(app.bg_color_hover, app.bg_color);
  app.bg_color_hover[0] = 1.0f;
  app.bg_color_hover[1] = 0.4f;
  app.bg_color_hover[2] = 0.4f;

  /* Pressed: darker red */
  copy_v4_v4(app.bg_color_pressed, app.bg_color);
  app.bg_color_pressed[0] = 0.7f;
  app.bg_color_pressed[1] = 0.2f;
  app.bg_color_pressed[2] = 0.2f;

  /* Text: white */
  copy_v4_fl(app.text_color, 1.0f);
  copy_v4_v4(app.text_color_hover, app.text_color);
  copy_v4_v4(app.text_color_pressed, app.text_color);

  copy_v3_fl(app.text_color_disabled, 0.6f);
  app.text_color_disabled[3] = 0.5f;

  copy_v4_fl(app.border_color, 0.0f);

  app.padding_h = tokens->button.padding_horizontal;
  app.padding_v = tokens->button.padding_vertical;
  app.min_height = tokens->button.min_height;
  app.corner_radius = tokens->button.corner_radius;
  app.border_width = 0;

  return app;
}

/**
 * GHOST: Minimal icon-only appearance.
 * No background until interaction.
 */
UIButtonAppearance ui_button_appearance_ghost(
    const struct DesignTokens *tokens,
    bool is_hovered,
    bool is_pressed,
    bool is_disabled)
{
  UIButtonAppearance app = {0};

  /* Base: completely transparent */
  copy_v4_fl(app.bg_color, 0.0f);

  /* Hover: subtle background */
  copy_v4_fl(app.bg_color_hover, 0.3f);
  app.bg_color_hover[3] = 0.15f;

  /* Pressed: more visible */
  copy_v4_fl(app.bg_color_pressed, 0.4f);
  app.bg_color_pressed[3] = 0.25f;

  /* Text: subtle gray */
  copy_v3_fl(app.text_color, 0.7f);
  app.text_color[3] = 1.0f;

  copy_v3_fl(app.text_color_hover, 0.9f);
  app.text_color_hover[3] = 1.0f;

  copy_v4_v4(app.text_color_pressed, app.text_color_hover);

  copy_v3_fl(app.text_color_disabled, 0.4f);
  app.text_color_disabled[3] = 0.5f;

  copy_v4_fl(app.border_color, 0.0f);

  app.padding_h = 4;  /* Icon-only buttons: small padding */
  app.padding_v = 4;
  app.min_height = 20;  /* Smaller than text buttons */
  app.corner_radius = 2.0f;  /* Small radius for icon buttons */
  app.border_width = 0;

  return app;
}

/**
 * Draw a button using consolidated appearance data.
 * TODO: Integrate with ui_draw_but() pipeline in interface_widgets.cc
 */
void ui_button_draw_styled(
    const struct rcti *rect,
    const UIButtonAppearance *appearance,
    const char *text,
    int icon)
{
  /* This is a placeholder for integration.
   * Will be expanded to use GPU drawing primitives:
   * - UI_draw_roundbox_4fv_ex() for background
   * - BLF_draw() for text
   * - Icon drawing code for icons
   */
}

/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 * Button Style Consolidation
 * Helpers and macros for unified button rendering based on variants.
 */

#pragma once

#include "interface_design_tokens.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ===== BUTTON VARIANT DEFINITIONS ===== */

/**
 * Button style variant.
 * Each variant has distinct visual hierarchy and semantic meaning.
 */
typedef enum UIButtonVariant {
  UI_BUTTON_VARIANT_PRIMARY = 0,      /* Primary action - high emphasis */
  UI_BUTTON_VARIANT_SECONDARY,         /* Secondary action - medium emphasis */
  UI_BUTTON_VARIANT_TERTIARY,          /* Tertiary action - low emphasis */
  UI_BUTTON_VARIANT_DANGER,            /* Destructive action - alert state */
  UI_BUTTON_VARIANT_GHOST,             /* Minimal/icon-only - no background */
} UIButtonVariant;

/* ===== BUTTON STATE DATA ===== */

/**
 * Runtime button appearance data computed from variant + state.
 * Used to render consistent button styles across the UI.
 */
typedef struct UIButtonAppearance {
  /* Background & Border */
  float bg_color[4];           /* Button background color (RGBA 0-1) */
  float border_color[4];       /* Border color */
  float bg_color_hover[4];     /* Background when hovered */
  float bg_color_pressed[4];   /* Background when pressed/active */

  /* Text */
  float text_color[4];         /* Text color (RGBA 0-1) */
  float text_color_hover[4];   /* Text color when hovered */
  float text_color_pressed[4]; /* Text color when pressed */
  float text_color_disabled[4];/* Text color when disabled */

  /* Dimensions */
  int padding_h;               /* Horizontal padding (pixels) */
  int padding_v;               /* Vertical padding (pixels) */
  int min_height;              /* Minimum button height */
  float corner_radius;         /* Corner radius (can be scaled by zoom) */
  int border_width;            /* Border width */
} UIButtonAppearance;

/* ===== APPEARANCE GENERATION ===== */

/**
 * Compute button appearance from variant and theme tokens.
 *
 * \param variant: Button style variant (PRIMARY, SECONDARY, etc.)
 * \param tokens: Pointer to global design tokens
 * \param is_hovered: True if button is under mouse cursor
 * \param is_pressed: True if button is being clicked or is active
 * \param is_disabled: True if button is disabled/inactive
 * \return Computed UIButtonAppearance with colors and dimensions
 */
UIButtonAppearance ui_button_appearance_get(
    UIButtonVariant variant,
    const struct DesignTokens *tokens,
    bool is_hovered,
    bool is_pressed,
    bool is_disabled);

/**
 * Compute appearance for PRIMARY variant (high emphasis).
 * Used for main call-to-action buttons.
 */
UIButtonAppearance ui_button_appearance_primary(
    const struct DesignTokens *tokens,
    bool is_hovered,
    bool is_pressed,
    bool is_disabled);

/**
 * Compute appearance for SECONDARY variant (medium emphasis).
 * Used for secondary actions alongside primary.
 */
UIButtonAppearance ui_button_appearance_secondary(
    const struct DesignTokens *tokens,
    bool is_hovered,
    bool is_pressed,
    bool is_disabled);

/**
 * Compute appearance for TERTIARY variant (low emphasis).
 * Used for optional/supplementary actions.
 */
UIButtonAppearance ui_button_appearance_tertiary(
    const struct DesignTokens *tokens,
    bool is_hovered,
    bool is_pressed,
    bool is_disabled);

/**
 * Compute appearance for DANGER variant (destructive alert).
 * Used for delete/destructive actions that need user confirmation.
 */
UIButtonAppearance ui_button_appearance_danger(
    const struct DesignTokens *tokens,
    bool is_hovered,
    bool is_pressed,
    bool is_disabled);

/**
 * Compute appearance for GHOST variant (minimal/icon).
 * Used for icon buttons without visible background until interaction.
 */
UIButtonAppearance ui_button_appearance_ghost(
    const struct DesignTokens *tokens,
    bool is_hovered,
    bool is_pressed,
    bool is_disabled);

/* ===== RENDERING HELPERS ===== */

/**
 * Draw a button using consolidated style from appearance data.
 * This replaces ad-hoc button drawing code with a consistent pipeline.
 *
 * \param rect: Button bounding rectangle
 * \param appearance: Pre-computed appearance data
 * \param text: Button label text (can be NULL for icon-only buttons)
 * \param icon: Icon ID (0 for no icon)
 */
void ui_button_draw_styled(
    const struct rcti *rect,
    const UIButtonAppearance *appearance,
    const char *text,
    int icon);

#ifdef __cplusplus
}
#endif

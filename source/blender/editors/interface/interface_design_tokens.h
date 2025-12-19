/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 * Design System Tokens for Blender UI
 * Centralized values for colors, spacing, and appearance.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* ===== COLOR TOKENS ===== */

/* Semantic colors */
typedef struct DesignTokensColors {
  /* Primary palette */
  unsigned char primary_bg[4];     /* Main background */
  unsigned char primary_fg[4];     /* Foreground/text */
  unsigned char primary_alt[4];    /* Alternative background */

  /* Interactive states */
  unsigned char interactive_hover[4];
  unsigned char interactive_active[4];
  unsigned char interactive_disabled[4];

  /* Feedback colors */
  unsigned char success[4];
  unsigned char warning[4];
  unsigned char error[4];
  unsigned char info[4];

  /* Focus/accessibility */
  unsigned char focus_ring[4];
  unsigned char focus_ring_alt[4];

  /* Node editor */
  unsigned char node_bg[4];
  unsigned char node_header[4];
  unsigned char node_socket[4];

} DesignTokensColors;

/* ===== SPACING TOKENS (in pixels) ===== */

typedef struct DesignTokensSpacing {
  int xs;  /* 2px - minimal */
  int sm;  /* 4px - compact */
  int md;  /* 8px - default */
  int lg;  /* 12px - spacious */
  int xl;  /* 16px - large gap */
  int xxl; /* 24px - section gap */
} DesignTokensSpacing;

/* ===== BORDER & RADIUS TOKENS ===== */

typedef struct DesignTokensBorders {
  int border_width;        /* Standard border width (1px) */
  int border_width_focus;  /* Focus ring width (2.5px scaled) */
  float radius_small;      /* Small radius (2px) */
  float radius_default;    /* Default radius (4px) */
  float radius_large;      /* Large radius (6px) */
} DesignTokensBorders;

/* ===== TYPOGRAPHY TOKENS ===== */

typedef struct DesignTokensTypography {
  int font_size_xs;        /* 10px */
  int font_size_sm;        /* 11px */
  int font_size_md;        /* 12px - default */
  int font_size_lg;        /* 14px */
  int line_height_tight;   /* 1.2 */
  int line_height_normal;  /* 1.5 */
  int line_height_loose;   /* 1.8 */
} DesignTokensTypography;

/* ===== BUTTON STYLE TOKENS ===== */

typedef enum DesignTokensButtonVariant {
  BUTTON_VARIANT_PRIMARY,     /* Primary action */
  BUTTON_VARIANT_SECONDARY,   /* Secondary action */
  BUTTON_VARIANT_TERTIARY,    /* Tertiary/minimal */
  BUTTON_VARIANT_DANGER,      /* Destructive action */
  BUTTON_VARIANT_GHOST,       /* No background */
} DesignTokensButtonVariant;

typedef struct DesignTokensButton {
  int padding_horizontal;  /* Horizontal padding (8px) */
  int padding_vertical;    /* Vertical padding (4px) */
  int min_height;          /* Minimum button height (24px) */
  float corner_radius;     /* Button corner radius (4px) */
  int border_width;        /* Border width when outlined (1px) */
} DesignTokensButton;

/* ===== TOKEN SINGLETON ===== */

/**
 * Get or initialize the global design tokens.
 * Called once at UI system startup.
 */
struct DesignTokens {
  DesignTokensColors colors;
  DesignTokensSpacing spacing;
  DesignTokensBorders borders;
  DesignTokensTypography typography;
  DesignTokensButton button;
};

extern struct DesignTokens g_design_tokens;

/**
 * Initialize design tokens from theme data.
 * Should be called after theme is loaded.
 */
void interface_design_tokens_init(const struct bTheme *theme);

/**
 * Get pointer to global tokens (convenience).
 */
struct DesignTokens *interface_design_tokens_get(void);

#ifdef __cplusplus
}
#endif

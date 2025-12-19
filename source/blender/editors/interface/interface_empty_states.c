/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 * UI Empty States Implementation
 * Visual feedback for empty lists and loading states.
 */

#include "interface_empty_states.h"
#include "interface_design_tokens.h"

#include "BLI_math_vector.h"
#include "BLI_rect.h"
#include "BLI_string.h"

#include "BLF_api.hh"

#include "GPU_immediate.hh"
#include "GPU_immediate_util.hh"
#include "GPU_state.hh"

#include "UI_interface.hh"
#include "UI_interface_icons.hh"

#include "DNA_userdef_types.h"

#include <cmath>

/* ===== INTERNAL HELPERS ===== */

/**
 * Get icon for empty state type.
 */
static int empty_state_icon_get(UIEmptyStateType type)
{
  switch (type) {
    case UI_EMPTY_STATE_NO_RESULTS:
      return ICON_VIEWZOOM;
    case UI_EMPTY_STATE_NO_DATA:
      return ICON_FILE_BLANK;
    case UI_EMPTY_STATE_PERMISSION_DENIED:
      return ICON_LOCKED;
    case UI_EMPTY_STATE_ERROR:
      return ICON_ERROR;
    case UI_EMPTY_STATE_GENERIC:
    default:
      return ICON_INFO;
  }
}

/**
 * Get text color for empty state type.
 */
static void empty_state_color_get(UIEmptyStateType type, float r_color[4])
{
  const DesignTokens *tokens = interface_design_tokens_get();

  switch (type) {
    case UI_EMPTY_STATE_ERROR:
      if (tokens) {
        r_color[0] = tokens->colors.error[0] / 255.0f;
        r_color[1] = tokens->colors.error[1] / 255.0f;
        r_color[2] = tokens->colors.error[2] / 255.0f;
        r_color[3] = 1.0f;
      }
      else {
        copy_v4_fl4(r_color, 0.95f, 0.26f, 0.21f, 1.0f); /* Red */
      }
      break;
    case UI_EMPTY_STATE_PERMISSION_DENIED:
      if (tokens) {
        r_color[0] = tokens->colors.warning[0] / 255.0f;
        r_color[1] = tokens->colors.warning[1] / 255.0f;
        r_color[2] = tokens->colors.warning[2] / 255.0f;
        r_color[3] = 1.0f;
      }
      else {
        copy_v4_fl4(r_color, 1.0f, 0.76f, 0.03f, 1.0f); /* Yellow */
      }
      break;
    default:
      /* Subtle gray for non-error states */
      copy_v4_fl4(r_color, 0.6f, 0.6f, 0.6f, 1.0f);
      break;
  }
}

/* ===== EMPTY STATE RENDERING ===== */

bool ui_empty_state_is_space_sufficient(const struct rcti *rect)
{
  /* Require at least 100x80 pixels for a proper empty state */
  return (BLI_rcti_size_x(rect) >= 100 && BLI_rcti_size_y(rect) >= 80);
}

void ui_draw_empty_state(const struct rcti *rect,
                         UIEmptyStateType type,
                         const char *title,
                         const char *subtitle,
                         const char *action_label)
{
  if (!ui_empty_state_is_space_sufficient(rect)) {
    return; /* Too small to render */
  }

  const int center_x = BLI_rcti_cent_x(rect);
  const int center_y = BLI_rcti_cent_y(rect);

  /* Get styling */
  float text_color[4];
  empty_state_color_get(type, text_color);
  const int icon = empty_state_icon_get(type);

  /* Draw icon */
  const int icon_size = 48;
  const int icon_y = center_y + 30;
  UI_icon_draw_ex(center_x - icon_size / 2,
                  icon_y - icon_size / 2,
                  icon,
                  1.0f / UI_SCALE_FAC,
                  0.5f, /* alpha */
                  0.0f,
                  text_color,
                  false,
                  UI_NO_ICON_OVERLAY_TEXT);

  /* Draw title */
  if (title) {
    const uiFontStyle *fstyle = UI_FSTYLE_WIDGET;
    BLF_batch_draw_begin();
    uiFontStyle fstyle_large = *fstyle;
    fstyle_large.points = fstyle->points * 1.2f; /* Slightly larger */

    BLF_color4fv(fstyle_large.uifont_id, text_color);
    UI_fontstyle_draw_simple(&fstyle_large, center_x, center_y, title, text_color);
    BLF_batch_draw_end();
  }

  /* Draw subtitle */
  if (subtitle) {
    const uiFontStyle *fstyle = UI_FSTYLE_WIDGET;
    BLF_batch_draw_begin();
    uiFontStyle fstyle_small = *fstyle;
    fstyle_small.points = fstyle->points * 0.9f; /* Slightly smaller */

    float subtle_color[4];
    copy_v4_v4(subtle_color, text_color);
    subtle_color[3] *= 0.7f; /* More transparent */

    BLF_color4fv(fstyle_small.uifont_id, subtle_color);
    UI_fontstyle_draw_simple(&fstyle_small, center_x, center_y - 20, subtitle, subtle_color);
    BLF_batch_draw_end();
  }

  /* Draw action label hint (not a real button, just a hint) */
  if (action_label) {
    const uiFontStyle *fstyle = UI_FSTYLE_WIDGET;
    BLF_batch_draw_begin();
    float action_color[4];
    copy_v4_fl4(action_color, 0.4f, 0.6f, 0.9f, 1.0f); /* Blue hint */

    BLF_color4fv(fstyle->uifont_id, action_color);
    UI_fontstyle_draw_simple(fstyle, center_x, center_y - 50, action_label, action_color);
    BLF_batch_draw_end();
  }
}

/* ===== LOADING SPINNER ===== */

void ui_draw_loading_spinner(const struct rcti *rect, float progress, const char *label)
{
  const int center_x = BLI_rcti_cent_x(rect);
  const int center_y = BLI_rcti_cent_y(rect);

  /* Draw spinner circle */
  const float radius = 20.0f;
  const int segments = 32;
  const float rotation = float(std::fmod(BLI_time_now_seconds() * 2.0, 2.0 * M_PI));

  GPU_blend(GPU_BLEND_ALPHA);
  GPU_line_width(3.0f);

  GPUVertFormat *format = immVertexFormat();
  uint pos = GPU_vertformat_attr_add(format, "pos", GPU_COMP_F32, 2, GPU_FETCH_FLOAT);
  uint col = GPU_vertformat_attr_add(format, "color", GPU_COMP_F32, 4, GPU_FETCH_FLOAT);

  immBindBuiltinProgram(GPU_SHADER_3D_FLAT_COLOR);

  if (progress < 0.0f) {
    /* Indeterminate spinner: rotating arc */
    immBegin(GPU_PRIM_LINE_STRIP, segments / 2);
    for (int i = 0; i < segments / 2; i++) {
      float angle = rotation + (i / float(segments / 2)) * M_PI * 1.5f;
      float alpha = 1.0f - (i / float(segments / 2)); /* Fade tail */
      immAttr4f(col, 0.4f, 0.6f, 0.9f, alpha);
      immVertex2f(pos, center_x + radius * cosf(angle), center_y + radius * sinf(angle));
    }
    immEnd();
  }
  else {
    /* Determinate progress: partial circle */
    const int filled_segments = int(segments * progress);
    immBegin(GPU_PRIM_LINE_STRIP, filled_segments + 1);
    for (int i = 0; i <= filled_segments; i++) {
      float angle = -M_PI / 2.0f + (i / float(segments)) * M_PI * 2.0f;
      immAttr4f(col, 0.4f, 0.6f, 0.9f, 1.0f);
      immVertex2f(pos, center_x + radius * cosf(angle), center_y + radius * sinf(angle));
    }
    immEnd();
  }

  immUnbindProgram();
  GPU_line_width(1.0f);
  GPU_blend(GPU_BLEND_NONE);

  /* Draw label */
  if (label) {
    const uiFontStyle *fstyle = UI_FSTYLE_WIDGET;
    BLF_batch_draw_begin();
    float label_color[4];
    copy_v4_fl4(label_color, 0.7f, 0.7f, 0.7f, 1.0f);

    BLF_color4fv(fstyle->uifont_id, label_color);
    UI_fontstyle_draw_simple(fstyle, center_x, center_y - 35, label, label_color);
    BLF_batch_draw_end();
  }
}

/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 * UI Empty States Components
 * Visual feedback for empty lists, search results, and loading states.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct rcti;
struct uiFontStyle;

/* ===== EMPTY STATE TYPES ===== */

/**
 * Types of empty state messages.
 * Each type can have distinct styling and iconography.
 */
typedef enum UIEmptyStateType {
  UI_EMPTY_STATE_GENERIC = 0,      /* Generic empty message */
  UI_EMPTY_STATE_NO_RESULTS,        /* Search/filter returned no results */
  UI_EMPTY_STATE_NO_DATA,           /* No data available yet */
  UI_EMPTY_STATE_PERMISSION_DENIED, /* User lacks permission */
  UI_EMPTY_STATE_ERROR,             /* Error occurred */
} UIEmptyStateType;

/* ===== EMPTY STATE RENDERING ===== */

/**
 * Draw an empty state message in a given rectangle.
 * Useful for lists, panels, or views that have no content.
 *
 * \param rect: Bounding box for the empty state (centered text/icon).
 * \param type: Type of empty state (determines icon and styling).
 * \param title: Main message title (e.g., "No Items Found").
 * \param subtitle: Optional secondary message (can be NULL).
 * \param action_label: Optional action button label (e.g., "Add New", can be NULL).
 */
void ui_draw_empty_state(const struct rcti *rect,
                         UIEmptyStateType type,
                         const char *title,
                         const char *subtitle,
                         const char *action_label);

/**
 * Draw a loading spinner with optional text.
 * Used to indicate background operations in progress.
 *
 * \param rect: Bounding box for the spinner (centered).
 * \param progress: Progress value 0.0-1.0 (use -1.0 for indeterminate spinner).
 * \param label: Optional loading message (e.g., "Loading...", can be NULL).
 */
void ui_draw_loading_spinner(const struct rcti *rect, float progress, const char *label);

/**
 * Check if a given rectangle is large enough to display empty state.
 * Returns false if too small, suggesting a simpler message.
 */
bool ui_empty_state_is_space_sufficient(const struct rcti *rect);

/* ===== CONVENIENCE WRAPPERS ===== */

/**
 * Draw "No search results" empty state.
 */
static inline void ui_draw_empty_state_no_search_results(const struct rcti *rect,
                                                          const char *query)
{
  char subtitle[128];
  if (query && query[0]) {
    BLI_snprintf(subtitle, sizeof(subtitle), "No results for \"%s\"", query);
  }
  else {
    BLI_strncpy(subtitle, "Try adjusting your search", sizeof(subtitle));
  }
  ui_draw_empty_state(rect, UI_EMPTY_STATE_NO_RESULTS, "No Results", subtitle, nullptr);
}

/**
 * Draw "No items yet" empty state with action.
 */
static inline void ui_draw_empty_state_no_items(const struct rcti *rect, const char *item_type)
{
  char title[128];
  BLI_snprintf(title, sizeof(title), "No %s", item_type);
  ui_draw_empty_state(rect, UI_EMPTY_STATE_NO_DATA, title, "Add your first item", "Add New");
}

/**
 * Draw generic loading indicator.
 */
static inline void ui_draw_loading_generic(const struct rcti *rect)
{
  ui_draw_loading_spinner(rect, -1.0f, "Loading...");
}

#ifdef __cplusplus
}
#endif

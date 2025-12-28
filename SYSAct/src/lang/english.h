/* - Prefixes - */
#define LANG_PREFIX_SDL3 "SDL3"
#define LANG_PREFIX_IMGUI "ImGui"

/* - Error - */

/* Misc. */
#define LANG_ERROR_INIT "Failed to initialize: %s"
#define LANG_ERROR_SAVE "Failed to save: %s"
#define LANG_ERROR_LOAD "Failed to load: %s"

/* SDL3 */

/* Create */
#define LANG_ERROR_SDL3_CREATE_WINDOW LANG_PREFIX_SDL3 ": Failed to create window: %s"
#define LANG_ERROR_SDL3_CREATE_CONTEXT LANG_PREFIX_SDL3 ": Failed to create GL context: %s"
#define LANG_ERROR_SDL3_CREATE_TEXTURE LANG_PREFIX_SDL3 ": Failed to create texture: %s"
#define LANG_ERROR_SDL3_CREATE_SURFACE LANG_PREFIX_SDL3 ": Failed to create surface: %s"
#define LANG_ERROR_SDL3_CREATE_IOSTREAM LANG_PREFIX_SDL3 ": Failed to create IOStream: %s"

/* Set */
#define LANG_ERROR_SDL3_SET_SCALE LANG_PREFIX_SDL3 ": Failed to set scaling: %s"
#define LANG_ERROR_SDL3_SET_COLOR LANG_PREFIX_SDL3 ": Failed to set texture color: %s"
#define LANG_ERROR_SDL3_SET_ALPHA LANG_PREFIX_SDL3 ": Failed to set texture alpha: %s"
#define LANG_ERROR_SDL3_SET_TITLE LANG_PREFIX_SDL3 ": Failed to set window title: %s"
#define LANG_ERROR_SDL3_SET_SIZE LANG_PREFIX_SDL3 ": Failed to set window size: %s"

/* Close */
#define LANG_ERROR_SDL3_CLOSE_IOSTREAM LANG_PREFIX_SDL3 ": Failed to close IOStream: %s"

/* ImGui */
#define LANG_ERROR_IMGUI_INIT LANG_PREFIX_IMGUI ": Failed to initialize"
#define LANG_ERROR_IMGUI_INIT_RENDERER LANG_PREFIX_IMGUI ": Failed to initialize renderer"

/* Action */
#define LANG_ACTION_SECTOR "Sector"
#define LANG_ACTION_LINEDEF "Linedef"
#define LANG_ACTION_REUSE "Reuse"
#define LANG_ACTION_ID "Id"
#define LANG_ACTION_NAME "Name"
#define LANG_ACTION_DATA "Data"
#define LANG_ACTION_SAVE "Save"
#define LANG_ACTION_LOAD "Load"
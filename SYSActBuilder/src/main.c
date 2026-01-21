#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#define CIMGUI_USE_SDL3
#define CIMGUI_USE_OPENGL3
#include <cimgui/cimgui.h>
#include <cimgui_impl.h>
#ifdef __APPLE
	#include <SDL.h>
	#include <gl.h>
#else
	#include <SDL3/SDL.h>
	#include <GL/gl.h>
#endif

#include "lang.h"
#include "action.h"
#include "macros.h"
#include "progInfo.h"

char main_noWait = 0;

static char running = 1;

static int waitTime;

static unsigned int lastTime;

static SDL_Window *window;
static SDL_GLContext glContext;
static SDL_Event event;

static inline void handleEvent() {
	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL3_ProcessEvent(&event);
		switch (event.type) {
			case SDL_EVENT_QUIT:
				running = 0;
				continue;
			default:
				break;
		}
	}
	return;
}

static inline int init(int argc) {
	SDL_SetAppMetadata(PROGRAM_NAME, PROGRAM_VERSION, "com.stevensys.sysact");
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		ERROR_MESSAGE(
			LANG_PREFIX_SDL3 ": " LANG_ERROR_INIT,
			SDL_GetError()
		);
		return 1;
	}
	
	window = SDL_CreateWindow(
		PROGRAM_NAME " v" PROGRAM_VERSION,
		RENDER_WIDTH, RENDER_HEIGHT,
		SDL_WINDOW_OPENGL
	);
	
	if (window == NULL) {
		ERROR_MESSAGE(
			LANG_ERROR_SDL3_CREATE_WINDOW,
			SDL_GetError()
		);
		return 1;
	}
	
	SDL_SetWindowPosition(
		window,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
	);
	
	glContext = SDL_GL_CreateContext(window);
	
	if (glContext == NULL) {
		ERROR_MESSAGE(
			LANG_ERROR_SDL3_CREATE_CONTEXT,
			SDL_GetError()
		);
		return 1;
	}
	
	igCreateContext(NULL);
	igStyleColorsDark(NULL);
	
	igGetIO_Nil()->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
	igGetIO_Nil()->IniFilename = NULL;
	
	if (!ImGui_ImplSDL3_InitForOpenGL(window, glContext)) {
		ERROR_MESSAGE(
			LANG_ERROR_IMGUI_INIT
		);
		return 1;
	}
	
	if (!ImGui_ImplOpenGL3_Init(
		#if __APPLE__
		"#version 150"
		#else
		"#version 130"
		#endif
	)) {
		ERROR_MESSAGE(
			LANG_ERROR_IMGUI_INIT_RENDERER
		);
		return 1;
	}
	
	if (argc < 2) {
		action_init();
	}
	return 0;
}


static inline void render() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	igNewFrame();
	
	igSetNextWindowPos((ImVec2){ 0.0f, 0.0f }, ImGuiCond_FirstUseEver, (ImVec2){ 0.0f, 0.0f });
	igSetNextWindowSize(igGetIO_Nil()->DisplaySize, ImGuiCond_FirstUseEver);
	
	igBegin(PROGRAM_NAME, NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	
	action_render();
	
	igEnd();
	
	igRender();
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
	SDL_GL_SwapWindow(window);
	return;
}

static inline void uninit() {
	action_uninit();
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	igDestroyContext(NULL);
	
	SDL_GL_DestroyContext(glContext);
	
	SDL_DestroyWindow(window);
	SDL_Quit();
	return;
}

int main(int argc, char *argv[]) {
	if (init(argc)) {
		ERROR_MESSAGE(
			LANG_ERROR_INIT,
			SDL_GetError()
		);
		return 1;
	}
	
	while (running) {
		if (!main_noWait) {
			lastTime = SDL_GetTicksNS();
		}
		
		handleEvent();
		render();
		
		if (main_noWait) {
			main_noWait = 0;
		} else {
			waitTime = (
				1000000000 / MAX_FPS
			) - (
				SDL_GetTicksNS() - lastTime
			);
			
			if (waitTime > 0) {
				SDL_DelayNS(waitTime);
			}
		}
	}
	uninit();
	return 0;
}
cmake_minimum_required(VERSION 3.22.1)
project(GenEnv)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Per funzionare con clangd


set(SRC_DIR "./")
# set(LIB_DIR "./lib")

set(ENGINE_DIR ${SRC_DIR}/engine)
set(ECS_DIR ${SRC_DIR}/ecs/genecs)
set(GLFW_DIR ${SRC_DIR}/io/glfw)
set(OPENGL_DIR ${SRC_DIR}/graphics/opengl)
set(MODEL_DIR ${SRC_DIR}/model)
set(CORE_DIR ${SRC_DIR}/core)

file(GLOB_RECURSE ENGINE_SRC ${ENGINE_DIR}/*.cpp)
file(GLOB_RECURSE ECS_SRC ${ECS_DIR}/**/*.cpp)
file(GLOB_RECURSE GLFW_SRC ${GLFW_DIR}/*.cpp)
file(GLOB_RECURSE OPENGL_SRC ${OPENGL_DIR}/*.cpp)
file(GLOB_RECURSE MODEL_SRC ${MODEL_DIR}/*.cpp)
file(GLOB_RECURSE CORE_SRC ${CORE_DIR}/*.cpp)


add_executable(run-GenEnv
	${ENGINE_SRC} ${ECS_SRC} ${GLFW_SRC} ${OPENGL_SRC} ${MODEL_SRC} ${CORE_SRC}
)

target_include_directories(run-GenEnv
	PUBLIC  ${ENGINE_DIR} ${ECS_DIR} ${GLFW_DIR} ${OPENGL_DIR} ${MODEL_DIR} ${CORE_DIR}
)

target_link_libraries(run-GenEnv
    GLEW
    GL                # OpenGL
    glfw              # Link alla libreria GLFW3 (CMake gestirà il prefisso `-l`)
    X11               # X11
    dl                # Dynamic Linker (necessario per alcune funzioni di runtime)
) #CHAT-GPT
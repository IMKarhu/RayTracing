add_library( imgui 
imgui.cpp 
imgui.h 
imgui_demo.cpp 
imgui_draw.cpp 
imgui_widgets.cpp 
imgui_tables.cpp 
imgui_internal.h 
imstb_rectpack.h
imstb_textedit.h 
imstb_truetype.h
imgui_impl_opengl3.cpp
imgui_impl_opengl3.h
imgui_impl_glfw.cpp
imgui_impl_glfw.h)

target_link_libraries(imgui PUBLIC glfw)
target_include_directories(imgui PUBLIC imgui)
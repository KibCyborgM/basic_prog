target_sources(multiple_level_menu
	PRIVATE
		menu.hpp
		menu_functions.cpp
		menu_functions.hpp
		menu_items.cpp
		menu_items.hpp
)

target_include_directories(multiple_level_menu
	PRIVATE
		"${PROJECT_SOURCE_DIR}/menu_src"
)
#pragma once
#include <ZUI.hpp>
#include <VisVec.hpp>

#define SETUP_ALGO(ALGO_N, ...) \
	template <int N> void setActionLoop() \
	{ \
		btn_algo[N - 1]->setAction([this] \
			{ \
				vec.swapAndClearBuffer(); \
				algo<N - 1>(); \
			} \
		); \
		setActionLoop<N - 1>(); \
	} \
	template <> void setActionLoop<0>() {} \
	void runSetActionLoop() override { \
		setActionLoop<ALGO_N>(); \
	} \
	template <int N> void algo(); \
	void setupAlgoNames(){ \
		algoNames = std::vector<std::string>{ \
			__VA_ARGS__ \
		}; \
	}

#define CREATE_ALGO(N, ...) template <> void algo<N>() __VA_ARGS__


class AlgoClass {
public:
	AlgoClass();

	zui::Frame& getFrame();

	void init(sf::RenderWindow& window);
	virtual void load() = 0;
	virtual void unload() = 0;

	void draw(sf::RenderWindow& window, sf::RenderStates states = sf::RenderStates::Default);

protected:
	void loadParentElements();
	void unloadParentElements();

	void createBackupVector();
	void loadBackupVector();

	virtual void loadGUI() = 0;
	virtual void loadVisVec() = 0;

	void placeElement(zui::Textbox* tb, zui::Page* pg, float x, float y, const std::string& str);

	virtual void setupAlgoNames() = 0;
	virtual void runSetActionLoop() = 0;

	void addAlgoName(const std::string& name);

	std::vector<std::string> algoNames;

	float speed;
	sf::RectangleShape bound;

	zui::Frame frm_main;
	zui::Page_ptr pg_head, pg_algo, pg_visvec;
	zui::TextButton_ptr btn_pause, btn_step;
	std::vector<zui::Textbox_ptr> btn_algo;
	zui::Slider_ptr sld_speed;

	VisVec vec;
	std::vector<int> vec_copy;
};


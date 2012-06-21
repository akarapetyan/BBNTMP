#ifndef WINDOW_HPP
#define WINDOW_HPP

/**
 * @file window.hpp
 * @brief Holder for UI widget implementation
 */

#include <QtCore/QObject>

#include <bb/cascades/Button>
#include <bb/cascades/Image>
#include <bb/cascades/Slider>

using namespace bb::cascades;

class Window : public QObject
{
    Q_OBJECT

public:
    Window();

public slots:
	void playPrevious(){}

	void playNext(){}

	void setImage();

private:
	Button* previousButton;
	Button* stopButton;
	Button* nextButton;
	Slider* opacitySlider;
	bool    isPlaying;
};

#endif

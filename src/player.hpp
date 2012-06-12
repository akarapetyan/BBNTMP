#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QtCore/QObject>

#include <mm/renderer.h>
#include <bps/bps.h>
#include <bps/screen.h>
#include <stdlib.h>


class Player : public QObject
{
    Q_OBJECT

public:
    Player();
    void runPlayer();
    ~Player();

private:
    void connectToMMR();
    void configureAudioVideo();
    void startPlayback();
    void handleKeyboardEvents();
    void detachFromMMR();
    void createWindow();
    void makeWindowVisible();
    void destroyScreen();

    int errorCode;

    // Renderer variables
	mmr_connection_t*   mmr_connection;
    mmr_context_t*      mmr_context;

    // Screen variables
    screen_context_t    screen_context;
    screen_window_t     screen_window;

	// I/O variables
	int                 video_device_output_id;
	int                 audio_device_output_id;

	// I/O devices
	static const char *video_device_url;
	static const char *audio_device_url;
	static const char *window_group_name;

};

#endif /* PLAYER_HPP */

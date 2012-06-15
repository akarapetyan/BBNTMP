/**
 * @file player.cpp
 * @brief Implementation of player class
 */

#include <bb/cascades/Application>

#include <fcntl.h>
#include <bps/navigator.h>

#include "player.hpp"
#include "exceptions.hpp"

using namespace ::bb::cascades;
using namespace exceptions;

const char* Player::video_device_url = "screen:?winid=videosamplewindowgroup&wingrp=videosamplewindowgroup";
const char* Player::audio_device_url = "audio:default";
const char* Player::window_group_name = "videosamplewindowgroup";

Player::Player()
	: errorCode(1)
	, mmr_connection(0)
	, mmr_context(0)
	, screen_context(0)
    , screen_window(0)
	, video_device_output_id (-1)
	, audio_device_output_id (-1)
{
	bps_initialize();
}

Player::~Player()
{
	mmr_context = 0;

	video_device_output_id = -1;
	audio_device_output_id = -1;

	mmr_disconnect(mmr_connection);
	mmr_connection = 0;

	bps_shutdown();

	screen_context = 0;
	screen_window = 0;
}

void Player::connectToMMR()
{
	mmr_connection = mmr_connect(NULL);
	if (mmr_connection == NULL) {
		throw exception(EXIT_FAILURE);
	}

	mmr_context = mmr_context_create(mmr_connection, "myUniqueContextName", 0, S_IRWXU|S_IRWXG|S_IRWXO);
	if (mmr_context == NULL) {
		throw exception(EXIT_FAILURE);
	}
}

/*
 * Configure video and audio output.
 */
void Player::configureAudioVideo()
{
	video_device_output_id = mmr_output_attach(mmr_context, video_device_url, "video");
	if (video_device_output_id == -1) {
		throw exception(EXIT_FAILURE);
	}

	audio_device_output_id = mmr_output_attach(mmr_context, audio_device_url, "audio");
	if (audio_device_output_id == -1) {
		throw exception(EXIT_FAILURE);
	}
}

void Player::startPlayback(const QString& fileName)
{
	// Build up the path where our bundled resource is.
	char cwd[PATH_MAX];
	char media_file[PATH_MAX];
	getcwd(cwd,PATH_MAX);

	//int rc = snprintf(media_file, PATH_MAX, "file://%s/app/native/pb_sample.mp4", cwd);
	//strcpy(media_file,"accounts/1000/shared/downloads/pb_sample.mp4");

//	FILE* f = fopen(media_file, "r");
	/*if ((rc == -1) || (rc >= PATH_MAX)) {
		throw exception(EXIT_FAILURE);
	}*/

	// Start the playback.
	//if (mmr_input_attach(mmr_context, media_file, "track") != 0) {
	if (mmr_input_attach(mmr_context, fileName.toStdString().c_str(), "track") != 0) {
		//const mmr_error_info_t* ptr = mmr_error_info(mmr_context);
		throw exception(EXIT_FAILURE);
	}
	if (mmr_play(mmr_context) != 0) {
		throw exception(EXIT_FAILURE);
	}
}

/*
 * Handle keyboard events and stop playback upon user request.
 */
void Player::handleKeyboardEvents()
{
	int exit_application = 0;
	while(true)
	{
		bps_event_t *event = NULL;
		if (bps_get_event(&event, -1) != BPS_SUCCESS) {
			throw exception(EXIT_FAILURE);
		}

		if (event) {

			if (bps_event_get_domain(event) == navigator_get_domain() &&
				bps_event_get_code(event) == NAVIGATOR_EXIT) {

				exit_application = 1;
			}

			if (exit_application) {
				return;
			}
		}
	}
}

void Player::detachFromMMR()
{
	if (mmr_stop(mmr_context) != 0) {
		throw exception(EXIT_FAILURE);
	}

	if (mmr_output_detach(mmr_context, audio_device_output_id) != 0) {
		throw exception(EXIT_FAILURE);
	}

	if (mmr_output_detach(mmr_context, video_device_output_id) != 0) {
		throw exception(EXIT_FAILURE);
	}

	if (mmr_context_destroy(mmr_context) != 0) {
		throw exception(EXIT_FAILURE);
	}
}

/*
 * Create the window used for video output.
 */
//TODO maybe delete later
void Player::createWindow()
{
	if (screen_create_context(&screen_context, SCREEN_APPLICATION_CONTEXT) != 0) {
		throw exception(EXIT_FAILURE);
	}

	if (screen_create_window(&screen_window, screen_context) != 0) {
		screen_destroy_context(screen_context);
		throw exception(EXIT_FAILURE);
	}

	if (screen_create_window_group(screen_window, window_group_name) != 0) {
		throw exception(EXIT_FAILURE);
	}

	int format = SCREEN_FORMAT_RGBA8888;
	if (screen_set_window_property_iv(screen_window, SCREEN_PROPERTY_FORMAT, &format) != 0) {
		throw exception(EXIT_FAILURE);
	}

	int usage = SCREEN_USAGE_NATIVE;
	if (screen_set_window_property_iv(screen_window, SCREEN_PROPERTY_USAGE, &usage) != 0) {
		throw exception(EXIT_FAILURE);
	}

	if (screen_create_window_buffers(screen_window, 1) != 0) {
		throw exception(EXIT_FAILURE);
	}
}

void Player::makeWindowVisible()
{
	int size[2]    = {0,0};

	// Get the render buffer
	screen_buffer_t temp_buffer[1];
	if (screen_get_window_property_pv( screen_window, SCREEN_PROPERTY_RENDER_BUFFERS, (void**)temp_buffer) != 0) {
		throw exception(EXIT_FAILURE);
	}

	// Fill the buffer with a solid color (black)
	int fill_attributes[3] = {SCREEN_BLIT_COLOR, 0x0, SCREEN_BLIT_END};
	if (screen_fill(screen_context, temp_buffer[0], fill_attributes) != 0) {
		throw exception(EXIT_FAILURE);
	}

	// Make the window visible
	if (screen_get_window_property_iv(screen_window, SCREEN_PROPERTY_SIZE, size) != 0) {
		throw exception(EXIT_FAILURE);
	}

	int temp_rectangle[4] = {0,0,size[0],size[1]};
	if (screen_post_window(screen_window, temp_buffer[0], 1, temp_rectangle, 0) != 0) {
		throw exception(EXIT_FAILURE);
	}

	// Prevent the backlight from going off
	int idle_mode = SCREEN_IDLE_MODE_KEEP_AWAKE;
	if (screen_set_window_property_iv(screen_window, SCREEN_PROPERTY_IDLE_MODE, &idle_mode) != 0) {
		throw exception(EXIT_FAILURE);
	}
}

void Player::destroyScreen()
{
	if (screen_destroy_window(screen_window) != 0) {
		throw exception(EXIT_FAILURE);
	}

	if (screen_destroy_context(screen_context) != 0) {
		throw exception(EXIT_FAILURE);
	}
}

//Use exceptions mechanism

void Player::runPlayer(const QString& fileName)
{
	createWindow();
	connectToMMR();
	configureAudioVideo();
	makeWindowVisible();
	startPlayback(fileName);
	screen_request_events(screen_context);
	navigator_request_events(0);
	handleKeyboardEvents();
	screen_stop_events(screen_context);
	detachFromMMR();
	destroyScreen();
}

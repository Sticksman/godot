/**************************************************************************/
/*  test_audio_stream_interactive.h                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef TEST_AUDIO_STREAM_INTERACTIVE_H
#define TEST_AUDIO_STREAM_INTERACTIVE_H

#include "../../servers/audio/audio_stream.h"
#include "../audio_stream_interactive.h"
#include "tests/test_macros.h"

namespace TestAudioStreamInteractive {

TEST_CASE("[Audio][AudioStreamInteractive] Getters and setters") {
	Ref<AudioStreamInteractive> stream = memnew(AudioStreamInteractive);

	stream->set_clip_count(2);
	CHECK(stream->get_clip_count() == 2);

	stream->set_initial_clip(1);
	CHECK(stream->get_initial_clip() == 1);

	stream->set_clip_name(0, StringName("Foo"));
	CHECK(stream->get_clip_name(0) == StringName("Foo"));

	stream->set_clip_auto_advance(0, AudioStreamInteractive::AUTO_ADVANCE_ENABLED);
	CHECK(stream->get_clip_auto_advance(0) == AudioStreamInteractive::AUTO_ADVANCE_ENABLED);

	Ref<AudioStream> a = memnew(AudioStream);
	stream->set_clip_stream(1, a);
	CHECK(stream->get_clip_stream(1) == a);

	CHECK(stream->get_stream_name() == "Transitioner");
}

TEST_CASE("[Audio][AudioStreamInteractive] Test transition") {
	Ref<AudioStreamInteractive> stream = memnew(AudioStreamInteractive);

	stream->set_clip_count(3);
	stream->set_initial_clip(0);

	stream->add_transition(
			0, 1,
			AudioStreamInteractive::TRANSITION_FROM_TIME_IMMEDIATE,
			AudioStreamInteractive::TRANSITION_TO_TIME_START,
			AudioStreamInteractive::FADE_CROSS,
			2.0);
	CHECK(stream->has_transition(0, 1) == true);
	CHECK(stream->has_transition(1, 2) == false);

	CHECK(stream->get_transition_from_time(0, 1) == AudioStreamInteractive::TRANSITION_FROM_TIME_IMMEDIATE);
	CHECK(stream->get_transition_to_time(0, 1) == AudioStreamInteractive::TRANSITION_TO_TIME_START);
	CHECK(stream->get_transition_fade_mode(0, 1) == AudioStreamInteractive::FADE_CROSS);
	CHECK(stream->get_transition_fade_beats(0, 1) == 2.0);
	CHECK(stream->is_transition_using_filler_clip(0, 1) == false);
	CHECK(stream->get_transition_filler_clip(0, 1) == -1);
	CHECK(stream->is_transition_holding_previous(0, 1) == false);

	stream->erase_transition(0, 1);
	CHECK(stream->has_transition(0, 1) == false);
	CHECK(stream->has_transition(1, 2) == false);
}

} // namespace TestAudioStreamInteractive

namespace TestAudioStreamPlaybackInteractive {

TEST_CASE("[Audio][AudioStreamPlaybackInteractive] Start and Stop") {
	Ref<AudioStreamInteractive> stream = memnew(AudioStreamInteractive);
	stream->set_clip_count(1);
	CHECK(stream->get_clip_count() == 1);

	Ref<AudioStream> a = memnew(AudioStream);
	stream->set_clip_stream(0, a);

	Ref<AudioStreamPlaybackInteractive> playback = stream->instantiate_playback();
	/* TODO: Figure out how to get the audio stream to return true here
	 * Unclear if an actual audiostream is needed to get start and stop to work
	playback->start();
	CHECK(playback->is_playing() == true);
	playback->stop();
	CHECK(playback->is_playing() == false);
	*/
}

} // namespace TestAudioStreamPlaybackInteractive

#endif // TEST_AUDIO_STREAM_INTERACTIVE_H

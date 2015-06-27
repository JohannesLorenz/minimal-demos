/*************************************************************************/
/* demo.cpp - a small demo song for minimal                              */
/* Copyright (C) 2014-2015                                               */
/* Johannes Lorenz (jlsf2013 @ sourceforge)                              */
/*                                                                       */
/* This program is free software; you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation; either version 3 of the License, or (at */
/* your option) any later version.                                       */
/* This program is distributed in the hope that it will be useful, but   */
/* WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU      */
/* General Public License for more details.                              */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program; if not, write to the Free Software           */
/* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA  */
/*************************************************************************/

#include <minimal/minimal.h> // TODO: rename!! minimal-zynaddsubfx.h
#include <minimal/jack_player.h>
#include <minimal/project.h>
#include <minimal/lfo.h>
#include <minimal/note_line.h>
#include <minimal/audio_sink.h>

using namespace mini;
using namespace bars;

extern "C"
{

void init(project_t& p)
{
	// general
	p.set_tempo(140);
	p.set_title("demo-song");

	// instruments
	// TODO: disallow "zynaddsubfx sine_base ...."
	zyn_tree_t& sine_bass = p.emplace<zynaddsubfx_t>("sine bass");
	audio_sink_t& sink = p.add_sink();

	//sine_bass.add_param_fixed("/bla", 1, std::string("zwei"));

//	sine_bass.add_command_fixed<zynaddsubfx_t::note_on<>>(0, 42, 10);


/*	// tracks
	track_t& track1 = p.add_track(sine_bass);
	//t.add_timeline(~~)
	track1.add_line(1,1, line_t(1,2,3));
//	p.add_track(track1);
	//t.set_param_fixed("", 3); // TODO: instrument*/

	using namespace daw;

	notes_t maj(note_geom_t(0_1, 0));
	maj.add_note(note_t(), note_geom_t(0_1, 0));
	maj.add_note(note_t(), note_geom_t(1_3, 1));
	maj.add_note(note_t(), note_geom_t(2_3, 2));

	// 8 major chords
	note_line_t& nl = p.emplace<note_line_t>();
	nl.add_notes(maj, note_geom_t(0_1, 62));
	nl.add_notes(maj, note_geom_t(1_1, 63));
	nl.add_notes(maj, note_geom_t(2_1, 64));
	nl.add_notes(maj, note_geom_t(3_1, 65));
	nl.add_notes(maj, note_geom_t(4_1, 66));
	nl.add_notes(maj, note_geom_t(5_1, 67));
	nl.add_notes(maj, note_geom_t(6_1, 68));
	nl.add_notes(maj, note_geom_t(7_1, 69));

//	lfo_t<int>& lfo_startup = p.emplace<lfo_t<int>>(0.0, 64.0, 100_1, 100_1, 0.5); // 1x 0 -> 64.0
	lfo_t<int>& lfo_leftright = p.emplace<lfo_t<int>>(-64.0, 64.0, 0_1, 8_1, 8.); // 4x from 0 to 8
	lfo_t<int>& lfo_volume = p.emplace<lfo_t<int>>(20, 80.0, 0_1, 8_1); // 1x 20 -> 80
	
//	lfo_t<int>& constant_0 = p.emplace<lfo_t<int>>(0.0, 0.0, 100_1, 100_1, 1.0f, 0.0f);
	lfo_t<int>& constant_1 = p.emplace<lfo_t<int>>(0.0, 0.0, 100_1, 100_1, 1.0f, 1.0f); // TODO: 100_1
	lfo_t<int>& constant_m2 = p.emplace<lfo_t<int>>(0.0, 0.0, 100_1, 100_1, 1.0f, -2.0f);

//	in_port<int> ip(sine_bass);
//	ip.connect(m_lfo->out);

	//zyn::p_envsustain<in_port_templ<int>>* envsustain = sine_bass.add0().global().amp_env().envsustain<in_port_templ<int>>(); // todo: need discretizer
	auto& volume = sine_bass.volume<in_port_templ<int>>();
	auto& panning = sine_bass.part0().Ppanning<in_port_templ<int>>();
	auto& ins_fx_i = sine_bass.insefx<>().efftype<in_port_templ<int>>();
		//sine_bass.part<0>().partefx<0>().efftype<in_port_templ<int>>();
	auto& ins_fx_part = sine_bass.part<0>().partefx<0>().eff0_part_id<in_port_templ<int>>();

	// effect connections
//	volume.cmd_ptr->port_at<0>() << _constant<int, 0>();
	
	// TODO: make cast if port_at is obvious (e.g. only 1 port)
	volume.cmd_ptr->port_at<0>() << lfo_volume;
	panning.cmd_ptr->port_at<0>() << lfo_leftright; //constant_0;
	ins_fx_part.cmd_ptr->port_at<0>() << constant_m2; // -2 is global
	ins_fx_i.cmd_ptr->port_at<0>() << constant_1;

	sine_bass.note_input() << nl;

	sine_bass.print_all_used(no_rt::mlog);

	sink << sine_bass;

	// PEnable
	// "part0/kit0/adpars/voice0/AmpEnvelope/Penvsustain:i"

/*	const auto ftor = [](int c) { return c % 100 + 50; };
	func<decltype(ftor), p_char, int> f(ftor);
	zynaddsubfx_t::note_on cmd(f, 2, 3);*/
}

}


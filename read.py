#!/usr/bin/env python

from mido import MidiFile


def midi_to_notes(midi_file_path):
    """
    Reads a MIDI file and produces a list of note events.

    Args:
        midi_file_path (str): The path to the MIDI file.

    Returns:
        list: A list of Note events in the format:
              [Note(offset, duration, octave, pitch), ...]
              Offset and duration are in beats, pitch is 0-11.
    """
    mid = MidiFile(midi_file_path)
    notes = []
    current_time_ticks = 0
    tempo = 120  # Default tempo in BPM
    ticks_per_beat = mid.ticks_per_beat

    for track in mid.tracks:
        note_on_events = {}

        for msg in track:
            current_time_ticks += msg.time

            if msg.type == 'set_tempo':
                tempo = 60000000 / msg.tempo
            elif msg.type == 'note_on':
                if msg.velocity > 0:
                    note_on_events[msg.note] = current_time_ticks
                else:
                    if msg.note in note_on_events:
                        start_time_ticks = note_on_events.pop(msg.note)
                        duration_ticks = current_time_ticks - start_time_ticks
                        duration_beats = duration_ticks / ticks_per_beat
                        octave = msg.note // 12
                        pitch = msg.note % 12
                        notes.append(Note(start_time_ticks / ticks_per_beat, duration_beats, octave, pitch))
            elif msg.type == 'note_off':
                if msg.note in note_on_events:
                    start_time_ticks = note_on_events.pop(msg.note)
                    duration_ticks = current_time_ticks - start_time_ticks
                    duration_beats = duration_ticks / ticks_per_beat
                    octave = msg.note // 12
                    pitch = msg.note % 12
                    notes.append(Note(start_time_ticks / ticks_per_beat, duration_beats, octave, pitch))

    # Sort notes by offset
    notes.sort(key=lambda note: note.offset)

    # Shift offsets to start from 0
    if notes:
        first_offset = notes[0].offset
        for note in notes:
            note.offset -= first_offset
            note.octave -= 2

    return notes


class Note:
    def __init__(self, offset, duration, octave, pitch):
        self.offset = offset
        self.duration = duration
        self.octave = octave
        self.pitch = pitch

    def __repr__(self):
        return f"Note({self.offset:.2f}, {self.duration:.2f}, {self.octave}, {self.pitch})"


if __name__ == '__main__':
    note_list = midi_to_notes('251meng.mid')
    for note in note_list:
        print(note)

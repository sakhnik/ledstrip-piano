#include "Player.h"
#include "Mapping.h"
#include "Adafruit_NeoPixel.h"
#include "Defs.h"
#include <Adafruit_NeoPixel.h>

#define PIN        2      // GPIO to which the strip is connected
#define NUM_LEDS   144     // Number of LEDs in the strip

Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
int update_count = 0;

Player::Player(Piece &piece, Mapping &mapping)
    : piece{piece}
    , mapping{mapping}
    , events{piece.GetEvents()}
    , events_count{piece.GetEventsCount()}
{
}

void Player::Setup()
{
    strip.begin();

    strip.clear();
    strip.show();
    Reset();
}

void Player::Tick()
{
    timer.tick();
    if (update_count > 0 && strip.canShow()) {
        strip.show();
        update_count = 0;
    }
}

void Player::NextEvent()
{
    for (; cur_idx < events_count; ++cur_idx) {
        const auto &event = events[cur_idx];
        switch (event.type) {
        case EventType::Bar:
            base += event.duration;
            base_millis += event.duration * mspb;
            break;
        case EventType::Note: {
            auto task = timer.at(
                base_millis + event.offset * mspb,
                [](void *ctx) {
                    reinterpret_cast<Player *>(ctx)->ProcessNow();
                    return false;
                },
                this
            );
            if (!task) {
                printf("Note on timer failure\n");
            }
            return;
            }
        }
    }
    if (cur_idx >= events_count) {
        Reset();
    }
}

void Player::Reset()
{
    base_millis = millis() + 5000;
    base = 0.f;
    cur_idx = 0;
    NextEvent();
}

void Player::ProcessNow()
{
    float offset = events[cur_idx].offset;
    for (; cur_idx < events_count; ++cur_idx) {
        const auto &event = events[cur_idx];
        if (event.type != EventType::Note) {
            NextEvent();
            break;
        }
        if (offset >= event.offset) {
            NoteOn(event);
        } else {
            NextEvent();
            break;
        }
    }
    if (cur_idx >= events_count) {
        Reset();
    }
}

void Player::NoteOn(const Event &event)
{
    auto rgba = mapping.GetColor(event.pitch);
    uint32_t color = strip.Color(rgba.r, rgba.g, rgba.b, rgba.w);
    auto pos = mapping.GetPosition(event.octave, event.pitch);

    if (pos != Mapping::NO_POS) {
        strip.setPixelColor(pos, color);
        ++update_count;
        auto task = timer.at(
            base_millis + (event.offset + event.duration) * mspb,
            [](void *ctx) {
                uint16_t pos = static_cast<uint16_t>(reinterpret_cast<intptr_t>(ctx));
                strip.setPixelColor(pos, 0);
                ++update_count;
                return false;
            },
            reinterpret_cast<void *>(static_cast<intptr_t>(pos))
        );
        if (!task) {
            printf("Note off timer failure\n");
        }
    }
}

/*
 * Copyright (c) 2022, Andreas Kling <andreas@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "TimerSerenity.h"
#include <LibCore/Timer.h>
#include <LibJS/Heap/Heap.h>
#include <LibJS/Heap/HeapFunction.h>

namespace Web::Platform {

JS::NonnullGCPtr<TimerSerenity> TimerSerenity::create(JS::Heap& heap)
{
    return heap.allocate_without_realm<TimerSerenity>();
}

TimerSerenity::TimerSerenity()
    : m_timer(Core::Timer::try_create().release_value_but_fixme_should_propagate_errors())
{
    m_timer->on_timeout = [this] {
        if (on_timeout)
            on_timeout->function()();
    };
}

TimerSerenity::~TimerSerenity() = default;

void TimerSerenity::start()
{
    m_timer->start();
}

void TimerSerenity::start(int interval_ms)
{
    m_timer->start(interval_ms);
}

void TimerSerenity::restart()
{
    m_timer->restart();
}

void TimerSerenity::restart(int interval_ms)
{
    m_timer->restart(interval_ms);
}

void TimerSerenity::stop()
{
    m_timer->stop();
}

void TimerSerenity::set_active(bool active)
{
    m_timer->set_active(active);
}

bool TimerSerenity::is_active() const
{
    return m_timer->is_active();
}

int TimerSerenity::interval() const
{
    return m_timer->interval();
}

void TimerSerenity::set_interval(int interval_ms)
{
    m_timer->set_interval(interval_ms);
}

bool TimerSerenity::is_single_shot() const
{
    return m_timer->is_single_shot();
}

void TimerSerenity::set_single_shot(bool single_shot)
{
    m_timer->set_single_shot(single_shot);
}

}

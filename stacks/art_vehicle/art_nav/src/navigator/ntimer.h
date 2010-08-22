/*
 *  Description:  Navigator driver timer class
 *
 *  Copyright Austin Robot Technology                    
 *  All Rights Reserved. Licensed Software.
 *
 *  This is unpublished proprietary source code of Austin Robot
 *  Technology, Inc.  The copyright notice above does not evidence any
 *  actual or intended publication of such source code.
 *
 *  PROPRIETARY INFORMATION, PROPERTY OF AUSTIN ROBOT TECHNOLOGY
 *
 *  $Id$
 */

#ifndef _NAV_TIMER_HH_
#define _NAV_TIMER_HH_

#include <sys/time.h>
#include <time.h>

#include <libplayercore/player.h>

#include <art/cycle.h>

/** @brief Navigator driver timer class.
 *
 *  This class is intended for drivers.  Rather than system time, it
 *  uses the ART Cycle class, which simulates time when running in
 *  Stage.
 */
class NavTimer
{
 public:

  /** @brief Constructor */
  NavTimer(Cycle *_cycle)
    {
      cycle = _cycle;
      this->Cancel();
    };

  virtual ~NavTimer() {};

  /** @brief Cancel timer. */
  virtual void Cancel(void)
  {
    timer_running = false;
  }

  /** @brief Return true if timer has expired.
   *
   *  Called once per cycle while timer is running.  Skipped cycles do
   *  not contribute to timer expiration.  That allows timers to pause
   *  while the vehicle is pausing.  It should not immediately begin
   *  passing after pausing behind a stopped vehicle, for example.
   */
  virtual bool Check(void)
  {
    if (!timer_running)
      return false;			// timer not set

    // decrement time remaining by the duration of one cycle
    time_remaining -= (1.0 / cycle->Frequency());
    return (time_remaining <= 0.0);
  }

  /** @brief Restart timer.
   *
   *  Conditionally start timer unless running and not expired.
   */
  virtual void Restart(double duration)
  {
    if (timer_running && time_remaining > 0.0)
      return;

    Start(duration);
  }

  /** @brief Start timer. */
  virtual void Start(double duration)
  {
    timer_running = true;
    time_remaining = duration;
  }

 protected:

  Cycle *cycle;				//< driver cycle class
  double time_remaining;		//< time remaining until done
  bool timer_running;			//< true when timer running
};

#endif // _NAV_TIMER_HH_